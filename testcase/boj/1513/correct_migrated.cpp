#include<bits/stdc++.h>
using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
#define INF 1234567890
#define ll long long
#define MOD 1000007

int N, M, C;
int Y[55], X[55];
int A[55][55];
int E[55][55]; // temp
int D[55][55]; // D[s][t] : s -> t까지 다 피해서 가는 경우의 수
ll dp[55][55]; // dp[k][i] : k개 방문할건데 현재 i에 위치했을때

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin.exceptions(ios::badbit | ios::failbit);
	cin >> N >> M >> C;
	int st = 0, en = 0, new_st = 0, new_en = 0;
	for(int i=1; i<=C; i++)
	{
		cin >> Y[i] >> X[i];
		A[Y[i]][X[i]] = i;

		if (Y[i] == 1 && X[i] == 1) st = i;
		if (Y[i] == N && X[i] == M) en = i;
	}

	if (!st)
	{
		// 한 칸씩 뒤로 밀기
		for(int i=C; i>=1; i--)
		{
			Y[i+1] = Y[i];
			X[i+1] = X[i];
			A[Y[i]][X[i]]++;
		}
		if (en) en++;

		C++;
		st = 1;
		new_st = 1;
		Y[1] = 1, X[1] = 1;
		A[1][1] = 1;
	}
	if (!en)
	{
		en = ++C;
		new_en = 1;
		Y[C] = N, X[C] = M;
		A[N][M] = C;
	}

	for(int k=1; k<=C; k++)
	{
		memset(E, 0, sizeof(E));
		E[Y[k]][X[k]] = 1;
		for(int i=Y[k]; i<=N; i++)
			for(int j=X[k]; j<=M; j++)
			{
				if (A[i][j]) D[k][A[i][j]] = E[i][j];

				if (!(i == Y[k] && j == X[k]) && A[i][j]) continue;
				E[i+1][j] += E[i][j], E[i+1][j] %= MOD;
				E[i][j+1] += E[i][j], E[i][j+1] %= MOD;
			}
	}

	dp[1][en] = 1;
	for(int k=2; k<=C; k++)
		for(int i=1; i<=C; i++)
			for(int j=i+1; j<=C; j++)
			{
				dp[k][i] += dp[k-1][j] * D[i][j];
				dp[k][i] %= MOD;
			}

	for(int k=0; k<=C - new_st - new_en; k++)
		cout << dp[k + new_st + new_en][st] << " ";
	cout << "\n";
	return 0;
}
