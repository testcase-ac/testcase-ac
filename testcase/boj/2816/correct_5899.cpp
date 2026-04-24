#include <bits/stdc++.h>
using namespace std;

string ls[100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int p = 0;
	for(int i=0; i<n; i++) {
		cin >> ls[i];
		if(ls[i] == "KBS1")
			p = i;
	}
	if(p) {
		for(int i=0; i<p; i++) {
			cout << '1';
		}
		for(int i=0; i<p; i++) {
			cout << '4';
		}
	}
	for(int i=0; i<n; i++) {
		if(ls[i] == "KBS2") {
			p = (i < p ? i+1 : i);
		}
	}
	for(int i=0; i<p; i++) {
		cout << '1';
	}
	for(int i=0; i<p-1; i++) {
		cout << '4';
	}
}
