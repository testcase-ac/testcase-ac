#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N on the first line
    int N = inf.readInt(1, 5000, "N");
    inf.readEoln();

    // --- Global property check: the process is well-defined and terminates ---
    // We simulate the described elimination game to ensure that:
    //  - the process can be carried out as stated without ambiguity,
    //  - it terminates with exactly one remaining participant,
    //  - there is always someone to eliminate at each step.
    //
    // This is not part of the contestant's job; it's to ensure
    // that the input always satisfies the problem's guarantees.

    vector<int> participants(N);
    for (int i = 0; i < N; ++i) participants[i] = i + 1; // T-shirt numbers 1..N

    int cur = 0;          // 백준 initially stands in front of t-shirt 1 (index 0)
    int step = 1;         // current step t
    int remaining = N;

    while (remaining > 1) {
        // We must ensure that step^3 is computable in 64-bit and does not overflow.
        // Since N <= 5000, at most N-1 steps are needed, step^3 <= 4999^3 < 2^63.
        long long t = step;
        long long cnt = t * t * t; // t^3

        // Move cnt-1 times clockwise over current alive participants.
        // Counting starts at current 'cur' as "하나", so we move cnt-1 steps.
        long long move = (cnt - 1) % remaining;
        cur = (int)((cur + move) % remaining);

        // Remove participant at index 'cur'
        participants.erase(participants.begin() + cur);
        remaining--;

        // After removal, Baekjoon moves clockwise to next person:
        // this is already at index 'cur' in the compacted vector.
        if (remaining == 0) break; // should never happen, but guard anyway
        if (cur >= remaining) cur = 0;

        step++;
        // Safety: we should not need more than N-1 steps
        ensuref(step <= N, "Game did not terminate within N-1 steps for N=%d", N);
    }

    // At the end exactly one participant must remain
    ensuref((int)participants.size() == 1,
            "Game ended with %d participants instead of 1", (int)participants.size());
    ensuref(participants[0] >= 1 && participants[0] <= N,
            "Final survivor t-shirt number %d out of range 1..%d",
            participants[0], N);

    inf.readEof();
}
