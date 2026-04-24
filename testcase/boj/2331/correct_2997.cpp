#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
int A, P;
int D(int n) {
	int ret = 0;
	while(n) {
		int i = n % 10;
		int f = 1;
		rep(k, P) f*=i;
		ret += f;
		n /= 10;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> A >> P;
	map<int,int> mp;
	int i = 0;
	int num = A;
	while(1) {
		//printf("num=%d.",num);
		if(mp.find(num) == mp.end()) {
			mp[num] = i;
			//printf("mp[num]=%d.", i);
		} else {
			return !(cout << mp[num]);
		}
		num = D(num);
		i++;
	}
}
