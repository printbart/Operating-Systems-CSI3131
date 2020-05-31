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
    else if(pid1 == 0){
        excelp("./calcloop", "calcloop", NULL);
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid2 == 0){
        char pid1_str[128];
        sprintf(pid1_str, "%d", pid1);
        execlp("./procmon", "procmon", pid1_str, NULL);
    }

    int result = wait(&status);

   result = wait(&status);

    pid3 = fork();
    if (pid3 < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid3 == 0){
        execlp("./cploop", "cploop", (char *) NULL);
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if(pid2 == 0){
        char pid3_str[128];
       sprintf(pid3_str, "%d", pid3);
       execlp("./procmon", "procmon", pid3_str, NULL);
    }

    result = wait(&status);
    result = wait(&status);

    return(0);


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
