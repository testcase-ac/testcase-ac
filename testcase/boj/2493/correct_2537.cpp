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

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, h;
	cin >> n;
	stack<pair<int,int>> stk; // height, index
	rep(i, n) {
		cin >> h;
		while(!stk.empty() && stk.top().first < h)
			stk.pop();
		if(stk.empty())
			cout << "0 ";
		else
			cout << stk.top().second << ' ';
		stk.emplace(h, i+1);
	}
}
