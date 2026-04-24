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
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s1,s2;
	cin >> s1 >> s2;
	int ans = 100;
	rep(i, sz(s2)-sz(s1)+1) {
		int temp = 0;
		rep(j, sz(s1)) {
			if(s1[j] != s2[i+j]) {
				temp++;
			}
		}
		//printf("i=%d,temp=%d\n",i,temp);
		ans = min(ans,temp);
	}
	cout << ans;
}
