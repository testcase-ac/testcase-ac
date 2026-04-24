#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, ans = 0;
	cin >> n;
	while(n--) {
		int h, m, d;
		scanf("%d:%d%d", &h, &m, &d);
		int t = h*60+m;
		for(int i=t; i<t+d; i++)
			ans += (420 <= i && i < 1140) ? 10 : 5;
	}
	cout << ans;
}
