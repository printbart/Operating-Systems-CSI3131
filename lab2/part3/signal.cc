/**
 * More info?
 * a.dotreppe@aspyct.org
 * http://aspyct.org
 * @aspyct (twitter)
 *
 * Hope it helps :)
 */
// $ kill -l
 // 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 // 6) SIGABRT      7) SIGEMT       8) SIGFPE       9) SIGKILL     10) SIGBUS
// 11) SIGSEGV     12) SIGSYS      13) SIGPIPE     14) SIGALRM     15) SIGTERM
// 16) SIGURG      17) SIGSTOP     18) SIGTSTP     19) SIGCONT     20) SIGCHLD
// 21) SIGTTIN     22) SIGTTOU     23) SIGIO       24) SIGXCPU     25) SIGXFSZ
// 26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGPWR      30) SIGUSR1
// 31) SIGUSR2     32) SIGRTMIN    33) SIGRTMIN+1  34) SIGRTMIN+2  35) SIGRTMIN+3
// 36) SIGRTMIN+4  37) SIGRTMIN+5  38) SIGRTMIN+6  39) SIGRTMIN+7  40) SIGRTMIN+8
// 41) SIGRTMIN+9  42) SIGRTMIN+10 43) SIGRTMIN+11 44) SIGRTMIN+12 45) SIGRTMIN+13
// 46) SIGRTMIN+14 47) SIGRTMIN+15 48) SIGRTMIN+16 49) SIGRTMAX-15 50) SIGRTMAX-14
// 51) SIGRTMAX-13 52) SIGRTMAX-12 53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9
// 56) SIGRTMAX-8  57) SIGRTMAX-7  58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4
// 61) SIGRTMAX-3  62) SIGRTMAX-2  63) SIGRTMAX-1  64) SIGRTMAX


#include <stdio.h>
#include <stdlib.h> 
#include <signal.h> // sigaction(), sigsuspend(), sig*()
#include <unistd.h> // alarm()

void handle_signal(int signal);
void handle_sigalrm(int signal);
void do_sleep(int seconds);

/* Usage example
 * 
 * First, compile and run this program:
 *     $ gcc signal.c
 *     $ ./a.out
 * 
 * It will print out its pid. Use it from another terminal to send signals
 *     $ kill -HUP <pid>
 *     $ kill -USR1 <pid>
 *     $ kill -ALRM <pid>
 *
 * Exit the process with ^C ( = SIGINT) or SIGKILL, SIGTERM
 */
int main() {
    struct sigaction sa;

    // Print pid, so that we can send signals from other shells
    printf("My pid is: %d\n", getpid());

    // Setup the sighub handler
    sa.sa_handler = &handle_signal;

    // Restart the system call, if at all possible
    sa.sa_flags = SA_RESTART;

    // Block every signal during the handler
    sigfillset(&sa.sa_mask);

    // Intercept SIGUSR1 and SIGINT
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error: cannot handle SIGUSR1"); // Should not happen
    }

    // Will always fail, SIGKILL is intended to force kill your process
    if (sigaction(SIGKILL, &sa, NULL) == -1) {
        perror("Cannot handle SIGKILL"); // Will always happen
        printf("You can never handle SIGKILL anyway...\n");
    }

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error: cannot handle SIGINT"); // Should not happen
    }

    for (;;) {
        printf("\nSleeping for ~3 seconds\n");
        sleep(3); // Later to be replaced with a SIGALRM
    }
}

void handle_signal(int signal) {
  sigset_t pending;

  if (signal == SIGUSR1){
    printf ("received SIGUSR1 signal \n");
  }
  else if (signal == SIGINT) exit(0); // CTRL C exit
  else return;


  printf("Done handling SIGUSR1\n\n");
}

