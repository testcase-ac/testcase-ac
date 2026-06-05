#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 26, "N");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "K");
    inf.readSpace();
    int q = inf.readInt(1, k, "Q");
    inf.readEoln();

    vector<int> unread(k);
    vector<int> sender(k);
    int previousUnread = 0;

    for (int i = 0; i < k; ++i) {
        unread[i] = inf.readInt(0, n - 1, "R");
        inf.readSpace();
        string p = inf.readToken("[A-Z]", "P");
        inf.readEoln();

        sender[i] = p[0] - 'A';
        ensuref(sender[i] < n, "sender at message %d is outside A..%c: %s",
                i + 1, char('A' + n - 1), p.c_str());
        ensuref(previousUnread <= unread[i],
                "unread count decreases at message %d: previous %d, current %d",
                i + 1, previousUnread, unread[i]);
        previousUnread = unread[i];
    }

    vector<int> knownReadMask(n, 1);
    for (int r = 0; r < n; ++r) {
        for (int i = 0; i < k; ++i) {
            if (unread[i] >= r) {
                knownReadMask[r] |= 1 << sender[i];
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        int knownRead = __builtin_popcount(static_cast<unsigned>(knownReadMask[unread[i]]));
        int possibleUnread = n - knownRead;
        ensuref(unread[i] <= possibleUnread,
                "message %d is contradictory: R=%d but at most %d people can be unread",
                i + 1, unread[i], possibleUnread);
    }

    inf.readEof();
}
