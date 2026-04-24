#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	for(int i=1; i<=T; i++) {
		int h;
		cin >> h;
		string s;
		cin >> s;
		for(char c: s) {
			if(c == 'c')
				h++;
			else
				h--;
		}
		printf("Data Set %d:\n%d\n\n", i, h);

	}
}
