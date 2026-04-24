#include <bits/stdc++.h>
using namespace std;
int arr[10000][6], mp[6] = {5,3,4,1,2,0}, n;
int chk(int t) {
	int sum = 0;
	for(int i=0; i<6; i++) {
		if(i != t && i != mp[t])
			sum = max(sum, arr[0][i]);
	}
	int nxt = arr[0][mp[t]];
	for(int i=1; i<n; i++) {
		for(int j=0; j<6; j++) {
			if(arr[i][j] == nxt)
				t = j;
		}
		int a = 0;
		for(int j=0; j<6; j++) {
			if(j != t && j != mp[t])
				a = max(a, arr[i][j]);
		}
		sum += a;
		nxt = arr[i][mp[t]];
	}
	return sum;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<6; j++) {
			cin >> arr[i][j];
		}
	}
	int ans = 0;
	for(int i=0; i<6; i++)
		ans = max(ans, chk(i));
	cout << ans;
}
