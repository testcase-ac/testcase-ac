#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    long long L = inf.readLong(2LL, 1000000000000LL, "L");
    inf.readEoln();

    // Track occupied positions (junction, distance)
    set<pair<char, long long>> occupied;
    for (int i = 0; i < N; i++) {
        // Junction: single character A, B, or C
        string jun = inf.readToken("[ABC]", "junction");
        char junction = jun[0];
        inf.readSpace();

        // Distance X from centre: 1 ≤ X ≤ L-1
        long long X = inf.readLong(1LL, L - 1, "X");
        inf.readSpace();

        // Direction: 0 or 1
        int dir = inf.readInt(0, 1, "dir");
        inf.readEoln();

        // Ensure no two ants have the same (junction, X)
        pair<char, long long> p = make_pair(junction, X);
        ensuref(!occupied.count(p),
                "Duplicate position for ant %d: junction %c, distance %lld",
                i + 1, junction, X);
        occupied.insert(p);
    }

    // No extra characters after last newline
    inf.readEof();
    return 0;
}
