/**
 * @file libasm/src/arch/ia32/handlers/i386_bts.c
 *
 * @ingroup IA32_instrs
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
  <i386 func="i386_bts" opcode="0xab"/>
 */

int i386_bts(asm_instr *new, u_char *opcode, u_int len, asm_processor *proc)
{
  new->len += 1;
  new->instr = ASM_BTS;

  new->type = ASM_TYPE_BITTEST | ASM_TYPE_BITSET | ASM_TYPE_WRITEFLAG;
  new->flagswritten = ASM_FLAG_CF;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODED,
                                new);
  new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_GENERAL,
                                new);

  return (new->len);
}
