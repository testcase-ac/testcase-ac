#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, cnt = 1, addi = 1;
	cin >> n;
	for(int h=1;; h++) {
		addi += h*4;
		cnt += addi;
		if(n < cnt)
			return !(cout << h);
	}
}
