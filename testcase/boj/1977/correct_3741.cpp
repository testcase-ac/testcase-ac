#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define square(i) ((i)*(i))
using namespace std;

int main() {
	int m, n;
	cin >> m >> n;
	int anssum = 0;
	int ansmin = 100000;
	for(int i=1;i<=100; i++) {
		int s = square(i);
		if(m <= s && s <= n) {
			if(s < ansmin) ansmin = s;
			anssum += s;
		}
	}
	if(anssum == 0)
		return !(cout << -1);
	cout << anssum << '\n' << ansmin;
}
