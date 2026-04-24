#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	double a[3], b[3];
	for(int i=0; i<3; i++) {
		cin >> a[i];
	}
	double mx = DBL_MAX;
	for(int i=0; i<3; i++) {
		cin >> b[i];
		mx = min(mx, a[i]/b[i]);
	}
	for(int i=0; i<3; i++) {
		printf("%.10f\n", a[i]-mx*b[i]);
	}
}
