#include "testlib.h"

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int n, m, s;
unordered_set<long long> edges;

struct Answer {
    bool possible;
    vector<int> first;
    vector<int> second;
};

long long edgeKey(int u, int v) {
    return 1LL * u * (n + 1) + v;
}

void validatePath(InStream& stream, const vector<int>& path, const string& name) {
    if ((int)path.size() < 2) {
        stream.quitf(_wa, "%s path length is less than 2", name.c_str());
    }
    if (path.front() != s) {
        stream.quitf(_wa, "%s path starts at %d instead of %d", name.c_str(), path.front(), s);
    }
    if (path.back() == s) {
        stream.quitf(_wa, "%s path ends at the starting hall %d", name.c_str(), s);
    }

    vector<int> used(n + 1, 0);
    for (int i = 0; i < (int)path.size(); ++i) {
        int v = path[i];
        if (used[v]) {
            stream.quitf(_wa, "%s path repeats hall %d", name.c_str(), v);
        }
        used[v] = 1;
        if (i + 1 < (int)path.size() && !edges.count(edgeKey(path[i], path[i + 1]))) {
            stream.quitf(_wa,
                         "%s path uses missing passage %d -> %d",
                         name.c_str(),
                         path[i],
                         path[i + 1]);
        }
    }
}

vector<int> readPath(InStream& stream, const string& name) {
    int length = stream.readInt(2, n, (name + " path length").c_str());
    vector<int> path(length);
    for (int i = 0; i < length; ++i) {
        path[i] = stream.readInt(1, n, format("%s[%d]", name.c_str(), i + 1).c_str());
    }
    return path;
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("Possible|Impossible", "verdict");
    if (verdict == "Impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after Impossible");
        }
        return {false, {}, {}};
    }

    vector<int> first = readPath(stream, "first");
    vector<int> second = readPath(stream, "second");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after path descriptions");
    }

    validatePath(stream, first, "first");
    validatePath(stream, second, "second");

    if (first.back() != second.back()) {
        stream.quitf(_wa,
                     "paths end at different halls: %d and %d",
                     first.back(),
                     second.back());
    }
    if (first == second) {
        stream.quitf(_wa, "the two paths are identical");
    }

    vector<int> owner(n + 1, 0);
    for (int i = 1; i + 1 < (int)first.size(); ++i) {
        owner[first[i]] = 1;
    }
    for (int i = 1; i + 1 < (int)second.size(); ++i) {
        if (owner[second[i]]) {
            stream.quitf(_wa, "intermediate hall %d appears in both paths", second[i]);
        }
    }

    return {true, first, second};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    s = inf.readInt();

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.insert(edgeKey(u, v));
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible) {
        if (!participant.possible) {
            quitf(_ok, "both outputs report Impossible");
        }
        quitf(_fail, "participant found valid paths while jury reports Impossible");
    }

    if (!participant.possible) {
        quitf(_wa, "participant reports Impossible, but jury has valid paths");
    }

    quitf(_ok, "valid pair of paths ending at hall %d", participant.first.back());
}
