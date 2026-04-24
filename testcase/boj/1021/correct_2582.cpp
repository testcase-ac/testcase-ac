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
	int n, m, ans=0;
	cin >> n >> m;
	vector<int> tofind(m);
	deque<int> dq;
	rep(i, m) cin >> tofind[i];
	rep(i, n) dq.push_back(i+1);
	for(int f: tofind) {
		int len = sz(dq);
		int atind = 0;
		while(dq[atind]!=f) atind++;
		if(atind == 0) {
			dq.pop_front();
		} else if(atind <= len - atind) {  // in front half
			do {
				ans++;
				dq.push_back(dq.front());
				dq.pop_front();
			} while(dq.front() != f);
			dq.pop_front();
		} else {  // in back half
			do {
				ans++;
				dq.push_front(dq.back());
				dq.pop_back();
			} while(dq.front() != f);
			dq.pop_front();
		}
	}
	cout << ans;
}
