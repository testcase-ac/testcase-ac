#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	if(n&1) {
		for(int i=0; i<n; i++) {
			cout << '*';
		}
		cout << '\n';
		for(int i=0; i<n/2; i++) {
			cout << ' ';
		}
		cout << "*\n";
		int t = 1;
		for(int i=n/2-1; i>=0; i--) {
			for(int j=0; j<i; j++)
				cout << ' ';
			cout << '*';
			for(int j=0; j<t; j++)
				cout << ' ';
			cout << "*\n";
			t+=2;
		}
	} else cout << "I LOVE CBNU";
}
