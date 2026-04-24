#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		int a[n+1], sum = 0;
		for(int i=1; i<=n; i++) {
			cin >> a[i];
			sum += a[i];
		}
		int i = max_element(a+1, a+n+1) - a, cnt = count(a+1, a+n+1, a[i]);
		if(cnt >= 2)
			cout << "no winner\n";
		else if(a[i]*2>sum)
			cout << "majority winner " << i << '\n';
		else
			cout << "minority winner " << i << '\n';
	}
}
