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
	ios::sync_with_stdio(false);cin.tie(NULL);
	int m1=3000, m2=3000, inp;
	rep(i, 3) {
		cin >> inp;
		m1 = min(m1, inp);
	}
	rep(i, 2) {
		cin >> inp;
		m2 = min(m2, inp);
	}
	cout << (m1 + m2 - 50);


}
