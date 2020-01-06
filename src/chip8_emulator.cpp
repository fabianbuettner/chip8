#include "CpuChip8.h"
#include "DisplayChip8.h"
#include "Emulator.h"
#include "InputChip8.h"
#include "MachineChip8.h"
#include "MemoryChip8.h"

#include <SDL2/SDL.h>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <stdexcept>

int main(int ac, char* av[])
{
    float scale;
    std::uint32_t emulation_clock_speed; // in Hz
    std::string rom_file;
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()("emulation-clock-speed,e", boost::program_options::value<std::uint32_t>(&emulation_clock_speed)->default_value(120), "emulation clock speed")("help,h", "produce help message")("rom-file", boost::program_options::value<std::string>(&rom_file), "rom file")("scale,s", boost::program_options::value<float>(&scale)->default_value(10), "scale factor")("verbosity,v", "enables verbosity");
    boost::program_options::positional_options_description p;
    p.add("rom-file", 1);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(ac, av).options(desc).positional(p).run(), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("rom-file")) {
        std::cout << "Loading rom-file \""
                  << vm["rom-file"].as<std::string>() << "\"" << std::endl;
    } else {
        std::cout << "Please specify a rom-file to load!" << std::endl;
        return 2;
    }

    try {
        boost::asio::io_context io_context;

        MemoryChip8 memory { rom_file };
        DisplayChip8 display { "chip8_emulator", scale };
        InputChip8 input {};
        CpuChip8 cpu { memory, display, input, emulation_clock_speed };
        if (vm.count("verbosity")) {
            cpu.setVerbosity(true);
        }
        MachineChip8 machine { cpu, emulation_clock_speed };
        Emulator emu { io_context, machine, emulation_clock_speed };

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return 3;
    }

    atexit(SDL_Quit);

    return 0;
}
