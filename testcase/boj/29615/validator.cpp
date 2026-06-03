#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    vector<bool> seen_waiting(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        int number = inf.readInt(1, n, "waiting_number");
        ensuref(!seen_waiting[number], "duplicate waiting number at index %d: %d", i, number);
        seen_waiting[number] = true;
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    vector<bool> seen_friend(n + 1, false);
    for (int i = 1; i <= m; ++i) {
        int number = inf.readInt(1, n, "friend_number");
        ensuref(!seen_friend[number], "duplicate friend number at index %d: %d", i, number);
        seen_friend[number] = true;
        if (i == m) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
