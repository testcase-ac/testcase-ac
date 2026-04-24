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

int goal;
bool canuse[10];
int minstep;
int factorarr[] = {1,10,100,1000,10000,100000};
void solve(int num, int presscnt, int tofill) {
	if(tofill == -1) {
		int tempans = presscnt+abs(goal-num);
		if(!presscnt) return;
		minstep = min(minstep, tempans);
		return;
	}
	if(!presscnt)
		solve(0, 0, tofill-1);
	int factor = factorarr[tofill];
	rep(i, 10) {
		if(!presscnt && !i && tofill) continue; 
		if(!canuse[i]) continue;
		solve(num+factorarr[tofill]*i, presscnt+1, tofill-1);
	}
}

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int m;
	cin >> goal >> m;
	rep(i, 10) canuse[i] = true;
	rep(i, m) {
		int inp;
		cin >> inp;
		canuse[inp] = false;
	}
	minstep = abs(100-goal);
	solve(0, 0, 5);
	cout << minstep;
}
