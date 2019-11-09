/**
**
*/
#include <libasm.h>
#include <libasm-int.h>

/**
  <instruction func="op_outsb" opcode="0x6e"/>
*/

int op_outsb(asm_instr *new, u_char *opcode, u_int len, asm_processor *proc)
{
  new->len += 1;
  new->instr = ASM_OUTSB;
  new->ptr_instr = opcode;

  new->len += asm_operand_fetch(&new->op[0], opcode, ASM_CONTENT_FIXED, new);
  new->op[0].type = ASM_OPTYPE_MEM;
  new->op[0].memtype = ASM_OP_BASE | ASM_OP_REFERENCE;
  new->op[0].regset = ASM_REGSET_R16;
  new->op[0].baser = ASM_REG_EDX;

  new->len += asm_operand_fetch(&new->op[1], opcode, ASM_CONTENT_XSRC, new);

  return (new->len);
}
