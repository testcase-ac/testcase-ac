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
	//ios::sync_with_stdio(false);cin.tie(NULL);
	string s;
	cin >> s;
	if(s[0] == 'F') {
		cout << "0.0";
	} else {
		int i = ('A' - s[0] + 4)*10;
		if(s[1] == '+') i += 3;
		else if (s[1] == '-') i-= 3;
		printf("%d.%d", i/10, i%10); 
	}
}
