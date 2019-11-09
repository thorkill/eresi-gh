/**
 * @file libasm/src/arch/ia32/operand_handlers/asm_operand_fetch_jump.c
 *
 * @ingroup IA32_operands
 */

#include <libasm.h>
#include <libasm-int.h>

/**
 * Decode data for operand type ASM_CONTENT_JUMP
 * @ingroup operand_handler
 * @param operand Pointer to operand structure to fill.
 * @param opcode Pointer to operand data
 * @param otype
 * @param ins Pointer to instruction structure.
 * @return Operand length
 */

int     asm_operand_fetch_jump(asm_operand *operand, u_char *opcode,
                               int otype, asm_instr *ins)
{
  u_int len;

  operand->content = ASM_CONTENT_JUMP;
  operand->type = ASM_OPTYPE_MEM;
  operand->memtype = ASM_OP_VALUE | ASM_OP_ADDRESS;
  operand->ptr = opcode;
  operand->imm = 0;
  len = asm_proc_opsize(ins->proc) ? 2 : 4;
  operand->len = len;
  memcpy(&operand->imm, opcode, len);
  return (len);
}
