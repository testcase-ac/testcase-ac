#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int aa, ha, ab, hb;
	cin >> aa >> ha >> ab >> hb;
	while(ha > 0 && hb > 0) {
		hb -= aa;
		ha -= ab;
	}
	if(ha <= 0 && hb <= 0) {
		cout << "DRAW";
	} else if(ha <= 0) {
		cout << "PLAYER B";
	} else
		cout << "PLAYER A";
}
