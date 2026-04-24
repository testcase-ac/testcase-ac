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
	while(!getline(cin, str).eof()) {
		int cnts[4]; set0(cnts);
		for(char c: str) {
			if(islower(c)) cnts[0]++;
			if(isupper(c)) cnts[1]++;
			if(isdigit(c)) cnts[2]++;
			if(c == ' ') cnts[3]++;
		}
		rep(i, 4) {
			cout << cnts[i] << ' ';
		}
		cout << '\n';
	}
}
