#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int num;
	cin >> num;
	while(1) {
		char op;
		cin >> op;
		if(op == '=')
			return !(cout << num);
		else {
			int a;
			cin >> a;
			if(op == '+')
				num += a;
			else if(op == '-')
				num -= a;
			else if(op == '*')
				num *= a;
			else if(op == '/')
				num /= a;
		}
	}
}
