#include <bits/stdc++.h>
using namespace std;

int main() {
	int r, g;
	cin >> r >> g;
	int gcd = __gcd(r, g);
	vector<int> factors;
	for(int i=1; i*i<=gcd; i++) {
		if(i*i == gcd) {
			factors.push_back(i);
		} else if(gcd % i == 0) {
			factors.push_back(i);
			factors.push_back(gcd / i);
		}
	}
	for(int f: factors) {
		printf("%d %d %d\n", f, r/f, g/f);
	}
}
