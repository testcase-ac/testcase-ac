#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<deque>
#include<set>
#include<map>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;

#define INF 1234567890
#define ll long long
#define MOD 1'000'000'007

int N, K;
int v[100101];
ll dp[11][100101], fen[100101];

ll Sum(int idx)
{
	ll ret = 0;
	while (idx)
	{
		ret += fen[idx];
		idx &= (idx - 1);
	}
	ret %= MOD;
	return ret;
}

void Add(int idx, ll val)
{
	while (idx <= N)
	{
		fen[idx] += val;
		idx += idx & -idx;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		cin >> v[i];
		dp[1][i] = 1;
	}

	for (int k = 2; k <= K; k++)
	{
		memset(fen, 0, sizeof(fen));
		for (int i = 0; i < N; i++)
		{
			dp[k][i] = Sum(v[i] - 1);
			Add(v[i], dp[k - 1][i]);
		}
	}

	ll res = 0;
	for (int i = 0; i < N; i++)
		res += dp[K][i];
	res %= MOD;
	cout << res;
	return 0;
}
