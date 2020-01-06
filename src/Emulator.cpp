#include "Emulator.h"

#include <boost/bind.hpp>

Emulator::Emulator(boost::asio::io_service& io, Machine& machine, std::uint32_t emulation_clock_speed)
    : machine { machine }
    , cpu_clock(io, boost::posix_time::milliseconds(1000 / emulation_clock_speed))
    , emulation_clock_speed{ emulation_clock_speed }
{
    cpu_clock.async_wait(boost::bind(&Emulator::cycle, this));
}

Emulator::~Emulator(void)
{
}

void Emulator::cycle(void)
{
    if (!machine.cycle()) {
        return;
    }

    cpu_clock.expires_at(cpu_clock.expires_at() + boost::posix_time::milliseconds(1000 / emulation_clock_speed));
    cpu_clock.async_wait(boost::bind(&Emulator::cycle, this));
}
