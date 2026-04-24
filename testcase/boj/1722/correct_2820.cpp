#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i,n) for(int i=0; i<(n); i++)
#define ll long long
using namespace std;
ll factorial[20];

int main() {
	factorial[0] = 1;
	for(int i=1; i<20; i++)
		factorial[i] = factorial[i-1]*i;
	int n, prob;
	cin >> n >> prob;
	vector<int> cand(n);
	rep(i,n) cand[i] = i+1;
	if(prob == 1) {
		ll k;
		cin >> k;
		k--;
		for(int i=n-1; i>=0; i--) {
			int ptr = k / factorial[i];
			k %= factorial[i];
			cout << cand[ptr] << ' ';
			cand.erase(cand.begin()+ptr);
		}
	} else {
		int t;
		ll ans = 1;
		for(int i=n-1; i>=0; i--) {
			cin >> t;
			auto it = find(cand.begin(), cand.end(), t);
			ans += (int)(it - cand.begin()) * factorial[i];
			cand.erase(it);
		}
		cout << ans;
	}

}
