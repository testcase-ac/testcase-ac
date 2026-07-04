#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeString(const vector<string>& pool, int maxLen) {
    int mode = rnd.next(0, 4);

    if (mode == 0 && !pool.empty()) {
        return rnd.any(pool);
    }

    if (mode == 1 && !pool.empty()) {
        string base = rnd.any(pool);
        int keep = rnd.next(1, static_cast<int>(base.size()));
        return base.substr(0, keep);
    }

    if (mode == 2 && !pool.empty()) {
        string base = rnd.any(pool);
        int start = rnd.next(0, static_cast<int>(base.size()) - 1);
        return base.substr(start);
    }

    int len = rnd.next(1, maxLen);
    string s;
    s.reserve(len);

    string alphabet = mode == 3 ? "abc" : "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

long long makeScore() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(-20, 20);
    if (mode == 2) return rnd.next(-1000, 1000);
    if (mode == 3) return rnd.next(0, 1) == 0 ? -1000000000LL : 1000000000LL;
    if (mode == 4) return rnd.next(-1000000000, 1000000000);
    return rnd.next(0, 1) == 0 ? -1 : 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(8, 45);
    int maxLen = rnd.next(1, 12);

    vector<string> pool = {
        "a", "b", "c", "ab", "abc", "abcd", "bc", "cde", "zz", "az"
    };
    vector<string> generated;
    int answerQueries = 0;

    println(q);
    for (int i = 0; i < q; ++i) {
        bool forceAnswer = (i == q - 1 && answerQueries == 0);
        bool emitAnswer = forceAnswer || rnd.next(100) < 35;

        if (emitAnswer) {
            println(rnd.next(0, 1) == 0 ? "+" : "-");
            ++answerQueries;
            continue;
        }

        string op = rnd.next(0, 1) == 0 ? "<" : ">";
        string str = makeString(pool, maxLen);
        long long score = makeScore();

        println(op, str, score);

        if (generated.size() < 30) {
            generated.push_back(str);
            pool.push_back(str);
        } else if (rnd.next(100) < 20) {
            pool[rnd.next(0, static_cast<int>(pool.size()) - 1)] = str;
        }
    }

    return 0;
}
