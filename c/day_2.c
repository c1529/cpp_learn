#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
bool play_game(void);
int roll_dice(void);//实现摇色子
int main() {
	srand(time(NULL));//设置随机种子，必须放在main里，防止程序过快导致每次随机数都是一样的
	int win_num = 0, losess_num = 0;
	char is_again;
	do {
		bool result = play_game();//play_game是游戏内容
		if (result) {
			win_num++;
		}else{
			losess_num++;
		}
		printf("\nPlay again?");//询问是否继续玩
		is_again = getchar();
		getchar();//消灭y后面的换行符
	} while (is_again == 'y' || is_again == 'Y');
	printf("\nWin:%d Losses:%d", win_num, losess_num);
	return 0;
}
int roll_dice(void) {
	int r1 = rand() % 6 + 1;
	int r2 = rand() % 6 + 1;
	return r1 + r2;
}
//具体游戏实现方法
bool play_game(void) {
	int total_points = roll_dice();
	if (total_points == 7 || total_points == 11) {
		printf("You roll:%d\n", total_points);
		printf("You Win!");
		return true;
	}
	else if (total_points==2|| total_points==3|| total_points==12) {
		printf("You roll:%d\n", total_points);
		printf("You Lose!");
		return false;
	}
	else {
		int goal_points = total_points;
		printf("You points is %d\n", goal_points);
		for (;;) {//无限摇骰子
			total_points = roll_dice();
				if (total_points == 7) {
					printf("You roll:%d\n", total_points);
					printf("You Lose!");
					return false;
				}
				if (total_points == goal_points) {
					printf("You roll:%d\n", total_points);
					printf("You Win!");
					return true;
				}
		}
	}
}
