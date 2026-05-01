#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in small, medium, or large range
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(1, 10);
    } else if (mode == 1) {
        N = rnd.next(11, 30);
    } else {
        N = rnd.next(31, 100);
    }

    // Generate initial switch states
    vector<int> states(N);
    for (int i = 0; i < N; i++) {
        states[i] = rnd.next(0, 1);
    }

    // Number of students S, vary with N but cap at 100
    int maxS = min(N * 3, 100);
    int S = rnd.wnext(maxS, rnd.next(-1, 1)) + 1;

    // Probability of a female student
    double femaleProb = rnd.next(0.0, 1.0);

    // Generate student operations
    vector<pair<int,int>> ops;
    ops.reserve(S);
    for (int i = 0; i < S; i++) {
        int gender = (rnd.next() < femaleProb ? 2 : 1);
        int t = rnd.next(-2, 2);
        int num = rnd.wnext(N, t) + 1;  // 1..N
        ops.emplace_back(gender, num);
    }

    // Output
    println(N);
    println(states);
    println(S);
    for (auto &p : ops) {
        println(p.first, p.second);
    }
    return 0;
}
