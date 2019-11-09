/**
 * @file libasm/src/arch/ia32/handlers/op_esc4.c
 *
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * Handler of FPU instruction group esc4 opcode 0xdc
  <instruction func="op_esc4" opcode="0xdc"/>
*/

int op_esc4(asm_instr *new, u_char *opcode, u_int len, asm_processor *proc)
{
  struct s_modrm *modrm;

  new->ptr_instr = opcode;
  modrm = (struct s_modrm *) opcode + 1;
  new->len += 1;

  switch (modrm->r)
    {
    case 0:
      new->instr = ASM_FADD;
      break;

    case 1:
      new->instr = ASM_FMUL;
      break;

    case 2:
      new->instr = ASM_FCOM;
      break;

    case 3:
      new->instr = ASM_FCOMP;
      break;

    case 4:
      new->instr = ASM_FSUB;
      break;

    case 5:
      new->instr = ASM_FSUBR;
      break;

    case 6:
      new->instr = ASM_FDIV;
      break;

    case 7:
      new->instr = ASM_FDIVR;
      break;
    }

  if (modrm->mod == 3)
    {
      new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_FPU_SCALED,
                                    new);
      new->op[0].type = ASM_OPTYPE_REG;
      new->op[0].len = 1;
      new->op[0].scale = modrm->m;
      new->len += asm_operand_fetch(&new->op[1], opcode + 1, ASM_CONTENT_FPU, new);
      new->op[1].type = ASM_OPTYPE_REG;
      new->len += 1;
    }
  else
    {
#if LIBASM_USE_OPERAND_VECTOR
      new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODED,
                                    new);
#else
      new->op[0].content = ASM_CONTENT_FIXED;
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
