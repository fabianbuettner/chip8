#include "Cpu.h"

std::ostream& operator<<(std::ostream& os, const Cpu& cpu)
{
    return cpu.write(os);
}
