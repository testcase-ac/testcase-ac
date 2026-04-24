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

bool state[4][8];
bool turned[4];

inline int another(int d){return (d==1?-1:1);}
void turn(int i, int d) {
	bool lturn = (i != 0 && state[i][6] != state[i-1][2] && !turned[i-1]);
	bool rturn = (i != 3 && state[i][2] != state[i+1][6] && !turned[i+1]);
	turned[i] = true;
	rotate(state[i], state[i]+(d == -1 ? 1 : 7), state[i]+8);
	if(lturn) turn(i-1, another(d));
	if(rturn) turn(i+1, another(d));
}

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	string s;
	rep(i, 4) {
		cin >> s;
		rep(j, 8) {
			state[i][j] = (s[j] == '0' ? false : true);
		}
	}
	int t;
	cin >> t;
	while(t--) {
		int n, d;
		cin >> n >> d;
		turn(n-1, d);
		set0(turned);
	}
	int pt = 0, factor = 1;
	rep(i, 4) {
		pt += (state[i][0] * factor);
		factor *= 2;
	}
	cout << pt;
}	
