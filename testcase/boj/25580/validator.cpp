#include "testlib.h"

#include <set>
#include <string>
#include <vector>
using namespace std;

static bool isAlgorithmName(const string& s) {
    if (s.empty() || s.size() > 20) {
        return false;
    }
    for (char c : s) {
        if (c < 'a' || c > 'z') {
            return false;
        }
    }
    return true;
}

static void addAlgorithm(const string& s, set<string>& algorithms, const char* field) {
    if (s == "0") {
        return;
    }
    ensuref(isAlgorithmName(s), "%s must be 0 or a lowercase algorithm name of length 1..20: %s",
            field, s.c_str());
    algorithms.insert(s);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 4, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[ABCD]{1,4}", "piece_row");
        ensuref((int)row.size() == n, "piece row %d must have length %d, found %d",
                i + 1, n, (int)row.size());
    }

    for (int i = 0; i < n; ++i) {
        inf.readInts(n, 1, 16, "level");
        inf.readEoln();
    }

    set<string> algorithms;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int hasMonster = inf.readInt(0, 1, "has_monster");
            inf.readSpace();
            string required = inf.readToken("0|[a-z]{1,20}", "required_algorithm");
            inf.readSpace();
            string learned = inf.readToken("0|[a-z]{1,20}", "learned_algorithm");

            if (j + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            if (hasMonster == 0) {
                ensuref(required == "0", "cell (%d, %d) has no monster but required algorithm is %s",
                        i + 1, j + 1, required.c_str());
                ensuref(learned == "0", "cell (%d, %d) has no monster but learned algorithm is %s",
                        i + 1, j + 1, learned.c_str());
            }
            addAlgorithm(required, algorithms, "required_algorithm");
            addAlgorithm(learned, algorithms, "learned_algorithm");
        }
    }

    int a = inf.readInt(0, 4, "a");
    inf.readEoln();

    vector<string> initialAlgorithms;
    if (a == 0) {
        if (!inf.seekEof()) {
            inf.readEoln();
        }
    } else {
        for (int i = 0; i < a; ++i) {
            initialAlgorithms.push_back(inf.readToken("[a-z]{1,20}", "initial_algorithm"));
            if (i + 1 < a) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    set<string> initialSet;
    for (const string& algorithm : initialAlgorithms) {
        ensuref(isAlgorithmName(algorithm), "invalid initial algorithm name: %s", algorithm.c_str());
        // CHECK: The statement says aespa initially knows a algorithms. Treat that count as distinct algorithms.
        ensuref(initialSet.insert(algorithm).second, "duplicate initial algorithm: %s", algorithm.c_str());
        algorithms.insert(algorithm);
    }

    ensuref(algorithms.size() <= 10, "too many distinct algorithms: %d", (int)algorithms.size());

    inf.readEof();
}
