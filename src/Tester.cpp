#include <Tester.h>

void Tester::run()
{
    for (const auto &[fname, pc] : fname_passing_pc) {
        VEmu em = VEmu {fname};
        em.set_pass_pc(pc);
        em.run();
    }
}

const std::map<std::string, uint64_t> Tester::fname_passing_pc = {
    {"../tests/bins/rv64ua_p_amoadd_d",   0x800001a8},
    {"../tests/bins/rv64ua_p_amoadd_w",   0x8000019c},
    {"../tests/bins/rv64ua_p_amoand_d",   0x8000019c},
    {"../tests/bins/rv64ua_p_amoand_w",   0x80000198},
    {"../tests/bins/rv64ua_p_amomax_d",   0x80000198},
    {"../tests/bins/rv64ua_p_amomaxu_d",  0x80000198},
    {"../tests/bins/rv64ua_p_amomaxu_w",  0x80000198},
    {"../tests/bins/rv64ua_p_amomax_w",   0x80000198},
    {"../tests/bins/rv64ua_p_amomin_d",   0x80000198},
    {"../tests/bins/rv64ua_p_amominu_d",  0x80000198},
    {"../tests/bins/rv64ua_p_amominu_w",  0x80000198},
    {"../tests/bins/rv64ua_p_amomin_w",   0x80000198},
    {"../tests/bins/rv64ua_p_amoor_d",    0x80000194},
    {"../tests/bins/rv64ua_p_amoor_w",    0x80000194},
    {"../tests/bins/rv64ua_p_amoswap_d",  0x8000019c},
    {"../tests/bins/rv64ua_p_amoswap_w",  0x80000198},
    {"../tests/bins/rv64ua_p_amoxor_d",   0x800001a0},
    {"../tests/bins/rv64ua_p_amoxor_w",   0x800001a8},
    {"../tests/bins/rv64ui_p_add",        0x8000062c},
    {"../tests/bins/rv64ui_p_addi",       0x800003cc},
    {"../tests/bins/rv64ui_p_addiw",      0x800003c0},
    {"../tests/bins/rv64ui_p_addw",       0x80000618},
    {"../tests/bins/rv64ui_p_auipc",      0x80000180},
    {"../tests/bins/rv64ui_p_bgeu",       0x80000530},
    {"../tests/bins/rv64ui_p_blt",        0x800003f8},
    {"../tests/bins/rv64ui_p_bltu",       0x800004c0},
    {"../tests/bins/rv64ui_p_bne",        0x800003fc},
    {"../tests/bins/rv64ui_p_fence_i",    0x80000204},
    {"../tests/bins/rv64ui_p_jal",        0x8000018c},
    {"../tests/bins/rv64ui_p_jalr",       0x8000020c},
    {"../tests/bins/rv64ui_p_lb",         0x80000384},
    {"../tests/bins/rv64ui_p_lbu",        0x80000384},
    {"../tests/bins/rv64ui_p_ld",         0x80000504},
    {"../tests/bins/rv64ui_p_lh",         0x800003a4},
    {"../tests/bins/rv64ui_p_lui",        0x80000198},
    {"../tests/bins/rv64ui_p_lw",         0x800003c4},
    {"../tests/bins/rv64ui_p_lwu",        0x8000040c},
    {"../tests/bins/rv64ui_p_sb",         0x8000052c},
    {"../tests/bins/rv64ui_p_sd",         0x8000077c},
    {"../tests/bins/rv64ui_p_sh",         0x800005b0},
    {"../tests/bins/rv64ui_p_sll",        0x80000744},
    {"../tests/bins/rv64ui_p_slli",       0x80000430},
    {"../tests/bins/rv64ui_p_slliw",      0x8000044c},
    {"../tests/bins/rv64ui_p_sllw",       0x80000744},
    {"../tests/bins/rv64ui_p_slt",        0x80000600},
    {"../tests/bins/rv64ui_p_slti",       0x800003ac},
    {"../tests/bins/rv64ui_p_sltiu",      0x800003ac},
    {"../tests/bins/rv64ui_p_sltu",       0x80000644},
    {"../tests/bins/rv64ui_p_sraiw",      0x800004b0},
    {"../tests/bins/rv64ui_p_sraw",       0x80000774},
    {"../tests/bins/rv64ui_p_srli",       0x80000434},
    {"../tests/bins/rv64ui_p_srliw",      0x80000468},
    {"../tests/bins/rv64ui_p_srlw",       0x8000075c},
    {"../tests/bins/rv64ui_p_subw",       0x800005f8},
    {"../tests/bins/rv64ui_p_sw",         0x800005bc},
    {"../tests/bins/rv64ui_p_xor",        0x80000700},
    {"../tests/bins/rv64ui_p_xori",       0x8000031c},
    {"../tests/bins/rv64um_p_div",        0x80000228},
    {"../tests/bins/rv64um_p_divu",       0x80000240},
    {"../tests/bins/rv64um_p_divuw",      0x80000220},
    {"../tests/bins/rv64um_p_divw",       0x80000214},
    {"../tests/bins/rv64um_p_mul",        0x80000604},
    {"../tests/bins/rv64um_p_mulh",       0x800005ac},
    {"../tests/bins/rv64um_p_mulhsu",     0x800005ac},
    {"../tests/bins/rv64um_p_mulhu",      0x8000062c},
    {"../tests/bins/rv64um_p_mulw",       0x80000510},
    {"../tests/bins/rv64um_p_rem",        0x80000224},
    {"../tests/bins/rv64um_p_remu",       0x80000228},
    {"../tests/bins/rv64um_p_remuw",      0x80000214},
    {"../tests/bins/rv64um_p_remw",       0x8000022c},
};
