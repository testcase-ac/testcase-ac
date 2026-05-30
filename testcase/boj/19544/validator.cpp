#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    vector<bitset<500>> mat(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            string name = "a_" + to_string(i + 1) + "_" + to_string(j + 1);
            int x = inf.readInt(0, 1, name.c_str());
            if (x) mat[i].set(j);
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    for (int i = 0; i < N; i++) {
        ensuref(mat[i].test(i),
                "diagonal element a_%d_%d must be 1", i + 1, i + 1);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!mat[i].test(j)) continue;
            bitset<500> diff = mat[j] & (~mat[i]);
            if (diff.none()) continue;
            int k = 0;
            while (!diff.test(k)) k++;
            ensuref(false,
                    "Transitivity violated: a_%d_%d = 1 and a_%d_%d = 1 but a_%d_%d = 0",
                    i + 1, j + 1, j + 1, k + 1, i + 1, k + 1);
        }
    }

    vector<int> comp(N, -1);
    vector<int> compSize;
    for (int i = 0; i < N; i++) {
        if (comp[i] != -1) continue;
        int id = compSize.size();
        compSize.push_back(0);
        for (int j = 0; j < N; j++) {
            if (mat[i].test(j) && mat[j].test(i)) {
                comp[j] = id;
                compSize[id]++;
            }
        }
    }

    int C = compSize.size();
    vector<bitset<500>> reach(C);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i].test(j)) reach[comp[i]].set(comp[j]);
        }
    }

    for (int c = 0; c < C; c++) {
        bool terminal = true;
        for (int d = 0; d < C; d++) {
            if (c != d && reach[c].test(d)) {
                terminal = false;
                break;
            }
        }

        ensuref(terminal || compSize[c] == 1,
                "non-terminal mutual-reachability class %d has size %d",
                c + 1, compSize[c]);

        for (int a = 0; a < C; a++) {
            if (a == c || !reach[c].test(a)) continue;
            for (int b = a + 1; b < C; b++) {
                if (b == c || !reach[c].test(b)) continue;
                ensuref(reach[a].test(b) || reach[b].test(a),
                        "reachable classes %d and %d from class %d are incomparable",
                        a + 1, b + 1, c + 1);
            }
        }
    }

    inf.readEof();
    return 0;
}
