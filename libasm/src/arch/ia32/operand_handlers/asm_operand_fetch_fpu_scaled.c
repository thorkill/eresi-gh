/**
 * @file asm_operand_fetch_fpu_scaled.c
 * @ingroup operand_handler
 * $Id: asm_operand_fetch_fpu_scaled.c 1319 2009-04-05 22:48:58Z strauss $
 */

#include <libasm.h>
#include <libasm-int.h>

/**
 * @todo
 * Implement optional parameter for scaled FPU operand fetching.
 */
/**
 * @ingroup operand_handler
 * Decode data for operand type ASM_CONTENT_FPU_SCALED
 * @param operand Pointer to operand structure to fill.
 * @param opcode Pointer to operand data
 * @param otype
 * @param ins Pointer to instruction structure.
 * @return Operand length
 */

int     asm_operand_fetch_fpu_scaled(asm_operand *operand, u_char *opcode,
                                     int otype, asm_instr *ins)
{
  operand->content = ASM_CONTENT_FPU_SCALED;
  return (0);
}
