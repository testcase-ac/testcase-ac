#include <cstdio>

int n, w;
int dp[10000][3];
int a[10000][2];

const int MAX_INT = 2000000000;

void dp_init(){
	for(int j = 0; j < n; j++){
		for(int k = 0; k < 3; k++){
			dp[j][k] = -1;
		}
	}
}

int min(int x, int y){
	return x > y ? y : x;
}

// in circle it is, nothing wrong with the algorithm ... maybe?
int opt_clock(int index, int dir, int side_vacant){
	if(index < 0) return 0;
	if(dp[index][dir] == -1){

		if(index == 1){
			int result;
			if(side_vacant == 0) { // upside is vacant
				if (dir == 2) result = 2;
				else if (dir == 1) {
					if(a[index][0] + a[index][1] <= w) result = 2;
					else {
						if(a[index][0] + a[index-1][0] <= w) result = 2;
						else result = 3;
					}
				}
				else {
					if(a[index][0] + a[index-1][0] <= w) result = 1;
					else result = 2;
				}
			}
			else {
				if (dir == 0) result = 2;
				else if (dir == 1) {
					if(a[index][0] + a[index][1] <= w) result = 2;
					else {
						if(a[index][1] + a[index-1][1] <= w) result = 2;
						else result = 3;
					}
				}
				else {
					if(a[index][1] + a[index-1][1] <= w) result = 1;
					else result = 2;
				}
			}
			dp[index][dir] = result;
		}
		else {
			int result = MAX_INT;
			if (dir == 0){ // only upside is vacant
				if(a[index][0] + a[index-1][0] <= w) result = opt_clock(index - 1, 2, side_vacant) + 1;
				result = min(result, opt_clock(index - 1, 1, side_vacant) + 1);
			}
			else if (dir == 1){ // both
				if(a[index][0] + a[index][1] <= w) {
					result = opt_clock(index - 1, 1, side_vacant) + 1; // vertical one
				}
				if(a[index][0] + a[index-1][0] <= w && a[index][1] + a[index-1][1] <= w){
					result = min(result, opt_clock(index - 2, 1,side_vacant) + 2);
				}
				result = min(min(result, opt_clock(index, 2, side_vacant) + 1), opt_clock(index, 0, side_vacant) + 1); // select each and see
			}
			else { // only downside is vacant
				if(a[index][1] + a[index-1][1] <= w) result = opt_clock(index - 1, 0, side_vacant) + 1;
				result = min(result, opt_clock(index - 1, 1, side_vacant) + 1);
			}
			dp[index][dir] = result;
		}
	}
	return dp[index][dir];
}

int opt(int index, int dir, int terminate_index){
	if(index < 0) return 0;
	if(dp[index][dir] == -1){
		if(index == terminate_index){
			int result;
			if(dir != 1) result = 1;
			else {
				if(a[index][0] + a[index][1] <= w) result = 1;
				else result = 2;
			}
			dp[index][dir] = result;
		}
		else {
			int result = MAX_INT;
			if (dir == 0){ // only upside is vacant
				if(a[index][0] + a[index-1][0] <= w) result = opt(index - 1, 2, terminate_index) + 1;
				result = min(result, opt(index - 1, 1, terminate_index) + 1);
			}
			else if (dir == 1){ // both
				if(a[index][0] + a[index][1] <= w) {
					result = opt(index - 1, 1,terminate_index) + 1; // vertical one
				}
				if(a[index][0] + a[index-1][0] <= w && a[index][1] + a[index-1][1] <= w){
					result = min(result, opt(index - 2, 1,terminate_index) + 2);
				}
				result = min(min(result, opt(index, 2,terminate_index) + 1), opt(index, 0,terminate_index) + 1); // select each and see
			}
			else { // only downside is vacant
				if(a[index][1] + a[index-1][1] <= w) result = opt(index - 1, 0,terminate_index) + 1;
				result = min(result, opt(index - 1, 1,terminate_index) + 1);
			}
			dp[index][dir] = result;
		}
	}
	return dp[index][dir];
}


int main(){
	int t;
	scanf("%d", &t);
	for(int i = 0; i < t; i++){
		scanf("%d%d", &n, &w);
		dp_init();
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < n; k++){
				scanf("%d", &a[k][j]);
			}
		}

		int final_result = opt(n-1, 1, 0);
		if(a[n-1][0] + a[0][0] <= w && a[n-1][1] + a[0][1] <= w) {
			dp_init();
			final_result = min(final_result, opt(n-2, 1, 1) + 2);
			dp_init();
			final_result = min(final_result, opt_clock(n-1, 2, 1) + 1);
			dp_init();
			final_result = min(final_result, opt_clock(n-1, 0, 0) + 1);
		}
		else {
			if(a[n-1][0] + a[0][0] <= w) {
				dp_init();
				final_result = min(final_result, opt_clock(n-1, 2, 1) + 1);
			}
			else if (a[n-1][1] + a[0][1] <= w){
				dp_init();
				final_result = min(final_result, opt_clock(n-1, 0, 0) + 1);
			}
		}
		printf("%d\n", final_result);
		
	}
}