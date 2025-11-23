#include "CPU/CPU.hpp"
#include <iostream>

namespace CPU {
    void CPU::reset() {
        Bit16 falseArr = {};

        halted = false;
        zf = false;
        pc.update(falseArr, true, false);
        pc.update(falseArr, true, true);
    }

    void CPU::loadProgram(const std::vector<Bit16>& program) {
        for(size_t i = 0; i < program.size(); ++i) {
            Bit16 addr = utils::IntToBit16(i);
            Bit16 data = program[i];
            mem.write(addr, data, true, false);
            mem.write(addr, data, true, true);
        }
    }

    bool CPU::isHalted() {
        return halted;
    }

    Bit16 CPU::getPC() const {
        return pc.read();
    }

    Bit16 CPU::readRegister(size_t index) const {
        Bit3 trans = utils::IntToBit3(index);
        Bit3 dummy = {};
        sequential::RegisterFile::RegisterFileResult result = rf.read(trans, dummy);
        return result.data1;
    }

    Bit16 CPU::readMemory(const Bit16& addr) const {
        return mem.read(addr);
    }

    void CPU::clock() {
        bool active = gate::NOT(halted);
        Bit16 currPC = pc.read();
        Bit16 readedInst = mem.read(currPC);
        std::cout << "Read instruction at PC=" << utils::BitToInt<16>(currPC) 
          << ": 0x" << std::hex << utils::BitToInt<16>(readedInst) << std::dec
          << std::endl;
        cu.loadInst(readedInst, false);
        cu.loadInst(readedInst, true);
        auto decodedInst = cu.getDecodedInst();
        auto controlSingal = cu.getControlSignal();
        auto readReg = rf.read(decodedInst.src1, decodedInst.src2);

        Bit3 zero_addr = {};
        auto destReg = rf.read(decodedInst.dest, zero_addr);

        Bit16 imm = {};
        for(size_t i = 0; i < BIT6; ++i) {
            imm[i] = decodedInst.immediate[i]; 
        }

        bool sign_bit = decodedInst.immediate[5];
        for(size_t i = BIT6; i < BIT16; ++i) {
            imm[i] = sign_bit;
        }

        bool is_halt = gate::AND(gate::AND(decodedInst.opcode[3], decodedInst.opcode[2]), gate::AND(decodedInst.opcode[1], decodedInst.opcode[0]));
        halted = gate::OR(halted, gate::AND(active, is_halt));
        Bit16 alu_in2 = selector::MUX(readReg.data2, imm, controlSingal.use_immediate);
        auto alu_result = ALU::ALU(readReg.data1, alu_in2, controlSingal.alu_opcode);
        bool new_zf = gate::OR(gate::AND(gate::NOT(controlSingal.reg_write_enable), zf), gate::AND(controlSingal.reg_write_enable, alu_result.zf));
        zf = new_zf;
        Bit16 addr_base = selector::MUX(readReg.data1, destReg.data1, controlSingal.mem_write);
        Bit16 mem_addr = adder::RippleCarryAdder(addr_base, imm).sum;
        Bit16 mem_data = mem.read(mem_addr);
        bool write_enable = gate::AND(active, controlSingal.mem_write);
        mem.write(mem_addr, readReg.data1, write_enable, false);
        mem.write(mem_addr, readReg.data1, write_enable, true);
        Bit16 write_data = selector::MUX(alu_result.result, mem_data, controlSingal.mem_read);
        bool reg_write_enable = gate::AND(active, controlSingal.reg_write_enable);

        rf.write(decodedInst.dest , write_data, reg_write_enable, false);
        rf.write(decodedInst.dest , write_data, reg_write_enable, true);
        bool branch_condition = gate::OR(gate::AND(controlSingal.is_jz, zf), gate::AND(controlSingal.is_jnz, gate::NOT(zf)));
        bool should_jmp = gate::OR(controlSingal.is_jump, branch_condition);
        
        Bit16 jmp_addr = {};
        for(size_t i = 0; i < BIT12; ++i) {
            jmp_addr[i] = decodedInst.address[i];
        }

        Bit16 next_pc = adder::Incrementor(currPC).sum;
        Bit16 new_pc = selector::MUX(next_pc, jmp_addr, should_jmp);
 
        pc.update(new_pc, true, false);
        pc.update(new_pc, true, true);
    }

    void CPU::loadProgramFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::string line;
        std::vector<Bit16> program;

        while(std::getline(file, line)) {
            if(line.empty()) {
                continue;
            }

            int value = std::stoi(line, nullptr, 16);
            Bit16 inst = utils::IntToBit16(value);

            program.push_back(inst);
        }

        file.close();
        loadProgram(program);
    }
}