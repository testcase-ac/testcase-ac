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
	string str;
	cin >> str;
	int h = 10;
	char last = str[0];
	for(int i=1; i<sz(str); i++) {
		if(str[i] == last)
			h += 5;
		else {
			h += 10;
			last = str[i];
		}
	}
	cout << h;
}
