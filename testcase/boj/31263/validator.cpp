#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 5000, "N");
    inf.readEoln();

    string S = inf.readToken("[0-9]{1,5000}", "S");
    ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d)", (int)S.size(), N);

    vector<char> reachable(N + 1, false);
    reachable[0] = true;
    for (int i = 0; i < N; ++i) {
        if (!reachable[i] || S[i] == '0') {
            continue;
        }
        int value = 0;
        for (int j = i; j < N && j < i + 3; ++j) {
            value = value * 10 + (S[j] - '0');
            if (value > 641) {
                break;
            }
            reachable[j + 1] = true;
        }
    }
    ensuref(reachable[N], "S cannot be split into numbers from 1 to 641 without leading zeroes");

    inf.readEoln();
    inf.readEof();
}
