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

// Class provides access to particular bits of an encapsulated
// value. T is the type of the value.
//
// T meant to be something like int, it can be your custom
// class, but the class must support bit operations (<<, |, &,...)
// with propper semantics.
//
// Parameter fields shows how to split the value. Each value in the pack
// represents the size of "bit field", the first one represent the lowest
// bits and so on.
//
// For example:
// bitaccessor<uint8_t, 1, 2, 3, 2> eg(42);
//                     /  /   |   \
//                    v  v    v    v
//                   |0|1 0|1 0 1|0 0| = 42
//                    0 1 2 3 4 5 6 7
template<typename T, bitsize_t ...fields>
struct bitaccessor
{
    explicit bitaccessor(T val = 0) :
        val_(val) {}

    bitaccessor(const bitaccessor&) = default;
    bitaccessor(bitaccessor&&) = default;
    bitaccessor& operator=(const bitaccessor&) = default;
    bitaccessor& operator=(bitaccessor&&) = default;

    // get the whole value
    T get_value() { return val_; } const
    // set the whole value
    void set_value(T val) { val_ = val; }

    // get the field with the index = idx
    template<bitsize_t idx>
    T get_field() const
    {
        T tmp = val_;
        tmp = tmp >> calcOffset<idx, fields...>();
        tmp = tmp & calcMask<T, idx, fields...>();
        return tmp;
    }
    // set the field with the index = idx
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
