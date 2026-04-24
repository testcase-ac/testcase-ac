#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int a[3];
	string s[3] = {"Soongsil", "Korea", "Hanyang"};
	for(int i=0; i<3; i++) {
		cin >> a[i];
	}
	if(a[0]+a[1]+a[2] >= 100)
		cout << "OK";
	else if(a[0] < a[1] && a[0] < a[2])
		cout << s[0];
	else if(a[1] < a[0] && a[1] < a[2])
		cout << s[1];
	else
		cout << s[2];
}
