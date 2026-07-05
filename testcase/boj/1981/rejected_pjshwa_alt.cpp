#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n'
const int INF = 247483647;
int N;
int arr[101][101];
int visited[101][101];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
vector<int> ans;
void solution()
{
	queue<pair<pair<int, int>, pair<int,int>>> q; // {{y좌표, x좌표}, {최소, 최대}}
	q.push({ {0,0}, {arr[0][0], arr[0][0]} });
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			visited[i][j] = INF;
		}
	}
	visited[0][0] = arr[0][0] - arr[0][0];
	int idx = 0;
	while (!q.empty())
	{
		auto item = q.front();
		int y = item.first.first;
		int x = item.first.second;
		int mn = item.second.first;
		int mx = item.second.second;
		q.pop();
		
		if (y == N - 1 && x == N - 1)
		{
			ans.push_back(mx - mn);
		}
		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (nx >= 0 && ny >= 0 && ny < N && nx < N)
			{
				int tmp_mx = max(mx, arr[ny][nx]);
				int tmp_mn = min(mn, arr[ny][nx]);
				if (visited[ny][nx] > tmp_mx - tmp_mn)
				{
					visited[ny][nx] = tmp_mx - tmp_mn;
					q.push({ {ny,nx}, {tmp_mn, tmp_mx} });
					
				}
			}
		}
	}
	sort(ans.begin(), ans.end());
	cout << ans[0] << endl;
}	
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	std::cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> arr[i][j];
		}
	}
	solution();
}
