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

#define END(p) return !(cout << (p))
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<string> arr(n);
	rep(i, n) cin >> arr[i];
	for(int s=min(n,m);s>=1;s--) {
		for(int i=0; i<=n-s; i++) {
			for(int j=0; j<=m-s; j++) {
				int comp[] = {arr[i][j], arr[i+s-1][j], arr[i][j+s-1], arr[i+s-1][j+s-1]};
				sort(comp, comp+4);
				if(comp[0] == comp[3])
					END(s*s);
			}
		}
	}
}
