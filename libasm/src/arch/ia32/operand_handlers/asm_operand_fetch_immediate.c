/**
 * @file libasm/src/arch/ia32/operand_handlers/asm_operand_fetch_immediate.c
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

int     asm_operand_fetch_immediate(asm_operand *operand, u_char *opcode,
                                    int otype, asm_instr *ins)
{
  operand->content = ASM_CONTENT_IMMEDIATE;
  operand->type = ASM_OPTYPE_IMM;
  operand->ptr = opcode;
  operand->imm = 0;
  operand->len = asm_proc_opsize(ins->proc) ? 2 : 4;
  memcpy(&operand->imm, opcode, operand->len);
  return (operand->len);
}
