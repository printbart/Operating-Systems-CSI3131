#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/* the program execution starts here */
int main(int argc, char **argv)
{
    char    *program;
    int pid1, pid2, pid3;
    int cnt = 0;
    int status;

    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid1 == 1){
        excelp("./calcloop");
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid2 == 1){
        excelp("./procmon", pid1);
    }

    pid1 = wait(&status); printf ("pid %d ended\n" ,pid1);
    pid2 = wait(&status); printf ("pid %d ended\n" ,pid2);

    pid3 = fork();
    if (pid3 < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid3 == 1){
        excelp("./cploop");
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid2 == 1){
        excelp("./procmon", pid3);
    }

    pid3 = wait(&status); printf ("pid %d ended\n" ,pid3);
    pid2 = wait(&status); printf ("pid %d ended\n" ,pid2);


    /* Here comes your code.*/
    /* It should do the following:
        1. fork/launch the program 'calcloop' and get its pid
        2. fork/launch 'procmon pid' where pid is the pid of the process launched in step 1
        3. wait till calcloop process ends
        4. wait till procmon process ends
        5. fork/launch the program 'cploop' and get its pid
        6. fork/launch 'procmon pid' where pid is the pid of the process launched in step 5
        7. wait till cploop process ends
        8. wait till procmon process ends
    */
}
