/**
 * @file libasm/src/arch/ia32/handlers/op_ret_i2.c
 *
 * @ingroup IA32_instrs
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * Handler for ret instruction, opcode 0xc2
 * @param new Pointer to instruction structure.
 * @param opcode Pointer to data to disassemble.
 * @param len Length of data to disassemble.
 * @param proc Pointer to processor structure.
 * @return Length of instruction.
*/

int op_ret_i2(asm_instr *new, u_char *opcode, u_int len,
              asm_processor *proc)
{
  new->len += 1;
  new->type = ASM_TYPE_RETPROC | ASM_TYPE_TOUCHSP | ASM_TYPE_EPILOG;
  new->spdiff = 4;
  new->instr = ASM_RET;
  new->ptr_instr = opcode;

  new->len += asm_operand_fetch(&new->op[0], opcode + 1,
                                ASM_CONTENT_IMMEDIATEWORD, new);

  return (new->len);
}
