#include "utilities.h"

#include <iomanip>
#include <sstream>

std::string int_to_hexstring(std::uint32_t i, std::uint8_t number_of_leading_zeros)
{
    std::stringstream stream;
    stream << "0x" << std::hex << std::setfill('0') << std::setw(number_of_leading_zeros) << i;
    return stream.str();
}
