
/**
 * @file libasm/src/arch/ia32/handlers/i386_bt_rm_r.c
 *
 * @ingroup IA32_instrs
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * Handler for instruction bt rm, r, opcode 0x0f 0xa3
 * @param new Pointer to instruction structure.
 * @param opcode Pointer to data to disassemble.
 * @param len Length of data to disassemble.
 * @param proc Pointer to processor structure.
 * @return Length of instruction.
*/

int i386_bt_rm_r(asm_instr *new, u_char *opcode, u_int len,
                 asm_processor *proc)
{
  struct s_modrm        *modrm;

  modrm = (struct s_modrm *) opcode + 1;
  new->instr = ASM_BT;
  new->len += 1;

  new->type = ASM_TYPE_BITTEST | ASM_TYPE_WRITEFLAG;
  new->flagswritten = ASM_FLAG_CF;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODED,
                                new);
  new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_GENERAL,
                                new);

  return (new->len);
}
