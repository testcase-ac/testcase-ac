#include <bits/stdc++.h>
using namespace std;
int arr[4] = {1,0,0,2};
pair<int, int> swp[6] = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	for(char c: s) {
		int a, b;
		tie(a, b) = swp[c-'A'];
		swap(arr[a], arr[b]);
	}
	int a1, a2;
	for(int i=0; i<4; i++) {
		if(arr[i] == 1) a1 = i+1;
		else if(arr[i] == 2) a2 = i+1;
	}
	cout << a1 << ' ' << a2;
}
