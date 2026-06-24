#include "testlib.h"

#include <map>
#include <vector>

using namespace std;

struct Answer {
    bool unbounded;
    long long value;
};

int n, m;
map<pair<int, int>, int> bestEdge;

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, 0};
    }

    vector<int> path;
    path.push_back(first);
    while (!stream.seekEof()) {
        path.push_back(stream.readInt(1, n, format("path[%d]", int(path.size()) + 1).c_str()));
    }

    if (path.front() != 1) {
        stream.quitf(_wa, "path starts at %d instead of 1", path.front());
    }
    if (path.back() != n) {
        stream.quitf(_wa, "path ends at %d instead of %d", path.back(), n);
    }

    long long value = 0;
    for (int i = 0; i + 1 < int(path.size()); ++i) {
        auto it = bestEdge.find({path[i], path[i + 1]});
        if (it == bestEdge.end()) {
            stream.quitf(_wa, "edge %d -> %d does not exist", path[i], path[i + 1]);
        }
        value += it->second;
    }

    return {false, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        int w = inf.readInt();
        auto key = make_pair(u, v);
        auto it = bestEdge.find(key);
        if (it == bestEdge.end() || it->second < w) {
            bestEdge[key] = w;
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.unbounded) {
        if (participant.unbounded) {
            quitf(_ok, "both answers report no optimal path");
        }
        quitf(_wa, "jury reports no optimal path, but participant printed a finite path");
    }

    if (participant.unbounded) {
        quitf(_wa, "participant reports no optimal path, but jury has value %lld", jury.value);
    }
    if (participant.value < jury.value) {
        quitf(_wa, "participant value %lld is less than jury value %lld", participant.value, jury.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail, "participant value %lld is greater than jury value %lld", participant.value, jury.value);
    }

    quitf(_ok, "answer value %lld", participant.value);
}
