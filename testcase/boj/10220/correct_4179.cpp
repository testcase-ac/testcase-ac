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

vector<int> arr, occ;
int n, ans;
void dfs(int s1, int s2, int i) {
	if(i == n) {
		rep(j, n) {
			if(arr[j] != occ[j])
				return;
		}
		ans++;
		return;
	}
	rep(j, n) {
		if(s1+j<=n && s2+i*j<=n) {
			arr[i] = j;
			occ[j]++;
			dfs(s1+j, s2+i*j, i+1);
			occ[j]--;
		}
	}
}

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		cin >> n;
		/*
		occ = vector<int>(n);
		arr = vector<int>(n);
		ans = 0;
		dfs(0,0,0);
		cout << ans << '\n';
		*/
		if(n <= 3 || n == 6) cout << "0\n";
		else if(n == 4) cout << "2\n";
		else cout << "1\n";
	}
}
