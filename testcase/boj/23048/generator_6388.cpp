#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N;
    // Occasionally test smallest cases
    if (rnd.next(0, 9) == 0) {
        N = 1;
    } else if (rnd.next(0, 9) == 0) {
        N = 2;
    } else {
        // Bias N toward small or large sometimes, uniform other times
        int t = rnd.next(-3, 3);
        // rnd.wnext gives [0, hi-1], so +1 gives [1, hi]
        N = rnd.wnext(500000, t) + 1;
        N = max(N, 3);
    }
    println(N);
    return 0;
}
