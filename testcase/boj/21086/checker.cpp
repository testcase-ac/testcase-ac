#include "testlib.h"

#include <cctype>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, m;
vector<pair<int, int>> edges;

string lowerToken(string token) {
    for (char& c : token) {
        c = char(tolower(static_cast<unsigned char>(c)));
    }
    return token;
}

struct Answer {
    bool notSmol;
    int size;
};

Answer readAnswer(InStream& stream) {
    string first = stream.readToken();
    string normalized = lowerToken(first);

    if (normalized == "not") {
        string second = lowerToken(stream.readToken());
        if (second != "smol") {
            stream.quitf(_wa, "expected 'not smol', found 'not %s'", second.c_str());
        }
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after 'not smol'");
        }
        return {true, -1};
    }

    int coverSize = 0;
    try {
        size_t parsed = 0;
        coverSize = stoi(first, &parsed);
        if (parsed != first.size()) {
            stream.quitf(_wa, "cover size token is not an integer: %s", first.c_str());
        }
    } catch (...) {
        stream.quitf(_wa, "cover size token is not an integer: %s", first.c_str());
    }

    if (coverSize < 0 || coverSize > n) {
        stream.quitf(_wa, "cover size %d is outside [0, %d]", coverSize, n);
    }

    vector<int> used(n + 1, 0);
    for (int i = 0; i < coverSize; ++i) {
        int vertex = stream.readInt(1, n, format("cover[%d]", i + 1).c_str());
        if (used[vertex]) {
            stream.quitf(_wa, "vertex %d appears more than once", vertex);
        }
        used[vertex] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after vertex cover");
    }

    for (int i = 0; i < m; ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        if (!used[u] && !used[v]) {
            stream.quitf(_wa,
                         "edge %d (%d, %d) is not covered",
                         i + 1,
                         u,
                         v);
        }
    }

    return {false, coverSize};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.push_back({u, v});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.notSmol) {
        if (participant.notSmol) {
            quitf(_ok, "not smol");
        }
        quitf(_wa, "jury says not smol, participant gave cover of size %d", participant.size);
    }

    if (participant.notSmol) {
        quitf(_wa, "jury has cover of size %d, participant says not smol", jury.size);
    }

    if (participant.size != jury.size) {
        quitf(_wa,
              "cover size differs from jury answer: expected %d, found %d",
              jury.size,
              participant.size);
    }

    quitf(_ok, "cover size %d", participant.size);
}
