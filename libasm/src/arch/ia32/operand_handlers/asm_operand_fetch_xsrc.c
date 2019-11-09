/**
 * @file libasm/src/arch/ia32/operand_handlers/asm_operand_fetch_xsrc.c
 *
 * @ingroup IA32_operands
 */

#include <libasm.h>
#include <libasm-int.h>

/**
 * Decode data for operand type ASM_CONTENT_XSRC
 * @param operand Pointer to operand structure to fill.
 * @param opcode Pointer to operand data
 * @param otype
 * @param ins Pointer to instruction structure.
 * @return Operand length
 */

int     asm_operand_fetch_xsrc(asm_operand *operand, u_char *opcode,
                               int otype, asm_instr *ins)
{
  operand->content = ASM_CONTENT_XSRC;
  operand->type = ASM_OPTYPE_MEM;
  operand->memtype = ASM_OP_BASE | ASM_OP_REFERENCE;
  operand->baser = ASM_REG_ESI;
  operand->regset = asm_proc_opsize(ins->proc) ? ASM_REGSET_R16 : ASM_REGSET_R32;
  operand->sbaser = get_reg_intel(operand->baser, operand->regset);
  operand->prefix = ASM_PREFIX_DS;
  return (0);
}
