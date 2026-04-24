#include <bits/stdc++.h>
using namespace std;
char arr[250][8];
int comp(int a, int b) {
	a *= 5, b *= 5;
	int cnt = 0;
	for(int i=0; i<5; i++) {
		for(int j=0; j<7; j++) {
			if(arr[a+i][j] != arr[b+i][j])
				cnt++;
		}
	}
	return cnt;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<5*n; i++) {
		cin >> arr[i];
	}
	pair<int, int> ans;
	int val = INT_MAX;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			int v = comp(i, j);
			if(v < val) {
				val = v;
				ans = {i+1, j+1};
			}
		}
	}
	cout << ans.first << ' ' << ans.second;
}
