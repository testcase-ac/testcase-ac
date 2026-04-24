#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

#define MAXN 1000
#define MOD 10007
int arr[MAXN+1][2];
/*
arr[i][0]: last two blocks are horizontal
arr[i][1]: last block is vertical
*/

int main() {
	arr[1][1] = 1;
	arr[2][0] = 1;
	arr[2][1] = 1;
	for(int i=3;i<=MAXN;i++) {
		arr[i][0] = (arr[i-2][0] + arr[i-2][1]) % MOD;
		arr[i][1] = (arr[i-1][0] + arr[i-1][1]) % MOD;
	}
	int n;
	cin >> n;
	cout << (arr[n][0] + arr[n][1]) % MOD;
}
