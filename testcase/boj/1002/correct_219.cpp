#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define sq(i) ((i)*(i))

using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int x1, y1, r1, x2, y2, r2;
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		if(x1 == x2 && y1 == y2 && r1 == r2) {
			cout << "-1\n";
			continue;
		}
		int distsq = sq(x1-x2) + sq(y1-y2);
		if(sq(r1+r2) < distsq) {
			cout << "0\n";
		} else if(sq(r1+r2) == distsq) {
			cout << "1\n";
		} else {
			if(sq(r1-r2) == distsq) {
				cout << "1\n";
			} else if(sq(r1-r2) > distsq) {
				cout << "0\n";
			} else {
				cout << "2\n";
			}
		}
	}
}
