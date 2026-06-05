#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]+", "S");
    inf.readEoln();
    string t = inf.readToken("[a-z]+", "T");
    inf.readEoln();
    inf.readEof();

    ensuref(s.size() <= 1000000, "|S| must be at most 10^6, got %d",
            int(s.size()));
    ensuref(t.size() <= 100, "|T| must be at most 100, got %d", int(t.size()));
    ensuref(t.size() <= s.size(), "|T| must be at most |S|, got %d > %d",
            int(t.size()), int(s.size()));

    string remaining;
    remaining.reserve(s.size());
    for (char c : s) {
        remaining.push_back(c);
        if (remaining.size() >= t.size() &&
            remaining.compare(remaining.size() - t.size(), t.size(), t) == 0) {
            remaining.resize(remaining.size() - t.size());
        }
    }
    ensuref(!remaining.empty(), "S must not become empty after censoring");
}
