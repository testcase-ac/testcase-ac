#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <functional>
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
#define def function
#define deb(v) cout << #v << ':' << v << '\n';
#define ldb long double
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<int> arr(n);
	rep(i, n) arr[i] = i+1;
	while(m--) {
		int i, j, k;
		cin >> i >> j >> k;
		rotate(arr.begin()+i-1, arr.begin()+k-1, arr.begin()+j);
	}
	rep(i, n) {
		cout << arr[i] << ' ';
	}
}
