#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
int main() {
	int y=1, e=1, s=1, m=1, E, S, M;
	cin >> E >> S >> M;
	while(e != E || s != S || m != M) {
		e++;
		s++;
		m++;
		y++;
		if(e == 16) e=1;
		if(s == 29) s=1;
		if(m == 20) m=1;
	}
	cout << y;

}
