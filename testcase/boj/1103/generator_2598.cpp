/* generator code */
#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // board dimensions small and hand-checkable
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    // probability of a hole in non-start cells
    double holeProb = rnd.next(0.0, 1.0);

    // output dimensions
    println(N, M);
    for (int i = 1; i <= N; i++) {
        string row;
        row.reserve(M);
        for (int j = 1; j <= M; j++) {
            if (i == 1 && j == 1) {
                // start cell must be a digit 1..9
                char c = char('1' + rnd.next(0, 8));
                row.push_back(c);
            } else {
                if (rnd.next() < holeProb) {
                    row.push_back('H');
                } else {
                    char c = char('1' + rnd.next(0, 8));
                    row.push_back(c);
                }
            }
        }
        println(row);
    }

    return 0;
}
