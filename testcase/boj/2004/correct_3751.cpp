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
/*
n 		t1,f1,min(t1,f1)
m 		t2,f2,min(t2,f2)
n-m		t3,f3,min(t3,f3)
min(t1,f1)-min(t2,f2)-min(t3,f3)
min(t1-t2-t3,f1-f2-f3)
*/
int s2(int x) {  // find # of factor 2 in factorial(x)
	int cnt2=0;
	for(ll t=2; t<=x; t*=2)
		cnt2 += x/t;
	return cnt2;
}
int s5(int x) {  // find # of factor 5 in factorial(x)
	int cnt5=0;
	for(ll t=5; t<=x; t*=5)
		cnt5 += x/t;
	return cnt5;
}

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	cout << min(s2(n)-s2(m)-s2(n-m), s5(n)-s5(m)-s5(n-m));
}
