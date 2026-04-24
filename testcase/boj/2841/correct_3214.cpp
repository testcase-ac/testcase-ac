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
	int n, p, a, b;
	cin >> n >> p;
	vector<stack<int>> stkArr(6);
	int ans = 0;
	while(n--) {
		cin >> a >> b;
		a--;
		if(stkArr[a].empty()) {
			stkArr[a].push(b);
			ans++;
		} else {
			while(!stkArr[a].empty() && b < stkArr[a].top()) {
				stkArr[a].pop();
				ans++;
			}
			if(stkArr[a].empty() || b > stkArr[a].top()) {
				stkArr[a].push(b);
				ans++;
			}
		}
	}
	cout << ans;
}
