#include "ai.h"

// bool
typedef int BOOL;
#define TRUE 1
#define FALSE 0
char board[BOARD_SIZE][BOARD_SIZE] = { 0 };
const int DIR[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

BOOL isInBound(int x, int y) {
	return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}






/**
 * YOUR CODE BEGIN
 * 你的代码开始
 */

 /**
  * You can define your own struct and variable here
  * 你可以在这里定义你自己的结构体和变量
  */
int myflag;
int max_x, max_y, max_k;

/**
 * 你可以在这里初始化你的AI
 */
void initAI(int me) {}

int evaluate(int flag) {
	int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	int score = 0;
	for (int k = 0; k < 8; k++) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (board[i][j] != flag) {
					continue;
				}
				score += 100;
			}
		}
	}
	return score;
}

int alphabeta(int depth, int alpha, int beta, int flag) {
	int other_flag = 3 - flag;
	int new_x, new_y;
	if (depth == 0) {
		return evaluate(flag);
	}
	int cur_board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			cur_board[i][j] = board[i][j];
		}
	}
	if (myflag==flag) {
		for (int di = 0; di< 8; di++) {
			for (int x = 0; x< BOARD_SIZE; x++) {
				for (int y = 0; y < BOARD_SIZE; y++) {
					if (board[x][y] != flag) {
						continue;
					}
					new_x = x + DIR[di][0];
					new_y = y + DIR[di][1];
					if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY) {
						//移动棋子
						board[x][y] = EMPTY;
						board[new_x][new_y] = flag;
						int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
						for (int i = 0; i < 4; i++) {
							int x1 = new_x + intervention_dir[i][0];
							int y1 = new_y + intervention_dir[i][1];
							int x2 = new_x - intervention_dir[i][0];
							int y2 = new_y - intervention_dir[i][1];
							if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == other_flag && board[x2][y2] == other_flag){
								board[x1][y1] = flag;
								board[x2][y2] = flag;
							}
						}
						int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
						for (int i = 0; i < 8; i++) {
							int x1 = new_x + custodian_dir[i][0];
							int y1 = new_y + custodian_dir[i][1];
							int x2 = new_x + custodian_dir[i][0] * 2;
							int y2 = new_y + custodian_dir[i][1] * 2;
							if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == flag && board[x1][y1] == other_flag) {
								board[x1][y1] = flag;
							}
						}
						

						int now_score = alphabeta(depth-1,alpha,beta,other_flag);

						//取消移动影响
						for (int i = 0; i < BOARD_SIZE; i++) {
							for (int j = 0; j < BOARD_SIZE; j++) {
								board[i][j] = cur_board[i][j];
							}
						}
						if (now_score > alpha) {
							alpha = now_score;
						}
						if (alpha > beta) {
							return alpha;
						}
					}
				}
			}
		}
		return alpha;
	}
	else {
		for (int di = 0; di < 8; di++) {
			for (int x = 0; x < BOARD_SIZE; x++) {
				for (int y = 0; y < BOARD_SIZE; y++) {
					if (board[x][y] != other_flag) {
						continue;
					}
					new_x = x + DIR[di][0];
					new_y = y + DIR[di][1];

					if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY) {
						//移动棋子
						board[x][y] = EMPTY;
						board[new_x][new_y] = other_flag;
						int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
						for (int i = 0; i < 4; i++) {
							int x1 = new_x + intervention_dir[i][0];
							int y1 = new_y + intervention_dir[i][1];
							int x2 = new_x - intervention_dir[i][0];
							int y2 = new_y - intervention_dir[i][1];
							if (isInBound(x1, y1) && isInBound(x2, y2) && board[x1][y1] == flag && board[x2][y2] == flag) {
								board[x1][y1] = other_flag;
								board[x2][y2] = other_flag;
							}
						}
						int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
						for (int i = 0; i < 8; i++) {
							int x1 = new_x + custodian_dir[i][0];
							int y1 = new_y + custodian_dir[i][1];
							int x2 = new_x + custodian_dir[i][0] * 2;
							int y2 = new_y + custodian_dir[i][1] * 2;
							if (isInBound(x1, y1) && isInBound(x2, y2) && board[x2][y2] == other_flag && board[x1][y1] == flag) {
								board[x1][y1] = other_flag;

							}
						}

						int now_score = alphabeta(depth -1, alpha, beta, other_flag);

						//取消移动影响
						for (int i = 0; i < BOARD_SIZE; i++) {
							for (int j = 0; j < BOARD_SIZE; j++) {
								board[i][j] = cur_board[i][j];
							}
						}

						if (now_score <beta) {
							beta = now_score;
						}
						if (alpha >= beta) {
							return beta;
						}
					}
				}
			}
		}
		return beta;
	}

}
struct Command tomove(char board[BOARD_SIZE][BOARD_SIZE]) {
	char now_board[BOARD_SIZE][BOARD_SIZE];
	int m_score, cur_score;
	if (myflag == 1) {
		m_score = -10000;
	}
	else {
		m_score = 10000;
	}
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] != myflag)
				continue;

		}
	}

}
/**
 * 轮到你落子。
 * 棋盘上0表示空白，1表示黑棋，2表示白旗
 * me表示你所代表的棋子(1或2)
 * 你需要返回一个结构体Command，在x属性和y属性填上你想要移动的棋子的位置，option填上你想要移动的方向。
 */
struct Command aiTurn(const char board[BOARD_SIZE][BOARD_SIZE], int flag) {
	struct Command preferedPos = { 0,0,0 };
	myflag = flag;
	int first = 1;
	if (flag == 1 && first == 1) {
		struct Command preferedPos = { 9,7,4 };
		first++;
	}
	else {
		struct Command preferedPos = tomove(board);
	}
	return preferedPos;
}

/**
 * 你的代码结束
 */