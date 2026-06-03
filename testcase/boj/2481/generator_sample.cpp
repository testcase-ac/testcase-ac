#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string toCode(int mask, int k) {
    string code(k, '0');
    for (int bit = 0; bit < k; ++bit) {
        if (mask & (1 << bit)) {
            code[k - 1 - bit] = '1';
        }
    }
    return code;
}

string withPrefixCode(const string& prefix, int mask, int suffixLen) {
    string code = prefix;
    for (int bit = 0; bit < suffixLen; ++bit) {
        code.push_back((mask & (1 << (suffixLen - 1 - bit))) ? '1' : '0');
    }
    return code;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int k = 0;
    vector<string> codes;

    if (mode == 0) {
        k = rnd.next(2, 5);
        int limit = 1 << k;
        int n = rnd.next(3, min(limit, 18));
        vector<int> masks;
        for (int mask = 0; mask < limit; ++mask) {
            masks.push_back(mask);
        }
        shuffle(masks.begin(), masks.end());
        masks.resize(n);
        if (find(masks.begin(), masks.end(), 0) == masks.end()) {
            masks[rnd.next(n)] = 0;
        }
        for (int mask : masks) {
            codes.push_back(toCode(mask, k));
        }
    } else if (mode == 1) {
        k = rnd.next(3, 8);
        int pathLen = rnd.next(3, min(k + 1, 9));
        string cur(k, '0');
        codes.push_back(cur);
        vector<int> bits;
        for (int i = 0; i < k; ++i) {
            bits.push_back(i);
        }
        shuffle(bits.begin(), bits.end());
        for (int i = 1; i < pathLen; ++i) {
            cur[bits[i - 1]] = '1';
            codes.push_back(cur);
        }
        int limit = 1 << k;
        int targetN = rnd.next(pathLen, min(limit, pathLen + 8));
        set<string> used(codes.begin(), codes.end());
        while ((int)codes.size() < targetN) {
            string code = toCode(rnd.next(limit), k);
            if (used.insert(code).second) {
                codes.push_back(code);
            }
        }
    } else if (mode == 2) {
        k = rnd.next(4, 10);
        int suffixLen = rnd.next(2, min(5, k - 1));
        int targetN = rnd.next(6, min(18, 2 * (1 << suffixLen)));
        set<string> used;
        for (string prefix : {string(k - suffixLen, '0'), string(k - suffixLen, '1')}) {
            for (int mask = 0; mask < (1 << suffixLen) && (int)codes.size() < targetN; ++mask) {
                string code = withPrefixCode(prefix, mask, suffixLen);
                if (used.insert(code).second) {
                    codes.push_back(code);
                }
            }
        }
    } else if (mode == 3) {
        k = rnd.next(12, 30);
        int varying = rnd.next(2, 6);
        int targetN = rnd.next(3, min(20, 1 << varying));
        set<string> used;
        while ((int)codes.size() < targetN) {
            string code(k, '0');
            int mask = rnd.next(1 << varying);
            for (int bit = 0; bit < varying; ++bit) {
                if (mask & (1 << bit)) {
                    code[bit] = '1';
                }
            }
            if (used.insert(code).second) {
                codes.push_back(code);
            }
        }
    } else {
        k = rnd.next(2, 7);
        int targetN = rnd.next(3, min(16, 1 << k));
        set<string> used;
        used.insert(string(k, '0'));
        codes.push_back(string(k, '0'));
        while ((int)codes.size() < targetN) {
            string code = toCode(rnd.next(1 << k), k);
            if (used.insert(code).second) {
                codes.push_back(code);
            }
        }
    }

    shuffle(codes.begin() + 1, codes.end());

    int n = codes.size();
    int m = rnd.next(2, min(50, n - 1));
    vector<int> queries;
    for (int i = 2; i <= n; ++i) {
        queries.push_back(i);
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(m);

    println(n, k);
    for (const string& code : codes) {
        println(code);
    }
    println(m);
    for (int query : queries) {
        println(query);
    }

    return 0;
}
