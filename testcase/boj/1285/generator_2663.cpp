#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N between 1 and 10
    int N = rnd.next(1, 10);
    // Skew factor for density of T's
    int t = rnd.next(1, 3) * (rnd.next(2) == 0 ? -1 : 1);
    // threshold in [0,99], skewed by wnext
    int threshold = rnd.wnext(100, t);
    // Output N and the grid
    println(N);
    for (int i = 0; i < N; i++) {
        string row;
        row.reserve(N);
        for (int j = 0; j < N; j++) {
            // rand < threshold gives T, else H
            row += (rnd.next(100) < threshold ? 'T' : 'H');
        }
        println(row);
    }
    return 0;
}
