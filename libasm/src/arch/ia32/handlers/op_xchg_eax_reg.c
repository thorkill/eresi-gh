/**
 * @file libasm/src/arch/ia32/handlers/op_xchg_eax_reg.c
 *
 * @ingroup IA32_instrs
 * @brief Handler for instruction xchg eax,reg opcode 0x91 to 0x97
*/
#include <libasm.h>
#include <libasm-int.h>

/**
 * @brief Handler for instruction xchg eax,reg opcode 0x91 to 0x97
 * @param instr Pointer to instruction structure.
 * @param opcode Pointer to data to disassemble.
 * @param len Length of data to disassemble.
 * @param proc Pointer to processor structure.
 * @return Length of instruction.
 */

int op_xchg_eax_reg(asm_instr *new, u_char *opcode, u_int len,
                    asm_processor *proc)
{
  new->instr = ASM_XCHG;
  new->ptr_instr = opcode;
  new->len += 1;
  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_FIXED, new);
  new->op[0].type = ASM_OPTYPE_REG;
  new->op[0].len = 0;
  new->op[0].baser = ASM_REG_EAX;
  new->op[0].regset = asm_proc_opsize(proc) ? ASM_REGSET_R16 : ASM_REGSET_R32;
  new->len += asm_operand_fetch(&new->op[1], opcode, ASM_CONTENT_OPMOD, new);
  return (new->len);
}
