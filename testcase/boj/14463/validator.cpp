#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50000, "N");
    inf.readEoln();

    // There must be exactly 2N following lines, each with a cow ID in [1, N].
    vector<int> cnt(N+1, 0);
    for (int i = 0; i < 2 * N; i++) {
        int x = inf.readInt(1, N, "cow_id");
        inf.readEoln();
        cnt[x]++;
    }

    // Each cow ID must appear exactly twice
    for (int i = 1; i <= N; i++) {
        ensuref(cnt[i] == 2,
                "Cow ID %d appears %d times; it must appear exactly twice", 
                i, cnt[i]);
    }

    // No extra data
    inf.readEof();
    return 0;
}
