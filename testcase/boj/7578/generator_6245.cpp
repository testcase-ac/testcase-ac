#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose N small, medium, or larger (<=30)
    int cat = rnd.next(0, 2);
    int N;
    if (cat == 0) {
        N = rnd.next(1, 5);
    } else if (cat == 1) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 30);
    }

    // Hyper-parameter: choose ID range type (tight, moderate, very sparse)
    int idt = rnd.next(0, 2);
    int id_max;
    if (idt == 0) {
        // IDs 0..N-1
        id_max = N - 1;
    } else if (idt == 1) {
        // IDs between 0 and a small multiple of N
        id_max = rnd.next(N, max(N + 1, N * 5));
    } else {
        // IDs up to 1e6
        id_max = 1000000;
    }

    // Generate N unique IDs in [0, id_max]
    set<int> sid;
    while ((int)sid.size() < N) {
        sid.insert(rnd.next(0, id_max));
    }
    vector<int> labels(sid.begin(), sid.end());
    // Shuffle to form A
    shuffle(labels.begin(), labels.end());
    vector<int> A = labels;

    // Generate B by different patterns: identity, reversed, random, nearly sorted
    vector<int> B = A;
    int mode = rnd.next(0, 3);
    if (mode == 1) {
        reverse(B.begin(), B.end());
    } else if (mode == 2) {
        shuffle(B.begin(), B.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, N / 3));
        for (int i = 0; i < swaps; i++) {
            int x = rnd.next(0, N - 1);
            int y = rnd.next(0, N - 1);
            swap(B[x], B[y]);
        }
    }
    // mode==0 leaves B identical to A

    // Output
    println(N);
    println(A);
    println(B);

    return 0;
}
