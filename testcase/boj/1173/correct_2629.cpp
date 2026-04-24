#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int N, lb, ub, inc, dec;
	cin >> N >> lb >> ub >> inc >> dec;
	if(ub-lb < inc) return !(cout << -1);
	int now = lb, cnt = 0, t = 0;
	while(cnt < N) {
		t++;
		if(now + inc <= ub) {
			now += inc;
			cnt++;
		} else {
			now = max(now-dec, lb);
		}
		
	}
	cout << t;
}
