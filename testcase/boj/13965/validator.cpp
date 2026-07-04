#include "testlib.h"

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

static int modNormalize(int value) {
    value %= 13;
    if (value < 0) value += 13;
    return value;
}

static bool hasConsistentEdgeDurations(vector<vector<int>> equations) {
    const int rows = equations.size();
    if (rows == 0) return true;
    const int vars = (int)equations[0].size() - 1;

    int row = 0;
    for (int col = 0; col < vars && row < rows; ++col) {
        int pivot = -1;
        for (int i = row; i < rows; ++i) {
            if (equations[i][col] != 0) {
                pivot = i;
                break;
            }
        }
        if (pivot == -1) continue;

        swap(equations[row], equations[pivot]);
        int inv = 1;
        while (equations[row][col] * inv % 13 != 1) ++inv;
        for (int j = col; j <= vars; ++j) {
            equations[row][j] = equations[row][j] * inv % 13;
        }

        for (int i = 0; i < rows; ++i) {
            if (i == row || equations[i][col] == 0) continue;
            int factor = equations[i][col];
            for (int j = col; j <= vars; ++j) {
                equations[i][j] = modNormalize(equations[i][j] - factor * equations[row][j]);
            }
        }
        ++row;
    }

    for (const auto& equation : equations) {
        bool allZero = true;
        for (int col = 0; col < vars; ++col) {
            if (equation[col] != 0) {
                allZero = false;
                break;
            }
        }
        if (allZero && equation[vars] != 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200, "N");
    inf.readSpace();
    int alice = inf.readInt(1, n, "A");
    inf.readSpace();
    int rabbit = inf.readInt(1, n, "R");
    inf.readSpace();
    int trips = inf.readInt(1, 500, "T");
    inf.readEoln();

    (void)alice;
    (void)rabbit;

    map<pair<int, int>, int> edgeId;
    vector<vector<int>> equations;

    for (int i = 0; i < trips; ++i) {
        int duration = inf.readInt(0, 12, "d");
        inf.readSpace();
        int places = inf.readInt(2, 800, "p");

        vector<int> path(places);
        for (int j = 0; j < places; ++j) {
            inf.readSpace();
            path[j] = inf.readInt(1, n, "a_j");
        }
        inf.readEoln();

        vector<int> equation(200 + 1, 0);
        for (int j = 0; j + 1 < places; ++j) {
            int u = path[j];
            int v = path[j + 1];
            // CHECK: A direct track is between two distinct locations; consecutive equal visits would not define a track.
            ensuref(u != v, "trip %d has consecutive equal locations at positions %d and %d", i + 1, j + 1, j + 2);

            if (u > v) swap(u, v);
            pair<int, int> edge = {u, v};
            auto [it, inserted] = edgeId.emplace(edge, (int)edgeId.size());
            ensuref(edgeId.size() <= 200, "more than 200 direct tracks are used");
            equation[it->second] = (equation[it->second] + 1) % 13;
        }
        equation[200] = duration;
        equations.push_back(equation);
    }

    int edgeCount = (int)edgeId.size();
    vector<vector<int>> compactEquations;
    compactEquations.reserve(equations.size());
    for (const auto& equation : equations) {
        vector<int> compact(edgeCount + 1);
        for (int i = 0; i < edgeCount; ++i) compact[i] = equation[i];
        compact[edgeCount] = equation[200];
        compactEquations.push_back(compact);
    }

    ensuref(hasConsistentEdgeDurations(compactEquations), "logged trips have no consistent edge durations modulo 13");

    inf.readEof();
}
