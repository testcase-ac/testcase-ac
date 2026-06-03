#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> corners = {1, 8, 57, 64};
    vector<int> rankEdges;
    for (int rank = 0; rank < 8; ++rank) {
        rankEdges.push_back(rank * 8 + 1);
        rankEdges.push_back(rank * 8 + 8);
    }

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.any(corners);
    } else if (mode == 1) {
        n = rnd.any(rankEdges);
    } else if (mode == 2) {
        int rank = rnd.next(0, 7);
        int file = rnd.next(0, 7);
        n = rank * 8 + file + 1;
    } else if (mode == 3) {
        n = rnd.next(2, 63);
    } else {
        n = rnd.next(1, 64);
    }

    println(n);
    return 0;
}
