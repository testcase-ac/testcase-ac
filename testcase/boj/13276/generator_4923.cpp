#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 1) Choose length of S
    int N = rnd.next(2, 10);

    // 2) Choose a small alphabet size
    int kLetters = rnd.next(1, min(5, N));
    vector<char> alphab;
    for (int i = 0; i < kLetters; i++) {
        alphab.push_back(char('a' + i));
    }

    // 3) Build S with some runs for diversity
    double block_prob = rnd.next();
    string S;
    S.reserve(N);
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < block_prob) {
            S.push_back(S[i - 1]);
        } else {
            S.push_back(rnd.any(alphab));
        }
    }

    // 4) Choose lengths for A and B
    int LA = rnd.next(1, min(N, 3));
    int LB = rnd.next(1, min(N, 3));

    // 5) Decide relation of A and B to S
    //    0: both in S, 1: A in S, B not, 2: both random, 3: B in S, A not
    int mode = rnd.next(0, 3);
    string A, B;
    char outside = char('a' + kLetters); // not in S

    if (mode == 0) {
        int posA = rnd.next(0, N - LA);
        A = S.substr(posA, LA);
        int posB = rnd.next(0, N - LB);
        B = S.substr(posB, LB);
    } else if (mode == 1) {
        int posA = rnd.next(0, N - LA);
        A = S.substr(posA, LA);
        B = string(LB, outside);
    } else if (mode == 2) {
        A.clear();
        B.clear();
        for (int i = 0; i < LA; i++) A.push_back(rnd.any(alphab));
        for (int i = 0; i < LB; i++) B.push_back(rnd.any(alphab));
    } else {
        int posB = rnd.next(0, N - LB);
        B = S.substr(posB, LB);
        A = string(LA, outside);
    }

    // 6) Output
    println(S);
    println(A);
    println(B);
    return 0;
}
