#include <stdio.h>

int main(){
	int a[10], b[10], wins[10];
	for(int i = 0; i < 10; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < 10; i++){
		scanf("%d", &b[i]);
	}
	int a_points = 0, b_points = 0;
	for(int i = 0; i < 10; i++){
		if(a[i] > b[i]){
			a_points += 3;
			wins[i] = 0;
		}
		else if (a[i] == b[i]){
			a_points += 1;
			b_points += 1;
			wins[i] = 2;
		}
		else{
			b_points += 3;
			wins[i] = 1;
		}
	}
	char winner;
	if(a_points > b_points) winner = 'A';
	else if (a_points < b_points) winner = 'B';
	else {
		int flag = 0;
		for(int i = 0; i < 10; i++){
			if(wins[9-i] != 2){
				if (wins[9-i] == 1) winner = 'B';
				else winner = 'A';
				flag = 1;
				break;
			}
		}
		if (!flag) winner = 'D';
	}
	printf("%d %d\n%c", a_points, b_points, winner);
}