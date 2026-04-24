#include <bits/stdc++.h>
using namespace std;
int a[2000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int ptr = 0;
	for(int i=1; ptr<1000; i++) {
		int t = i;
		while(t--)
			a[ptr++] = i;
	}
	int x, y;
	cin >> x >> y;
	cout << accumulate(a+x-1, a+y, 0);
}
