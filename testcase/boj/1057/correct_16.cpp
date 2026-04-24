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


inline int nextno(int a) {
	return (a+1)/2;
}
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m, k;
	cin >> n >> m >> k;
	int ans = 1;
	if(m > k) swap(m, k);
	while(!(m % 2 && m+1==k)) {
		m = nextno(m);
		k = nextno(k);
		ans++;
	}
	cout << ans;
}
