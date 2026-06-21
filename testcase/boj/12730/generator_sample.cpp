#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

string engineName(int caseIndex, int engineIndex, bool useWords) {
    static const vector<string> words = {
        "Alpha", "Beta", "Gamma", "Delta", "Omega", "Search", "Find", "Query",
        "Atlas", "Nova", "Echo", "Prime", "Vector", "Nimbus", "Orbit"};

    if (useWords) {
        return words[(caseIndex + engineIndex) % words.size()] + " " +
               words[(caseIndex * 3 + engineIndex * 5) % words.size()] +
               vtos(caseIndex + engineIndex);
    }

    return string("E") + vtos(caseIndex) + "N" + vtos(engineIndex);
}

vector<int> makeQueries(int engineCount, int queryCount, int mode) {
    vector<int> queries;
    queries.reserve(queryCount);

    if (queryCount == 0) {
        return queries;
    }

    if (mode == 0) {
        int engine = rnd.next(engineCount);
        for (int i = 0; i < queryCount; ++i) {
            queries.push_back(engine);
        }
    } else if (mode == 1) {
        int start = rnd.next(engineCount);
        int step = rnd.next(1, engineCount - 1);
        for (int i = 0; i < queryCount; ++i) {
            queries.push_back((start + i * step) % engineCount);
        }
    } else if (mode == 2) {
        vector<int> order(engineCount);
        for (int i = 0; i < engineCount; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < queryCount; ++i) {
            queries.push_back(order[i % engineCount]);
        }
    } else {
        int hot = rnd.next(engineCount);
        for (int i = 0; i < queryCount; ++i) {
            if (rnd.next(100) < 65) {
                queries.push_back(hot);
            } else {
                queries.push_back(rnd.next(engineCount));
            }
        }
    }

    return queries;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 6);
    println(caseCount);

    for (int caseIndex = 1; caseIndex <= caseCount; ++caseIndex) {
        int engineCount = rnd.next(2, 8);
        int mode = rnd.next(4);
        int queryCount;
        if (mode == 0) {
            queryCount = rnd.next(0, 8);
        } else if (mode == 1) {
            queryCount = rnd.next(engineCount, engineCount * 4);
        } else if (mode == 2) {
            queryCount = rnd.next(engineCount + 1, engineCount * 5);
        } else {
            queryCount = rnd.next(1, 24);
        }

        bool useWords = rnd.next(2) == 1;
        vector<string> engines;
        engines.reserve(engineCount);
        for (int i = 0; i < engineCount; ++i) {
            engines.push_back(engineName(caseIndex, i, useWords));
        }

        vector<int> queries = makeQueries(engineCount, queryCount, mode);

        println(engineCount);
        for (const string& engine : engines) {
            println(engine);
        }
        println(queryCount);
        for (int query : queries) {
            println(engines[query]);
        }
    }

    return 0;
}
