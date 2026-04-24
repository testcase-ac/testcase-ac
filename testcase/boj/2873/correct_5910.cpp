#include <iostream>
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

inline bool eq(int x1, int y1, int x2, int y2) { return x1==x2 && y1==y2;}
char s[1000000];
int p=0;
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int R, C;
	cin >> R >> C;
	if(R % 2) {
		bool right = true;
		int r = 0;
		while(r < R) {
			rep(i, C-1) s[p++] = (right ? 'R' : 'L');
			if(r < R-1) s[p++] = 'D';
			r++;
			right = !right;	
		}
	} else if(C % 2) {
		bool down = true;
		int c = 0;
		while(c < C) {
			rep(i, R-1) s[p++] = (down ? 'D' : 'U');
			if(c < C-1) s[p++] = 'R';
			c++;
			down = !down;
		}
	} else {
		int arr[R][C];
		rep(i,R) rep(j, C) cin >> arr[i][j];
		int mr, mc, minv = 1000000007;
		for(int r=0; r<R; r++) {
			for(int c=(r%2?0:1); c<C; c+=2) {
				if(arr[r][c] < minv) {
					minv = arr[r][c];
					mr = r, mc = c;
				}
			}
		}
		int c = 0, r = 0;
		while(r < R) {
			if(mr == r || mr == r+1) {
				bool uord = true;
				while(!eq(r, c, mr|1, C-1)) {
					if(uord) {
						if(eq(r^1,c,mr,mc)) {
							s[p++] = 'R';
							c++;
							continue;
						}
						s[p++] = (r&1?'U':'D');
						r^=1;
					} else {
						s[p++] = 'R';
						c++;
					}
					uord = !uord;
				}
				if(r < R-1) s[p++] = 'D';
				r++;
			} else {
				rep(j,C-1) s[p++] = (c?'L':'R');
				s[p++] = 'D';
				rep(j,C-1) s[p++] = (c?'R':'L');
				r+=2;
				if(r < R-1) s[p++] = 'D';
			}
		}
	}
	cout << s;
}
