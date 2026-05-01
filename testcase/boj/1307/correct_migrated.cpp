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
#include<numeric>
#include<deque>
using namespace std;
template <typename T1, typename T2>
istream& operator>>(istream& i, pair<T1, T2>& p)
{
	i >> p.first >> p.second;
	return i;
}
static istream& operator>>(istream& i, bool& b)
{
	int t; i >> t; b = (t != 0);
	return i;
}

vector<vector<int>>odd(int n)
{
	vector<vector<int>> res(n, vector<int>(n));
	int x = 0;
	int y = n / 2;
	for (int i = 1; i <= n * n; i++)
	{
		res[x][y] = i;
		int nx = (x + n - 1) % n;
		int ny = (y + 1) % n;
		if (res[nx][ny]) x = (x + 1) % n;
		else x = nx, y = ny;
	}
	return res;
}
vector<vector<int>>even_even(int n)
{
	vector<vector<int>> res(n, vector<int>(n));
	int cnt = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			res[i][j] = cnt++;
		}
	}
	for (int i = n / 4; i < n / 4 * 3; i++)
	{
		for (int j = 0; j < n / 4; j++)
		{
			swap(res[i][j], res[n - i - 1][n - j - 1]);
			swap(res[j][i], res[n - j - 1][n - i - 1]);
		}
	}
	return res;
}
vector<vector<int>>even_odd(int n)
{
	vector<vector<int>> res(n, vector<int>(n));
	vector<vector<int>> half = odd(n / 2);
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n / 4; j++)
		{
			if (i == n / 4) res[i][j + 1] = n * n * 3 / 4;
			else res[i][j] = n * n * 3 / 4;
		}
		for (int j = n / 4; j < n / 2; j++)
		{
			if (i == n / 4) res[i + n / 2][j + 1] = n * n * 3 / 4;
			else res[i + n / 2][j] = n * n * 3 / 4;
		}
	}
	res[n * 3 / 4][0] = n * n * 3 / 4;
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = n / 2; j < n * 3 / 4 + 2; j++)
		{
			res[i][j] = n * n / 2;
			res[i + n / 2][j] = n * n / 4;
		}
		for (int j = n * 3 / 4 + 2; j < n; j++)
		{
			res[i][j] = n * n / 4;
			res[i + n / 2][j] = n * n / 2;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			res[i][j] += half[i % (n / 2)][j % (n / 2)];
		}
	}
	return res;
}
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>>a;
	switch (n % 4)
	{
	case 1:
	case 3:
		a = odd(n); break;
	case 0:
		a = even_even(n); break;
	case 2:
		a = even_odd(n); break;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
	return 0;
}
