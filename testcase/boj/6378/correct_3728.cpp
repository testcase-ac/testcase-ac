#include <bits/stdc++.h>
using namespace std;

int get(int i) {
	if(i < 10) return i;
	int ret = 0;
	while(i) {
		ret += i % 10;
		i /= 10;
	}
	return get(ret);
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	while(1) {
		int num = 0;
		string s;
		cin >> s;
		if(s == "0") break;
		for(char c: s) num += (c - '0');
		cout << get(num) << '\n';
	}
}
