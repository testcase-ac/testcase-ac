#include "testlib.h"
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int L = rnd.next(1, 50);                // total max length
    double pCompress = rnd.next(0.0, 1.0);   // prob to try compression
    double pNested = rnd.next(0.0, 1.0);     // prob to nest inside Q
    int maxPlainLen = rnd.next(1, 5);        // max consecutive plain digits
    int maxDepth = rnd.next(1, 3);           // max nesting depth

    function<string(int,int)> build = [&](int rem, int depth) -> string {
        if (rem <= 0) return "";
        bool tryC = depth > 0 && rnd.next() < pCompress && rem >= 3;
        if (tryC) {
            int K = rnd.next(0, 9);
            int maxQLen = rem - 2; // subtract for "K("
            // decide nest or plain Q
            bool nest = depth > 1 && rnd.next() < pNested;
            string Q;
            if (nest && maxQLen > 0) {
                int qAlloc = rnd.next(0, maxQLen);
                Q = build(qAlloc, depth - 1);
            } else {
                int qLen = rnd.next(0, maxQLen);
                Q.reserve(qLen);
                for (int i = 0; i < qLen; i++)
                    Q.push_back(char('0' + rnd.next(0, 9)));
            }
            string seg = string(1, char('0' + K)) + "(" + Q + ")";
            if ((int)seg.size() <= rem)
                return seg;
        }
        // fallback to plain digits
        int maxP = min(rem, maxPlainLen);
        int pLen = rnd.next(1, maxP);
        string seg;
        seg.reserve(pLen);
        for (int i = 0; i < pLen; i++)
            seg.push_back(char('0' + rnd.next(0, 9)));
        return seg;
    };

    // Build the string in segments until reaching length L
    string S;
    int rem = L;
    while (rem > 0) {
        string part = build(rem, maxDepth);
        if (part.empty()) break;
        S += part;
        rem = L - (int)S.size();
    }
    if (S.empty()) S = "0"; // ensure non-empty

    println(S);
    return 0;
}
