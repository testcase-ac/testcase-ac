#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int k, c, x, y;
		cin >> k >> c;
		int g = gcd(k, c, x, y);
		if(g != 1)
			cout << "IMPOSSIBLE\n";
		else {
            y = (y%k+k)%k;
            while((long long)c*y <= k)
            	y += k;
            if(y > 1e9)
            	cout << "IMPOSSIBLE\n";
            else
            	cout << y << '\n';
		}
	}
}
