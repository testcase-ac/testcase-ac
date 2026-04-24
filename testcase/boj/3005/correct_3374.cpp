#include <bits/stdc++.h>
using namespace std;

char arr[25][25];
string ans = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<R; i++) {
		string s;
		for(int j=0; j<C; j++) {
			if(arr[i][j] == '#') {
				if(s.size() >= 2)
					ans = min(ans, s);
				s.clear();
			} else {
				s.push_back(arr[i][j]);
			}
		}
		if(s.size() >= 2)
			ans = min(ans, s);
	}
	for(int j=0; j<C; j++) {
		string s;
		for(int i=0; i<R; i++) {
			if(arr[i][j] == '#') {
				if(s.size() >= 2)
					ans = min(ans, s);
				s.clear();
			} else {
				s.push_back(arr[i][j]);
			}
		}
		if(s.size() >= 2)
			ans = min(ans, s);
	}
	cout << ans;
}
