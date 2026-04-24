#include <bits/stdc++.h>
using namespace std;

char arr[100][101];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C;
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
	}
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			int out = -1;
			for(int k=j; k>=0; k--) {
				if(arr[i][k] == 'c') {
					out = j-k;
					break;
				}
			}
			cout << out << ' ';
		}
		cout << '\n';
	}

}
