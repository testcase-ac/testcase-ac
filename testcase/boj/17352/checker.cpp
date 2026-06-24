#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

int n;
Dsu* dsu;

pair<int, int> readAnswer(InStream& stream) {
    int a = stream.readInt(1, n, "first island");
    int b = stream.readInt(1, n, "second island");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the two island numbers");
    }

    if (a == b) {
        stream.quitf(_wa, "the two islands must be different, found %d twice", a);
    }
    if (dsu->find(a) == dsu->find(b)) {
        stream.quitf(_wa,
                     "islands %d and %d are already connected before adding a bridge",
                     a, b);
    }
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    Dsu inputDsu(n);
    dsu = &inputDsu;

    for (int i = 0; i < n - 2; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        inputDsu.unite(a, b);
    }

    readAnswer(ans);
    auto participant = readAnswer(ouf);

    quitf(_ok,
          "bridge %d %d connects the two components",
          participant.first,
          participant.second);
}
