#include <cstdio>

int max(int x, int y){
	if(x > y) return x;
	else return y;
}

int main(){
	int n;
	scanf("%d", &n);
	int triangle[n][n];
	scanf("%d", &triangle[0][0]);
	for(int i = 1; i < n; i++){
		for(int j = 0; j < i + 1; j++){
			int temp;
			scanf("%d", &temp);
			if(j == 0) triangle[i][j] = triangle[i-1][j] + temp;
			else if(j == i) triangle[i][j] = triangle[i-1][j-1] + temp;
			else{
				triangle[i][j] = max(triangle[i-1][j-1], triangle[i-1][j]) + temp;
			}
		}
	}
	int max_sum = 0;
	for(int i = 0; i < n; i++){
		if(max_sum < triangle[n-1][i]) max_sum = triangle[n-1][i];
	}
	printf("%d\n", max_sum);
}