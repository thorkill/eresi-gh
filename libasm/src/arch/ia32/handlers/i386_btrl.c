/**
 * @file libasm/src/arch/ia32/handlers/i386_btrl.c
 *
 * @ingroup IA32_instrs
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * Handler for instruction btrl, opcode 0x0f 0xba
 * @param new Pointer to instruction structure.
 * @param opcode Pointer to data to disassemble.
 * @param len Length of data to disassemble.
 * @param proc Pointer to processor structure.
 * @return Length of instruction.
 */

int     i386_btrl(asm_instr *new, u_char *opcode, u_int len,
                  asm_processor *proc)
{
  new->len += 1;
  new->instr = ASM_BTRL;

  new->type = ASM_TYPE_BITTEST | ASM_TYPE_BITSET | ASM_TYPE_WRITEFLAG;
  new->flagswritten = ASM_FLAG_CF;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODED,
                                new);
  new->len += asm_operand_fetch(&new->op[1], opcode + 1,
                                ASM_CONTENT_IMMEDIATEBYTE, new);

  return (new->len);
}
