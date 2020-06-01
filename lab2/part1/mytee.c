#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


/**
 * pipe stdout to stdin and read from stdin  
 *
 */

int main(int argc, char **argv)
{
	int pipefd[2];
  int pid;
  int pid2;
  char *tee_args[] = {"tee", NULL};

  pipe(pipefd);

  if (fork() == 0)
  {
      close(pipefd[1]);  // close the write end of the pipe in the parent
      dup2(pipefd[0], 0); // redirect to stdin
      close(pipefd[0]);

      execvp("tee", tee_args);
  }
  else
  {
    // char buffer[1024];
      char *buffer = (char *)malloc(1024);
      char **ptr = &buffer;
      size_t bufsize = 1024;

      close(pipefd[0]);  // close the write end of the pipe in the parent
      dup2(pipefd[1], 1); // redirect to stdin
      close(pipefd[1]);

      int counter = 0;
      while (getline(&buffer, &bufsize, stdin) > 0)
      {
        printf("%d %s",counter, buffer);
        counter++;
      }
  }
}
