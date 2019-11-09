/**
 * @file libasm/src/arch/arm/handlers/asm_arm_mla.c
** @ingroup ARM_instrs
*/
#include "libasm.h"

int     asm_arm_mla(asm_instr *ins, u_char *buf, u_int len,
                    asm_processor *proc)
{
  struct s_arm_decode_multiply opcode;
  struct s_asm_proc_arm *inter;

  LIBASM_PROFILE_FIN();

  inter = proc->internals;
  arm_convert_multiply(&opcode, buf);

  arm_decode_condition(ins, opcode.cond);

  ins->instr = inter->multiply_table[(opcode.op << 5) | (opcode.cond << 1) |
                                                      opcode.s];

  ins->name = ins->proc->instr_table[ins->instr];

  MASSIGNTYPE(ins, ASM_TYPE_ARITH);

  if (opcode.s)
    {
      MASSIGNTYPE(ins, ASM_TYPE_WRITEFLAG);
      ins->flagswritten = ASM_ARM_FLAG_N | ASM_ARM_FLAG_Z;
    }

  ins->nb_op = 4;

  /* Decode operands */
  ins->op[0].baser = opcode.r1; /* This is Rd */
  ins->op[0].destination = 1;
  asm_arm_op_fetch(&ins->op[0], buf, ASM_ARM_OTYPE_REGISTER, ins);

  ins->op[1].baser = opcode.r4; /* This is Rm */
  asm_arm_op_fetch(&ins->op[1], buf, ASM_ARM_OTYPE_REGISTER, ins);

  ins->op[2].baser = opcode.r3; /* This is Rs */
  asm_arm_op_fetch(&ins->op[2], buf, ASM_ARM_OTYPE_REGISTER, ins);

  ins->op[3].baser = opcode.r2; /* This is Rn */
  asm_arm_op_fetch(&ins->op[3], buf, ASM_ARM_OTYPE_REGISTER, ins);

  if (MISTYPE(ins, ASM_TYPE_BRANCH)
      || MISTYPE(ins, ASM_TYPE_CALLPROC)
      || MISTYPE(ins, ASM_TYPE_RETPROC))
    {
      MASSIGNTYPE(ins, ASM_TYPE_INDCONTROL);
    }

  LIBASM_PROFILE_FOUT(4);
}
