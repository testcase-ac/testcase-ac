#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int L, P, ans;
	cin >> L >> P;
	ans = L * P;
	rep(i, 5) {
		int inp;
		cin >> inp;
		cout << (inp - ans) << ' ';
	}

}
