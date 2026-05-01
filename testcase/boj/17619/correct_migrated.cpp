//Please do not change anything in this solution.
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<string>
#include<cstring>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<unordered_map>
using namespace std;
typedef struct frog
{
	int x1, x2, num;
}f;
bool cmp(f a, f b)
{
	return a.x1 < b.x1;
}
int n, q;
f data1[100001];
int arr[100001];
bool ans[100001];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, q, y, endline, p = 1;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		cin >> data1[i].x1 >> data1[i].x2 >> y;
		data1[i].num = i;
	}
	sort(data1 + 1, data1 + n + 1, cmp);
	arr[data1[1].num] = p;
	endline = data1[1].x2;
	for (int i = 2; i <= n; i++)
	{
		if (data1[i].x1 <= endline)
		{
			arr[data1[i].num] = p;
			endline = max(endline, data1[i].x2);
		}
		else
		{
			p++;
			arr[data1[i].num] = p;
			endline = data1[i].x2;
		}
	}
	for (int i = 1; i <= q; i++)
	{
		int a, b;
		cin >> a >> b;
		if (arr[a] == arr[b]) ans[i] = 1;
		cout << ans[i] << '\n';
	}
	return 0;
}
