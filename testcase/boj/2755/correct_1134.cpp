#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, sum = 0, cnt = 0;
	cin >> n;
	while(n--) {
		string s, p;
		int t;
		cin >> s >> t >> p;
		int c = 0;
		if(p[0] == 'A')
			c = 40;
		else if(p[0] == 'B')
			c = 30;
		else if(p[0] == 'C')
			c = 20;
		else if(p[0] == 'D')
			c = 10;
		if(p.size() == 2 && p[1] == '+')
			c += 3;
		if(p.size() == 2 && p[1] == '-')
			c -= 3;
		sum += c * t;
		cnt += t;
	}
	printf("%.2f", (double)sum/cnt/10 + 1e-9);
}
