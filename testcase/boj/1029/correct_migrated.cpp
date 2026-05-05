#include <stdio.h>
#include <algorithm>
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
const int INF = 10;
int N, mem[16384][14], board[14][14], ans;
char input[15][16];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%s", input[i]);
	N--;
	for (int i = 1; i < (1 << N); i++)
	{
		for (int j = 0; j < N; j++) mem[i][j] = INF;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) board[i][j] = input[i + 1][j + 1] - '0';
	}
	for (int i = 0; i < N; i++) mem[1 << i][i] = input[0][i + 1] - '0';
	for (int i = 1; i < (1 << N); i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mem[i][j] == INF) continue;
			int temp = N + 1;
			for (int k = 0; k < N; k++)
			{
				if ((i&(1 << k)) > 0) continue;
				temp--;
				if (board[j][k] >= mem[i][j]) mem[i | (1 << k)][k] = std::min(mem[i | (1 << k)][k], board[j][k]);
			}
			ans = std::max(ans, temp);
		}
	}
	printf("%d\n", ans);
	return 0;
}
