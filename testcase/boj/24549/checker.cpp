#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int n, m, k;
vector<vector<int>> blocked;

const int edx[] = {-3, -3, -2, -2, 2, 2, 3, 3};
const int edy[] = {2, -2, 3, -3, 3, -3, 2, -2};

bool inside(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

void markBlocked(int x, int y) {
    if (inside(x, y)) {
        blocked[x][y] = 1;
    }
}

struct Answer {
    int count;
};

void invalid(InStream& stream, TResult verdict, const string& message) {
    stream.quitf(verdict, "%s", message.c_str());
}

Answer readAnswer(InStream& stream, TResult invalidVerdict) {
    int count = stream.readInt(0, n * m, "number of elephants");
    vector<pair<int, int>> elephants;
    elephants.reserve(count);
    set<pair<int, int>> used;

    for (int i = 0; i < count; ++i) {
        int x = stream.readInt(1, n, format("x[%d]", i + 1).c_str());
        int y = stream.readInt(1, m, format("y[%d]", i + 1).c_str());
        pair<int, int> cell = {x, y};

        if (used.count(cell)) {
            invalid(stream, invalidVerdict, format("duplicate elephant at (%d, %d)", x, y));
        }
        if (blocked[x][y]) {
            invalid(stream, invalidVerdict,
                    format("elephant %d is placed on an unsafe cell (%d, %d)", i + 1, x, y));
        }

        for (const auto& other : elephants) {
            int dx = x - other.first;
            int dy = y - other.second;
            for (int dir = 0; dir < 8; ++dir) {
                if (dx == edx[dir] && dy == edy[dir]) {
                    invalid(stream, invalidVerdict,
                            format("elephants at (%d, %d) and (%d, %d) attack each other",
                                   x, y, other.first, other.second));
                }
            }
        }

        used.insert(cell);
        elephants.push_back(cell);
    }

    if (!stream.seekEof()) {
        invalid(stream, invalidVerdict, "extra output after elephant positions");
    }
    return {count};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    k = inf.readInt();
    blocked.assign(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i < k; ++i) {
        int x = inf.readInt();
        int y = inf.readInt();

        markBlocked(x, y);
        markBlocked(x - 1, y);
        markBlocked(x + 1, y);
        markBlocked(x, y + 1);

        for (int dir = 0; dir < 8; ++dir) {
            markBlocked(x + edx[dir], y + edy[dir]);
        }
    }

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (participant.count < jury.count) {
        quitf(_wa, "jury places more elephants: jury=%d participant=%d", jury.count, participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail, "participant found a better placement: jury=%d participant=%d", jury.count, participant.count);
    }
    quitf(_ok, "accepted placement with %d elephants", participant.count);
}
