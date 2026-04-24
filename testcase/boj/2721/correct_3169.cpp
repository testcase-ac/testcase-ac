#include <bits/stdc++.h>
using namespace std;
int w[301];
int t(int i) {
	return (1+i)*i/2;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=1; i<=300; i++) {
		w[i] = w[i-1]+i*t(i+1);
	}
	int n;
	cin >> n;
	while(n--) {
		int t;
		cin >> t;
		cout << w[t] << '\n';
	}
}
