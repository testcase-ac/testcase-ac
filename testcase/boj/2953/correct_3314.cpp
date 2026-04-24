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
	int ansi, anspt=-1;
	rep(i, 5) {
		int pt=0, temp;
		rep(j, 4) {
			cin >> temp;
			pt+=temp;
		}
		if(pt > anspt) {
			ansi = i+1;
			anspt = pt;
		}
	}
	printf("%d %d", ansi, anspt);
}
