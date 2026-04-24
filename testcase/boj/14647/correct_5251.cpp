#include <bits/stdc++.h>
using namespace std;
int arr[500][500];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, s = 0;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			int t;
			cin >> t;
			while(t) {
				if(t % 10 == 9)
					arr[i][j]++;
				t /= 10;
			}
			s += arr[i][j];
		}	
	}
	int mx = 0;
	for(int i=0; i<n; i++) {
		mx = max(mx, accumulate(arr[i], arr[i]+m, 0));
	}
	for(int j=0; j<m; j++) {
		int t = 0;
		for(int i=0; i<n; i++) {
			t += arr[i][j];
		}
		mx = max(mx, t);
	}
	cout << s - mx;
}
