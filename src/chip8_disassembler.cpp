#include "Cpu.h"
#include "Disassembler.h"

#include <boost/program_options.hpp>
#include <stdexcept>
#include <iostream>

int main(int ac, char* av[]) {
    std::string rom_file;
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("rom-file", boost::program_options::value<std::string>(&rom_file), "rom file")
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
        Cpu cpu{rom_file, 0};
        Disassembler disassembler{cpu};
        std::cout << disassembler << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return 3;
    }

    return 0;
}
