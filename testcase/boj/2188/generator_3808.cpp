#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    double zeroProb = rnd.next(0.0, 0.5);
    double fullProb = rnd.next(0.0, 0.5);
    double intervalProb = rnd.next(0.0, 1.0);

    // Output N and M
    println(N, M);

    // Generate each cow's preference list
    for (int i = 0; i < N; ++i) {
        vector<int> choice;
        if (rnd.next() < zeroProb) {
            // no choices
        } else if (rnd.next() < fullProb) {
            // all stalls
            choice.resize(M);
            for (int j = 0; j < M; ++j) choice[j] = j + 1;
        } else if (rnd.next() < intervalProb) {
            // interval of stalls
            int l = rnd.next(1, M);
            int r = rnd.next(l, M);
            for (int j = l; j <= r; ++j) choice.push_back(j);
        } else {
            // random subset of stalls
            int t = rnd.any(vector<int>{-1, 0, 1});
            int S = rnd.wnext(M, t) + 1;  // between 1 and M
            vector<int> all(M);
            for (int j = 0; j < M; ++j) all[j] = j + 1;
            shuffle(all.begin(), all.end());
            choice.assign(all.begin(), all.begin() + S);
        }
        if (choice.empty()) {
            println(0);
        } else {
            println(choice.size(), choice);
        }
    }
    return 0;
}
