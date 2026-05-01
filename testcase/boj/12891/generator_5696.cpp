#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate length N in [1,30] with bias
    int wN = rnd.any(vector<int>{-3, -1, 0, 1, 3});
    int N = rnd.wnext(30, wN) + 1;
    // Generate window size P in [1,N] with bias
    int wP = rnd.any(vector<int>{-3, -1, 0, 1, 3});
    int P = rnd.wnext(N, wP) + 1;

    // Build DNA string S with either uniform or skewed distribution
    vector<char> letters = {'A','C','G','T'};
    string S;
    S.reserve(N);
    if (rnd.next() < 0.3) {
        char major = rnd.any(letters);
        double skewProb = rnd.next() * 0.5 + 0.5;  // between 0.5 and 1.0
        for (int i = 0; i < N; i++) {
            if (rnd.next() < skewProb)
                S.push_back(major);
            else
                S.push_back(rnd.any(letters));
        }
    } else {
        for (int i = 0; i < N; i++) {
            S.push_back(rnd.any(letters));
        }
    }

    // Generate total requirement in [0,P] with bias
    int wReq = rnd.any(vector<int>{-3, -1, 0, 1, 3});
    int total_req = rnd.wnext(P+1, wReq);  // yields 0..P

    // Randomly distribute total_req among A,C,G,T
    vector<int> req(4);
    int rem = total_req;
    for (int i = 0; i < 3; i++) {
        int v = rnd.next(0, rem);
        req[i] = v;
        rem -= v;
    }
    req[3] = rem;
    shuffle(req.begin(), req.end());

    // Output
    println(N, P);
    println(S);
    println(req[0], req[1], req[2], req[3]);

    return 0;
}
