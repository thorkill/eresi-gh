/**
**
*/
#include <libasm.h>
#include <libasm-int.h>

/**
  <instruction func="i386_group15" opcode="0xae"/>
 */

int i386_group15(asm_instr *new, u_char *opcode, u_int len,
                 asm_processor *proc)
{
  struct s_modrm        *modrm;
  modrm = (struct s_modrm *) opcode + 1;

  new->len += 1;

  switch (modrm->r)
    {
    case 2:
      new->instr = ASM_LDMXCSR;
      new->op[0].content = ASM_CONTENT_ENCODED;
#if LIBASM_USE_OPERAND_VECTOR
      new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODED,
                                    new);
#else
      operand_rmv(&new->op[0], opcode + 1, len - 1, proc);
      new->len += new->op[0].len;
#endif
      break;

    case 3:
      new->instr = ASM_STMXCSR;
#if LIBASM_USE_OPERAND_VECTOR
      new->len += asm_operand_fetch(&new->op[0], opcode + 1, ASM_CONTENT_ENCODED,
                                    new);
#else
      new->op[0].content = ASM_CONTENT_ENCODED;
      operand_rmv(&new->op[0], opcode + 1, len - 1, proc);
      new->len += new->op[0].len;
#endif
      break;

    case 7:
      new->instr = ASM_CLFLUSH;
      new->op[0].content = ASM_CONTENT_GENERAL;
      break;

    default:
      new->len = 0;
      break;
    }

  return (new->len);
}
