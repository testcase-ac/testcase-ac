#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <stack>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
using namespace std;

int main() {
	int n, inp;
	cin >> n;
	stack<int> stk;
	int nextToOut = 1;
	rep(i, n) {
		cin >> inp;
		if(inp == nextToOut) {
			nextToOut++;
			while(!stk.empty() && stk.top() == nextToOut) {
				nextToOut++;
				stk.pop();
			}
		} else {
			stk.push(inp);
		}
	}
	if(stk.empty()) return !(cout << "Nice");
	else return !(cout << "Sad");
}
