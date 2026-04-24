#include <bits/stdc++.h>
using namespace std;
double bin(int m) {
	double l = 0, r = 250;
	while(r-l > 1e-7) {
		double mid = (l+r)/2;
		if((250-mid)*m < 31250)
			r = mid;
		else
			l = mid;
	}
	return l;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a, b;
	double ax = 0, ay = 0;
	cin >> a >> b;
	if(a+b == 250) {
		int m = max(a, b);
		double l = bin(m);
		if(a < 125)
			ax = l;
		else
			ay = l;
		
	} else {
		bool swp = 0;
		if(!a) swap(a, b), swp = 1;
		if(a > 125)
			ay = 31250.0/a;
		else {
			double l = bin(250-a);
			ax = l, ay = 250-l;
		}
		if(swp)
			swap(ax, ay);

	}
	printf("%.2f %.2f\n", ax, ay);
}
