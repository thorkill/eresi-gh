/**
**
*/
#include <libasm.h>
#include <libasm-int.h>

/**
  <instruction func="op_mov_rv_rmv" opcode="0x8b"/>
*/

int op_mov_rv_rmv(asm_instr *new, u_char *opcode, u_int len,
                  asm_processor *proc)
{
  new->ptr_instr = opcode;
  new->len += 1;
  new->type = ASM_TYPE_ASSIGN;
  new->instr = ASM_MOV;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_GENERAL,
                                new);
  new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_ENCODED,
                                new);

  if (new->op[1].type == ASM_OPTYPE_REG &&
      new->op[0].baser == ASM_REG_EBP &&
      new->op[1].baser == ASM_REG_ESP)
    {

      new->type |= ASM_TYPE_PROLOG;
    }
  else if (new->op[1].type == ASM_OPTYPE_REG &&
           new->op[0].baser == ASM_REG_ESP &&
           new->op[1].baser == ASM_REG_EBP)
    {

      new->type |= ASM_TYPE_EPILOG;
    }

  return (new->len);
}
