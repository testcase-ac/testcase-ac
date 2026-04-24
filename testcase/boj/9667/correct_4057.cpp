#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+3;
bool has[MX], factor[MX];
int ans = 0;
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}
void proc(int j) {
	if(factor[j]) return;
	factor[j] = 1;
	ans += phi(j);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n+1; i++) {
		int t;
		cin >> t;
		has[t] = 1;
	}
	for(int i=2; i<MX; i++) {
		if(!has[i]) continue;
		for(int j=2; j*j<=i; j++) {
			if(i % j == 0) {
				proc(j);
				proc(i/j);
			}
		}
		proc(i);
	}
	cout << ans;
}
