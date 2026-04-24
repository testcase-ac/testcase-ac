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

vector<pair<int,int>> arr(4);

bool ok(int i, int i1, int i2) {
	ll y1 = arr[i].second - arr[i1].second, x1 = arr[i].first - arr[i1].first;
	ll y2 = arr[i].second - arr[i2].second, x2 = arr[i].first - arr[i2].first;
	return x1 * x2 + y1 * y2 == 0;
}

ll sq(int i) {
	return (ll)i*(ll)i;
}
ll dist(int i, int j) {
	return sq(arr[i].second - arr[j].second) + sq(arr[i].first - arr[j].first);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		rep(i, 4) cin >> arr[i].first >> arr[i].second;
		vector<int> p = {1,2,3};
		do {
			if(ok(0, p[0], p[1]) && ok(p[0], 0, p[2]) && ok(p[1], 0, p[2]) && dist(0,p[0])==dist(0, p[1])) {
				cout << "1\n";
				goto next;
			}
		} while(next_permutation(p.begin(), p.end()));
		cout << "0\n";
		next:;
	}
}
