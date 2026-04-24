#include <bits/stdc++.h>
using namespace std;

bool f(string &s) {
	stack<char> stk;
	for(char c: s) {
		if(c == '[' || c == '(') stk.push(c);
		else if(c == ']') {
			if(stk.empty() || stk.top() != '[') return 0;
			stk.pop();
		}
		else if(c == ')') {
			if(stk.empty() || stk.top() != '(') return 0;
			stk.pop();
		}
	}
	return stk.empty();
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	while(1) {
		getline(cin, s);
		if(s == ".") break;
		cout << (f(s) ? "yes\n" : "no\n");
	}
    cout << '\n';
    cout << '\n';
    cout << '\n';cout << '\n';cout << '\n';cout << '\n';cout << '\n';
        cout << '\n';
    cout << '\n';
    cout << '\n';cout << '\n';cout << '\n';cout << '\n';cout << '\n';
        cout << '\n';
    cout << '\n';
    cout << '\n';cout << '\n';cout << '\n';cout << '\n';cout << '\n';
        cout << '\n';
    cout << '\n';
    cout << '\n';cout << '\n';cout << '\n';cout << '\n';cout << '\n';
}