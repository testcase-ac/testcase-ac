#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

char win_move(char c) {
    if (c == 'R') return 'P';
    if (c == 'P') return 'S';
    return 'R';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int t = rnd.next(1, 10);
    println(t);
    const string moves = "RPS";
    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 20);
        println(n);
        int type = rnd.next(0, 2); // 0=uniform,1=bias p1 wins,2=bias tie
        double prob = rnd.next(5, 9) / 10.0;
        for (int i = 0; i < n; ++i) {
            char c1, c2;
            if (type == 0) {
                // uniform random
                c1 = rnd.any(moves);
                c2 = rnd.any(moves);
            } else if (type == 1) {
                // bias towards player1 wins
                if (rnd.next() < prob) {
                    c2 = rnd.any(moves);
                    c1 = win_move(c2);
                } else {
                    c1 = rnd.any(moves);
                    c2 = rnd.any(moves);
                }
            } else {
                // bias towards ties
                if (rnd.next() < prob) {
                    c1 = c2 = rnd.any(moves);
                } else {
                    c1 = rnd.any(moves);
                    c2 = rnd.any(moves);
                }
            }
            printf("%c %c\n", c1, c2);
        }
    }
    return 0;
}
