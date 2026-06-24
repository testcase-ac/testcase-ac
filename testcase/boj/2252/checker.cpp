#include "testlib.h"

#include <vector>

using namespace std;

int n, m;
vector<pair<int, int>> edges;

struct Answer {
    vector<int> order;
};

Answer readAnswer(InStream& stream, TResult invalidVerdict) {
    vector<int> order(n);
    vector<int> position(n + 1, -1);

    for (int i = 0; i < n; ++i) {
        int student = stream.readInt(1, n, format("order[%d]", i + 1).c_str());
        if (position[student] != -1) {
            stream.quitf(invalidVerdict,
                         "student %d appears more than once, at positions %d and %d",
                         student,
                         position[student] + 1,
                         i + 1);
        }
        order[i] = student;
        position[student] = i;
    }

    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %d students", n);
    }

    for (const auto& edge : edges) {
        int before = edge.first;
        int after = edge.second;
        if (position[before] > position[after]) {
            stream.quitf(invalidVerdict,
                         "constraint %d before %d is violated: positions are %d and %d",
                         before,
                         after,
                         position[before] + 1,
                         position[after] + 1);
        }
    }

    return {order};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.push_back({a, b});
    }

    readAnswer(ans, _fail);
    readAnswer(ouf, _wa);

    quitf(_ok, "valid topological order");
}
