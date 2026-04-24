#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <string>
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
#define deb(v) cout << #v << ':' << v << '\n';
#define ldb long double
using namespace std;
// 5 3 2 2 2 1
/*
5 4 3 2 1 -0
1 5 4 3 2 -4
1 2 5 4 3 -7
1 2 3 4 5 -10
3 2 1 - 0
	First number is 1 at origpos 2, relpos 2. Move it to end of the sorted list. (+2)
	Now the list is X 3 2
	First number 2 is at origpos 1, relpos 2. Move it to end of the sorted list. (+1)
	Now the list is X X 3.
*/
vector<int> bit;
int n;
inline int lsb(int i){return i&-i;}
void update(int i, int v) {
	while(i <= n) {
		bit[i] += v;
		i += lsb(i);
	}
}
int query(int i) {
	int ret = 0;
	while(i) {
		ret += bit[i];
		i -= lsb(i);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	bit.resize(n+1);
	pair<int,int> arr[n];
	rep(i,n) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
	sort(arr, arr+n);
	ll ans = 0;
	rep(i, n) {
		int orig = arr[i].second;
		ans += max(orig - i + query(n) - query(orig+1), 0);
		update(orig+1, 1);
	}
	cout << ans;
}