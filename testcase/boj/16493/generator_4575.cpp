#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of days (N) and number of chapters (M)
    int N = rnd.next(1, 30);
    int M = rnd.next(1, 10);

    // Generate chapters with diverse time/page distributions
    vector<pair<int,int>> chapters;
    for (int i = 0; i < M; i++) {
        // Hyper-parameter biases for this chapter
        int timeBias  = rnd.next(-1, 1);  // -1: prefer small times, 1: prefer large times
        int pageBias  = rnd.next(-1, 1);  // -1: prefer small pages, 1: prefer large pages

        // rnd.wnext(hi, t) gives a number in [0, hi-1] skewed by t
        int ti = rnd.wnext(20, timeBias) + 1;   // reading time in [1,20]
        int pi = rnd.wnext(300, pageBias) + 1;  // pages in [1,300]

        chapters.emplace_back(ti, pi);
    }

    // Shuffle so item order is random
    shuffle(chapters.begin(), chapters.end());

    // Output
    println(N, M);
    for (auto &c : chapters) {
        println(c.first, c.second);
    }

    return 0;
}
