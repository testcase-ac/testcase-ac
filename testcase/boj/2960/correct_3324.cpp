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
	int n, k;
	cin >> n >> k;
	bool erased[n+1]; set0(erased);
	int erasecnt = 0;
	for(int p=2;;p++) {
		if(erased[p]) continue;
		for(int i=p; i<=n; i+=p) {
			if(!erased[i]) {
				erased[i] = true;
				erasecnt++;
				if(erasecnt == k)
					return !(cout << i);				
			}
		}
	}
}
