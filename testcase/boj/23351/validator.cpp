#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read single test case
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readSpace();
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readEoln();

    // Check constraints that involve multiple variables
    ensuref((long long)A * (long long)B < N,
            "Constraint A * B < N violated: A=%d, B=%d, N=%d", A, B, N);
    ensuref(N % A == 0,
            "Constraint A is a divisor of N violated: N=%d, A=%d", N, A);

    // Additional global validation:
    // The problem guarantees that input is such that we can define an answer.
    // At least ensure that with optimal watering strategy, the process is
    // well-defined and we can simulate a bit without contradictions.
    //
    // We'll simulate a safe upper bound of days to confirm that the process
    // does not require unbounded time and that the "first death day" exists.
    // Since N, K <= 100 and A*B < N, we can argue that death must occur
    // in finite time. A loose bound is enough; we can simulate up to e.g.
    // 1e6 days using int without overflow (levels stay reasonably small).
    //
    // However, we should not re-solve the optimization problem; instead,
    // we just verify that for any watering pattern respecting rules,
    // the simulation logic is consistent. No extra constraints are stated
    // like "answer is at most X" that we must check.

    // To be safe, we can check a trivial strategy (e.g., always water the
    // same segment) to ensure at least one plant eventually dies, meaning
    // the "first death day" exists for that strategy; given constraints,
    // this must hold if model isn't degenerate.
    const int MAX_DAYS_CHECK = 100000; // generous upper bound
    vector<int> water(N, K);
    int segmentStart = 0; // fixed simple strategy: always water first segment [0, A-1]
    int deathDay = -1;
    for (int day = 1; day <= MAX_DAYS_CHECK; ++day) {
        // 1) Water A consecutive pots starting at segmentStart
        for (int i = 0; i < A; ++i) {
            water[segmentStart + i] += B;
        }
        // 2) All pots lose 1 moisture
        for (int i = 0; i < N; ++i) {
            water[i] -= 1;
        }
        // 3) If any becomes 0 or less, it dies; record first such day
        bool anyDead = false;
        for (int i = 0; i < N; ++i) {
            if (water[i] <= 0) {
                anyDead = true;
                break;
            }
        }
        if (anyDead) {
            deathDay = day;
            break;
        }
    }
    ensuref(deathDay != -1,
            "Simulation check failed: with a simple strategy no plant dies within %d days; "
            "input may violate hidden assumptions.", MAX_DAYS_CHECK);

    inf.readEof();
}
