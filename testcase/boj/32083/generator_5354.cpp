#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checking
    int N = rnd.next(1, 10);
    int maxDiff = min(20 - N, N * 2);
    int diff = rnd.next(0, maxDiff);
    int M = N + diff;

    // Hyper-parameter: alphabet size choices
    vector<int> Lcand = {1, 2, 3, 5, 10, 26};
    int L = rnd.any(Lcand);

    // Random continuous segment of the uppercase alphabet
    char base = char('A' + rnd.next(0, 26 - L));
    vector<char> alphabet;
    for (int i = 0; i < L; i++) 
        alphabet.push_back(char(base + i));

    // Bias parameters for weighted sampling
    vector<int> ts = {-2, -1, 1, 2};

    // Build string A
    string A;
    A.reserve(N);
    for (int i = 0; i < N; i++) {
        int t = rnd.any(ts);
        int idx = rnd.wnext(L, t);
        A.push_back(alphabet[idx]);
    }

    // Build string B
    string B;
    B.reserve(M);
    for (int i = 0; i < M; i++) {
        int t = rnd.any(ts);
        int idx = rnd.wnext(L, t);
        B.push_back(alphabet[idx]);
    }

    // Output
    println(N, M);
    printf("%s\n", A.c_str());
    printf("%s\n", B.c_str());

    return 0;
}
