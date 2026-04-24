#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;
	for(int tc=1; tc<=T; tc++) {
		long long a, b, c;
		cin >> a >> b >> c;
		a *= a;
		b *= b;
		c *= c;
		printf("Scenario #%d:\n", tc);
		if(a+b==c || a+c==b || b+c == a)
			cout << "yes\n\n";
		else
			cout << "no\n\n";
	}
}
