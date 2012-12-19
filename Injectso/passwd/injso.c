/**
 * \file injso.c
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月27日星期一22:22:47
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gelf.h"
#include "gptrace.h"


void
call_dl_open (int pid, unsigned long addr, char *libname)
{
  void *pRLibName;
  struct user_regs_struct regs;

  /*
     先找个空间存放要装载的共享库名，我们可以简单的把它放入堆栈
   */
  pRLibName = ptrace_push (pid, libname, strlen (libname) + 1);

  /* 设置参数到寄存器 */
  ptrace_readreg (pid, &regs);
  regs.eax = (unsigned long) pRLibName;
  regs.ecx = 0x0;
  regs.edx = RTLD_LAZY;
  ptrace_writereg (pid, &regs);

  /* 调用_dl_open */
  ptrace_call (pid, addr);
  puts ("call _dl_open ok");
}

int
main (int argc, char *argv[])
{
  int pid;
  struct link_map *map;
  char sym_name[256];
  unsigned long sym_addr;
  unsigned long new_addr, old_addr, rel_addr;

  pid = atoi (argv[1]);

  ptrace_attach (pid);

  map = get_linkmap (pid);

  sym_addr = find_symbol (pid, map, "_dl_open");
  printf ("found _dl_open at addr %p\n", sym_addr);
  call_dl_open (pid, sym_addr,
		"/home/joker/JustForFun/Injectso/passwd/so.so");

/* 找到我们的新函数newread的地址 */
  strcpy (sym_name, "newread");	/* intercept */
  sym_addr = find_symbol (pid, map, sym_name);
  printf ("%s addr\t %p\n", sym_name, sym_addr);

  /* 找到read的RELOCATION地址 */
  strcpy (sym_name, "read");
  rel_addr = find_sym_in_rel (pid, sym_name);
  printf ("%s rel addr\t %p\n", sym_name, rel_addr);

  /* 找到用于保存read地址的指针 */
  strcpy (sym_name, "oldread");
  old_addr = find_symbol (pid, map, sym_name);
  printf ("%s addr\t %p\n", sym_name, old_addr);

  /* 函数重定向 */
  puts ("intercept...");	/* intercept */
  ptrace_read (pid, rel_addr, &new_addr, sizeof (new_addr));
  ptrace_write (pid, old_addr, &new_addr, sizeof (new_addr));
  ptrace_write (pid, rel_addr, &sym_addr, sizeof (sym_addr));
  puts ("injectso ok");

  /* 脱离进程 */
  ptrace_detach (pid);

  exit (0);
}
