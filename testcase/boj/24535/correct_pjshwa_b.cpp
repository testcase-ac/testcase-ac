
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <tuple>
#include <string.h>
#include <math.h>
#include <random>
#include <functional>
#include <assert.h>
#include <math.h>
#define MOD ((i64)1e9 + 7)
#define all(x) (x).begin(), (x).end()
#define xx first
#define yy second

using namespace std;

template<typename T, typename Pr = less<T>>
using pq = priority_queue<T, vector<T>, Pr>;
using i64 = long long int;
using ii = pair<int, int>;
using ii64 = pair<i64, i64>;



class Mapping
{
public:
	void init(const vector<int>& raw, int base = 0)
	{
		start = base;
		arr = raw;
		sort(arr.begin(), arr.end());
		arr.erase(unique(arr.begin(), arr.end()), arr.end());
	}

	int get_idx(int k)
	{
		return start + (lower_bound(all(arr), k) - arr.begin());
	}

	int get_value(int idx)
	{
		return arr[idx - start];
	}

	int size()
	{
		return arr.size();
	}

private:
	int start;
	vector<int> arr;
};

int xcnt[505][505];
int ycnt[505][505];

int main()
{
	int n;
	scanf("%d", &n);

	vector<ii> pos(n);
	vector<int> xs;
	vector<int> ys;

	Mapping xm;
	Mapping ym;

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &pos[i].xx, &pos[i].yy);
		xs.push_back(pos[i].xx);
		ys.push_back(pos[i].yy);
	}

	xm.init(xs, 1);
	ym.init(ys, 1);

	for (int i = 0; i < n; i++)
	{
		pos[i].xx = xm.get_idx(pos[i].xx);
		pos[i].yy = ym.get_idx(pos[i].yy);
		xcnt[pos[i].xx][pos[i].yy]++;
		ycnt[pos[i].xx][pos[i].yy]++;
	}

	for (int i = 1; i <= xm.size(); i++)
	{
		for (int j = 1; j <= ym.size(); j++)
		{
			xcnt[i][j] += xcnt[i - 1][j];
			ycnt[i][j] += ycnt[i][j - 1];
		}
	}

	int ans = 0;

	for (int i = 1; i <= xm.size(); i++)
		ans = max(ans, xcnt[i][ym.size()]);

	for (int i = 1; i <= ym.size(); i++)
		ans = max(ans, ycnt[xm.size()][i]);


	for (int y1 = 1; y1 <= ym.size(); y1++)
	{
		for (int y2 = y1 + 1; y2 <= ym.size(); y2++)
		{
			int base = xcnt[xm.size()][y1] + xcnt[xm.size()][y2];

			vector<int> maxr(xm.size() + 5);

			for (int x = 1; x <= xm.size(); x++)
			{
				int rcnt = ycnt[x][y2] - ycnt[x][y1 - 1]
					- (xcnt[xm.size()][y1] - xcnt[x - 1][y1])
					- (xcnt[xm.size()][y2] - xcnt[x - 1][y2]);

				maxr[x] = rcnt;
			}

			for (int x = xm.size(); x >= 1; x--)
				maxr[x] = max(maxr[x], maxr[x + 1]);

			for (int x = 1; x <= xm.size(); x++)
			{
				int lcnt = ycnt[x][y2] - ycnt[x][y1 - 1]
					- xcnt[x][y1] - xcnt[x][y2];
				int now = base + lcnt + maxr[x + 1];
				ans = max(ans, now);
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}
