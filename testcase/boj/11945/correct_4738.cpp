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
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	char arr[n][m];
	string s;
	rep(i, n) {
		cin >> s;
		rep(j, m)
			arr[i][j] = s[j];
	}
	rep(i, n) {
		for(int j=m-1;j>=0;j--)
			cout << arr[i][j];
		cout << '\n';
	}
}
