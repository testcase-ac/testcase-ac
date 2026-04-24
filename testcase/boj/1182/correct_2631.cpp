#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
#define MAXN 20
int arr[MAXN], ans, goal, maxi;
void rec(int i, int sum, bool allnotinc) {
	if(i == maxi) {
		if(!allnotinc && goal == sum) ans++;
		return;
	}
	rec(i+1, sum+arr[i], false);
	rec(i+1, sum, allnotinc);
}

int main() {
	int n, s;
	cin >> n >> s;
	rep(i, n) cin >> arr[i];
	maxi = n;
	goal = s;
	rec(0, 0, true);
	cout << ans;
}
