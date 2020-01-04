#include "Cpu.h"
//#include "Disassembler.h"
#include "Emulator.h"

#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <stdexcept>
#include <iostream>

int main(int ac, char* av[]) {
    std::uint32_t cpu_clock_speed; // in Hz
    std::string rom_file;
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("cpu-clock-speed,c", boost::program_options::value<std::uint32_t>(&cpu_clock_speed)->default_value(120), "cpu clock speed")
        ("help,h", "produce help message")
        ("rom-file", boost::program_options::value<std::string>(&rom_file), "rom file")
        ("verbosity,v", "enables verbosity")
    ;
    boost::program_options::positional_options_description p;
    p.add("rom-file", 1);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(ac, av).
          options(desc).positional(p).run(), vm);
    boost::program_options::notify(vm);

    if(vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if(vm.count("rom-file")) {
        std::cout << "Loading rom-file \"" 
             << vm["rom-file"].as<std::string>() << "\"" << std::endl;
    }
    else {
        std::cout << "Please specify a rom-file to load!" << std::endl;
        return 2;
    }
    
    try {
        boost::asio::io_context io_context;
        Cpu cpu{rom_file, cpu_clock_speed};
        if(vm.count("verbosity")) {
            cpu.setVerbosity(true);
        }
        Emulator emu{"chip8-emulator", io_context, cpu};
        io_context.run();
        //Disassembler disassembler{cpu};
        //std::cout << disassembler << std::endl;
        //while(emu.run) {
        //    emu.cycle();
        //}
    }
    catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return 3;
    }

    return 0;
}
