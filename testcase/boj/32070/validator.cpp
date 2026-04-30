#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Frequency count for colors 1..N
    vector<int> freq(N + 1, 0);

    // Read the N boxes, each with two balls A_i and B_i
    for (int i = 1; i <= N; i++) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readEoln();

        // Count occurrences
        freq[a]++;
        freq[b]++;
    }

    // Check that each color appears exactly twice in total
    for (int color = 1; color <= N; color++) {
        ensuref(freq[color] == 2,
                "Color %d appears %d times but must appear exactly twice",
                color, freq[color]);
    }

    // No extra data
    inf.readEof();
    return 0;
}
