#include "Disassembler.h"
#include "utilities.h"

#include <iomanip>

Disassembler::Disassembler(Cpu& cpu) : cpu{cpu} {
}

Disassembler::~Disassembler(void) {
}

std::ostream& operator<<(std::ostream& os, Disassembler& disassembler) {
    os << "address\topcode\tdescription" << std::endl;
    for(std::uint32_t i = disassembler.cpu.PC; i < disassembler.cpu.program.size();) {
        std::shared_ptr<Opcode> instruction = disassembler.cpu.emitInstruction(&disassembler.cpu.program[i]);
        if(instruction) {
            os << int_to_hexstring(i, 3) << "\t" << int_to_hexstring(disassembler.cpu.opcode, 4) << "\t" << instruction->getMnemonic() << std::endl;
            i += 2;
        }
        else {
            os << int_to_hexstring(i, 3) << "\t" << int_to_hexstring(disassembler.cpu.program[i], 2) << "\t" << "not an opcode" << std::endl;
            i++;
        }
    }
    return os;
}
