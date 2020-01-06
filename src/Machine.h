#pragma once

#include <cstdint>

class Machine {
public:
    virtual bool cycle(void) = 0;
};
