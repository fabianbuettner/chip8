#pragma once

#include "Machine.h"

#include <boost/asio.hpp>

class Emulator {
private:
    std::uint32_t emulation_clock_speed;
    Machine& machine;
    boost::asio::deadline_timer cpu_clock;

public:
    Emulator(boost::asio::io_service& io, Machine& machine, std::uint32_t emulation_clock_speed);
    ~Emulator(void);

private:
    void cycle(void);
};
