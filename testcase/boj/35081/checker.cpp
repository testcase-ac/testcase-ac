#include "testlib.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    string assignment;
};

int n, k, q;
vector<int> leave_time;
vector<int> return_time;

Claim readClaim(InStream& stream) {
    string token = stream.readToken("[01]+|impossible", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "impossible") {
        return {true, ""};
    }
    if ((int)token.size() != q) {
        stream.quitf(_wa, "assignment length is %d, expected %d", (int)token.size(), q);
    }
    return {false, token};
}

void validateAssignment(InStream& stream, const string& assignment) {
    vector<tuple<int, int, int>> events;
    events.reserve(2 * q);
    for (int i = 0; i < q; ++i) {
        events.emplace_back(leave_time[i], -1, i);
        events.emplace_back(return_time[i], 1, i);
    }
    sort(events.begin(), events.end());

    int people_home = n;
    int keys_at_flat = k;
    for (auto [time, type, trip] : events) {
        bool takes_key = assignment[trip] == '1';
        if (type == -1) {
            if (takes_key) {
                if (keys_at_flat == 0) {
                    stream.quitf(_wa,
                                 "trip %d leaves with a key at time %d, but no key is available",
                                 trip + 1, time);
                }
                --keys_at_flat;
            }
            --people_home;
        } else {
            if (people_home == 0 && !takes_key) {
                stream.quitf(_wa,
                             "trip %d returns at time %d without a key while the flat is empty",
                             trip + 1, time);
            }
            ++people_home;
            if (takes_key) {
                ++keys_at_flat;
                if (keys_at_flat > k) {
                    stream.quitf(_wa,
                                 "trip %d returns a key at time %d, increasing keys in flat to %d",
                                 trip + 1, time, keys_at_flat);
                }
            }
        }
    }

    if (people_home != n || keys_at_flat != k) {
        stream.quitf(_wa,
                     "invalid final state: people_home=%d keys_at_flat=%d",
                     people_home, keys_at_flat);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    q = inf.readInt();
    leave_time.resize(q);
    return_time.resize(q);
    for (int i = 0; i < q; ++i) {
        inf.readInt();
        leave_time[i] = inf.readInt();
        return_time[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    if (!jury.impossible) {
        validateAssignment(ans, jury.assignment);
    }

    Claim participant = readClaim(ouf);
    if (participant.impossible) {
        if (jury.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_wa, "participant claims impossible, but jury provides a valid assignment");
    }

    validateAssignment(ouf, participant.assignment);
    if (jury.impossible) {
        quitf(_fail, "participant provides a valid assignment while jury claims impossible");
    }

    quitf(_ok, "valid assignment");
}
