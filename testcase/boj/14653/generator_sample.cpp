#include "testlib.h"

#include <utility>
#include <vector>
using namespace std;

static bool isValidHistory(int n, const vector<pair<int, int>>& messages) {
    vector<int> knownReadMask(n, 1);

    for (int r = 0; r < n; ++r) {
        for (const auto& message : messages) {
            if (message.first >= r) {
                knownReadMask[r] |= 1 << message.second;
            }
        }
    }

    for (const auto& message : messages) {
        int knownRead = __builtin_popcount(static_cast<unsigned>(knownReadMask[message.first]));
        int possibleUnread = n - knownRead;
        if (message.first > possibleUnread) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int k;
    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.next(8, 20);
    } else if (mode == 2) {
        n = rnd.next(8, 15);
        k = rnd.next(10, 35);
    } else {
        n = rnd.next(20, 26);
        k = rnd.next(15, 45);
    }

    vector<pair<int, int>> messages;
    int previousUnread = 0;

    for (int i = 0; i < k; ++i) {
        vector<pair<int, int>> candidates;

        for (int attempt = 0; attempt < 200; ++attempt) {
            int unread;
            if (mode == 0 && previousUnread == 0 && rnd.next(0, 2) == 0) {
                unread = 0;
            } else if (rnd.next(0, 3) == 0) {
                unread = previousUnread;
            } else {
                int upper = min(n - 1, previousUnread + rnd.next(0, 2));
                unread = rnd.next(previousUnread, upper);
            }

            int sender;
            if (n == 1 || rnd.next(0, 4) == 0) {
                sender = 0;
            } else {
                sender = rnd.next(0, n - 1);
            }

            vector<pair<int, int>> trial = messages;
            trial.emplace_back(unread, sender);
            if (isValidHistory(n, trial)) {
                candidates.emplace_back(unread, sender);
            }
        }

        if (candidates.empty()) {
            for (int sender = 0; sender < n; ++sender) {
                vector<pair<int, int>> trial = messages;
                trial.emplace_back(previousUnread, sender);
                if (isValidHistory(n, trial)) {
                    candidates.emplace_back(previousUnread, sender);
                }
            }
        }

        pair<int, int> chosen = rnd.any(candidates);
        messages.push_back(chosen);
        previousUnread = chosen.first;
    }

    int q;
    if (mode == 1) {
        q = rnd.next(1, min(k, 5));
    } else if (mode == 2) {
        q = rnd.next(max(1, k - 5), k);
    } else {
        q = rnd.next(1, k);
    }

    println(n, k, q);
    for (const auto& message : messages) {
        println(message.first, string(1, char('A' + message.second)));
    }

    return 0;
}
