#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small or medium N
    int N;
    if (rnd.next(0, 1) == 0) {
        // small case
        N = rnd.next(2, 5);
    } else {
        // medium case
        N = rnd.next(6, 15);
    }

    // Generate unique other channel names (excluding KBS1, KBS2)
    int M = N - 2;
    set<string> S;
    const string KS1 = "KBS1";
    const string KS2 = "KBS2";
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    while ((int)S.size() < M) {
        // Hyper-parameter: name length small or up to max 10
        int len;
        if (rnd.next(0, 2) == 0) len = rnd.next(1, 3);
        else len = rnd.next(4, 10);

        string s;
        for (int i = 0; i < len; i++) {
            s += chars[rnd.next((int)chars.size() - 1)];
        }
        if (s == KS1 || s == KS2) continue;
        S.insert(s);
    }
    vector<string> others(S.begin(), S.end());

    // Choose positions for KBS1 and KBS2, ensure not already [0]="KBS1",[1]="KBS2"
    int pos1, pos2;
    do {
        pos1 = rnd.next(0, N - 1);
        pos2 = rnd.next(0, N - 1);
    } while (pos1 == pos2 || (pos1 == 0 && pos2 == 1));

    // Build final list
    vector<string> vs(N);
    int idx = 0;
    for (int i = 0; i < N; i++) {
        if (i == pos1) {
            vs[i] = KS1;
        } else if (i == pos2) {
            vs[i] = KS2;
        } else {
            vs[i] = others[idx++];
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(vs[i]);
    }

    return 0;
}
