/**
 * @file libasm/src/arch/ia32/operand_handlers/asm_operand_fetch_immediateword.c
 *
 * @ingroup IA32_operands
 */

#include <libasm.h>
#include <libasm-int.h>

/**
 * Decode data for operand type ASM_CONTENT_YDEST
 * @ingroup operand_handler
 * @param operand Pointer to operand structure to fill.
 * @param opcode Pointer to operand data
 * @param otype
 * @param ins Pointer to instruction structure.
 * @return Operand length
 */

int     asm_operand_fetch_immediateword(asm_operand *operand, u_char *opcode,
                                        int otype, asm_instr *ins)
{
  operand->content = ASM_CONTENT_IMMEDIATE;
  operand->type = ASM_OPTYPE_IMM;
  operand->ptr = opcode;
  operand->imm = 0;
  operand->len = 2;
  memcpy(&operand->imm, opcode, 2);
  return (2);
}
