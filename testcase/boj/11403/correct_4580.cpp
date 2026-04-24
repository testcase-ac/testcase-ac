#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

#define MAXN 100
int arr[MAXN][MAXN];

int main() {
	int n;
	cin >> n;
	rep(i, n) {
		rep(j, n) {
			cin >> arr[i][j];
		}
	}
	rep(i, n) {
		rep(j, n) {
			rep(k, n) {  // node j can go to node k with help of node i
				if(arr[i][k] && arr[j][i])
					arr[j][k] = 1;
			}
		}
	}
	rep(i, n) {
		rep(j, n) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
}
