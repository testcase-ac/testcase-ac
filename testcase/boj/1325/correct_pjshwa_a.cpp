#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

char buf[1100100];
inline int ri()
{
	static int i = 0;
	int r = buf[i++] - '0';
	while (buf[i] >= '0')
		r = (r * 10) + buf[i++] - '0';
	return ++i, r;
}

char buf2[50000];
int idx;

inline void wi(int x)
{
	char s[6];
	int i = 0;
	do {
		s[i++] = x % 10 + '0';
		x /= 10;
	} while (x);
	for (i--; i >= 0; i--)
		buf2[idx++] = s[i];
	buf2[idx++] = ' ';
}

vector<short> adj[10001], radj[10001];
vector<short> cadj[10001];
vector<short> g[10001];
short in[10001];
char v[10001];
bool v2[10001];
ull s[10001][157];

short ans[10001];

short fin[10001];
int t;

void dfs(int i)
{
	v[i] = 1;
	for (int x : adj[i])
		if (v[x] != 1)
			dfs(x);
	fin[t++] = i;
}

void rdfs(int i, vector<short>& ret)
{
	ret.push_back(i);
	v[i] = 2;
	for (int x : radj[i])
		if (v[x] != 2)
			rdfs(x, ret);
}

void f(int i)
{
	v2[i] = true;
	for (int x : cadj[i])
	{
		if (!v2[x])
			f(x);
		for (int j = 0; j < 157; j++)
			s[i][j] |= s[x][j];
	}
	for (int j = 0; j < 157; j++)
		ans[i] += __builtin_popcountll(s[i][j]);
}

int ans2[10001];

int main()
{
	fread(buf, 1, sizeof buf, stdin);

	int n, m, i;
	n = ri();
	m = ri();
	for (i = 0; i < m; i++)
	{
		int a, b;
		a = ri();
		b = ri();
		adj[b].push_back(a);
		radj[a].push_back(b);
	}

	for (i = 1; i <= n; i++)
		if (v[i] != 1)
			dfs(i);

	int cnt = 0;
	for (t--; t >= 0; t--)
	{
		int x = fin[t];
		if (v[x] != 2)
		{
			rdfs(x, g[cnt]);

			for (int z : g[cnt])
			{
				s[cnt][z >> 6] |= (1ull << (z & 63));
				in[z] = cnt;
			}
			cnt++;
		}
	}
	for (i = 0; i < cnt; i++)
		for (int x : g[i])
			for (int y : adj[x])
				cadj[i].push_back(in[y]);
	int mx = 0;
	for (i = 0; i < cnt; i++)
	{
		if (!v2[i])
			f(i);
		if (ans[i] > mx)
			mx = ans[i];
	}

	int sdf = 0;
	for (i = 0; i < cnt; i++)
		if (ans[i] == mx)
			for (int x : g[i])
				ans2[sdf++] = x;
	sort(ans2, ans2 + sdf);
	for (i = 0; i < sdf; i++)
		wi(ans2[i]);
	fwrite(buf2, 1, idx, stdout);
}

// djm03178 - https://www.acmicpc.net/source/19008325
