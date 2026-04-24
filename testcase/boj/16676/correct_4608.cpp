#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	if(!n)
		return !(cout << 1);
	ll t = 1, cnt = 0;
	while(1) {
		if(n < t)
			return !(cout << cnt);
		t = t*10+1;
		cnt++;
	}
}
