#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXC = 100;  // maximum coordinate
    const int MAXN = 10;   // maximum number of cities

    // number of cities and factory position
    int N = rnd.next(1, MAXN);
    int L = rnd.next(1, MAXC);

    // decide how many cities lie to the left of the factory
    int kLeft;
    if (L == 1) {
        // no room to the left
        kLeft = 0;
    } else if (L == MAXC) {
        // no room to the right, so all on the left
        kLeft = N;
    } else {
        int mixType = rnd.next(0, 2);
        if (mixType == 0) {
            // bias towards many left cities
            kLeft = rnd.wnext(N + 1, 1);
        } else if (mixType == 1) {
            // bias towards few left cities
            kLeft = rnd.wnext(N + 1, -1);
        } else {
            // uniform
            kLeft = rnd.next(0, N);
        }
    }
    if (kLeft > N) kLeft = N;
    int kRight = N - kLeft;

    // generate city coordinates
    vector<int> xs;
    // left side cities
    for (int i = 0; i < kLeft; i++) {
        xs.push_back(rnd.next(1, L - 1));
    }
    // right side cities
    for (int i = 0; i < kRight; i++) {
        xs.push_back(rnd.next(L + 1, MAXC));
    }
    // shuffle so delivery order in input is random
    shuffle(xs.begin(), xs.end());

    // output
    println(N, L);
    for (int x : xs) {
        println(x);
    }

    return 0;
}
