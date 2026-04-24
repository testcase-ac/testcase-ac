#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for maximum M to keep cases small
    const int M_MAX = 30;
    int M = rnd.next(1, M_MAX);

    // Hyper-parameters for biased selection
    vector<int> tvals = {-3, -1, 0, 1, 3};

    // Determine maximum move size (<=22 and <=M) with bias
    int t1 = rnd.any(tvals);
    int raw_max_move = rnd.wnext(min(22, M), t1);
    int max_move = max(1, raw_max_move);

    // Determine K (# of moves) (<=6 and <=max_move) with bias
    int t2 = rnd.any(tvals);
    int raw_K = rnd.wnext(min(max_move, 6), t2);
    int K = max(1, min(raw_K, min(max_move, 6)));

    // Build pool of possible moves [1..max_move], shuffle and pick K distinct
    vector<int> moves;
    for (int i = 1; i <= max_move; ++i) {
        moves.push_back(i);
    }
    shuffle(moves.begin(), moves.end());
    moves.resize(K);
    sort(moves.begin(), moves.end());

    // Output
    println(M);
    println(K);
    println(moves);

    return 0;
}
