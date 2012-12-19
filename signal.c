#include <signal.h>

{
	sigset_t newmask, oldmask, waitmask;
	
	if(signal(SIGINT, sig_int) == SIG_ERR)
		printf("init signal error!\n");
	
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSER1);
	sigemptyset(&newmask);
	sigaddst(&newmask, SIGINT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("set block mask failed!\n");
	
	/* enter the critical section! */
	/* allow all signal except SIGUSR1 */
	if(sigsuspend(&waitmask) != -1)
		printf("sigsuspend error!\n");
	/* restore the old mask , don't use the SIG_UNBLOCK! */	
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK error!\n");

	exit(0);
}
