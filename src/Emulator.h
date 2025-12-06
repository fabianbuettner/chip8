#pragma once

#include "Machine.h"

#include <boost/asio.hpp>
#include <cstdint>

class Emulator {
private:
    std::uint32_t emulation_clock_speed;
    Machine& machine;
    boost::asio::steady_timer cpu_clock;

public:
    Emulator(boost::asio::io_context& io, Machine& machine, std::uint32_t emulation_clock_speed);
    ~Emulator(void);

private:
    void cycle(void);
};
