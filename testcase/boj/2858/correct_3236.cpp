#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, b;
	cin >> r >> b;
	int sum = r+b;
	for(int w=1;;w++) {
		if(sum % w) continue;
		int l = sum / w;
		if(2*l+2*w-4 == r)
			return !printf("%d %d", l, w);
	}
}
