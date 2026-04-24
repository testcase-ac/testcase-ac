#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		for(int i=2;; i++) {
			int cnt = 0;
			while(n % i == 0) {
				n /= i;
				cnt++;
			}
            if(cnt) printf("%d %d\n", i, cnt);
			if(n == 1) break;
		}
	}
}
