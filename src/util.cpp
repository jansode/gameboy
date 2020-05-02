#include "../include/util.h"

u16 ParseHexValue(const std::string &str)
{
    u16 value;
    std::stringstream ss;
    ss << std::hex << str;
    ss >> value;
    return value;
}
