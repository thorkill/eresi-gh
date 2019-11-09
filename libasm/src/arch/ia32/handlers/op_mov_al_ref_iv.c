/**
**
*/
#include <libasm.h>
#include <libasm-int.h>

/**
  <instruction func="op_mov_al_ref_iv" opcode="0xa0"/>
*/

int op_mov_al_ref_iv(asm_instr *new, u_char *opcode, u_int len,
                     asm_processor *proc)
{
  new->len += 1;
  new->instr = ASM_MOV;
  new->ptr_instr = opcode;
  new->type = ASM_TYPE_ASSIGN;

  new->len += asm_operand_fetch(&new->op[0], opcode, ASM_CONTENT_FIXED, new);
  new->op[0].type = ASM_OPTYPE_REG;
  new->op[0].baser = ASM_REG_AL;
  new->op[0].regset = ASM_REGSET_R8;

  new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_OFFSET, new);

  return (new->len);
}
