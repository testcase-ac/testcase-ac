#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int k;
	cin >> k;
	k--;
	int d = 1;
	while(k-(1<<d) >= 0) {
		k -= (1<<d);
		d++;
	}
	for(int i=d-1; i>=0; i--) {
		cout << (k&(1<<i) ? '7' : '4');
	}
}
