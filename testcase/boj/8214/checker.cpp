#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int gn;
vector< vector<char> > adj;

// Reads and validates an answer (list of gn/3 friends) from the given stream.
// On failure, quits with _wa for contestant stream or _fail for jury stream.
int readAns(InStream &stream) {
    int need = gn / 3;
    // Read count
    int k = stream.readInt(need, need, "number of invited friends");
    vector<int> v(k);
    for (int i = 0; i < k; i++) {
        v[i] = stream.readInt(1, gn, ("friend[" + to_string(i+1) + "]").c_str());
    }
    // Check strictly increasing
    for (int i = 1; i < k; i++) {
        if (v[i] <= v[i-1]) {
            stream.quitf(_wa,
                "list is not strictly increasing: friend[%d]=%d after friend[%d]=%d",
                i+1, v[i], i, v[i-1]);
        }
    }
    // Check clique: every pair must know each other
    for (int i = 0; i < k; i++) {
        for (int j = i+1; j < k; j++) {
            if (!adj[v[i]-1][v[j]-1]) {
                stream.quitf(_wa,
                    "friends %d and %d do not know each other",
                    v[i], v[j]);
            }
        }
    }
    // No extra tokens
    stream.skipBlanks();
    if (!stream.eof()) {
        stream.quitf(_wa, "extra tokens after the list of invited friends");
    }
    return 0;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    int n = inf.readInt();
    int m = inf.readInt();
    gn = n;
    adj.assign(n, vector<char>(n, 0));
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        adj[a-1][b-1] = adj[b-1][a-1] = 1;
    }

    // Read and validate jury answer (must not be broken)
    readAns(ans);
    // Read and validate contestant answer
    readAns(ouf);

    // If we reach here, contestant answer is valid
    quitf(_ok, "OK");
}
