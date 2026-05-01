#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(0, 100, "N");
    inf.readEoln();

    // Data structures to validate uniqueness and consistency
    vector<string> names_rec(N);
    vector<int> W(N), D(N);
    vector<long long> P(N);
    set<string> name_set;

    for (int i = 0; i < N; ++i) {
        string S = inf.readToken("[A-Za-z]{1,12}", "S");
        ensuref(!name_set.count(S),
                "Duplicate senior name in records at line %d: '%s'",
                i + 2, S.c_str());
        name_set.insert(S);
        names_rec[i] = S;

        inf.readSpace();
        int w = inf.readInt(1, 10, "W");
        W[i] = w;

        inf.readSpace();
        int d = inf.readInt(0, 6, "D");
        D[i] = d;

        inf.readSpace();
        long long p = inf.readLong(0LL, 100000LL, "P");
        P[i] = p;

        inf.readEoln();
    }

    // Read money info, must be exactly N lines
    set<string> seen_money_names;
    vector<long long> M(N);
    vector<string> names_money(N);

    for (int i = 0; i < N; ++i) {
        string S = inf.readToken("[A-Za-z]{1,12}", "S_money");
        inf.readSpace();
        long long m = inf.readLong(0LL, 100000LL, "M");
        inf.readEoln();

        ensuref(name_set.count(S),
                "Money line %d contains unknown senior name '%s'",
                i + 2 + N, S.c_str());
        ensuref(!seen_money_names.count(S),
                "Duplicate senior name in money section at line %d: '%s'",
                i + 2 + N, S.c_str());
        seen_money_names.insert(S);

        names_money[i] = S;
        M[i] = m;
    }

    // Ensure that every recorded senior appears exactly once in money lines
    ensuref(seen_money_names.size() == name_set.size(),
            "Some seniors in records have no corresponding money line");

    // Build mapping from name to indices (for convenience if needed)
    unordered_map<string,int> rec_idx;
    for (int i = 0; i < N; ++i)
        rec_idx[names_rec[i]] = i;

    // Check the implied condition: if senior has enough money, they must buy
    // This is not a property we can "validate" without the intended algorithm,
    // but there's no extra global invariant promised except data format.
    // However, we must ensure input consistency regarding these promises:
    // The problem guarantees "한 선배는 두 번 이상 밥을 사주지 않으며 모든 선배의 이름은 다르다."
    // We've already enforced unique names and 1 record per senior.

    // No further global constraints (like existence of answer, connectivity, etc.)
    // are specified that require simulation for validation.

    inf.readEof();
}
