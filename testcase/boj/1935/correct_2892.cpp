#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	string s;
	cin >> n >> s;
	int arr[n];
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	stack<double> stk;
	for(char c: s) {
		if(isalpha(c)) {
			stk.push(arr[c-'A']);
		} else {
			double b = stk.top();
			stk.pop();
			double a = stk.top();
			stk.pop();
			if(c == '+')
				stk.push(a+b);
			else if(c == '-')
				stk.push(a-b);
			else if(c == '*')
				stk.push(a*b);
			else if(c == '/')
				stk.push(a/b);
		}
	}
	cout << fixed << setprecision(2) << stk.top();
}
