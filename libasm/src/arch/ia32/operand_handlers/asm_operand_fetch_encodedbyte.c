/**
 * @file libasm/src/arch/ia32/operand_handlers/asm_operand_fetch_encodedbyte.c
 *
 * @ingroup IA32_operands
 */

#include <libasm.h>
#include <libasm-int.h>

/**
 * @ingroup operand_handler
 * Decode data for operand type ASM_CONTENT_ENCODEDBYTE
 * @param operand Pointer to operand structure to fill.
 * @param opcode Pointer to operand data
 * @param otype
 * @param ins Pointer to instruction structure.
 * @return Operand length
 */

int     asm_operand_fetch_encodedbyte(asm_operand *operand, u_char *opcode,
                                      int otype, asm_instr *ins)
{
  int len;
  operand->content = ASM_CONTENT_ENCODED;
  len = operand_rmb(operand, opcode, ins->proc);
  operand->sbaser = get_reg_intel(operand->baser, operand->regset);
  operand->sindex = get_reg_intel(operand->indexr, operand->regset);
  return (len);
}
