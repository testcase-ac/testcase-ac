#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

int arr[5][5];
pii where(int x) {
	rep(i,5){
		rep(j,5) {
			if(arr[i][j] == x)
				return {i,j};
		}
	}
	return {MOD,MOD};
}
bool check() {
	int cnt = 0;
	rep(i,5) {
		bool all0 = true;
		rep(j,5) {
			if(arr[i][j] != 0) {
				all0 = false;
				break;
			}
		}
		if(all0) cnt++;
	}
	rep(i,5) {
		bool all0 = true;
		rep(j,5) {
			if(arr[j][i] != 0) {
				all0 = false;
				break;
			}
		}
		if(all0) cnt++;
	}
	bool all0 = true;
	rep(i,5) {
		if(arr[i][i] != 0) {
			all0 = false;
			break;
		}
	}
	if(all0) cnt++;
	all0 = true;
	rep(i,5) {
		if(arr[i][4-i] != 0) {
			all0 = false;
			break;
		}
	}
	if(all0) cnt++;
	return cnt >= 3;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	rep(i,5)rep(j,5) cin >> arr[i][j];
	rep(i,25) {
		int x;
		cin >> x;
		auto w = where(x);
		arr[w.first][w.second] = 0;
		if(check()) return !(cout << i+1);
	}
}
