#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int R = rnd.next(6, 8);
    int C = rnd.next(6, 8);
    int T = rnd.next(1, 5);
    println(R, C, T);
    int purifierRow = rnd.next(2, R - 4);
    double zeroProb = rnd.next(0.1, 0.9);
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(j == 0 && (i == purifierRow || i == purifierRow + 1)) {
                cout << -1;
            } else {
                if(rnd.next() < zeroProb) {
                    cout << 0;
                } else {
                    cout << rnd.next(1, 9);
                }
            }
            if(j == C - 1) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
    }

}
