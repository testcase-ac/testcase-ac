#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#include<stack>
#include<vector>
#include<queue>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
using namespace std;
template <typename T1, typename T2>
istream& operator>>(istream& i, pair<T1, T2>& p)
{
	i >> p.first >> p.second;
	return i;
}
int n;
int ans;
vector<int>graph[200001];
bool vs[200001];
int deg[200001];
vector<int>t;
void dfs(int nod)
{
	vs[nod] = 1;
	t.push_back(nod);
	for (int i=0;i<graph[nod].size();i++)
	{
		int next = graph[nod][i];
		if (!vs[next]) dfs(next);
	}
}
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
		deg[y]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!vs[i])
		{
			t.clear();
			dfs(i);
			if (t.size() == 1) continue;
			int cnt = 0;
			for (auto j : t)
				cnt += deg[j] >= 2;
			if (cnt >= 2)
			{
				cout << -1;
				return 0;
			}
			ans += t.size() + 1;
		}
	}
	cout << ans;
	return 0;
}
