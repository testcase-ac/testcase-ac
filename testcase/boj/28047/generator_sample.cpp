#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

vector<string> makeNames(int n) {
    vector<string> names;
    for (char a = 'a'; a <= 'z' && static_cast<int>(names.size()) < n; ++a) {
        names.push_back(string(1, a));
    }
    for (char a = 'a'; a <= 'z' && static_cast<int>(names.size()) < n; ++a) {
        for (char b = 'a'; b <= 'z' && static_cast<int>(names.size()) < n; ++b) {
            names.push_back(string() + a + b);
        }
    }
    for (char a = 'a'; a <= 'z' && static_cast<int>(names.size()) < n; ++a) {
        for (char b = 'a'; b <= 'z' && static_cast<int>(names.size()) < n; ++b) {
            for (char c = 'a'; c <= 'z' && static_cast<int>(names.size()) < n; ++c) {
                names.push_back(string() + a + b + c);
            }
        }
    }
    return names;
}

vector<string> raceParticipants(const vector<string>& order, int winnerPos, int size) {
    int n = static_cast<int>(order.size());
    vector<int> candidates;
    for (int pos = winnerPos; pos < n; ++pos) {
        candidates.push_back(pos);
    }
    shuffle(candidates.begin(), candidates.end());

    vector<string> participants{order[winnerPos - 1]};
    for (int pos : candidates) {
        if (static_cast<int>(participants.size()) == size) {
            break;
        }
        participants.push_back(order[pos]);
    }
    shuffle(participants.begin(), participants.end());
    return participants;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = 2;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 18);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(20, 45);
    }

    vector<string> names = makeNames(n);
    shuffle(names.begin(), names.end());

    vector<string> order = names;
    shuffle(order.begin(), order.end());

    vector<pair<int, vector<string>>> races;
    if (mode == 2) {
        for (int winnerPos = 1; winnerPos <= n - 1; ++winnerPos) {
            int size = n - winnerPos + 1;
            races.push_back({winnerPos, raceParticipants(order, winnerPos, size)});
        }
    } else {
        int targetRaces = rnd.next(max(1, n / 2), min(3 * n, 35));
        for (int i = 0; i < targetRaces; ++i) {
            int winnerPos;
            if (rnd.next(0, 99) < 35) {
                winnerPos = rnd.next(1, min(n - 1, 3));
            } else {
                winnerPos = rnd.next(1, n - 1);
            }
            int maxSize = n - winnerPos + 1;
            int size = rnd.next(2, maxSize);
            races.push_back({winnerPos, raceParticipants(order, winnerPos, size)});

            if (rnd.next(0, 99) < 25) {
                int secondSize = rnd.next(2, maxSize);
                races.push_back({winnerPos, raceParticipants(order, winnerPos, secondSize)});
            }
        }
    }

    println(n);
    println(names);
    println(static_cast<int>(races.size()));
    for (const auto& race : races) {
        cout << race.second.size() << ' ' << race.first;
        for (const string& name : race.second) {
            cout << ' ' << name;
        }
        cout << '\n';
    }

    return 0;
}
