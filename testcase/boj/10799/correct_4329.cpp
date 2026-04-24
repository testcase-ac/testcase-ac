#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
using namespace std;

int main() {
	string str;
	cin >> str;
	bool justleft = false;
	int leftcnt = 0, ans = 0;
	for(char c: str) {
		if(c == '(') {
			leftcnt++;
			if(justleft) ans++;
			justleft = true;
		} else if(c == ')') {
			leftcnt--;
			if(justleft) ans += leftcnt;
			justleft = false;
		}
	}
	cout << ans;
}
