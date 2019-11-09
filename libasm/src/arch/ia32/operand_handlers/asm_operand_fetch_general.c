/**
 * @file libasm/src/arch/ia32/operand_handlers/asm_operand_fetch_general.c
 *
 * @ingroup IA32_operands
 * @brief Operand Handler to decode data for operand type ASM_CONTENT_GENERAL
 */

#include <libasm.h>
#include <libasm-int.h>

/**
 * @brief Decode data for operand type ASM_CONTENT_GENERAL
 * @ingroup operand_handler
 * @param operand Pointer to operand structure to fill.
 * @param opcode Pointer to operand data
 * @param type Not used.
 * @param ins Pointer to instruction structure.
 * @return Operand length
 */

int     asm_operand_fetch_general(asm_operand *operand, u_char *opcode,
                                  int type, asm_instr *ins)
{
  struct s_modrm        *modrm;

  operand->content = ASM_CONTENT_GENERAL;
  operand->type = ASM_OPTYPE_REG;
  operand->regset = asm_proc_opsize(ins->proc) ? ASM_REGSET_R32 : ASM_REGSET_R16;
  modrm = (struct s_modrm *) opcode;
  operand->baser = modrm->r;
  operand->sbaser = get_reg_intel(operand->baser, operand->regset);
  operand->len = 0;
  return (0);
}
