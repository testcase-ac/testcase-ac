#include <bits/stdc++.h>
using namespace std;
struct Tank {
	int i, r, c;
};
vector<pair<int, char>> ans;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	Tank arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i].r >> arr[i].c;
		arr[i].i = i+1;
	}
	sort(arr, arr+n, [](Tank &a, Tank &b){return a.r < b.r;});
	for(int i=0; i<n; i++) {
		int l = arr[i].r-(i+1);
		for(int j=0; j<l; j++) {
			ans.push_back({arr[i].i, 'U'});
		}
	}
	for(int i=n-1; i>=0; i--) {
		int l = i+1-arr[i].r;
		for(int j=0; j<l; j++) {
			ans.push_back({arr[i].i, 'D'});
		}
	}
	sort(arr, arr+n, [](Tank &a, Tank &b){return a.c < b.c;});
	for(int i=0; i<n; i++) {
		int l = arr[i].c-(i+1);
		for(int j=0; j<l; j++) {
			ans.push_back({arr[i].i, 'L'});
		}
	}
	for(int i=0; i<n; i++) {
		int l = i+1-arr[i].c;
		for(int j=0; j<l; j++) {
			ans.push_back({arr[i].i, 'R'});
		}
	}
	cout << ans.size() << '\n';
	for(auto a: ans) cout << a.first << ' ' << a.second << '\n';
}
