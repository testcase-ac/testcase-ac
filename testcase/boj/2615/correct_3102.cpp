#include <bits/stdc++.h>
using namespace std;

int arr[19][19], di[] = {-1,0,1,1}, dj[] = {1,1,1,0};
int main() {
	for(int i=0; i<19; i++) {
		for(int j=0; j<19; j++) {
			cin >> arr[i][j];
		}
	}
	for(int j=0; j<19; j++) {
		for(int i=0; i<19; i++) {
			if(!arr[i][j]) continue;
			for(int t=0; t<4; t++) {
				int cnt = 1;
				int ti = i + di[t], tj = j + dj[t];
				while(0 <= ti && ti < 19 && 0 <= tj && tj < 19 && arr[ti][tj] == arr[i][j]) {
					cnt++;
					ti += di[t], tj += dj[t];
				}
				ti = i - di[t], tj = j - dj[t];
				while(0 <= ti && ti < 19 && 0 <= tj && tj < 19 && arr[ti][tj] == arr[i][j]) {
					cnt++;
					ti -= di[t], tj -= dj[t];
				}
				if(cnt == 5) {
					return !printf("%d\n%d %d", arr[i][j], i+1, j+1);
				}
			}
		}
	}
	puts("0");
}
