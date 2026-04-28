#include <bits/stdc++.h>
using namespace std;

int par[10005];
vector<int> h[105];
int cp;

int getp(int t)
{
	return par[t] == t ? t : par[t] = getp(par[t]);
}

void mer(int a, int b)
{
	a = getp(a); b = getp(b);
	if (a == b) return;
	--cp; par[a] = b;
}

int main()
{
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n * n; i++)
	{
		int x;
		scanf("%d",&x);
		h[x].push_back(i);
	}
	
	int ans = 0;
	
	for (int i = 100; i >= 1; i--)
	{
		for (int t : h[i])
		{
			par[t] = t;
			++cp;
			if (t % n != 1 && par[t-1]) mer(t-1, t);
			if (t % n && par[t+1]) mer(t+1, t);
			if (t + n <= n * n && par[t+n]) mer(t+n, t);
			if (t >= n+1 && par[t-n]) mer(t-n, t);
		}
		
		ans = max(ans, cp);
	}
	
	printf("%d\n", ans);
}

// https://www.acmicpc.net/source/15511469
