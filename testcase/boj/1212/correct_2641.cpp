#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string input, ans;
	cin >> input;
	if(input == "0") return !(cout << 0);
	for(char c: input) {
		string append;
		int i = c - '0';
		rep(k, 3) {
			append = (char)((i % 2)+'0') + append;
			i /= 2;
		}
		ans += append;
	}
	int i = 0;
	while(ans[i] == '0') i++;
	for(;i<sz(ans);i++) cout << ans[i];

}
