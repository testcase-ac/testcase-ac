#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readSpace();
    int k = inf.readInt(2, n, "k");
    inf.readEoln();

    string s = inf.readToken("[a-z]{2,200000}", "s");
    inf.readEoln();
    inf.readEof();

    ensuref(static_cast<int>(s.size()) == n, "s length must be n");

    vector<pair<char, int>> groups;
    int remaining = 0;
    for (char c : s) {
        if (!groups.empty() && groups.back().first == c) {
            ++groups.back().second;
        } else {
            groups.push_back({c, 1});
        }
        ++remaining;

        if (groups.back().second == k) {
            remaining -= k;
            groups.pop_back();
        }
    }

    ensuref(remaining > 0, "final string must not be empty");
}
