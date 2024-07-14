#include <sys/user.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <elf.h>


void singleStep(pid_t pid, void * data);
struct iovec getRegs( pid_t pid,struct user_regs_struct * regPtr);
void printX8664Regs(struct user_regs_struct regs);
