#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: small, medium, large
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) N = rnd.next(1, 5);
    else if (mode == 1) N = rnd.next(6, 15);
    else N = rnd.next(16, 50);

    // Choose M range: low, mid, high
    vector<pair<int,int>> Mranges = {{1,10}, {11,50}, {51,100}};
    auto seg = rnd.any(Mranges);
    int M = rnd.next(seg.first, seg.second);

    vector<int> scores;
    if (N == 1) {
        // Only one subject, must be positive
        scores.push_back(M);
    } else {
        // Determine number of zeros among the other N-1 scores
        vector<int> ts = {-2, -1, 0, 1, 2};
        int t = rnd.any(ts);
        int z = rnd.wnext(N, t);  // between 0 and N-1
        if (z > N-1) z = N-1;
        // Start with one maximum score
        scores.push_back(M);
        // Add zeros
        for (int i = 0; i < z; i++) scores.push_back(0);
        // Add other random scores in [0, M]
        for (int i = z; i < N-1; i++) {
            scores.push_back(rnd.next(0, M));
        }
        // Shuffle all scores
        shuffle(scores.begin(), scores.end());
    }

    // Output
    println(N);
    println(scores);

    return 0;
}
