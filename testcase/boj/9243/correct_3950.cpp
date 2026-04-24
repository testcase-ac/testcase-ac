#include <bits/stdc++.h>
using namespace std;
string ok = "Deletion succeeded", fail = "Deletion failed";
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	string a, b;
	cin >> a >> b;
	if(n&1) {
		for(int i=0; i<(int)a.size(); i++) {
			if(a[i] == b[i])
				return !(cout << fail);
		}
	} else {
		for(int i=0; i<(int)a.size(); i++) {
			if(a[i] != b[i])
				return !(cout << fail);
		}
	}
	cout << ok;
}
