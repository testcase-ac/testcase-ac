#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, cnt = 0;
	cin >> n;
	for(int i=2;; i++) {
		while(n % i == 0) {
			n /= i;
			cnt++;
		}
		if(n == 1) break;
	}
	cout << (int)ceil(log2(cnt));
}
