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
	int n, k;
	cin >> n >> k;
	int cnt = 0;
	for(int i=1; i<=n; i++) {
		if(n % i == 0) {
			cnt++;
			if(cnt == k) {
				return !(cout << i);
			}
		}
	}
	cout << 0;
}
