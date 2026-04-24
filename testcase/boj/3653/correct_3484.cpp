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

using namespace std;
inline int lsb(int i){return i & (-i);}

void update(vector<int> &bit, int i, int v) {
	while(i < sz(bit)) {
		bit[i] += v;
		i += lsb(i);
	}
}
int query(vector<int> &bit, int i) {
	int ret = 0;
	while(i) {
		ret += bit[i];
		i -= lsb(i);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		vector<int> bit(n+m+1), where(n+1);
		int next = m;
		for(int i=m+1; i<=n+m; i++) {
			update(bit, i, 1);
			where[i-m] = i;
		}
		while(m--) {
			int i;
			cin >> i;
			update(bit, where[i], -1);
			cout << query(bit, where[i]) << ' ';
			update(bit, next, 1);
			where[i] = next;
			next--;
		}
		cout << '\n';
	}
}
