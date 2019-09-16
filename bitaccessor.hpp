



template<typename T, int ...fields>
struct BitAccessor
{
    explicit BitAccessor(T val = 0) :
        val_(val) {}

    BitAccessor(const BitAccessor&) = default;
    BitAccessor(BitAccessor&&) = default;
    BitAccessor& operator=(const BitAccessor&) = default;
    BitAccessor& operator=(BitAccessor&&) = default;

    T getValue() { return val_; }
    void setValue(T val) { val_ = val; }

    template<int Idx>
    T getField();
    template<int Idx>
    void setField(T val);
private:
    T val_;
};

