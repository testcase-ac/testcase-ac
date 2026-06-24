#include "testlib.h"

#include <climits>
#include <set>
#include <vector>

using namespace std;

int n;
long long targetHay;
vector<long long> initialHay;
set<pair<int, int>> roads;

struct Answer {
    int orderCount;
};

Answer readAnswer(InStream& stream) {
    int orderCount = stream.readInt(0, n - 1, "order count");
    vector<long long> hay = initialHay;

    for (int i = 1; i <= orderCount; ++i) {
        int source = stream.readInt(1, n, format("source[%d]", i).c_str());
        int destination = stream.readInt(1, n, format("destination[%d]", i).c_str());
        long long amount = stream.readLong(1LL, LLONG_MAX, format("amount[%d]", i).c_str());

        if (!roads.count({source, destination})) {
            stream.quitf(_wa, "order %d uses non-road edge %d -> %d", i, source, destination);
        }
        if (amount > hay[source]) {
            stream.quitf(_wa,
                         "order %d moves %lld bales from barn %d with only %lld bales",
                         i,
                         amount,
                         source,
                         hay[source]);
        }

        hay[source] -= amount;
        hay[destination] += amount;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d orders", orderCount);
    }

    for (int barn = 1; barn <= n; ++barn) {
        if (hay[barn] != targetHay) {
            stream.quitf(_wa,
                         "barn %d has %lld bales after all orders, expected %lld",
                         barn,
                         hay[barn],
                         targetHay);
        }
    }

    return {orderCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialHay.assign(n + 1, 0);

    long long totalHay = 0;
    for (int barn = 1; barn <= n; ++barn) {
        initialHay[barn] = inf.readLong();
        totalHay += initialHay[barn];
    }
    targetHay = totalHay / n;

    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        roads.insert({u, v});
        roads.insert({v, u});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.orderCount > jury.orderCount) {
        quitf(_wa,
              "too many orders: participant=%d jury=%d",
              participant.orderCount,
              jury.orderCount);
    }
    if (participant.orderCount < jury.orderCount) {
        quitf(_fail,
              "participant found fewer valid orders: participant=%d jury=%d",
              participant.orderCount,
              jury.orderCount);
    }

    quitf(_ok, "valid sequence with %d orders", participant.orderCount);
}
