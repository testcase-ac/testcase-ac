#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

bool reveq(string &s1, string &s2) {
	if(sz(s1) != sz(s2)) return false;
	for(int i=0; i<(sz(s1)/2); i++) {
		if(s1[i] != s2[sz(s1)-1-i]) return false;
	}
	return true;
}

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<string> arr(n);
	rep(i,n) cin >> arr[i];
	rep(i,n) {
		rep(j,n) {
			if(reveq(arr[i], arr[j])) {
				return !printf("%d %c", sz(arr[i]), arr[i][sz(arr[i])/2]);
			}
		}
	}
}
