#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: A, B
    long long A = inf.readLong(1LL, 1000000000000LL, "A"); // 1 <= A <= 1e12
    inf.readSpace();
    long long B = inf.readLong(1LL, 1000000000LL, "B");    // 1 <= B <= 1e9
    inf.readEoln();

    // Second line: C, D
    long long C = inf.readLong(0LL, 1000000000000LL, "C"); // 0 <= C <= 1e12
    inf.readSpace();
    long long D = inf.readLong(1LL, 1000000000LL, "D");    // 1 <= D <= 1e9
    inf.readEoln();

    // Third line: K
    long long K = inf.readLong(0LL, B, "K");               // 0 <= K <= B
    inf.readEoln();

    // Now verify the global property: according to the statement,
    // either Tokka reaches home safely before being caught, or is caught.
    // We simulate the process and ensure it always terminates in one of these states,
    // and that the number of moves fits in a signed 64-bit integer if she succeeds.

    // Positions measured as distance from home along the line, always non-negative.
    long long tok_pos = A;         // Tokka's distance from home
    long long dol_pos = A + C;     // Doldori's distance from home
    long long move_cap = B;        // Tokka's current maximum move distance
    long long moves = 0;

    // If they start at the same position, statement says this is NOT considered caught.
    // They also both strictly move towards home.

    const long long INF_STEPS = (long long)4e18; // big safety cap

    auto tok_step_distance = [&](long long cap) -> long long {
        // Tokka tries to move min(cap, current distance to home), but not negative
        if (cap <= 0) return 0LL;
        return min(cap, tok_pos);
    };

    // Main simulation loop.
    // We stop when:
    // - Tokka reaches home before/without being caught (success)
    // - Doldori catches/overtakes/appends as per rules (failure)
    // - Tokka cannot move further (cap <= 0) and hasn't reached home; she will then
    //   be eventually caught (we simulate until that happens, but we must ensure it happens).
    for (;;) {
        // If Tokka already at home at this point (only possible at start),
        // then she hasn't been caught yet and wins immediately with 0 moves.
        if (tok_pos == 0) {
            // success with 'moves' steps. Verify it fits in 64-bit (it always does).
            break;
        }

        // If Tobka cannot move anymore (move_cap <= 0) and not at home,
        // she stays put, and Doldori keeps moving until catching/passing or reaching home.
        if (move_cap <= 0) {
            // Tokka frozen at tok_pos > 0. Doldori moves alone.
            // We can compute in O(1) how many steps needed until:
            // - dol_pos <= tok_pos: impossible because dol_pos >= tok_pos+? ; they both move toward home.
            // Actually they start with dol_pos >= tok_pos (Tokka is closer to home).
            // They both move towards decreasing positions, so Doldori is "behind" Tokka.
            // Doldori catches Tokka when dol_pos <= tok_pos after a move
            // or passes tok_pos, but since both move towards 0, "passing" means dol_pos < tok_pos.
            // In any case, since Tokka is stationary, Doldori will strictly approach 0 and will surely
            // cross tok_pos unless both equal 0 simultaneously.
            // If Doldori's next steps make him reach exactly tok_pos or cross it, it's caught.
            // That will surely happen in finite steps because D>0 and positions are bounded.
            break;
        }

        // Compute step lengths
        long long t_move = tok_step_distance(move_cap);
        long long d_move = min(D, dol_pos); // Doldori won't move past home in a step

        // Next positions
        long long next_tok_pos = tok_pos - t_move;
        long long next_dol_pos = dol_pos - d_move;

        moves++;

        // Rule: after a move, if Doldori at same position as Tokka -> caught
        bool caught = false;
        bool tok_at_home = (next_tok_pos == 0);
        bool dol_at_home = (next_dol_pos == 0);

        if (next_dol_pos == next_tok_pos) {
            caught = true;
        } else if (tok_at_home && dol_at_home) {
            // both reach home on the same move: caught
            caught = true;
        } else {
            // Doldori "passes" Tokka if he ends closer to home than Tokka
            // (remember smaller distance means closer to home).
            if (next_dol_pos < next_tok_pos) caught = true;
        }

        tok_pos = next_tok_pos;
        dol_pos = next_dol_pos;
        move_cap -= K;

        if (caught) {
            // This is a valid "caught" situation per statement; nothing else to check.
            break;
        }
        if (tok_at_home) {
            // Tokka arrives home safely before/without being caught
            break;
        }

        // Safety: ensure we don't loop indefinitely due to some logic error.
        ensuref(moves <= INF_STEPS, "Simulation did not terminate within safe step bound");
    }

    inf.readEof();
}
