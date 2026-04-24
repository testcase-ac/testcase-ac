#include <bits/stdc++.h>
using namespace std;
char arr[256][256];
string refr = "ACAGCGTAATCGGAGT", ls = "AGCT";

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			arr[ls[i]][ls[j]] = refr[i*4+j];
		}
	}
	int n;
	string s;
	cin >> n >> s;
	while(s.size() > 1) {
		char a, b;
		b = s.back();
		s.pop_back();
		a = s.back();
		s.pop_back();
		s.push_back(arr[a][b]);
	}
	cout << s[0];
}
