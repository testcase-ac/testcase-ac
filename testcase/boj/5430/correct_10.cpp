#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <deque>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	char dummy;
	cin >> T;
	while(T--) {
		string cmd;
		cin >> cmd;
		int n, len;
		cin >> n;
		deque<int> dq(n);
		cin >> dummy;
		rep(i, n) {
			cin >> dq[i];
			if(i < n-1) cin >> dummy;
		}
		cin >> dummy;
		bool atfront = true;
		for(char c: cmd) {
			if(c == 'R') {
				atfront = !atfront;
			} else if(c == 'D'){
				if(dq.empty()) {
					cout << "error\n";
					goto nexttc;
				}
				if(atfront) dq.pop_front();
				else dq.pop_back();
			}
		}
		cout << '[';
		len = sz(dq);
		if(len) {
			if(atfront) {
				rep(i, len-1) {
					cout << dq[i] << ',';
				}
				cout << dq[len-1];
			} else {
				for(int i=len-1;i>0;i--) {
					cout << dq[i] << ',';
				}
				cout << dq[0];
			}			
		}
		cout << "]\n";
		nexttc:;
	}
}
