#include "testlib.h"

#include <map>

using namespace std;

struct Triple {
    char direction;
    int distance;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    map<int, Triple> triples;
    for (int idx = 1; idx <= n; ++idx) {
        int position = inf.readInt(-1000000, 1000000, "i");
        inf.readSpace();
        string direction_token = inf.readToken("L|R", "j");
        inf.readSpace();
        int distance = inf.readInt(1, 2000000, "k");
        inf.readEoln();

        ensuref(triples.emplace(position, Triple{direction_token[0], distance}).second,
                "duplicate triple position at line %d: %d", idx + 1, position);
    }

    int current = inf.readInt(-1000000, 1000000, "current_position");
    inf.readEoln();
    inf.readEof();

    for (int step = 1; step <= n; ++step) {
        auto it = triples.find(current);
        ensuref(it != triples.end(), "no unused triple for position %d at step %d", current, step);

        Triple triple = it->second;
        triples.erase(it);

        long long next = current + (triple.direction == 'L' ? -1LL : 1LL) * triple.distance;
        ensuref(next >= -3000000LL && next <= 3000000LL,
                "next position out of derived bounds at step %d: %lld", step, next);
        current = static_cast<int>(next);
    }

    ensuref(triples.empty(), "not all triples were referred");
}
