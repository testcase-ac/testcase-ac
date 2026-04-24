#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int k, t, a[6];
	cin >> k;
	for(int i=0; i<6; i++) {
		cin >> t >> a[i];
	}
	int i = (a[0] > a[2] && a[0] > a[4] ? 0: a[2]>a[4] ? 2 : 4);
	int j = (a[1] > a[3] && a[1] > a[5] ? 1: a[3]>a[5] ? 3 : 5);
	int area = a[i]*a[j]-a[(i+3)%6]*a[(j+3)%6];
	cout << area*k;
}
