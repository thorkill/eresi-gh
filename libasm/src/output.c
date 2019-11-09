/**
 * @brief ASCII Output wrappers.
 * @file output.c
 * @ingroup libasm_engine
 *
 * Author  : <sk at devhell dot org>
 */
#include <libasm.h>
#include <libasm-int.h>

/**
 * @brief Wrapper to internal resolving handler for immediate values.
 * @param proc Pointer to processor structure
 * @param val Value to resolve
 * @param buf Pointer to store string
 * @param len Length of string
 */
void  asm_resolve_immediate(asm_processor *proc, eresi_Addr val,
                            char *buf, u_int len)
{
  LIBASM_PROFILE_FIN();
  proc->resolve_immediate(proc->resolve_data, val, buf, len);
  LIBASM_PROFILE_VOUT();
}

/**
 * @brief Wrapper to internal Ascii output handler.
 * @param instr Pointer to instruction structure
 * @param addr Virtual address of instruction
 * @return Pointer to a static buffer containing current instruction string
 */
char  *asm_display_instr_att(asm_instr *instr, eresi_Addr addr)
{
  char  *to_ret;

  LIBASM_PROFILE_FIN();
  to_ret = instr->proc->display_handle(instr, addr);
  LIBASM_PROFILE_ROUT(to_ret);
}

/**
 * @brief Debug dump to stderr of an operand
 * @param op Pointer to operand structure.
 * @return Always returns 0.
 */
int asm_debug_operand(asm_operand *op)
{
  fprintf(stderr, "[*] Operand Dump\n[*] len: %d type: %d size: %d content: %d\n",
          op->len, op->type, op->size, op->content);

  switch (op->type)
    {
    case ASM_OPTYPE_REG:
      fprintf(stderr, "[*] Type: ASM_OPTYPE_REG\n");
      break;

    case ASM_OPTYPE_IMM:
      fprintf(stderr, "[*] Type: ASM_OPTYPE_IMM\n");
      break;

    case ASM_OPTYPE_MEM:
      fprintf(stderr, "[*] Type: ASM_OPTYPE_MEM\n");
      fprintf(stderr, "[*] Memory Type: %s %s %s %s %s %s\n",
              (op->memtype & ASM_OP_VALUE) ? "ASM_OP_VALUE" : ".",
              (op->memtype & ASM_OP_BASE) ? "ASM_OP_BASE" : ".",
              (op->memtype & ASM_OP_INDEX) ? "ASM_OP_INDEX" : ".",
              (op->memtype & ASM_OP_SCALE) ? "ASM_OP_SCALE" : ".",
              (op->memtype & ASM_OP_REFERENCE) ? "ASM_OP_REFERENCE" : ".",
              (op->memtype & ASM_OP_ADDRESS) ? "ASM_OP_ADDRESS" : ".");
      break;

    default:
      fprintf(stderr, "[*] Type: UNKNOWN!\n");
      break;
    }

  return 0;
}

/**
 * @brief Return a string describing the operand content
 * @param content Operand content
 * @return A pointer to a static string
 */

char  *asm_operand_content_string(int content)
{
  switch (content)
    {
    case ASM_CONTENT_OPMOD:
      return ("opmod");

    case ASM_CONTENT_ADDRESS:
      return ("address");

    case ASM_CONTENT_CONTROL:
      return ("control");

    case ASM_CONTENT_DEBUG:
      return ("debug");

    case ASM_CONTENT_ENCODED:
      return ("encoded");

    case ASM_CONTENT_ENCODEDBYTE:
      return ("encodedbyte");

    case ASM_CONTENT_FLAGS:
      return ("flags");

    case ASM_CONTENT_GENERAL:
      return ("general");

    case ASM_CONTENT_GENERALBYTE:
      return ("generalbyte");

    case ASM_CONTENT_IMMEDIATE:
      return ("immediate");

    case ASM_CONTENT_IMMEDIATEWORD:
      return ("immediateword");

    case ASM_CONTENT_IMMEDIATEBYTE:
      return ("immediatebyte");

    case ASM_CONTENT_SHORTJUMP:
      return ("shortjump");

    case ASM_CONTENT_JUMP:
      return ("jump");

    case ASM_CONTENT_MEMORY:
      return ("memory");

    case ASM_CONTENT_OFFSET:
      return ("offset");

    case ASM_CONTENT_PMMX:
      return ("pmmx");

    case ASM_CONTENT_QMMX:
      return ("qmmx");

    case ASM_CONTENT_REGISTER:
      return ("register");

    case ASM_CONTENT_SEGMENT:
      return ("segment");

    case ASM_CONTENT_FPU:
      return ("fpu");

    case ASM_CONTENT_FPU_SCALED:
      return ("fpu_scaled");

    case ASM_CONTENT_XSRC:
      return ("xsrc");

    case ASM_CONTENT_YDEST:
      return ("ydest");

    case ASM_CONTENT_VALUE:
      return ("value");
    }

  return ("undocumented content");
}

/**
 * @brief Return a string describing the operand type
 * @param content Operand type
 * @return A pointer to a static string
 */

char  *asm_operand_type_string(int type)
{
  switch (type)
    {
    case ASM_OPTYPE_REG:
      return ("register");

    case ASM_OPTYPE_IMM:
      return ("immediate");

    case ASM_OPTYPE_MEM:
      return ("memory");

    case ASM_OPTYPE_NONE:
    default:
      return ("none");
    }
}
