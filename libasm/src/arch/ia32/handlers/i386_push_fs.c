/**
*/
#include <libasm.h>
#include <libasm-int.h>

/**
  Opcode :              0x0f 0xa0
  Instruction :         PUSH
  <i386 func="i386_push_fs" opcode="0xa0"/>
*/

int i386_push_fs(asm_instr *new, u_char *opcode, u_int len, asm_processor *proc)
{
  new->instr = ASM_PUSH;
  new->len += 1;
  new->len += asm_operand_fetch(&new->op[0], opcode, ASM_CONTENT_FIXED, new);
  new->op[0].type = ASM_OPTYPE_REG;
  new->op[0].regset = ASM_REGSET_SREG;
  new->op[0].len = 0;
  new->op[0].ptr = 0;
  new->op[0].baser = ASM_REG_FS;
  return (new->len);
}
