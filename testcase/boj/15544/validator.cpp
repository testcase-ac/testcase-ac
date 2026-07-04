#include "testlib.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

static int parseToken(const string& token, int tc) {
    ensuref(!token.empty(), "empty token in record %d", tc);

    int start = 0;
    if (token[0] == '-') {
        ensuref(token.size() > 1, "bare minus sign in record %d", tc);
        start = 1;
    }

    ensuref(token[start] != '0' || (int)token.size() == start + 1,
            "non-canonical integer token '%s' in record %d", token.c_str(), tc);
    for (int i = start; i < (int)token.size(); ++i) {
        ensuref('0' <= token[i] && token[i] <= '9',
                "non-integer token '%s' in record %d", token.c_str(), tc);
    }

    long value = strtol(token.c_str(), nullptr, 10);
    ensuref(-98 <= value && value <= 39,
            "record %d token %s is outside the possible value range",
            tc, token.c_str());
    return (int)value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 99, "n");
    inf.readEoln();

    int tc = 1;
    setTestCase(tc);

    vector<int> remaining;
    vector<int> path;
    int rooms = 0;
    bool hasToken = false;

    while (tc <= n) {
        string line = inf.readLine("[^]{1,999}", "record_line");
        ensuref(line.front() != ' ' && line.back() != ' ',
                "record %d line has leading or trailing space", tc);

        int pos = 0;
        while (pos < (int)line.size()) {
            int next = (int)line.find(' ', pos);
            if (next == (int)string::npos) {
                next = (int)line.size();
            }
            ensuref(next > pos, "record %d line has repeated spaces", tc);

            string token = line.substr(pos, next - pos);
            int x = parseToken(token, tc);
            ensuref(x != 1, "record token 1 cannot be a room degree or distance delta");

            if (x == 0) {
                ensuref(hasToken, "record %d must contain at least one value before 0", tc);
                ensuref(path.empty(), "record %d ended before all rooms were closed", tc);

                ++tc;
                if (tc <= n) {
                    setTestCase(tc);
                    remaining.clear();
                    path.clear();
                    rooms = 0;
                    hasToken = false;
                } else {
                    ensuref(next == (int)line.size(),
                            "extra token after the final record terminator");
                }

                pos = next + 1;
                continue;
            }

            hasToken = true;

            if (x > 0) {
                ensuref(rooms < 99, "record %d has at least 100 rooms", tc);
                ++rooms;
                remaining.push_back(x);

                if (!path.empty()) {
                    int parent = path.back();
                    ensuref(remaining[parent] > 0,
                            "record %d opens a new room from room %d with no remaining doors",
                            tc, parent + 1);
                    --remaining[parent];
                    --remaining.back();
                }

                path.push_back(rooms - 1);
            } else {
                ensuref(!path.empty(), "record %d has a negative token with no current room", tc);
                int currentDepth = (int)path.size() - 1;
                int targetDepth = currentDepth + x;
                ensuref(0 <= targetDepth && targetDepth < currentDepth,
                        "record %d has invalid distance delta %d at depth %d",
                        tc, x, currentDepth);

                int current = path.back();
                int target = path[targetDepth];
                ensuref(remaining[current] > 0,
                        "record %d opens a door from room %d with no remaining doors",
                        tc, current + 1);
                ensuref(remaining[target] > 0,
                        "record %d opens a door to room %d with no remaining doors",
                        tc, target + 1);
                --remaining[current];
                --remaining[target];
            }

            while (!path.empty() && remaining[path.back()] == 0) {
                path.pop_back();
            }

            pos = next + 1;
        }
    }

    inf.readEof();
}
