#include "testlib.h"
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(3, 15, "N");
    inf.readEoln();

    // 2. Read mp, mf, ms, mv
    int mp = inf.readInt(0, 500, "mp");
    inf.readSpace();
    int mf = inf.readInt(0, 500, "mf");
    inf.readSpace();
    int ms = inf.readInt(0, 500, "ms");
    inf.readSpace();
    int mv = inf.readInt(0, 500, "mv");
    inf.readEoln();

    // 3. Ensure at least one minimum is positive
    ensuref(mp + mf + ms + mv > 0, "At least one of mp, mf, ms, mv must be positive");

    // 4. Read N lines of ingredients
    vector<int> p(N), f(N), s(N), v(N), c(N);
    for (int i = 0; i < N; ++i) {
        p[i] = inf.readInt(0, 500, "p_i");
        inf.readSpace();
        f[i] = inf.readInt(0, 500, "f_i");
        inf.readSpace();
        s[i] = inf.readInt(0, 500, "s_i");
        inf.readSpace();
        v[i] = inf.readInt(0, 500, "v_i");
        inf.readSpace();
        c[i] = inf.readInt(0, 500, "c_i");
        inf.readEoln();
    }

    // 5. Check that there exists at least one subset that meets the requirements
    // (Otherwise, the problem's guarantee "조건을 만족하는 답이 없다면 -1을 출력" would be vacuous)
    bool feasible = false;
    int min_cost = INT_MAX;
    vector<int> best_subset;
    for (int mask = 1; mask < (1 << N); ++mask) {
        int tp = 0, tf = 0, ts = 0, tv = 0, tc = 0;
        vector<int> subset;
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                tp += p[i];
                tf += f[i];
                ts += s[i];
                tv += v[i];
                tc += c[i];
                subset.push_back(i + 1);
            }
        }
        if (tp >= mp && tf >= mf && ts >= ms && tv >= mv) {
            feasible = true;
            if (tc < min_cost) {
                min_cost = tc;
                best_subset = subset;
            } else if (tc == min_cost && subset < best_subset) {
                best_subset = subset;
            }
        }
    }
    ensuref(feasible, "No subset of ingredients meets the minimum nutrient requirements");

    inf.readEof();
}
