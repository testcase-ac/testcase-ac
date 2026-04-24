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

string compress(vector<string> &arr, int x, int y, int size) {
	string ret;
	if(size == 1) {
		ret += arr[x][y];
		return ret;
	}
	char allsame = arr[x][y];
	bool issame = true;
	rep(i, size) {
		rep(j, size) {
			if(allsame != arr[x+i][y+j]) {
				issame = false;
				goto out;
			}
		}
	}
	out:;
	if(issame) {
		ret += allsame;
	} else {
		ret += '(';
		ret += compress(arr, x, y, size/2);
		ret += compress(arr, x, y+size/2, size/2);
		ret += compress(arr, x+size/2, y, size/2);
		ret += compress(arr, x+size/2, y+size/2, size/2);
		ret += ')';
	}
	return ret;
}


int main() {
	int n;
	cin >> n;
	vector<string> arr(n);
	rep(i, n) cin >> arr[i];
	cout << compress(arr, 0, 0, n);

}
