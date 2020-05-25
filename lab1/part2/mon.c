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
