#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s;
	cin >> s;
	int joi=0, ioi=0;
	rep(i, sz(s)-2) {
		if(s[i+1] == 'O' && s[i+2] == 'I') {
			if(s[i] == 'J')
				joi++;
			else if(s[i] == 'I')
				ioi++;
		}
	}
	cout << joi << '\n' << ioi;
}
