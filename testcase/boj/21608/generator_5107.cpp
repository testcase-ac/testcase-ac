#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter 1: grid size N
    int N = rnd.next(3, 6);
    int S = N * N;

    // Hyper-parameter 2: seating order
    vector<int> order(S);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    // Output N
    println(N);
    // For each student in the chosen order, pick 4 liked students
    for (int stu : order) {
        // Build candidate pool excluding the student itself
        vector<int> cand;
        cand.reserve(S-1);
        for (int x = 1; x <= S; ++x)
            if (x != stu) cand.push_back(x);
        // Hyper-parameter 3: diversity in liking sets
        // with 50% chance take contiguous window, else fully random
        if (rnd.next(0,1) == 0 && S > 5) {
            // choose a random window of size up to S/2
            int win = min((int)cand.size(), max(4, S/2));
            int start = rnd.next(0, (int)cand.size() - win);
            vector<int> window(cand.begin() + start, cand.begin() + start + win);
            shuffle(window.begin(), window.end());
            window.resize(4);
            println(stu, window);
        } else {
            // fully random selection
            shuffle(cand.begin(), cand.end());
            cand.resize(4);
            println(stu, cand);
        }
    }
    return 0;
}
