#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOARD_SIZE 12
#define EMPTY 0
#define BLACK 1
#define WHITE 2
typedef int BOOL;
#define TRUE 1
#define FALSE 0
typedef int OPTION;
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UP_LEFT 4
#define UP_RIGHT 5
#define DOWN_LEFT 6
#define DOWN_RIGHT 7
#define MAX_BYTE 10000
#define START "START"
#define PLACE "PLACE"
#define TURN  "TURN"
#define END   "END"
struct Command
{
  int x;
  int y;
  OPTION option;
};
struct Command _command={0,0,0};//用来返回棋子和方向 
char buffer[MAX_BYTE] = {0};
char board[BOARD_SIZE][BOARD_SIZE] = {0};
int me_flag;
int other_flag;
int score[12][12];
int x,y,dir;
const int DIR[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
void debug(const char *str) {
  printf("DEBUG %s\n", str);
  fflush(stdout);
}
int max(int x,int y){
	if(x>y)
	return x;
	else
	 return y;
}
int min(int x,int y){
	if(x>y)
	return y;
	else
	 return x;
}
void printBoard() {
  char visual_board[BOARD_SIZE][BOARD_SIZE] = {0};
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == EMPTY) {
        visual_board[i][j] = '.';
      } else if (board[i][j] == BLACK) {
        visual_board[i][j] = 'O';
      } else if (board[i][j] == WHITE) {
        visual_board[i][j] = 'X';
      }
    }
    printf("%s\n", visual_board[i]);
  }
}
BOOL isInBound(int x, int y) {
  return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}
BOOL move(int x, int y, OPTION option, int cur_flag,char board[12][12]) {
    if (board[x][y] != cur_flag) {
    return FALSE;
  }
  int new_x = x + DIR[option][0];
  int new_y = y + DIR[option][1];
    if (!isInBound(new_x, new_y) || board[new_x][new_y] != EMPTY) {
    return FALSE;
  }
  board[x][y] = EMPTY;
  board[new_x][new_y] = cur_flag;
  int cur_other_flag = 3 - cur_flag;
  int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
  for (int i = 0; i < 4; i++) {
    int x1 = new_x + intervention_dir[i][0];
    int y1 = new_y + intervention_dir[i][1];
    int x2 = new_x - intervention_dir[i][0];
    int y2 = new_y - intervention_dir[i][1];
    if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == cur_other_flag && board[x2][y2] == cur_other_flag) {
      board[x1][y1] = cur_flag;
      board[x2][y2] = cur_flag;
    }
  }
  int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
  for (int i = 0; i < 8; i++) {
    int x1 = new_x + custodian_dir[i][0];
    int y1 = new_y + custodian_dir[i][1];
    int x2 = new_x + custodian_dir[i][0] * 2;
    int y2 = new_y + custodian_dir[i][1] * 2;
    if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == cur_flag && board[x1][y1] == cur_other_flag) {
      board[x1][y1] = cur_flag;
    }
  }
  return TRUE;
}
int SCORE(char board[12][12]){
	int scor1=0,scor2=0,sum,s1=0,s2=0;
	char evaluate[12][12]={0};
		for(int i=4;i<8;i++)
	for(int j=3;j<9;j++)
	evaluate[i][j]=10;
	for(int i=4;i<8;i++)
	for(int j=3;j<9;j++)
	evaluate[i][j]=10;
	for(int i=2;i<10;i++)
	for(int j=2;j<10;j++){
		if(evaluate[i][j]!=10)
		evaluate[i][j]=5;
	}
	for(int i=0;i<12;i++)
	for(int j=0;j<12;j++){
		if(board[i][j]==1)
		scor1++,s1=s1+evaluate[i][j];
		if(board[i][j]==2)
		scor2++,s2=s2+evaluate[i][j];
	}
	sum=(scor1-scor2)*100+s1-s2;
	return sum;
}
int search(char board[12][12],int flag,int deep,int alpha,int beta){
	if(deep==1){
      int sum;
      sum=SCORE(board);
      return sum;
	}
    char newboard[12][12];
	int score,scoresum,otherflag=3-flag;
	for(int i=0;i<12;i++)
	for(int j=0;j<12;j++)
	newboard[i][j]=board[i][j];
	if(flag==1)
	score=-10000;
	else
	score=10000;
	for(int i=0;i<12;i++)
	for(int j=0;j<12;j++){
		if(newboard[i][j]==flag){
			for(int k=0;k<8;k++){
				if(move(i,j,k,flag,newboard)==1){
					if(flag==1){
						score=max(search(newboard,otherflag,deep-1,alpha,beta),score);
						alpha=score;
						if(alpha>=beta){
							return beta;
						}
					}
					if(flag==2){
						score=min(search(newboard,otherflag,deep-1,alpha,beta),score);
						beta=score;
						if(alpha>=beta){
							return alpha;
						}
					}
				}
	                for(int m=0;m<12;m++)
                	for(int n=0;n<12;n++)
                 	newboard[m][n]=board[m][n];	
			}
		}
	}
   	 return score;	
}
struct Command decision(char board[12][12])
{
    char newboard[12][12];
	for(int i=0;i<12;i++)
	for(int j=0;j<12;j++)
	newboard[i][j]=board[i][j];	
	int score,_score;
	if(me_flag==1)
	_score=-10000;
	else
	_score=10000;
	for(int i=0;i<12;i++)
	for(int j=0;j<12;j++){
		if(newboard[i][j]==me_flag){
			for(int k=0;k<8;k++){
				if(move(i,j,k,me_flag,newboard)==1){
					if(me_flag==1){
						
						score=max(search(newboard,3-me_flag,4,-10000,10000),_score);
					if(score!=_score){
						_command.x=i,_command.y=j,_command.option=k,_score=score;
					}
				
					}
					if(me_flag==2){
					
						score=min(search(newboard,3-me_flag,4,-10000,10000),_score);
					if(score!=_score){
						_command.x=i,_command.y=j,_command.option=k,_score=score;
					}	
						
					}
				}
				 for(int m=0;m<12;m++)
               	 for(int n=0;n<12;n++)
                 newboard[m][n]=board[m][n];
			}
		}
	}
	return _command;
}
int _turn=1;
struct Command aiTurn(const char board[BOARD_SIZE][BOARD_SIZE], int me) {
	if(_turn==1&&me==1){
		 struct Command preferedPos ={9,7,4};
		 _turn++;
		 return preferedPos;
	}
	else{
	char newboard[12][12];
    for(int i=0;i<12;i++)
	for(int j=0;j<12;j++)
	newboard[i][j]=board[i][j];
	struct Command preferedPos = decision(newboard);
    return preferedPos;
	}

}
BOOL place(int x, int y, OPTION option, int cur_flag) {
    if (board[x][y] != cur_flag) {
    return FALSE;
  }
  int new_x = x + DIR[option][0];
  int new_y = y + DIR[option][1];
    if (!isInBound(new_x, new_y) || board[new_x][new_y] != EMPTY) {
    return FALSE;
  }
  board[x][y] = EMPTY;
  board[new_x][new_y] = cur_flag;
  int cur_other_flag = 3 - cur_flag;
  int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
  for (int i = 0; i < 4; i++) {
    int x1 = new_x + intervention_dir[i][0];
    int y1 = new_y + intervention_dir[i][1];
    int x2 = new_x - intervention_dir[i][0];
    int y2 = new_y - intervention_dir[i][1];
    if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == cur_other_flag && board[x2][y2] == cur_other_flag) {
      board[x1][y1] = cur_flag;
      board[x2][y2] = cur_flag;
    }
  }
  int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
  for (int i = 0; i < 8; i++) {
    int x1 = new_x + custodian_dir[i][0];
    int y1 = new_y + custodian_dir[i][1];
    int x2 = new_x + custodian_dir[i][0] * 2;
    int y2 = new_y + custodian_dir[i][1] * 2;
    if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == cur_flag && board[x1][y1] == cur_other_flag) {
      board[x1][y1] = cur_flag;
    }
  }
  return TRUE;
}
void start(int flag) {
  memset(board, 0, sizeof(board));
  for (int i = 0; i < 3; i++) {
    board[2][2 + i] = WHITE;
    board[6][6 + i] = WHITE;
    board[5][3 + i] = BLACK;
    board[9][7 + i] = BLACK;
  }

  for (int i = 0; i < 2; i++) {
    board[8 + i][2] = WHITE;
    board[2 + i][9] = BLACK;
  }
}
  void turn() {
 struct Command command = aiTurn((const char (*)[BOARD_SIZE])board, me_flag);
  place(command.x, command.y, command.option, me_flag);
  printf("%d %d %d\n", command.x, command.y, command.option);
  fflush(stdout);
}
void end(int x) {

}
void loop() {
  while (TRUE)
  {
    memset(buffer, 0, sizeof(buffer));
    gets(buffer);

    if (strstr(buffer, START))
    {
      char tmp[MAX_BYTE] = {0};
      sscanf(buffer, "%s %d", tmp, &me_flag);
      other_flag = 3 - me_flag;
      start(me_flag);
      printf("OK\n");
      fflush(stdout);
    }
    else if (strstr(buffer, PLACE))
    {
      char tmp[MAX_BYTE] = {0};
      int x, y;
      OPTION option;
      sscanf(buffer, "%s %d %d %d", tmp, &x, &y, &option);
      place(x, y, option, other_flag);
    }
    else if (strstr(buffer, TURN))
    {
      turn();
    }
    else if (strstr(buffer, END))
    {
      char tmp[MAX_BYTE] = {0};
      int x;
      sscanf(buffer, "%s %d", tmp, &x);
      end(x);
    }
  }
}
int main(int argc, char *argv[]) {
  loop();
  return 0;
}
