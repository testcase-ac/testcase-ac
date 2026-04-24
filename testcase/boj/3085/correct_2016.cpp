#include <bits/stdc++.h>
using namespace std;

char arr[50][50];
int n;
int calc() {
	int ret = 0;
	for(int i=0; i<n; i++) {
		int lastc = '0', cnt = 0;
		for(int j=0; j<n; j++) {
			if(arr[i][j] == lastc)
				cnt++;
			else {
				ret = max(cnt, ret);
				lastc = arr[i][j];
				cnt = 1;
			}
		}
		ret = max(cnt, ret);
	}
	for(int i=0; i<n; i++) {
		int lastc = '0', cnt = 0;
		for(int j=0; j<n; j++) {
			if(arr[j][i] == lastc)
				cnt++;
			else {
				ret = max(cnt, ret);
				lastc = arr[j][i];
				cnt = 1;
			}
		}
		ret = max(cnt, ret);
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n;
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		for(int j=0; j<n; j++) {
			arr[i][j] = s[j];
		}
	}
	int ans = 1;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(j+1<n) {
				swap(arr[i][j], arr[i][j+1]);
				ans = max(ans, calc());
				swap(arr[i][j], arr[i][j+1]);
			}
			if(i+1<n) {
				swap(arr[i][j], arr[i+1][j]);
				ans = max(ans, calc());
				swap(arr[i][j], arr[i+1][j]);
			}
		}
	}
	cout << ans;
}
