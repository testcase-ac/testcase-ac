#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

vector<int> make_row(int N) {
    // decide number of plates
    int cnt;
    int t = rnd.next(0, 9);
    if (t < 1) {
        cnt = 0;               // empty row
    } else if (t > 8) {
        cnt = N;               // full row
    } else {
        if (N >= 2)
            cnt = rnd.next(1, N - 1);
        else
            cnt = 1;           // when N==1
    }
    // generate plate values in original order
    vector<int> plates;
    for (int i = 0; i < cnt; i++) {
        int v;
        do {
            v = rnd.next(-10, 10);
        } while (v == 0);
        plates.push_back(v);
    }
    // prepare row with zeros
    vector<int> row(N, 0);
    if (cnt == 0) return row;
    double cluster = rnd.next();
    if (cluster < 0.3 || cnt == 1) {
        // scatter plates randomly
        vector<int> pos(N);
        iota(pos.begin(), pos.end(), 0);
        shuffle(pos.begin(), pos.end());
        pos.resize(cnt);
        sort(pos.begin(), pos.end());
        for (int i = 0; i < cnt; i++) {
            row[pos[i]] = plates[i];
        }
    } else if (cluster < 0.6) {
        // single contiguous block
        int start = rnd.next(0, N - cnt);
        for (int i = 0; i < cnt; i++) {
            row[start + i] = plates[i];
        }
    } else {
        // two blocks if possible
        if (cnt >= 2) {
            int k1 = rnd.next(1, cnt - 1);
            int k2 = cnt - k1;
            // possible starts for block2 avoiding overlap
            int start1 = rnd.next(0, N - k1);
            vector<int> good;
            for (int s = 0; s <= N - k2; s++) {
                if (s + k2 <= start1 || s >= start1 + k1)
                    good.push_back(s);
            }
            if (good.empty()) {
                // fallback to one block
                int start = rnd.next(0, N - cnt);
                for (int i = 0; i < cnt; i++)
                    row[start + i] = plates[i];
            } else {
                int start2 = rnd.any(good);
                for (int i = 0; i < k1; i++)
                    row[start1 + i] = plates[i];
                for (int i = 0; i < k2; i++)
                    row[start2 + i] = plates[k1 + i];
            }
        } else {
            // cnt==1 fallback
            int p = rnd.next(0, N - 1);
            row[p] = plates[0];
        }
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // choose N: small, medium, or larger (up to 30)
    int N;
    int mode = rnd.next(0, 9);
    if (mode < 5) {
        N = rnd.next(1, 5);
    } else if (mode < 8) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 30);
    }
    auto top = make_row(N);
    auto bot = make_row(N);
    // output
    println(N);
    println(top);
    println(bot);
    return 0;
}
