#ifndef BIT_ACCESSOR
#define BIT_ACCESSOR

#include <vector>


namespace bal
{

using bitsize_t = unsigned;

template<bitsize_t idx, bitsize_t ...fields>
constexpr bitsize_t calcOffset()
{
    std::vector<bitsize_t> tmp = {fields...};
    bitsize_t offset = 0;
    for(bitsize_t i = 0; i < idx; ++i)
    {
        offset += tmp[i];
    }
    return offset;
}

template<typename T, bitsize_t idx, bitsize_t ...fields>
constexpr T calcMask()
{
    std::vector<bitsize_t> tmp = {fields...};
    T mask = (1 << tmp[idx]) - 1;
    return mask;
}

template<typename T, bitsize_t ...fields>
struct bitaccessor
{
    explicit bitaccessor(T val = 0) :
        val_(val) {}

    bitaccessor(const bitaccessor&) = default;
    bitaccessor(bitaccessor&&) = default;
    bitaccessor& operator=(const bitaccessor&) = default;
    bitaccessor& operator=(bitaccessor&&) = default;

    T get_value() { return val_; } const
    void set_value(T val) { val_ = val; }

    template<bitsize_t idx>
    T get_field() const
    {
        T tmp = val_;
        tmp = tmp >> calcOffset<idx, fields...>();
        tmp = tmp & calcMask<T, idx, fields...>();
        return tmp;
    }
    template<int idx>
    void set_field(T field_val)
    {
        assert(field_val & ~calcMask<T, idx, fields...>() == 0 &&
               "the provided value is bigger than the field");
        field_val = field_val << calcOffset<idx, fields...>();
        // let the compiler optimize it
        auto mask = calcMask<T, idx, fields...>() << calcOffset<idx, fields...>();
        val_ = val_ & ~mask;
        val_ += field_val;
    }
private:
    T val_;
}; //struct bitaccessor
}; //namespace bal
#endif
