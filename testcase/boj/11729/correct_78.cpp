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

void hanoi(int n, int start, int finish, int middle) {
	if(n == 1)
		printf("%d %d\n", start, finish);
	else {
		hanoi(n-1, start, middle, finish);
		printf("%d %d\n", start, finish);
		hanoi(n-1, middle, finish, start);
	}
}

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	printf("%d\n", (1<<n)-1);
	hanoi(n, 1, 3, 2);
}
