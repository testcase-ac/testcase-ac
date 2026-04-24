#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	long long x, y, now;
	cin >> x >> y;
	now = y*100/x;
	if(now >= 99) return !(cout << -1);
	long long left = 1, right = 1e9, mid;
	while(left < right) {
		mid = (left+right)/2;
		if((y+mid)*100/(x+mid) > now)
			right = mid;
		else
			left = mid+1;
	}
	cout << left;
}
