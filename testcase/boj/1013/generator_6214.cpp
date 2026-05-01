#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(5, 10);
    vector<string> tests;
    tests.reserve(T);

    for (int ti = 0; ti < T; ti++) {
        bool makeValid = rnd.next(0, 1) == 0;
        // For valid, build segments; for invalid, either small or corrupt a valid
        if (makeValid) {
            int K = rnd.next(1, 5);
            string s;
            for (int i = 0; i < K; i++) {
                if (rnd.next(0,1) == 0) {
                    // pattern 100+1+
                    int z = rnd.next(2, 5);
                    int o = rnd.next(1, 5);
                    s.push_back('1');
                    for (int j = 0; j < z; j++) s.push_back('0');
                    for (int j = 0; j < o; j++) s.push_back('1');
                } else {
                    // pattern 01
                    s.push_back('0');
                    s.push_back('1');
                }
            }
            tests.push_back(s);
        } else {
            // occasionally produce a very short invalid
            if (rnd.next(0, 3) == 0) {
                char c = rnd.next(0,1) ? '1' : '0';
                tests.push_back(string(1, c));
            } else {
                // first build a valid sequence of segments
                int K = rnd.next(1, 5);
                vector<string> segs;
                segs.reserve(K);
                for (int i = 0; i < K; i++) {
                    if (rnd.next(0,1) == 0) {
                        int z = rnd.next(2, 5);
                        int o = rnd.next(1, 5);
                        string seg = "1";
                        seg.append(z, '0');
                        seg.append(o, '1');
                        segs.push_back(seg);
                    } else {
                        segs.push_back("01");
                    }
                }
                // choose one segment to corrupt
                int idx = rnd.next(0, K-1);
                string &bad = segs[idx];
                if (bad == "01") {
                    // corrupt to "00"
                    bad = "00";
                } else {
                    // drop last char
                    if (bad.size() > 1) bad.pop_back();
                }
                // concatenate
                string s;
                for (auto &seg : segs) s += seg;
                tests.push_back(s);
            }
        }
    }

    println(T);
    for (auto &s : tests) println(s);
    return 0;
}
