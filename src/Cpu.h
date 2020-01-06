#pragma once

#include <iostream>

struct Cpu {
    virtual bool cycle(void) = 0;
    virtual std::ostream& printDisassembly(std::ostream& os) = 0;
    virtual std::ostream& write(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Cpu& cpu);
};
