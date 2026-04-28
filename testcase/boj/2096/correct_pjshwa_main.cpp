#include <cstdio>

// memory
// global variable?

int max(int a, int b){
	return a > b ? a : b;
}

int min(int a, int b){
	return a < b ? a : b;
}

int min_rolldown(int (*a)[3], int size){

	int a_array[3];
	int height = 0;

	a_array[0] = a[0][0];
	a_array[1] = a[0][1];
	a_array[2] = a[0][2];

	int t1, t2, t3;

	while(height != size - 1){
		height++;
		t1 = a[height][0] + min(a_array[0], a_array[1]);
		t2 = a[height][1] + min(min(a_array[0], a_array[1]), a_array[2]);
		t3 = a[height][2] + min(a_array[2], a_array[1]);
		a_array[0] = t1;
		a_array[1] = t2;
		a_array[2] = t3;
	}

	return min(min(a_array[0], a_array[1]), a_array[2]);
}

int max_rolldown(int (*a)[3], int size){

	int a_array[3];
	int height = 0;

	a_array[0] = a[0][0];
	a_array[1] = a[0][1];
	a_array[2] = a[0][2];

	int t1, t2, t3;

	while(height != size - 1){
		height++;
		t1 = a[height][0] + max(a_array[0], a_array[1]);
		t2 = a[height][1] + max(max(a_array[0], a_array[1]), a_array[2]);
		t3 = a[height][2] + max(a_array[2], a_array[1]);
		a_array[0] = t1;
		a_array[1] = t2;
		a_array[2] = t3;
	}

	return max(max(a_array[0], a_array[1]), a_array[2]);
}

int main(){
	int n;
	scanf("%d", &n);

	// int dp[n][3];
	int a[n][3];

	for(int i = 0; i < n; i++){
		for(int j = 0; j < 3; j++){
			scanf("%d", &a[i][j]);
		}
	}

	// dp_array_print(dp, n);
	printf("%d %d\n", max_rolldown(a, n), min_rolldown(a, n));
}