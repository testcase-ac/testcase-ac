#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int prec(char c) {
	if(c == '*' || c == '/') return 2;
	else if(c == '+' || c == '-') return 1;
	else return 0;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s;
	cin >> s;
	stack<char> stk;
	for(char c: s) {
		if(isalpha(c)) {
			cout << c;
		} else {
			if(c == '(') {
				stk.push(c);
			} else {
				while(!stk.empty() && prec(stk.top()) >= prec(c)){
					if(stk.top() == '(') {
						stk.pop();
						break;
					}
					cout << stk.top();
					stk.pop();
				}
				if(c != ')') stk.push(c);
			}
		}
		//printf("processed %c, sz(stk)=%d\n", c, sz(stk));
	}
	while(!stk.empty()) {
		cout << stk.top();
		stk.pop();
	}
}
