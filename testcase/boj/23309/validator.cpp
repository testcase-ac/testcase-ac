#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxId = 1000000;

    int n = inf.readInt(1, 500000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1500000, "m");
    inf.readEoln();

    vector<int> prv(maxId + 1, 0);
    vector<int> nxt(maxId + 1, 0);
    vector<char> active(maxId + 1, 0);
    vector<int> initial(n);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int station = inf.readInt(1, maxId, "station");
        ensuref(!active[station], "duplicate initial station id %d", station);
        active[station] = 1;
        initial[i] = station;
    }
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int station = initial[i];
        prv[station] = initial[(i + n - 1) % n];
        nxt[station] = initial[(i + 1) % n];
    }

    int activeCount = n;
    for (int q = 1; q <= m; ++q) {
        string op = inf.readToken("BN|BP|CN|CP", "op");
        inf.readSpace();
        int i = inf.readInt(1, maxId, "i");
        ensuref(active[i], "operation %d references inactive station %d", q, i);

        if (op == "BN" || op == "BP") {
            inf.readSpace();
            int j = inf.readInt(1, maxId, "j");
            ensuref(!active[j], "operation %d inserts already active station %d", q, j);
            inf.readEoln();

            if (op == "BN") {
                int after = nxt[i];
                nxt[i] = j;
                prv[j] = i;
                nxt[j] = after;
                prv[after] = j;
            } else {
                int before = prv[i];
                nxt[before] = j;
                prv[j] = before;
                nxt[j] = i;
                prv[i] = j;
            }
            active[j] = 1;
            ++activeCount;
        } else {
            ensuref(activeCount >= 2, "operation %d deletes when fewer than 2 stations are active", q);
            inf.readEoln();

            int removed = (op == "CN") ? nxt[i] : prv[i];
            int before = prv[removed];
            int after = nxt[removed];
            nxt[before] = after;
            prv[after] = before;
            active[removed] = 0;
            prv[removed] = 0;
            nxt[removed] = 0;
            --activeCount;
        }
    }

    inf.readEof();
}
