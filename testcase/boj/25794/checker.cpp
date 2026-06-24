#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Point = pair<ll, ll>;

const int MAX_K = 200000;
const ll COORD_LIMIT = 4000000000000000000LL;

int X, Y;
vector<Point> moves;

vector<Point> buildMoves() {
    vector<Point> result;
    vector<ll> sx = {-1, 1};
    vector<ll> sy = {-1, 1};

    for (ll a : {static_cast<ll>(X), static_cast<ll>(Y)}) {
        ll b = (a == X ? Y : X);
        for (ll dxSign : sx) {
            for (ll dySign : sy) {
                Point move = {dxSign * a, dySign * b};
                if (move != Point{0, 0}) {
                    result.push_back(move);
                }
            }
        }
    }

    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}

bool isLegalMove(const Point& from, const Point& to) {
    ll dx = to.first - from.first;
    ll dy = to.second - from.second;
    for (const Point& move : moves) {
        if (dx == move.first && dy == move.second) {
            return true;
        }
    }
    return false;
}

struct Answer {
    int k;
};

Answer readAnswer(InStream& stream, int maxK) {
    int k = stream.readInt(0, maxK, "K");
    stream.readEoln();

    Point current = {0, 0};
    set<Point> eaten;

    for (int i = 0; i < k; ++i) {
        ll nx = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("x[%d]", i + 1));
        stream.readSpace();
        ll ny = stream.readLong(-COORD_LIMIT, COORD_LIMIT, format("y[%d]", i + 1));
        stream.readEoln();

        Point next = {nx, ny};
        if (!isLegalMove(current, next)) {
            stream.quitf(_wa,
                         "move %d from (%lld, %lld) to (%lld, %lld) is not legal",
                         i + 1,
                         current.first,
                         current.second,
                         next.first,
                         next.second);
        }
        if (eaten.count(next)) {
            stream.quitf(_wa,
                         "move %d lands on eaten chocolate at (%lld, %lld)",
                         i + 1,
                         next.first,
                         next.second);
        }

        eaten.insert(current);
        current = next;
    }

    stream.readEof();

    for (const Point& move : moves) {
        Point next = {current.first + move.first, current.second + move.second};
        if (!eaten.count(next)) {
            stream.quitf(_wa,
                         "knight is not stuck after %d moves: can move to (%lld, %lld)",
                         k,
                         next.first,
                         next.second);
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    X = inf.readInt();
    Y = inf.readInt();
    moves = buildMoves();

    Answer jury = readAnswer(ans, MAX_K);
    Answer participant = readAnswer(ouf, MAX_K);

    if (participant.k > jury.k) {
        quitf(_wa,
              "participant uses more moves than jury: participant=%d jury=%d",
              participant.k,
              jury.k);
    }
    if (participant.k < jury.k) {
        quitf(_fail,
              "participant found a shorter valid game: participant=%d jury=%d",
              participant.k,
              jury.k);
    }

    quitf(_ok, "valid game ending in %d moves", participant.k);
}
