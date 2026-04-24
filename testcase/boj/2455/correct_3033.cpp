#include <iostream>
#include <stdio.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
	int a, b, curr = 0, max=0;
	rep(i, 4) {
		cin >> a >> b;
		curr -= a;
		curr += b;
		if(curr > max)
			max = curr;
	}
	cout << max;
}
