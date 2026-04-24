#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stack>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
using namespace std;

int main() {
	int t;
	cin >> t;
	int ans = 0;
	while(t--) {
		string str;
		cin >> str;
		stack<char> stk;
		for(char c: str) {
			if(!stk.empty() && stk.top() == c)
				stk.pop();
			else
				stk.push(c);
		}
		if(stk.empty()) ans++;
	}
	cout << ans;
}
