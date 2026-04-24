#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	if(n <= 2) return !(cout << 2);
	vector<ll> primes = {2};
	for(ll i=3;;i+=2) {
		bool ok = true;
		for(ll p: primes) {
			if(p*p>i)
				break;
			if(i % p == 0) {
				ok = false;
				break;
			}
		}
		if(ok) {
			primes.push_back(i);
			if(i >= n) {
				string s = to_string(i);
				int sz = s.size();
				bool pali = true;
				for(int j=0; j<sz/2; j++) {
					if(s[j] != s[sz-j-1]) {
						pali = false;
						break;
					}
				}
				if(pali)
					return !(cout << s);
			}
		}
	}
}
