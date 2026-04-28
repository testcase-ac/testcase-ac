#include <cstdio>

int main(){
	int n;
	scanf("%d", &n);
	if(n == 1){
		printf("1");
		return 0;
	}
	int a[n];
	int streak = 1;
	int max_streak = 1;
	scanf("%d", &a[0]);
	for(int i = 1; i < n; i++){
		scanf("%d", &a[i]);
		if(a[i-1] < a[i]){
			if(max_streak < streak) max_streak = streak;
			streak = 1;
		}
		else {
			streak++;
		}
	}
	if(max_streak < streak) max_streak = streak;
	streak = 1;
	for(int i = 1; i < n; i++){
		if(a[i-1] > a[i]){
			if(max_streak < streak) max_streak = streak;
			streak = 1;
		}
		else {
			streak++;
		}
	}
	if(max_streak < streak) max_streak = streak;
	printf("%d", max_streak);
	return 0;
}