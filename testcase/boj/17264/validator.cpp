#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, P
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    // Second line: W, L, G
    int W = inf.readInt(0, 100, "W");
    inf.readSpace();
    int L = inf.readInt(0, 100, "L");
    inf.readSpace();
    int G = inf.readInt(1, 100000, "G");
    inf.readEoln();

    // Next P lines: player name (uppercase, len<=20) and result (W or L)
    // Also build mapping and ensure no duplicate names
    unordered_map<string, char> outcome;
    outcome.reserve(P * 2);
    outcome.max_load_factor(0.7);

    for (int i = 0; i < P; ++i) {
        string name = inf.readToken("[A-Z]{1,20}", "player_name");
        inf.readSpace();
        string res = inf.readToken("W|L", "result");
        inf.readEoln();

        ensuref(!outcome.count(name),
                "Duplicate player info for name '%s' on line %d",
                name.c_str(), i + 3);
        outcome[name] = res[0];
    }

    // Next N lines: names of teammates (uppercase, len<=20)
    vector<string> games;
    games.reserve(N);
    for (int i = 0; i < N; ++i) {
        string name = inf.readToken("[A-Z]{1,20}", "game_player_name");
        inf.readEoln();
        games.push_back(name);
    }

    // Now validate global properties implied by the statement:
    // - Score never goes below 0
    // - Score changes exactly as described:
    //   * If name is in mapping:
    //        'W' -> +W
    //        'L' -> -L
    //   * Else -> -L
    // - Stop caring after reaching >= G, but this is only a description; we
    //   just simulate fully to ensure no contradictions like negative score.

    long long score = 0;
    bool escaped = false;
    for (int i = 0; i < N; ++i) {
        if (!escaped) {
            auto it = outcome.find(games[i]);
            if (it != outcome.end()) {
                if (it->second == 'W') {
                    score += W;
                } else {
                    score -= L;
                    if (score < 0) score = 0;
                }
            } else {
                // Unknown player => always lose
                score -= L;
                if (score < 0) score = 0;
            }
            if (score >= G) {
                escaped = true;
            }
        } else {
            // After escape, statement says "그 이후에 게임은 신경쓰지 않는다."
            // This is descriptive only; no additional constraints to enforce.
        }

        // Just to be safe, ensure score never drops below 0
        ensuref(score >= 0, "Score became negative after game %d", i + 1);
    }

    // Nothing else to validate globally:
    // - There's no guarantee that escape always happens; both outcomes allowed.

    inf.readEof();
}
