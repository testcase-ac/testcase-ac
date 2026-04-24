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
	//ios::sync_with_stdio(false);cin.tie(NULL);
	ll S, sum=0;
	cin >> S;
	for(int n=1;;n++) {
		sum += n;
		if((sum+n+1) > S) {
			cout << n << ' ';
			return 0;
		}
	}
}
