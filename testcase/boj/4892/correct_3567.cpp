#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, t = 1;
	while(cin >> n) {
		if(!n) break;
		n *= 3;
		printf("%d. %s %d\n", t, n&1 ? "odd" : "even", (n+1)/2*3/9);
		t++;
	}
}
