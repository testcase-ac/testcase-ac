#include <iostream>
#include <deque>

#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

string a, t;
deque<char> ldq, rdq;

bool lmatch() {
	if(sz(ldq) < sz(a)) return false;
	for(int i=0; i<sz(a); i++) {
		if(ldq[sz(ldq)-sz(a)+i] != a[i]) return false;
	}
	return true;
}

bool rmatch() {
	if(sz(rdq) < sz(a)) return false;
	for(int i=0; i<sz(a); i++) {
		if(rdq[i] != a[i]) return false;
	}
	return true;
}

bool imatch(int i) {
	for(int j=0; j<sz(a); j++) {
		if((i+j<sz(ldq)? ldq[i+j] : rdq[i+j-sz(ldq)]) != a[j]) return false;
	}
	return true;
}

inline void print(deque<char> &dq) {
	for(char c:dq) cout << c;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> a >> t;
	int l = 0, r = sz(t)-1;
	while(l <= r) {
		while(l <= r) {
			ldq.push_back(t[l++]);
			if(lmatch()) {
				ldq.erase(ldq.end()-sz(a), ldq.end());
				break;
			}
		}
		while(l <= r) {
			rdq.push_front(t[r--]);
			if(rmatch()) {
				rdq.erase(rdq.begin(), rdq.begin()+sz(a));
				break;
			}
		}
	}
	bool flag = false, left = true;
	do {
		flag = false;
		int lb = max(sz(ldq)-sz(a)+1, 0), rb = min(sz(ldq)-1, sz(ldq)+sz(rdq)-sz(a));
		for(int i=(left?lb:rb); lb<=i&&i<=rb;(left?i++:i--)) {
			if(imatch(i)) {
				auto it = rdq.begin()+(i+sz(a)-sz(ldq));
				ldq.erase(ldq.begin()+i, ldq.end());
				rdq.erase(rdq.begin(), it);
				flag = true;
				break;
			}
		}
		left = !left;
	} while(flag);
	print(ldq);
	print(rdq);
}
