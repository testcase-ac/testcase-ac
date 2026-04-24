#include <bits/stdc++.h>
using namespace std;

int dr[] = {1,0,-1,0}, dc[] = {0, 1, 0, -1};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		int r = 0, c = 0, dir = 0, mxr = 0, mnr = 0, mxc = 0, mnc = 0;
		for(char t: s) {
			if(t == 'F')
				r += dr[dir], c += dc[dir];
			else if(t == 'B')
				r -= dr[dir], c -= dc[dir];
			else if(t == 'L')
				dir = (dir+3)%4;
			else if(t == 'R')
				dir = (dir+1)%4;
			mxr = max(mxr, r);
			mxc = max(mxc, c);
			mnr = min(mnr, r);
			mnc = min(mnc, c);
		}
		cout << (mxr - mnr) * (mxc - mnc) << '\n';
	}
}
