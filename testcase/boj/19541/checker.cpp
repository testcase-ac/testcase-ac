#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int N, M;
vector<vector<int>> meetings;
vector<int> final_inf;

// Reads and validates an answer (from either jury or participant).
// Returns a vector of size N with the initial infection state if the answer is "YES",
// or an empty vector if the answer is "NO".
// If the answer is invalid, quits with _wa (for ouf) or _fail (for ans).
vector<int> readAns(InStream &stream) {
    // read YES/NO token
    string tok = stream.readToken();
    if (tok == "NO") {
        // no solution
        return vector<int>();
    } else if (tok != "YES") {
        stream.quitf(_wa, "expected 'YES' or 'NO', found '%s'", tok.c_str());
    }
    // read initial vector
    vector<int> init(N);
    for (int i = 0; i < N; i++) {
        init[i] = stream.readInt(0, 1, format("initial[%d]", i+1).c_str());
    }
    // simulate forward
    vector<int> cur = init;
    for (int mi = 0; mi < M; mi++) {
        bool any = false;
        for (int v : meetings[mi]) {
            if (cur[v-1]) { any = true; break; }
        }
        if (any) {
            for (int v : meetings[mi]) {
                cur[v-1] = 1;
            }
        }
    }
    // check matches final_inf
    for (int i = 0; i < N; i++) {
        if (cur[i] != final_inf[i]) {
            stream.quitf(_wa, "simulation mismatch at person %d: expected %d, got %d",
                        i+1, final_inf[i], cur[i]);
        }
    }
    return init;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    N = inf.readInt();
    M = inf.readInt();
    meetings.resize(M);
    for (int i = 0; i < M; i++) {
        int k = inf.readInt(2, N);
        meetings[i].resize(k);
        for (int j = 0; j < k; j++) {
            meetings[i][j] = inf.readInt(1, N);
        }
    }
    final_inf.resize(N);
    for (int i = 0; i < N; i++) {
        final_inf[i] = inf.readInt(0, 1);
    }
    // read and validate both answers
    vector<int> ans_init = readAns(ans);
    vector<int> part_init = readAns(ouf);

    bool jury_no = ans_init.empty();
    bool part_no = part_init.empty();

    if (jury_no && part_no) {
        quitf(_ok, "both answer NO");
    }
    if (jury_no && !part_no) {
        quitf(_wa, "participant found a solution, but jury says NO");
    }
    if (!jury_no && part_no) {
        quitf(_wa, "jury found a solution, but participant says NO");
    }
    // both have a valid solution
    quitf(_ok, "valid solution provided");
}
