#include <bits/stdc++.h>
using namespace std;
int f(int n) {
	int ret = 0;
	while(n) {
		ret += (n%10)*(n%10);
		n /= 10;
	}
	return ret;
}
bool seen[1000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n != 1) {
		n = f(n);
		if(seen[n])
			return !(cout << "UNHAPPY");
		seen[n] = 1;
	}
	cout << "HAPPY";
}
