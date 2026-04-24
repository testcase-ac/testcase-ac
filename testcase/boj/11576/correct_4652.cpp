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
	int a, b, m;
	cin >> a >> b >> m;
	int num = 0;
	while(m--) {
		int t;
		cin >> t;
		num *= a;
		num += t;
	}
	vector<int> ans;
	while(num) {
		ans.push_back(num % b);
		num /= b;
	}
	reverse(ans.begin(), ans.end());
	for(int t: ans) cout << t << ' ';

}
