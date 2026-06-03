#include "testlib.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readSpace();
    int t = inf.readInt(1, 250, "t");
    inf.readEoln();

    string finalState = inf.readToken("[01]{2,100}", "final_state");
    ensuref((int)finalState.size() == n, "final state length is %d, expected %d",
            (int)finalState.size(), n);
    inf.readEoln();

    vector<tuple<int, int, int>> interactions;
    vector<bool> usedTime(251, false);
    for (int i = 0; i < t; ++i) {
        int time = inf.readInt(1, 250, "time");
        inf.readSpace();
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(x != y, "interaction %d has identical cows %d", i + 1, x);
        ensuref(!usedTime[time], "multiple interactions at time %d", time);
        usedTime[time] = true;
        interactions.emplace_back(time, x - 1, y - 1);
    }

    inf.readEof();

    sort(interactions.begin(), interactions.end());

    vector<int> target(n);
    for (int i = 0; i < n; ++i) {
        target[i] = finalState[i] == '1';
    }

    bool hasValidExplanation = false;
    for (int patientZero = 0; patientZero < n && !hasValidExplanation; ++patientZero) {
        for (int k = 0; k <= t + 1 && !hasValidExplanation; ++k) {
            vector<int> infected(n, 0);
            vector<int> remaining(n, 0);
            infected[patientZero] = 1;
            remaining[patientZero] = k;

            for (auto [time, x, y] : interactions) {
                (void)time;
                bool xInfected = infected[x];
                bool yInfected = infected[y];

                if (xInfected && remaining[x] > 0) {
                    --remaining[x];
                    if (!infected[y]) {
                        infected[y] = 1;
                        remaining[y] = k;
                    }
                }
                if (yInfected && remaining[y] > 0) {
                    --remaining[y];
                    if (!infected[x]) {
                        infected[x] = 1;
                        remaining[x] = k;
                    }
                }
            }

            if (infected == target) {
                hasValidExplanation = true;
            }
        }
    }

    ensuref(hasValidExplanation,
            "final state has no valid patient-zero and K explanation");
}
