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

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	char arr[5][16]; set0(arr);
	rep(i, 5) cin >> arr[i];
	rep(j, 15) {
		rep(i, 5) {
			if(arr[i][j]) cout << arr[i][j];
		}
	}
}
