#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MOD 9901
#define MAXN 100000
int arr[MAXN+1][3];

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	arr[0][0] = 1;
	for(int i=1; i<=n; i++) {
		arr[i][0] = (arr[i-1][0] + arr[i-1][1] + arr[i-1][2]) % MOD;
		arr[i][1] = (arr[i-1][0] + arr[i-1][2]) % MOD;
		arr[i][2] = (arr[i-1][0] + arr[i-1][1]) % MOD;
	}
	cout << ((arr[n][0] + arr[n][1] + arr[n][2]) % MOD);
}
