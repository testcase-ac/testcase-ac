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

int arr[26];
int main() {
	string str;
	cin >> str;
	for(char c: str) {
		arr[(int)(c-'a')]++;
	}
	rep(i, 26) {
		cout << arr[i] << ' ';
	}
}
