#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	unordered_map<ll, int> mp;
	int n;
	cin >> n;
	int maxcnt = 0;
	ll maxnum=LLONG_MAX;
	while(n--) {
		ll i;
		cin >> i;
		mp[i]++;
		if(mp[i] > maxcnt || (mp[i] == maxcnt && i < maxnum)) {
			maxcnt = mp[i];
			maxnum = i;
		}
	}
	cout << maxnum;
}
