#include <bits/stdc++.h>
using namespace std;
const int MX = 102;
bool arr[MX][MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int a, b;
		cin >> a >> b;
		for(int x=a; x<a+10; x++) {
			for(int y=b; y<b+10; y++) {
				arr[x][y] = 1;
			}
		}
	}
	int ans = 0;
	for(int i=0; i<MX-1; i++) {
		for(int j=0; j<MX-1; j++) {
			if(arr[i][j] != arr[i+1][j])
				ans++;
			if(arr[i][j] != arr[i][j+1])
				ans++;
		}
	}
	cout << ans;
}
