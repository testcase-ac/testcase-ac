#include <bits/stdc++.h>
using namespace std;
char arr[5][5], str[10];
set<string> st;
int dr[] = {-1,1,0,0}, dc[] = {0,0,1,-1};
void f(int d, int r, int c) {
	if(d == 6) {
		string s(str);
		st.insert(s);
		return;
	}
	str[d] = arr[r][c];
	for(int i=0; i<4; i++) {
		int tr = r+dr[i], tc = c+dc[i];
		if(0<=tr&&tr<5 && 0<=tc&&tc<5) {
			f(d+1, tr, tc);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n = 5;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> arr[i][j];
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			f(0,i,j);
		}
	}
	cout << st.size();
}
