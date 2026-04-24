#include <iostream>
#include <cstring>

using namespace std;

char arr[201][201];
int tm[201][201];
int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R, C, N;
    cin >> R >> C >> N;
    for (int i = 0; i < R; i++) {
        cin >> arr[i];
        for (int j = 0; j < C; j++) {
            tm[i][j] = (arr[i][j] == 'O' ? 0 : -1);
        }
    }
    if(N == 1) {
        for(int i=0; i<R; i++) {
            for(int j=0; j<C; j++) {
                cin >> arr[i][j];
            }
        }
    }
    for(int t=2; t<=N; t++) {
        if(t % 2 == 0) {
            for(int i=0; i<R; i++) {
                for(int j=0; j<C; j++) {
                    if(arr[i][j] != 'O') {
                        arr[i][j] = 'O';
                        tm[i][j] = t;
                    }
                }
            }
        } else {
            for(int i=0; i<R; i++) {
                for(int j=0; j<C; j++) {
                    if(tm[i][j] != t-1) {
                        arr[i][j] = '.';
                        for(int x=0; x<4; x++) {
                            int rx = i + dr[x], cx = j + dc[x];
                            if(rx < 0 || rx >= R || cx < 0 || cx >= C) continue;
                            arr[rx][cx] = '.';
                        }
                        tm[i][j] = t;
                    }
                }
            }
        }
    }
    for(int i=0; i<R; i++) {
        cout << arr[i] << '\n';
    }
}
