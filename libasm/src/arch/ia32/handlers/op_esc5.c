/**
 * @file libasm/src/arch/ia32/handlers/op_esc5.c
 *
 * @ingroup IA32_instrs
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * Handler for esc5 instruction group, opcode 0xdd
 * @param new Pointer to instruction structure.
 * @param opcode Pointer to data to disassemble.
 * @param len Length of data to disassemble.
 * @param proc Pointer to processor structure.
 * @return Length of instruction.
*/

int op_esc5(asm_instr *new, u_char *opcode, u_int len,
            asm_processor *proc)
{
  struct s_modrm *modrm;
  new->ptr_instr = opcode;

  modrm = (struct s_modrm *) opcode + 1;
  new->len += 1;

  if (modrm->mod == 3)
    {
      new->len += 1;

      switch (modrm->r)
        {
        case 3:
          new->instr = ASM_FSTP;
          break;

        case 4:
          new->instr = ASM_FUCOM;
          break;

        case 5:
          new->instr = ASM_FUCOMP;
          break;

        default:
          new->instr = ASM_BAD;
          break;
        }
    }
  else
    switch (modrm->r)
      {
      case 0:
        new->instr = ASM_FLD;
        break;

      case 1:
        new->instr = ASM_BAD;
        break;

      case 2:
        new->instr = ASM_FST;
        break;

      case 3:
        new->instr = ASM_FSTP;
        break;

      case 4:
        new->instr = ASM_BAD; // ASM_FRSTOR;
        break;

      case 5:
        new->instr = ASM_BAD; // ;
        break;

      case 6:
        if (!(new->prefix & ASM_PREFIX_FWAIT))
          {
            new->instr = ASM_FNSAVE;
          }
        else
          {
            new->instr = ASM_FSAVE;
          }

        break;

      case 7:
        if (!(new->prefix & ASM_PREFIX_FWAIT))
          {
            new->instr = ASM_FNSAVE;
          }
        else
          {
            new->instr = ASM_FSAVE;
          }

        break;
      }

  if (modrm->mod == 3)
    {
      new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_FPU_SCALED,
                                    new);
      new->op[0].type = ASM_OPTYPE_REG;
      new->op[0].len = 1;
      new->op[0].ptr = opcode + 1;
      new->op[0].scale = modrm->m;
    }
  else
    {
#if LIBASM_USE_OPERAND_VECTOR
      new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODED,
                                    new);
#else
      new->op[0].content = ASM_CONTENT_ENCODED;
      operand_rmv(&new->op[0], opcode + 1, len - 1, proc);
#endif
    }

#if LIBASM_USE_OPERAND_VECTOR
#else

  if (new->op[0].content)
    {
      new->len += new->op[0].len;
    }

#endif
  return (new->len);
}
