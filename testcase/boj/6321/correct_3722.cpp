#include <bits/stdc++.h>
using namespace std;

int main() {
	//ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		string s;
		cin >> s;
		printf("String #%d\n", i);
		for(char c: s) {
			cout << (char)((((c-'A')+1)%26)+'A');
		}
		cout << "\n\n";
	}
}
