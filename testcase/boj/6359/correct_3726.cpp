#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 100
int ansarr[MAXN+1];
bool opened[MAXN+1];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	for(int i=1; i<=MAXN; i++) {
		for(int j=i; j<=MAXN; j+=i) {
			opened[j] = !opened[j];
		}
		for(int j=1; j<=i; j++) {
			if(opened[j]) ansarr[i]++;
		}
	}
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		cout << ansarr[n] << '\n';
	}
}
