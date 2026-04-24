#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C, A, B;
	cin >> R >> C >> A >> B;
	char ch[2] = {'X', '.'};
	for(int r=0; r<R; r++) {
		int i;
		for(int a=0; a<A; a++) {
			i = r&1;
			for(int c=0; c<C; c++) {
				for(int b=0; b<B; b++) {
					cout << ch[i];
				}
				i ^= 1;
			}
			cout << '\n';
		}
	}
}
