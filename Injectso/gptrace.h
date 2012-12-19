/**
 * \file gptrace.h
 * \author  wzj
 * \brief 
 * \version 
 * \note  
 * \date: 2012年08月27日星期一21:55:22
 */ 
 #ifndef _G2_PTRACE_API_
 #define _G2_PTRACE_API_

 #include <sys/ptrace.h>
 #include <wait.h>
 #include <sys/user.h>
 #include <errno.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>

 extern void ptrace_attach(int pid);
 extern void ptrace_cont(int pid);
 extern void ptrace_detach(int pid);
 extern void ptrace_write(int pid, unsigned long addr, void *vptr, int len);
 extern void ptrace_read(int pid, unsigned long addr, void *vptr, int len);
 extern char * ptrace_readstr(int pid, unsigned long addr);
 extern void ptrace_readreg(int pid, struct user_regs_struct *regs);
 extern void ptrace_writereg(int pid, struct user_regs_struct *regs);
 extern void * ptrace_push(int pid, void *paddr, int size);
 extern void ptrace_call(int pid, unsigned long addr);
 extern void restart_syscall(void);

 #endif 
