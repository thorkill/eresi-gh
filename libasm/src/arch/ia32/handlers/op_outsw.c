/**
**
*/
#include <libasm.h>
#include <libasm-int.h>

/**
  <instruction func="op_outsw" opcode="0x6f"/>
  <instruction func="op_outsd" opcode="0x6f"/>
*/

int op_outsw(asm_instr *new, u_char *opcode, u_int len, asm_processor *proc)
{
  new->ptr_instr = opcode;
  new->len += 1;

  if (!asm_proc_opsize(proc))
    {
      new->instr = ASM_OUTSW;
    }
  else
    {
      new->instr = ASM_OUTSD;
    }

  new->len += asm_operand_fetch(&new->op[0], opcode, ASM_CONTENT_FIXED, new);
  new->op[0].type = ASM_OPTYPE_MEM;
  new->op[0].memtype = ASM_OP_BASE | ASM_OP_REFERENCE;
  new->op[0].regset = ASM_REGSET_R16;
  new->op[0].baser = ASM_REG_DX;

  new->len += asm_operand_fetch(&new->op[1], opcode, ASM_CONTENT_XSRC, new);
  return (new->len);
}
