/**
 * @brief Handler for instruction push cs opcode 0x0e
 *
 * @ingroup IA32_instrs
*/
#include <libasm.h>
#include <libasm-int.h>

/**
 * @brief Handler for instruction push cs opcode 0x0e
 */
int op_push_cs(asm_instr *new, u_char *opcode, u_int len,
               asm_processor *proc)
{
  new->len += 1;
  new->ptr_instr = opcode;
  new->instr = ASM_PUSH;
  new->type = ASM_TYPE_TOUCHSP | ASM_TYPE_STORE;
  new->spdiff = -4;
  new->len += asm_operand_fetch(&new->op[0], opcode, ASM_CONTENT_FIXED, new);
  new->op[0].type = ASM_OPTYPE_REG;
  new->op[0].regset = ASM_REGSET_SREG;
  new->op[0].baser = ASM_REG_CS;
  return (new->len);
}
