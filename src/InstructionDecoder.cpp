#include <cstring>
#include "../include/InstructionDecoder.h"

InstructionDecoder &InstructionDecoder::the() {
    static InstructionDecoder inst;
    return inst;
}

Instruction InstructionDecoder::decode(const uint32_t inst) {
    auto t = instr_type(inst);
    switch (t) {
        case Instruction::Type::R:
            return decode_r(inst);
        case Instruction::Type::I:
            return decode_i(inst);
        case Instruction::Type::S:
            return decode_s(inst);
        case Instruction::Type::B:
            return decode_b(inst);
        case Instruction::Type::U:
            return decode_u(inst);
        case Instruction::Type::J:
            return decode_j(inst);
        case Instruction::Type::WRONG: default:
            return Instruction(t, IName::XXX, Fields{});
    }
}

std::map<IName, uint8_t> InstructionDecoder::i_opcodes = {
        {IName::LB,    0b0000011},
        {IName::LBU,   0b0000011},
        {IName::LH,    0b0000011},
        {IName::LHU,   0b0000011},
        {IName::LW,    0b0000011},
        {IName::ADDI,  0b0010011},
        {IName::SLTI,  0b0010011},
        {IName::SLTIU, 0b0010011},
        {IName::XORI,  0b0010011},
        {IName::ORI,   0b0010011},
        {IName::ANDI,  0b0010011},
        {IName::SLLI,  0b0010011},
        {IName::SRLI,  0b0010011},
        {IName::SRAI,  0b0010011},
        {IName::JALR,  0b1100111},
};

std::map<IName, uint8_t> InstructionDecoder::r_opcodes = {
        {IName::ADD,  0b0110011},
        {IName::SUB,  0b0110011},
        {IName::SLL,  0b0110011},
        {IName::SLT,  0b0110011},
        {IName::SLTU, 0b0110011},
        {IName::XOR,  0b0110011},
        {IName::SRL,  0b0110011},
        {IName::SRA,  0b0110011},
        {IName::OR,   0b0110011},
        {IName::AND,  0b0110011},
};
std::map<IName, uint8_t> InstructionDecoder::b_opcodes = {
        {IName::BEQ,  0b1100011},
        {IName::BNE,  0b1100011},
        {IName::BLT,  0b1100011},
        {IName::BGE,  0b1100011},
        {IName::BLTU, 0b1100011},
        {IName::BGEU, 0b1100011},
};

std::map<IName, uint8_t> InstructionDecoder::s_opcodes = {
        {IName::SB, 0b0100011},
        {IName::SH, 0b0100011},
        {IName::SW, 0b0100011},
};

std::map<IName, uint8_t> InstructionDecoder::j_opcodes = {
        {IName::JAL, 0b1101111},
};

std::map<IName, uint8_t> InstructionDecoder::u_opcodes = {
        {IName::LUI,   0b0110111},
        {IName::AUIPC, 0b0010111},
};

const std::map<IName, uint8_t> InstructionDecoder::i_funct3{
        {IName::LB,    0b000},
        {IName::LH,    0b001},
        {IName::LW,    0b010},
        {IName::LBU,   0b100},
        {IName::LHU,   0b101},
        {IName::ADDI,  0b000},
        {IName::SLTI,  0b010},
        {IName::SLTIU, 0b011},
        {IName::XORI,  0b100},
        {IName::ORI,   0b110},
        {IName::ANDI,  0b111},
        {IName::SLLI,  0b001},
        {IName::SRLI,  0b101},
        {IName::SRAI,  0b101},
};

const std::map<IName, uint8_t> InstructionDecoder::r_funct3{
        {IName::ADD,  0b000},
        {IName::SUB,  0b000},
        {IName::SLL,  0b001},
        {IName::SLT,  0b010},
        {IName::SLTU, 0b011},
        {IName::XOR,  0b100},
        {IName::SRL,  0b101},
        {IName::SRA,  0b101},
        {IName::OR,   0b110},
        {IName::AND,  0b111},
};

const std::map<IName, uint8_t> InstructionDecoder::b_funct3{
        {IName::BEQ,  0b000},
        {IName::BNE,  0b001},
        {IName::BLT,  0b100},
        {IName::BGE,  0b101},
        {IName::BLTU, 0b110},
        {IName::BGEU, 0b111},
};

const std::map<IName, uint8_t> InstructionDecoder::s_funct3{
        {IName::SB, 0b000},
        {IName::SH, 0b001},
        {IName::SW, 0b010},
};

const std::map<IName, uint8_t> InstructionDecoder::r_funct7{
        {IName::ADD,  FUNCT7_PRIMARY},
        {IName::SUB,  FUNCT7_ALT},
        {IName::SLL,  FUNCT7_PRIMARY},
        {IName::SLT,  FUNCT7_PRIMARY},
        {IName::SLTU, FUNCT7_PRIMARY},
        {IName::XOR,  FUNCT7_PRIMARY},
        {IName::SRL,  FUNCT7_PRIMARY},
        {IName::SRA,  FUNCT7_ALT},
        {IName::OR,   FUNCT7_PRIMARY},
        {IName::AND,  FUNCT7_PRIMARY},
};

Instruction::Type InstructionDecoder::instr_type(uint8_t op) {
    for (const auto& [k, v] : i_opcodes) {
        if (op == v) return Instruction::Type::I;
    }

    for (const auto& [k, v] : j_opcodes) {
        if (op == v) return Instruction::Type::J;
    }

    for (const auto& [k, v] : s_opcodes) {
        if (op == v) return Instruction::Type::S;
    }

    for (const auto& [k, v] : b_opcodes) {
        if (op == v) return Instruction::Type::B;
    }

    for (const auto& [k, v] : r_opcodes) {
        if (op == v) return Instruction::Type::R;
    }

    for (const auto& [k, v] : u_opcodes) {
        if (op == v) return Instruction::Type::U;
    }

    return Instruction::Type::WRONG;
}

Instruction::Type InstructionDecoder::instr_type(uint32_t inst) {
    uint8_t op = extract_opcode(inst);
    return instr_type(op);
}

Fields InstructionDecoder::get_fields(uint32_t inst) {
    uint8_t funct3 = extract_funct3(inst);
    uint8_t funct7 = extract_funct7(inst);
    uint8_t op = extract_opcode(inst);
    uint8_t rd = extract_rd(inst);
    uint8_t rs1 = extract_rs1(inst);
    uint8_t rs2 = extract_rs2(inst);

    return Fields {
            .OPCode = op,
            .rd = rd,
            .funct3 = funct3,
            .rs1 = rs1,
            .rs2 = rs2,
            .funct7 = funct7,
            .imm = 0,
    };
}

uint8_t InstructionDecoder::get_opcode(IName name) {
    if (name == IName::XXX) {
        return -1;
    }
    if (r_opcodes.find(name) != r_opcodes.end())
        return r_opcodes.at(name);
    if (i_opcodes.find(name) != i_opcodes.end())
        return i_opcodes.at(name);
    if (j_opcodes.find(name) != j_opcodes.end())
        return j_opcodes.at(name);
    if (s_opcodes.find(name) != s_opcodes.end())
        return s_opcodes.at(name);
    if (b_opcodes.find(name) != b_opcodes.end())
        return b_opcodes.at(name);
    if (u_opcodes.find(name) != u_opcodes.end())
        return u_opcodes.at(name);

    return -1;
}

IName InstructionDecoder::get_iname(uint8_t op) {
    Instruction::Type t = instr_type(op);

    if (t == Instruction::Type::WRONG) {
        return IName::XXX;
    }

    if (t == Instruction::Type::I) {
        for (const auto&[k, v] : i_opcodes) {
            if (op == v) return k;
        }
        return IName::XXX;
    }
    if (t == Instruction::Type::J) {
        for (const auto&[k, v] : j_opcodes) {
            if (op == v) return k;
        }
        return IName::XXX;
    }

    if (t == Instruction::Type::S) {
        for (const auto&[k, v] : s_opcodes) {
            if (op == v) return k;
        }
        return IName::XXX;
    }

    if (t == Instruction::Type::B) {
        for (const auto&[k, v] : b_opcodes) {
            if (op == v) return k;
        }
        return IName::XXX;
    }
    if (t == Instruction::Type::R) {
        for (const auto&[k, v] : r_opcodes) {
            if (op == v) return k;
        }
        return IName::XXX;
    }

    if (t == Instruction::Type::U) {
        for (const auto&[k, v] : u_opcodes) {
            if (op == v) return k;
        }
        return IName::XXX;
    }

    return IName::XXX;
}

IName InstructionDecoder::get_iname(uint32_t inst) {
    auto op = extract_opcode(inst);
    return get_iname(op);
}

uint8_t InstructionDecoder::get_funct3(IName name) {
    auto op = get_opcode(name);
    return get_funct3(op);
}

uint8_t InstructionDecoder::get_funct3(uint32_t inst) {
    auto op = extract_opcode(inst);
    return get_funct3(op);
}

uint8_t InstructionDecoder::get_funct3(uint8_t op) {
    auto n = get_iname(op);
    auto t = instr_type(op);

    if (t == Instruction::Type::WRONG) {
        return -1;
    }

    if (t == Instruction::Type::I &&
        i_funct3.find(n) != i_funct3.end()) {
        return i_funct3.at(n);
    }

    if (t == Instruction::Type::S &&
        s_funct3.find(n) != s_funct3.end()) {
        return s_funct3.at(n);
    }

    if (t == Instruction::Type::B &&
        b_funct3.find(n) != b_funct3.end()) {
        return b_funct3.at(n);
    }

    if (t == Instruction::Type::R &&
        r_funct3.find(n) != b_funct3.end()) {
        return r_funct3.at(n);
    }

    return -1;
}

uint8_t InstructionDecoder::get_funct7(IName name) {
    auto op = get_opcode(name);
    return get_funct7(op);
}

uint8_t InstructionDecoder::get_funct7(uint32_t inst) {
    auto op = extract_opcode(inst);
    return get_funct7(op);
}

uint8_t InstructionDecoder::get_funct7(uint8_t op) {
    auto t = instr_type(op);
    auto n = get_iname(op);

    if (t != Instruction::Type::R)
        return -1;

    if (r_funct7.find(n) != r_funct7.end()) {
        return r_funct7.at(n);
    }

    return -1;
}

Instruction InstructionDecoder::decode_r(uint32_t inst) {
    Fields f = get_fields(inst);
    for (auto [ins, f3] : r_funct3) {
        if (f3 == f.funct3 && r_funct7.at(ins) == f.funct7) {
            return Instruction(Instruction::Type::R, ins, f);
        }
    }
    return Instruction(Instruction::Type::WRONG, IName::XXX, f);
}

Instruction InstructionDecoder::decode_i(uint32_t) {
    return Instruction(Instruction::Type::I, IName::XXX, Fields{});
}

Instruction InstructionDecoder::decode_b(uint32_t) {
    return Instruction(Instruction::Type::B, IName::XXX, Fields{});
}

Instruction InstructionDecoder::decode_s(uint32_t) {
    return Instruction(Instruction::Type::S, IName::XXX, Fields{});
}

Instruction InstructionDecoder::decode_j(uint32_t) {
    return Instruction(Instruction::Type::J, IName::XXX, Fields{});
}

Instruction InstructionDecoder::decode_u(uint32_t) {
    return Instruction(Instruction::Type::U, IName::XXX, Fields{});
}

uint8_t InstructionDecoder::extract_opcode(uint32_t inst) {
    return inst & OPCODE_MASK;
}

uint8_t InstructionDecoder::extract_funct3(uint32_t inst) {
    return (inst & FUNCT3_MASK) >> 12U;
}

uint8_t InstructionDecoder::extract_funct7(uint32_t inst) {
    return (inst & FUNCT7_MASK) >> 25U;
}

uint8_t InstructionDecoder::extract_rd(uint32_t inst) {
    return (inst & RD_MASK) >> 7U;
}

uint8_t InstructionDecoder::extract_rs1(uint32_t inst) {
    return (inst & RS1_MASK) >> 15U;
}

uint8_t InstructionDecoder::extract_rs2(uint32_t inst) {
    return (inst & RS2_MASK) >> 20U;
}
