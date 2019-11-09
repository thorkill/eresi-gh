/**
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
  <i386 func="i386_jns" opcode="0x89"/>
*/

int i386_jns(asm_instr *new, u_char *opcode, u_int len, asm_processor *proc)
{
  new->type = ASM_TYPE_BRANCH | ASM_TYPE_CONDCONTROL;
  new->instr = ASM_BRANCH_NOT_SIGNED;
  new->len += 1;

#if LIBASM_USE_OPERAND_VECTOR
  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_JUMP, new);
#else
  new->op[0].content = ASM_CONTENT_JUMP;
  new->op[0].type = ASM_OPTYPE_MEM;
  new->op[0].memtype = ASM_OP_VALUE | ASM_OP_ADDRESS;
  new->op[0].ptr = opcode + 1;
  new->op[0].len = 4;
  memcpy(&new->op[0].imm, opcode + 1, 4);
  new->len += 4;
#endif

  return (new->len);
}
