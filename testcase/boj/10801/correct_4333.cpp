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
	int A[10], B[10];
	rep(i, 10) cin >> A[i];
	rep(i, 10) cin >> B[i];
	int a=0, b=0;
	rep(i, 10) {
		if(A[i] > B[i]) a++;
		else if(A[i] < B[i]) b++;
	}
	if(a > b) cout << 'A';
	else if(a < b) cout << 'B';
	else cout << 'D';
}
