/**
 * @file libasm/src/arch/ia32/handlers/op_sbb_rmb_rb.c
 *
 * @ingroup IA32_instrs
**
*/
#include <libasm.h>
#include <libasm-int.h>

/**
  <instruction func="op_sbb_rmb_rb" opcode="0x18"/>
*/

int op_sbb_rmb_rb(asm_instr *new, u_char *opcode, u_int len,
                  asm_processor *proc)
{
  new->len += 1;
  new->instr = ASM_SBB;
  new->ptr_instr = opcode;
  new->type = ASM_TYPE_ARITH | ASM_TYPE_WRITEFLAG | ASM_TYPE_READFLAG;
  new->flagsread = ASM_FLAG_CF;
  new->flagswritten = ASM_FLAG_AF | ASM_FLAG_CF | ASM_FLAG_PF |
                      ASM_FLAG_OF | ASM_FLAG_SF | ASM_FLAG_ZF;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODEDBYTE,
                                new);
  new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_GENERALBYTE,
                                new);

  return (new->len);
}
