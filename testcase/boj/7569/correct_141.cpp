#include <cstdio>
#include <queue>

#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
int dr[] = {1,-1,0,0,0,0};
int dc[] = {0,0,1,-1,0,0};
int dh[] = {0,0,0,0,1,-1};

int R, C, H;
inline int isvalid(int h, int r, int c) {
	return (h>=0) && (h<H) && (r>=0) && (r<R) && (c>=0) && (c<C);
}
char buf[1<<15];
int idx = 1<<15;
inline char read()
{
	if (idx == 1<<15)
    {
        fread(buf, 1, 1<<15, stdin);
        idx = 0;
    }
    return buf[idx++];
}
inline int readInt()
{
	int sum = 0;
    bool fl = false;
    char nw = read();
    
    while (nw == ' ' || nw == '\n' || nw == '\r') nw = read();
    if (nw == '-') fl = true, nw = read();
    while (nw >= '0' && nw <= '9')
    {
        sum = sum*10 + nw-48;
        nw = read();
    }
    
    return fl ? -sum : sum;
}
typedef struct pos {
	int h,r,c;
}pos;

int main() {
	C = readInt();
	R = readInt();
	H = readInt();
	int arr[H][R][C];
	int zerocnt = 0;
	queue<pos> que;
	rep(h, H) {
		rep(r, R) {
			rep(c, C) {
				arr[h][r][c] = readInt();
				if(arr[h][r][c] == 0)
					zerocnt++;
				else if(arr[h][r][c] == 1)
					que.push((pos){h,r,c});
			}
		}
	}
	int ans = -1;
	while(!que.empty()) {
		int s = sz(que);
		while(s--) {
			pos p = que.front();
			que.pop();
			rep(i, 6) {	
				int th=p.h+dh[i], tr=p.r+dr[i], tc=p.c+dc[i];
				if(isvalid(th, tr, tc) && arr[th][tr][tc] == 0) {
					arr[th][tr][tc] = 1;
					zerocnt--;
					que.push((pos){th,tr,tc});
				}
			}
		}
		ans++;
	}
	if(!zerocnt) {
		printf("%d\n", ans);
	} else {
		printf("-1");
	}
}