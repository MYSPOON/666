#include "ai.h"

// bool
typedef int BOOL;
#define TRUE 1
#define FALSE 0

const int DIR[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

BOOL isInBound(int x, int y) {
	return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

/**
 * YOUR CODE BEGIN
 * ��Ĵ��뿪ʼ
 */

 /**
  * You can define your own struct and variable here
  * ����������ﶨ�����Լ��Ľṹ��ͱ���
  */
int now_flag[BOARD_SIZE][BOARD_SIZE] = { 0 };
int tiao(int new_x,int new_y,int flag) {
	int score=0;
	int intervention_dir[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	for (int i = 0; i < 4; i++) {
		int x1 = new_x + intervention_dir[i][0];
		int y1 = new_y + intervention_dir[i][1];
		int x2 = new_x - intervention_dir[i][0];
		int y2 = new_y - intervention_dir[i][1];
		if (isInBound(x1, y1) && isInBound(x2, y2) && now_flag[x1][y1] ==3-flag  && now_flag[x2][y2] == 3-flag) {
			score+=100;
		}
	}

	int custodian_dir[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int i = 0; i < 8; i++) {
		int x1 = new_x + custodian_dir[i][0];
		int y1 = new_y + custodian_dir[i][1];
		int x2 = new_x + custodian_dir[i][0] * 2;
		int y2 = new_y + custodian_dir[i][1] * 2;
		if (isInBound(x1, y1) && isInBound(x2, y2) && now_flag[x2][y2] == flag && now_flag[x1][y1] == 3-flag) {
			score += 75;
		}
	}
	return score;
}

/**
 * ������������ʼ�����AI
 */
void initAI(int me) {

}

struct Command findValidPos(const char board[BOARD_SIZE][BOARD_SIZE], int flag) {
	struct Command command = { 0, 0, 0 };

	int score[8][BOARD_SIZE][BOARD_SIZE] = { 0 }, max_score = 0;
	int max_x, max_y, max_k;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			now_flag[i][j] = board[i][j];
		}
	}

	for (int k = 0; k < 8; k++) {
		const int* delta = DIR[k];
		for (int x = 0; x < BOARD_SIZE; x++) {
			for (int y = 0; y < BOARD_SIZE; y++) {
				if (board[x][y] != flag) {
					continue;
				}
				int new_x = x + delta[0];
				int new_y = y + delta[1];
				if (isInBound(new_x, new_y) && board[new_x][new_y] == EMPTY) {
					if (tiao(new_x, new_y, flag)) {
						command.x = max_x;
						command.y = max_y;
						command.option = max_k;
						return command;
					}
					else {
						max_k = k; max_x = x; max_y = y;
					}
				}
			}
		}
	}
	command.x = max_x;
	command.y = max_y;
	command.option = max_k;
	return command;
}

/**
 * �ֵ������ӡ�
 * ������0��ʾ�հף�1��ʾ���壬2��ʾ����
 * me��ʾ�������������(1��2)
 * ����Ҫ����һ���ṹ��Command����x���Ժ�y������������Ҫ�ƶ������ӵ�λ�ã�option��������Ҫ�ƶ��ķ���
 */
struct Command aiTurn(const char board[BOARD_SIZE][BOARD_SIZE], int me) {
	/*
	 * TODO��������д�����AI��
	 * ������һ��ʾ��AI����ֻ��Ѱ�ҵ�һ�����µ�λ�ý������ӡ�
	 */
	struct Command preferedPos = findValidPos(board, me);

	return preferedPos;
}

/**
 * ��Ĵ������
 */