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
int dr[] = {0,0,-1,1};
int dc[] = {1,-1,0,0};
int n, m;
inline bool isvalid(int r, int c) {
	return r>=0 && r<n && c>=0 && c<m;
}
inline int c2i(char c) {
	switch(c) {
		case 't': return 0;
		case 'u': return 1;
		case 'l': return 2;
		case 'r': return 3;
		case 'f': return 4;
		case 'b': return 5;
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int r, c, K;
	cin >> n >> m >> r >> c >> K;
	int arr[n][m];
	rep(i,n) rep(j,m) cin >> arr[i][j];
	vector<int> dice(6); // T U L R F B
	rep(k, K) {
		int dir, tr, tc;
		cin >> dir;
		dir--;
		tr = r+dr[dir], tc = c+dc[dir];
		if(!isvalid(tr, tc)) continue;
		if(dir == 0) {  // 동
			// T->R->U->L->T
			int temp = dice[c2i('t')];
			dice[c2i('t')] = dice[c2i('l')];
			dice[c2i('l')] = dice[c2i('u')];
			dice[c2i('u')] = dice[c2i('r')];
			dice[c2i('r')] = temp;
		} else if(dir == 1) { // 서
			// T->L->U->R->T
			int temp = dice[c2i('t')];
			dice[c2i('t')] = dice[c2i('r')];
			dice[c2i('r')] = dice[c2i('u')];
			dice[c2i('u')] = dice[c2i('l')];
			dice[c2i('l')] = temp;
		} else if(dir == 2) { // 남
			// T->F->U->B->T
			int temp = dice[c2i('t')];
			dice[c2i('t')] = dice[c2i('b')];
			dice[c2i('b')] = dice[c2i('u')];
			dice[c2i('u')] = dice[c2i('f')];
			dice[c2i('f')] = temp;
		} else { // 복
			int temp = dice[c2i('t')];
			dice[c2i('t')] = dice[c2i('f')];
			dice[c2i('f')] = dice[c2i('u')];
			dice[c2i('u')] = dice[c2i('b')];
			dice[c2i('b')] = temp;
		}
		cout << dice[c2i('t')] << '\n';
		if(arr[tr][tc]) {
			dice[c2i('u')] = arr[tr][tc];
			arr[tr][tc] = 0;
		} else {
			arr[tr][tc] = dice[c2i('u')];
		}
		r = tr;
		c = tc;
	}

}
