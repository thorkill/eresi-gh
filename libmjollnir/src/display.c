/*
** display.c for libmjollnir in elfsh
** 
** Contain printing functions for debug purpose only
**
** FIXME: needs to use vm_output() and not printf inside elfsh.
**
** Started on  Tue Jan 02 04:04:18 2006 mayhem
*/
#include "libmjollnir.h"


/* Some constant data */
char	*call_type_str[] = 
{
  "CONT",
  "JUMP",
  "CALL",
  "RET",
  "UNKN"
};


/* Print block */
void		mjr_block_dump(mjrblock_t *b) 
{
  printf("[B]=(%lX) [V]=(%lX) sz=(%04u) \n", 
	 (unsigned long) b, (unsigned long) b->vaddr, b->size);
}


/* Display all information about a block */
int			mjr_block_display(mjrblock_t *cur, mjropt_t *disopt)
{
  mjrcaller_t		*ccal;
  char			*str;
  char			*end_str;
  elfsh_SAddr		offset;
  elfsh_SAddr		end_offset;
  char			buf1[30];
  char			buf2[30];
  
  ELFSH_PROFILE_IN(__FILE__, __FUNCTION__, __LINE__);

  str = elfsh_reverse_metasym(disopt->file, cur->vaddr, &offset);

  end_str = elfsh_reverse_metasym(disopt->file, 
				  cur->vaddr + cur->size, &end_offset);

  if (str == NULL)
    *buf1 = 0x00;
  else
    snprintf(buf1, sizeof (buf1), "<%s + " UFMT ">", str, offset);
  if (end_str == NULL || !(cur->true))
    *buf2 = 0x00;
  else
    snprintf(buf2, sizeof (buf2), "<%s + " UFMT ">", end_str, end_offset);
      
  printf("[%8lx:%05i:%8lx:%8lx] %-4s %-30s --> %-30s ", 
	 (unsigned long) cur->vaddr, cur->size, (unsigned long) cur->true, 
	 (unsigned long) cur->false, call_type_str[cur->type], buf1, buf2);
      
  if (cur->false == 0xFFFFFFFF)
    printf(" [?]");
  else if (cur->false != NULL)
    {
      str = elfsh_reverse_metasym(disopt->file, cur->false, &offset);
      printf(" [%s + " UFMT "]", (str ? str : ""), offset);
    }
      
  printf("\n");
  if (disopt->level > 0)
    for (ccal = cur->caller; ccal; ccal = ccal->next) 
      {
	str = elfsh_reverse_metasym(disopt->file, ccal->vaddr, &offset);
	printf("\texecuted from: (" AFMT ") <%s + " UFMT "> : %s\n",
	       ccal->vaddr, (str ? str : ""), (elfsh_SAddr) offset, 
	       call_type_str[ccal->type]);
      }
  ELFSH_PROFILE_ROUT(__FILE__, __FUNCTION__, __LINE__, ++disopt->counter);
}


/* Print the content of the control flow section */
int		mjr_blocks_display(mjrcontext_t	*c, int level)
{
  mjropt_t	opt;
  mjrblock_t	*block;
  char		**keys;
  int		index;
  int		blocnbr;

  ELFSH_PROFILE_IN(__FILE__, __FUNCTION__, __LINE__);
  opt.counter = 0;
  opt.level   = level;
  opt.file    = c->obj;
  keys        = hash_get_keys(&c->blkhash, &blocnbr);

  for (index = 0; index < blocnbr; index++)
    {
      block = hash_get(&c->blkhash, keys[index]);
      mjr_block_display(block, &opt);
    }

  ELFSH_PROFILE_ROUT(__FILE__, __FUNCTION__, __LINE__, opt.counter);
}

/* Print information for functions */
void		mjr_function_display(mjrfunc_t *func)
{
  printf(" - FUNC ["AFMT"] %30s MD5: %s \n", func->vaddr, func->name, func->md5);
}

/* Print the functions in the function hash for the current context */
void		mjr_funcs_display(mjrcontext_t *c)
{
  char		**keys;
  int		keynbr;
  int		index;
  mjrfunc_t	*current;

  keys = hash_get_keys(&c->funchash, &keynbr);
  for (index = 0; index < keynbr; index++)
    {
      current = hash_get(&c->funchash, keys[index]);
      mjr_function_display(current);
    }
  hash_free_keys((char *) keys);
}


/* Shortcut for vaddr 2 string with allocation .. */
char	*_vaddr2str(elfsh_Addr addr)
{
  char *tmp;
  
  tmp = elfsh_malloc(BSIZE_SMALL);
  snprintf(tmp, BSIZE_SMALL, AFMT, addr);
  return ((char *) tmp);
}
