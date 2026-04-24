#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Base valid 6x6 knight tour (cycle)
    vector<string> base = {
        "A1","B3","A5","C6","E5","F3","D2","F1","E3","F5","D4","B5",
        "A3","B1","C3","A2","C1","E2","F4","E6","C5","A6","B4","D5",
        "F6","E4","D6","C4","B6","A4","B2","D1","F2","D3","E1","C2"
    };
    // Parse to 0-based coords
    vector<pair<int,int>> tour;
    for (auto &s : base) {
        int x = s[0] - 'A';
        int y = s[1] - '1';
        tour.emplace_back(x, y);
    }
    // Random dihedral transformation
    int t = rnd.next(0, 7);
    bool do_reflect = (t >= 4);
    int rot = t % 4;
    vector<pair<int,int>> trans;
    for (auto &p : tour) {
        int x = p.first, y = p.second;
        if (do_reflect) x = 5 - x;
        // apply rotation rot times: (x,y)->(y,5-x)
        for (int i = 0; i < rot; i++) {
            int nx = y;
            int ny = 5 - x;
            x = nx; y = ny;
        }
        trans.emplace_back(x, y);
    }
    // Random cyclic shift
    int offset = rnd.next(0, 35);
    vector<pair<int,int>> seq(36);
    for (int i = 0; i < 36; i++) {
        seq[i] = trans[(i + offset) % 36];
    }
    // Random reverse direction (keeping start point)
    if (rnd.next(0, 1) == 1) {
        // Make reversed tour starting at seq[0]
        vector<pair<int,int>> rev = seq;
        for (int i = 1; i < 36; i++) {
            rev[i] = seq[(36 - i) % 36];
        }
        seq = rev;
    }
    // Output 36 lines
    for (auto &p : seq) {
        char c1 = char('A' + p.first);
        char c2 = char('1' + p.second);
        string s;
        s.push_back(c1);
        s.push_back(c2);
        println(s);
    }
    return 0;
}
