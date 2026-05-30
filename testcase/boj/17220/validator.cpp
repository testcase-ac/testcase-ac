#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 26, "N");
    inf.readSpace();
    int M = inf.readInt(1, 600, "M");
    inf.readEoln();

    // Map supplier labels 'A'.. to indices 0..N-1
    auto readNode = [&](const char* name) -> int {
        string t = inf.readToken("[A-Z]", name);
        char c = t[0];
        int id = c - 'A';
        ensuref(0 <= id && id < N,
                "Node %s = '%c' (id %d) is out of allowed range A..%c for N=%d",
                name, c, id, char('A' + N - 1), N);
        return id;
    };

    // Read M relations: "A B" meaning A -> B, one per line
    for (int i = 0; i < M; ++i) {
        int u = readNode("u");
        inf.readSpace();
        int v = readNode("v");
        inf.readEoln();

        (void)u;
        (void)v;
    }

    // Read last line: number of known suppliers K, then K labels
    int K = inf.readInt(0, N, "K");
    if (K > 0) inf.readSpace();
    vector<int> arrested;
    arrested.reserve(K);
    vector<bool> isArrested(N, false);

    for (int i = 0; i < K; ++i) {
        int x = readNode("arrested_i");
        if (i + 1 < K) inf.readSpace();
        // suppliers in this list should be distinct (natural assumption)
        ensuref(!isArrested[x],
                "Arrested supplier '%c' appears multiple times",
                char('A' + x));
        isArrested[x] = true;
        arrested.push_back(x);
    }
    inf.readEoln();

    inf.readEof();
}
