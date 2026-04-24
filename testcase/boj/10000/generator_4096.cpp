#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of circles
    int N = rnd.next(1, 10);
    // Maximum radius hyper-parameter
    int rMax = rnd.next(3, 10);
    // Maximum gap between adjacent circles
    int gapMax = rnd.next(0, 5);

    vector<pair<long long, long long>> circles;
    // Starting x-coordinate
    long long x0 = rnd.next(-10, 10);
    long long x = x0;
    long long last_r = 0;
    for (int i = 0; i < N; ++i) {
        long long r = rnd.next(1, rMax);
        if (i == 0) {
            x = x0;
        } else {
            long long gap = rnd.next(0, gapMax);
            x += last_r + r + gap;
        }
        circles.emplace_back(x, r);
        last_r = r;
    }

    // Shuffle to randomize input order
    shuffle(circles.begin(), circles.end());

    // Output
    println(N);
    for (auto &c : circles) {
        println(c.first, c.second);
    }
    return 0;
}
