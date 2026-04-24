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
	int n;
	cin >> n;
	while(n--) {
		int a, b, c;
		cin >> a >> b >> c;
		b -= c;
		if(a > b) cout << "do not advertise\n";
		else if (a < b) cout << "advertise\n";
		else cout << "does not matter\n";
	}
}
