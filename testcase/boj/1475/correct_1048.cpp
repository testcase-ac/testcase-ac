#include <iostream>
#include <stdio.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
	string str;
	cin >> str;
	vector<int> arr(9);
	for(char c: str) {
		int a = (int)(c - '0');
		arr[(a == 9 ? 6 : a)]++;
	}
	arr[6] = (arr[6] + 1) / 2;
	int m = 0;
	rep(i, 9) m = max(m, arr[i]);
	cout << m;
}
