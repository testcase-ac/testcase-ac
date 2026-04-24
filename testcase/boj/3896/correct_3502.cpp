#include <bits/stdc++.h>
using namespace std;
const int MX = 1300000;
bool sieve[MX];
vector<int> v;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=2; i<MX; i++) {
		if(!sieve[i]) {
			v.push_back(i);
			for(int j=i*2; j<MX; j+=i) {
				sieve[j] = 1;
			}
		}
	}
	int T;
	cin >> T;
	while(T--) {
		int k;
		cin >> k;
		if(k == 1) cout << "0\n";
		else {
			auto it = lower_bound(v.begin(), v.end(), k);
			if(*it == k) cout << "0\n";
			else {
				cout << (*it - *prev(it)) << '\n';
			}
		}
	}
}
