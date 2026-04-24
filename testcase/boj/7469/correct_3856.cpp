#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define deb(v) cout << #v << ':' << v

using namespace std;

#define MAXN 100000
int n, m;
// Iterative segment tree implementation adapted for this solution.
// Reference: http://codeforces.com/blog/entry/18051
vector<int> st[2*MAXN];
void build() {
	for(int i=n-1;i>0; i--) {
		int j = 0, k = 0;
		vector<int> &lv = st[2*i], &rv = st[2*i+1];
		while(j < sz(lv) && k < sz(rv)) {
			if(lv[j] < rv[k])
				st[i].push_back(lv[j++]);
			else
				st[i].push_back(rv[k++]);
		}
		while(j < sz(lv))
			st[i].push_back(lv[j++]);
		while(k < sz(rv))
			st[i].push_back(rv[k++]);
	}
}

void _query(int l, int r, int mid, int &lb, int &ub) {
	// lb/ub = count numbers smaller than (or equal to) mid
	// mid would be [`lb+1`th, `ub`th]. If lb == ub then mid does not exist
	for(l += n, r += n; l < r; l /= 2, r /= 2) {
		if(l&1) {
			auto pr = equal_range(st[l].begin(), st[l].end(), mid);
			lb += pr.first - st[l].begin();
			ub += pr.second - st[l].begin();
			l++;
		}
		if(r&1) {
			r--;
			auto pr = equal_range(st[r].begin(), st[r].end(), mid);
			lb += pr.first - st[r].begin();
			ub += pr.second - st[r].begin();
		}
	}
}

int query(int i, int j, int k) {
	// return kth number within i~j segment
	int l = -MOD+7, r = MOD-7, mid;
	while(l < r) {
		mid = (l+r+1)/2;
		int lb = 0, ub = 0;
		_query(i, j, mid, lb, ub);
		if(ub < k)
			l = mid+1;
		else if(lb + 1 > k)
			r = mid-1;
		else
			return mid;
	}
	return l;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n >> m;
	for(int i=n; i<2*n; i++) {
		int t;
		cin >> t;
		st[i] = {t};
	}
	build();
	while(m--) {
		int i, j, k;
		cin >> i >> j >> k;
		cout << query(i-1, j, k) << '\n';
	}
}
