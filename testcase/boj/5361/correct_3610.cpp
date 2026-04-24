#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <iomanip>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	double arr[] = {350.34, 230.9, 190.55, 125.3, 180.9};
	cout << setprecision(2) << fixed;
	int n;
	cin >> n;
	while(n--) {
		int ARR[5];
		rep(i, 5) cin >> ARR[i];
		double output = 0;
		rep(i, 5) output += (arr[i] * ARR[i]);
		cout << '$' << output << '\n';
	}

}
