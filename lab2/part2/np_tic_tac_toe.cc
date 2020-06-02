
#include <stdio.h>
#include <stdlib.h> 
#include <signal.h> // sigaction(), sigsuspend(), sig*()
#include <unistd.h> // alarm()
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "tic_tac_toe.h"


/* Usage example
 * 
 * First, compile and run this program:
 *     $ gcc np_tic_tac_toe.c -o np_tic_tac_toe
 *     if not already created, create a named pipe (FIFO)
 *     $ mkfifo my_pipe 
 *
 *     In two separe shells run:
 *     $ ./np_tic_tac_toe X 
 *     $ ./np_tic_tac_toe O 
 * 
 *
 */
 
 
int main(int argc, char **argv) {
  tic_tac_toe *game = new tic_tac_toe();
  char player;

  if (argc != 2) {
    printf ("Usage: sig_tic_tac_toe [X|O] \n");
    return (-1);
  }
  player = argv[1][0];
  if (player != 'X' && player != 'O') {
    printf ("Usage: player names must be either X or O");
    return (-2);
  }

  int fd;
  char str[256] = "";
  char myfifo[128] = "part2/my_pipe";

  int turn = 0;

  do{
    if( (player == 'X' && turn%2 == 0) || (player == 'O' && turn%2 == 1) ){
      game->display_game_board();
      game->get_player_move(player);
      game->display_game_board();
      fd = open(myfifo, O_WRONLY);
      write(fd, game->convert2string(), strlen(game->convert2string())+1);
      close(fd);
    }
    else{
      fd = open(myfifo, O_RDONLY);
      read(fd, str, 256);
      close(fd);
      game->set_game_state(str);
    }
    printf("%s\n", "Incrementing Turn");
    turn++;
    
  }while ((game->game_result()) == '-');
  game->display_game_board();
  printf ("Game finished, result: %c \n", (game->game_result()));
  return 0;
}
