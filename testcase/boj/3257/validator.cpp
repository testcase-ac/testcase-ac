#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static bool hasInterleaving(const string& first, const string& second, const string& screen) {
    vector<vector<char>> reachable(first.size() + 1, vector<char>(second.size() + 1, 0));
    reachable[0][0] = 1;

    for (int i = 0; i <= static_cast<int>(first.size()); ++i) {
        for (int j = 0; j <= static_cast<int>(second.size()); ++j) {
            if (!reachable[i][j]) {
                continue;
            }
            int k = i + j;
            if (i < static_cast<int>(first.size()) && first[i] == screen[k]) {
                reachable[i + 1][j] = 1;
            }
            if (j < static_cast<int>(second.size()) && second[j] == screen[k]) {
                reachable[i][j + 1] = 1;
            }
        }
    }

    return reachable[first.size()][second.size()];
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string first = inf.readLine("[a-z]{1,150}", "first");
    string second = inf.readLine("[a-z]{1,150}", "second");
    string screen = inf.readLine("[a-z]{1,300}", "screen");

    ensuref(screen.size() == first.size() + second.size(),
            "screen length must equal the sum of the two word lengths");
    ensuref(hasInterleaving(first, second, screen),
            "screen word must be an order-preserving interleaving of the two words");

    inf.readEof();
}
