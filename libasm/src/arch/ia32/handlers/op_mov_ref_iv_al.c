/**
 * @file libasm/src/arch/ia32/handlers/op_mov_ref_iv_al.c
 *
 * @ingroup IA32_instrs
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 *
 * <instruction func="op_mov_ref_iv_al" opcode="0xa2"/>
 */

int op_mov_ref_iv_al(asm_instr *new, u_char *opcode, u_int len,
                     asm_processor *proc)
{
  new->instr = ASM_MOV;
  new->type = ASM_TYPE_ASSIGN;
  new->ptr_instr = opcode;
  new->len += 1;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_OFFSET, new);

  new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_FIXED, new);
  new->op[1].content = ASM_CONTENT_FIXED;
  new->op[1].regset = ASM_REGSET_R8;
  new->op[1].type = ASM_OPTYPE_REG;
  new->op[1].baser = ASM_REG_AL;

  return (new->len);
}
