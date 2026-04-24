#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int R = 1, C = 1;
    while(R * C <= 2) {
        R = rnd.next(1, 6);
        C = rnd.next(1, 6);
    }
    println(R, C);
    vector<string> arr(R, string(C, '.'));
    int r = rnd.next(0, R-1), c = rnd.next(0, C-1);
    arr[r][c] = 'J';
    int F_count = rnd.next(1, (R*C-1)/2);
    int W_count = rnd.next(0, R*C-1-F_count);
    vector<pair<int, int>> cands;
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            if(arr[i][j] == '.') {
                cands.push_back({i, j});
            }
        }
    }
    shuffle(cands.begin(), cands.end());
    for(int i=0; i<F_count; i++) {
        arr[cands[i].first][cands[i].second] = 'F';
    }
    for(int i=F_count; i<F_count+W_count; i++) {
        arr[cands[i].first][cands[i].second] = '#';
    }
    for(string s : arr) {
        println(s);
    }
}
