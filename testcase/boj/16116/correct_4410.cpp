#include <bits/stdc++.h>
using namespace std;
bool exist[216];
int c2i[256], blocks[8][3] = {{0,1,4},{4,1,2},{1,0,5},{1,5,2},{4,2,3},{3,2,5},{4,3,0},{3,5,0}};
int h(int *a) {
	return a[0]*36+a[1]*6+a[2];
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int id = 0;
	for(char c: {'B','G','O','R','W','Y'})
		c2i[c] = id++;
	for(int i=0; i<8; i++) {
		int a[6];
		for(int j=0; j<3; j++) {
			char c;
			cin >> c;
			a[j] = a[j+3] = c2i[c];
		}
		exist[h(a)] = exist[h(a+1)] = exist[h(a+2)] = true;
	}
	int perm[] = {0,1,2,3,4,5};
	do {
		bool ok = true;
		for(int *b: blocks) {
			int a[] = {perm[b[0]], perm[b[1]], perm[b[2]]};
			if(!exist[h(a)]) {
				ok = false;
				break;
			}
		}
		if(ok) return !(cout << "YES");
	}while(next_permutation(perm,perm+6));
	cout << "NO";
}
