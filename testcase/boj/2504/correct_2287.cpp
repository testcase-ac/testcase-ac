#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

#define FAIL return !(cout << 0)
using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	string str;
	cin >> str;
	int val = 0;
	stack<int> chker;
	for(char c: str) {
		if(c == '(')
			chker.push(0);
		else if(c == '[')
			chker.push(1);
		else {
			if(chker.empty())
				FAIL;
			if((chker.top() == 0 && c == ']') || (chker.top() == 1 && c == ')'))
				FAIL;
			chker.pop();
		}
	}
	if(!chker.empty())
		FAIL;
	stack<int> stk;
	for(int i=0; i<sz(str); i++) {
		char c = str[i];
		if(c == '(' || c == '[') {
			stk.push(val);
			val = 0;
		} else if(c == ')') {
			if(str[i-1] == '(')
				val = stk.top() + 2;
			else
				val = stk.top() + val * 2;
			stk.pop();
		} else if(c == ']') {
			if(str[i-1] == '[')
				val = stk.top() + 3;
			else
				val = stk.top() + val * 3;
			stk.pop();
		}
	}
	cout << val;
}
