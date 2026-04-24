#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

struct Fraction {
	int p, q;
	double operator() (){
		return (double)p/q;
	}
	void sub(int p2, int q2) {
		p = p*q2 - p2*q;
		q *= q2;
		if(!p) return;
		int g = __gcd(p, q);
		p /= g;
		q /= g;
	}
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		Fraction f;
		cin >> f.p >> f.q;
		while(1) {
			int nextq = (f.q%f.p?f.q/f.p+1:f.q/f.p);
			f.sub(1,nextq);
			if(!f.p) {
				cout << nextq << '\n';
				break;
			}
		}
	}
}
