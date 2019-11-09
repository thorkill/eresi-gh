/**
 * @file libasm/src/arch/ia32/handlers/op_xchg_rmb_rb.c
 * @brief Handler for instruction xchg rmb,rb opcode 0x86
 *
 * @ingroup IA32_instrs
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * @brief Handler for instruction xchg rmb,rb opcode 0x86
 * @param instr Pointer to instruction structure.
 * @param opcode Pointer to data to disassemble.
 * @param len Length of data to disassemble.
 * @param proc Pointer to processor structure.
 * @return Length of instruction.
 */

int op_xchg_rmb_rb(asm_instr *instr, u_char *opcode, u_int len,
                   asm_processor *proc)
{
  instr->len += 1;
  instr->ptr_instr = opcode;
  instr->instr = ASM_XCHG;
  instr->type = ASM_TYPE_LOAD | ASM_TYPE_STORE;

  instr->len += asm_operand_fetch(&instr->op[0], opcode + 1,
                                  ASM_CONTENT_ENCODEDBYTE, instr);
  instr->len += asm_operand_fetch(&instr->op[1], opcode + 1,
                                  ASM_CONTENT_GENERALBYTE, instr);

  return (instr->len);
}
