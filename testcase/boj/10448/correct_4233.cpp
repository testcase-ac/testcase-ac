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

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	vector<int> T;
	for(int i=1;;i++) {
		if(i*(i+1)/2 >= 1000) break;
		T.push_back(i*(i+1)/2);
	}
	bool able[1001];
	int s = sz(T);
	rep(i, s) {
		rep(j, s) {
			rep(k, s) {
				if(T[i]+T[j]+T[k] <= 1000)
				able[T[i]+T[j]+T[k]] = true;
			}
		}
	}
	int n;
	cin >> n;
	while(n--) {
		int i;
		cin >> i;
		cout << able[i] << '\n';
	}
}
