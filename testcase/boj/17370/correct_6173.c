#include <stdio.h>

int seen[200][200];
int n;

int dfs(int x, int y, int dir, int dist) {
	if (seen[x][y]) {
		if (dist == n) return 1;
		return 0;
	} else if (dist == n) return 0;

	seen[x][y] = 1;

	int cnt = 0;
	if (y%2 == 0) {
		switch (dir) {
		case 0:
			cnt += dfs(x-1, y-1, 1, dist+1);
			cnt += dfs(x+1, y-1, 2, dist+1);
			break;
		case 1:
			cnt += dfs(x, y+1, 0, dist+1);
			cnt += dfs(x+1, y-1, 2, dist+1);
			break;
		case 2:
			cnt += dfs(x, y+1, 0, dist+1);
			cnt += dfs(x-1, y-1, 1, dist+1);
			break;
		}
	} else {
		switch (dir) {
		case 0:
			cnt += dfs(x+1, y+1, 1, dist+1);
			cnt += dfs(x-1, y+1, 2, dist+1);
			break;
		case 1:
			cnt += dfs(x, y-1, 0, dist+1);
			cnt += dfs(x-1, y+1, 2, dist+1);
			break;
		case 2:
			cnt += dfs(x, y-1, 0, dist+1);
			cnt += dfs(x+1, y+1, 1, dist+1);
			break;
		}
	}

	seen[x][y] = 0;

	return cnt;
}

int main(void) {
	scanf("%d", &n);
	seen[100][100] = 1;
	printf("%d\n", dfs(100, 101, 0, 0));
}
