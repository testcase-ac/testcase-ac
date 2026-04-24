#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+2;
string arr[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	int ans = 1e9;
	for(char c='a'; c<='z'; c++) {
		int f = 1e9, b = 1e9; 
		for(int i=0; i<n; i++) {
			int f2 = 1e9, b2 = 1e9, len = arr[i].size(); 
			for(int j=0; j<len; j++) {
				if(arr[i][j] == c) {
					f2 = min(f2, j);
					b2 = min(b2, len-j-1);
					ans = min({ans, f+b2, b+f2});
				}
			}
			f = min(f, f2);
			b = min(b, b2);
		}
	}
	cout << (ans >= 1e9 ? -1 : ans);

}
