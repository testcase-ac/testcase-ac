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

int arr[42];
int main() {
	int a;
	rep(i, 10) {
		cin >> a;
		arr[a%42]++;
	}
	int ans = 0;
	rep(i, 42) {
		if(arr[i]) ans++;
	}
	cout << ans;
}
