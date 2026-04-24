#include <bits/stdc++.h>
using namespace std;

int main() {
	int p;
	cin >> p;
	while(p--) {
		int n;
		double d, a, b, f;
		cin >> n >> d >> a >> b >> f;
		double t = d/(a+b);
		printf("%d %.2f\n", n, f*t);
	}
}
