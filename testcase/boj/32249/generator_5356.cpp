#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for N and M bias
    int tN = rnd.next(-2, 2);
    int tM = rnd.next(-2, 2);
    int N = rnd.wnext(10, tN) + 1; // biases small or large depending on tN
    int M = rnd.wnext(10, tM) + 1; // biases small or large depending on tM

    // Prepare cards: exactly N*M A's and N*M B's
    int total = 2 * N * M;
    int half = N * M;
    vector<char> cards;
    cards.reserve(total);
    for (int i = 0; i < half; i++) cards.push_back('A');
    for (int i = 0; i < half; i++) cards.push_back('B');
    shuffle(cards.begin(), cards.end());

    // Assign to Alice and Bob
    vector<string> alice(N, string(M, 'A'));
    vector<string> bob(N, string(M, 'A'));
    for (int i = 0; i < N * M; i++) {
        alice[i / M][i % M] = cards[i];
        bob[i / M][i % M]   = cards[N * M + i];
    }

    // Number of swap queries, small for hand-checkability
    int maxQ = min(20, total);
    int Q = rnd.next(1, maxQ);

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) println(alice[i]);
    for (int i = 0; i < N; i++) println(bob[i]);
    println(Q);
    for (int i = 0; i < Q; i++) {
        int r1 = rnd.next(1, N);
        int c1 = rnd.next(1, M);
        int r2 = rnd.next(1, N);
        int c2 = rnd.next(1, M);
        println(r1, c1, r2, c2);
    }
    return 0;
}
