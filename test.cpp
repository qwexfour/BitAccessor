#include <iostream>

#include "bitaccessor.hpp"

int main()
{
    bal::bitaccessor<int, 1, 2, 3> tmp(1);
    tmp.set_value(63);
    std::cout << "value: " << tmp.get_value() << std::endl;
    std::cout << "0: " << tmp.get_field<0>() << " 1: "
              << tmp.get_field<1>() << " 2: " << tmp.get_field<2>()
              << std::endl;
    return 0;
}
