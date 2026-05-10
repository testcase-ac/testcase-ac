#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Problem {
    int L, G;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_P = 100000;
    const int MAX_M = 10000;
    const int MAX_L = 100;
    const int MAX_G = 100;

    // Read initial number of problems
    int N = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    // Track current problems: P -> (L,G)
    // Using array since P in [1,100000]
    vector<Problem> cur(MAX_P + 1, Problem{-1, -1});
    int curCount = 0;

    for (int i = 0; i < N; ++i) {
        int P = inf.readInt(1, MAX_P, "P");
        inf.readSpace();
        int L = inf.readInt(1, MAX_L, "L");
        inf.readSpace();
        int G = inf.readInt(1, MAX_G, "G");
        inf.readEoln();

        ensuref(cur[P].L == -1,
                "Initial problems contain duplicate P=%d at index %d", P, i);

        cur[P] = {L, G};
        ++curCount;
    }

    int M = inf.readInt(1, MAX_M, "M");
    inf.readEoln();

    int recommendCmdCount = 0;

    for (int qi = 0; qi < M; ++qi) {
        string cmd = inf.readToken("[a-z0-9]+", "command");

        if (cmd == "add") {
            inf.readSpace();
            int P = inf.readInt(1, MAX_P, "P");
            inf.readSpace();
            int L = inf.readInt(1, MAX_L, "L");
            inf.readSpace();
            int G = inf.readInt(1, MAX_G, "G");
            inf.readEoln();

            ensuref(cur[P].L == -1,
                    "add uses already existing problem P=%d at query %d", P, qi);

            cur[P] = {L, G};
            ++curCount;
        } else if (cmd == "solved") {
            inf.readSpace();
            int P = inf.readInt(1, MAX_P, "P");
            inf.readEoln();

            ensuref(curCount >= 1,
                    "solved command issued when there is no problem at query %d", qi);
            ensuref(cur[P].L != -1,
                    "solved uses non-existing problem P=%d at query %d", P, qi);

            cur[P] = {-1, -1};
            --curCount;
        } else if (cmd == "recommend") {
            inf.readSpace();
            int G = inf.readInt(1, MAX_G, "G");
            inf.readSpace();
            int x = inf.readInt(-1, 1, "x");
            inf.readEoln();
            ensuref(x == -1 || x == 1, "x in recommend must be -1 or 1, got %d", x);

            ensuref(curCount >= 1,
                    "recommend command issued when there is no problem at query %d", qi);

            // Ensure there's at least one problem with group G
            bool hasG = false;
            for (int p = 1; p <= MAX_P; ++p) {
                if (cur[p].L != -1 && cur[p].G == G) {
                    hasG = true;
                    break;
                }
            }
            ensuref(hasG,
                    "recommend command with G=%d but no problem in that group at query %d",
                    G, qi);

            ++recommendCmdCount;
        } else if (cmd == "recommend2") {
            inf.readSpace();
            int x = inf.readInt(-1, 1, "x");
            inf.readEoln();
            ensuref(x == -1 || x == 1,
                    "x in recommend2 must be -1 or 1, got %d", x);

            ensuref(curCount >= 1,
                    "recommend2 command issued when there is no problem at query %d", qi);

            ++recommendCmdCount;
        } else if (cmd == "recommend3") {
            inf.readSpace();
            int x = inf.readInt(-1, 1, "x");
            inf.readSpace();
            int L = inf.readInt(1, MAX_L, "L");
            inf.readEoln();
            ensuref(x == -1 || x == 1,
                    "x in recommend3 must be -1 or 1, got %d", x);

            ensuref(curCount >= 1,
                    "recommend3 command issued when there is no problem at query %d", qi);

            ++recommendCmdCount;
        } else {
            ensuref(false, "Unknown command '%s' at query %d", cmd.c_str(), qi);
        }
    }

    ensuref(recommendCmdCount >= 1,
            "There must be at least one recommend/recommend2/recommend3 command");

    inf.readEof();
}
