#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 6//  设置棋盘最大尺寸
int Exa(char board[][MAXSIZE], int arrput[][MAXSIZE], char level)//计算步数
{
	int rowd, cold, row, col, x, y = 0;
	int step = 0;	
	char foe;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	char player = -1 * foe;
	for (row = 0; row < MAXSIZE; row++)
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			arrput[row][col] = 0;
		}
	}
	for (row = 0; row < MAXSIZE; row++)
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			if (board[row][col] != 0)//找到二维数组中值为1的元素
				continue;
			for (rowd = -1; rowd <= 1; rowd++)
				for (cold = -1; cold <= 1; cold++)
				{
					//判断是否越界
					if (row + rowd < 0 || row + rowd >= MAXSIZE|| col + cold < 0 || col + cold >= MAXSIZE|| (rowd == 0 && cold == 0))
					{
						continue;
					}
					if (board[row + rowd][col + cold] == foe)
					{
						x = row + rowd;
						y = col + cold;
						while (1)
						{
							x += rowd;
							y += cold;
							if (x < 0 || x >= MAXSIZE || y < 0 || y >= MAXSIZE)
							{
								break;
							}
							if (board[x][y] == 0)
							{
								break;
							}
							if (board[x][y] == player)
							{
								arrput[row][col] = 1;
								step++;
								break;
							}
						}
					}
				}
		}
	}
	return step;
}
void Show(char board[][MAXSIZE])//显示棋盘
{
	int row, col;
	printf("\n   ");
	for (col = 0; col < MAXSIZE; col++)//显示 棋盘横向标识
	{
		printf("%c   ", col + 'a');
	}
	for (row = 0; row < MAXSIZE; row++)
	{
		printf("\n ");
		for (col = 0; col < MAXSIZE; col++)
		{
			printf("+---");
			if (col == (MAXSIZE - 1))
				printf("+\n");
		}
		printf("%c", row + '1');
		for (col = 0; col < MAXSIZE; col++)
		{
			if (board[row][col] == 1)//根据数组中的值显示相应的标记
				printf("|╳  ");
			else if (board[row][col] == -1)
				printf("|○ ");
			else
			{
				printf("|   ");
			}
			if (col == (MAXSIZE - 1))
				printf("|   ");
		}
		if (row == (MAXSIZE - 1))
		{
			printf("\n ");
			for (col = 0; col < MAXSIZE; col++)//显示分隔符
			{
				printf("+---");
				if (col == (MAXSIZE - 1))
					printf("+\n");
			}
		}
	}
}
void Print(char board[][MAXSIZE], int row, int col, char level) //更新棋盘
{
	int rowd = 0, cold = 0, x = 0, y = 0;
	char foe;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	char player = -1 * foe;
	board[row][col] = player;
	for (rowd = -1; rowd <= 1; rowd++)
	{
		for (cold = -1; cold <= 1; cold++)
		{
			if (row + rowd < 0 || row + rowd >= MAXSIZE || col + cold < 0|| col + cold >= MAXSIZE || (rowd == 0 && cold == 0))//判断是否越界
			{
				continue;
			}
			if (board[row + rowd][col + cold] == foe)
			{
				x = row + rowd;
				y = col + cold;
				while (1)
				{
					x += rowd;
					y += cold;
					if (x < 0 || x >= MAXSIZE || y < 0 || y >= MAXSIZE)//判断越界
					{
						break;
					}
					if (board[x][y] == 0)
					{
						break;
					}
					if (board[x][y] == player)
					{
						while (board[x -= rowd][y -= cold] == foe)//找到当前的位置
						{
							board[x][y] = player;
						}
						break;
					}
				}
			}
		}
	}
}
int CalSore(char board[][MAXSIZE], char level)//计算成绩
{
	int score = 0;
	int row, col;
	char foe ;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	char player = -1 * foe;
	for (row = 0; row < MAXSIZE; row++)
		for (col = 0; col < MAXSIZE; col++)
		{
			score = score - (board[row][col] == foe);
			score = score + (board[row][col] == player);
		}
		return score;
}
void Foeplay(char board[][MAXSIZE], int arrput[][MAXSIZE], char level)
{
	int row, col, row1, col1, i, j;
	int score = 0, minscore = 100;
	char board1[MAXSIZE][MAXSIZE];
	int arrput1[MAXSIZE][MAXSIZE];
	char foe;
	if (level == 1)
		foe = -1;
	else
		foe = 1;
	for (row = 0; row < MAXSIZE; row++)
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			if (arrput[row][col] == 0)
			{
				continue;
			}
			for (i = 0; i < MAXSIZE; i++)
			{
				for (j = 0; j < MAXSIZE; j++)
				{
					board1[i][j] = board[i][j];
				}
			}
			Print(board1, row, col, level);
			Exa(board1, arrput1, foe);
			if ((row == 0 && col == 0) || (row == 0 && col == MAXSIZE - 1 || row == MAXSIZE - 1 && col == 0 || row == MAXSIZE - 1 && col == MAXSIZE - 1))
			{
				minscore = score;
				row1 = row;
				col1 = col;
			}
			else if (row == 0 || row == MAXSIZE - 1 || col == 0 || col == MAXSIZE - 1)
			{
				minscore = score;
				row1 = row;
				col1 = col;
			}
			else if (score < minscore)
			{
				minscore = score;
				row1 = row;
				col1 = col;
			}
		}
	}
	Print(board, row1, col1, level);
}
int main()
{
	char board[MAXSIZE][MAXSIZE];
	int arrput[MAXSIZE][MAXSIZE] = { 0 };
	int row, col, x, y;
	int count = 4;
	int level = 1;		
	int cross = 0;
	int score[2];
	char ok;
	char input[100];
	int order = 0;
	printf("=============================翻转棋=============================\n");
	printf("REVERSI\n");
	printf("You will be white - (O)\nI will be black - (X).\nok a square for your move by typing a digit for the row\nand a letter for the column with no spaces between.\nGood luck! Press Enter to start.\n");
	scanf("%c", &ok);
	for (row = 0; row < MAXSIZE; row++)//设置棋盘的初始值
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			board[row][col] = 0;
		}
	}
	board[MAXSIZE / 2 - 1][MAXSIZE / 2 - 1] = board[MAXSIZE / 2][MAXSIZE / 2] = -1;	//初始化参数
	board[MAXSIZE / 2 - 1][MAXSIZE / 2] = board[MAXSIZE / 2][MAXSIZE / 2 - 1] = 1;	
	printf("\nInitial:\n");
	Show(board);//显示棋盘
	int i = 0;
	for (i = count; count < (MAXSIZE*MAXSIZE) && cross < 2;)
	{
		if (level == 1)
		{
			level = 0;
			if (Exa(board, arrput, 2))
			{
				while (1)
				{
					printf("Please enter your move (row column- no space):");
					scanf("%s", input);
					x = input[0] - '0';//根据用户输入的位置将其转化成二维数组的下标
					y = input[1];
					x--;
					if (y >= 'a')
					{
						y = y - 'a' + 1;
					}
					else
					{
						y = y - 'A' + 1;
					}
					y--;//将用户输入的列标转换成二维数组的列下标
					if (x >= 0 && y >= 0 && x < MAXSIZE && y < MAXSIZE && arrput[x][y])//判断输入是否正确
					{
						Print(board, x, y, 2);
						count++;
						break;
					}
					else
					{
						printf("Not a valid move, try again.\n");
					}
				}
				Show(board);//根据用户输入的位置进行更新棋盘并显示
			}
			else if (++cross < 2)
			{
				printf("NO MOVE,AI GO.\n");
			}
			else
			{
				printf("BOTH NO MOVE, GAME OVER.\n");
			}
		}
		else
		{
			level = 1;
			if (Exa(board, arrput, 1))
			{
				cross = 0;
				Foeplay(board, arrput, 1);
				count++;
				Show(board);
			}
			else
			{
				if (++cross < 2)
				{
					printf("NO MOVE, nowplay GO.\n");
				}
				else
				{
					printf("BOTH NO MOVE, GAME OVER.");
				}
			}
		}
	} 
	Show(board);
	score[0] = score[1] = 0;
	for (row = 0; row < MAXSIZE; row++)//开始计算分数
	{
		for (col = 0; col < MAXSIZE; col++)
		{
			score[0] = score[0] + (board[row][col] == -1);
			score[1] = score[1] + (board[row][col] == 1);
		}
	}
	printf("Final score:\n");
	printf("AI:%d\nnowplay:%d\n", score[1], score[0]);
	scanf("%c", &ok);
	return 0;
}