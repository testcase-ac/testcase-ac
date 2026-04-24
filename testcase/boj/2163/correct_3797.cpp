#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

inline int min(int a, int b) {
	return (a > b ? b : a);
}

using namespace std;

#define MAXN 300
int arr[MAXN+1][MAXN+1];
int main() {
	int n, m;
	cin >> n >> m;
	cout << (n*m) - 1;
}
