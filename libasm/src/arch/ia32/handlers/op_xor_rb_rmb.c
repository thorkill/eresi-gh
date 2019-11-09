/**
 * @file libasm/src/arch/ia32/handlers/op_xor_rb_rmb.c
 *
 * @ingroup IA32_instrs
 * @brief Handler for instruction xor rb,rmb opcode 0x32
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * @brief Handler for instruction xor rb,rmb opcode 0x32
 * @param instr Pointer to instruction structure
 * @param  opcode Pointer to data to disassemble.
 * @param len Length of data to disassemble.
 * @param proc Pointer to processor structure.
*/

int op_xor_rb_rmb(asm_instr *new, u_char *opcode, u_int len,
                  asm_processor *proc)
{
  new->instr = ASM_XOR;
  new->len += 1;
  new->type = ASM_TYPE_ARITH | ASM_TYPE_WRITEFLAG;
  new->flagswritten = ASM_FLAG_CF | ASM_FLAG_OF | ASM_FLAG_PF |
                      ASM_FLAG_ZF | ASM_FLAG_SF;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_GENERALBYTE,
                                new);
  new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_ENCODEDBYTE,
                                new);

  return (new->len);
}
