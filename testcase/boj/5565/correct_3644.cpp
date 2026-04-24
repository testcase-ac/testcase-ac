#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

int main() {
	int n, temp;
	cin >> n;
	rep(i, 9) {
		cin >> temp;
		n -= temp;
	}
	cout << n;
}
