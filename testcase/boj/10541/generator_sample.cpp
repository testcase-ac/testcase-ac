#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000000LL;
    int mode = rnd.next(0, 5);

    long long n;
    string word;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int len = rnd.next(1, 6);
        string alphabet = "AB";
        for (int i = 0; i < len; ++i) word += rnd.any(alphabet);
    } else if (mode == 1) {
        n = rnd.next(40, 250);
        int len = rnd.next(2, 12);
        for (int i = 0; i < len; ++i) word += char('A' + (i % rnd.next(2, 5)));
    } else if (mode == 2) {
        n = rnd.next(maxN - 1000000, maxN);
        int len = rnd.next(1, 20);
        string alphabet = "ABCXYZ";
        for (int i = 0; i < len; ++i) word += rnd.any(alphabet);
    } else if (mode == 3) {
        n = rnd.next(1LL, maxN);
        word = string(rnd.next(1, 18), char('A' + rnd.next(0, 25)));
    } else if (mode == 4) {
        n = rnd.next(1LL, maxN);
        int len = rnd.next(10, 30);
        for (int i = 0; i < len; ++i) word += char('A' + rnd.next(0, 25));
    } else {
        n = rnd.next(999999999000000000LL, maxN);
        int len = rnd.next(2, 30);
        string alphabet = "JANETIBCDF";
        for (int i = 0; i < len; ++i) word += rnd.any(alphabet);
    }

    int k = rnd.next(8, 28);
    vector<pair<long long, char>> queries;

    auto addQuery = [&](long long row, char letter) {
        row = max(1LL, min(n, row));
        queries.push_back({row, letter});
    };

    addQuery(1, rnd.any(word));
    addQuery(n, rnd.any(word));
    if (n >= 2) addQuery(2, char('A' + rnd.next(0, 25)));
    if (n >= 3) addQuery(3, char('A' + rnd.next(0, 25)));

    long long len = (long long)word.size();
    for (long long base : {len - 1, len, len + 1, 2 * len, 2 * len + 1}) {
        if (base >= 1 && base <= n) addQuery(base, char('A' + rnd.next(0, 25)));
    }

    while ((int)queries.size() < k) {
        long long row;
        int rowMode = rnd.next(0, 5);
        if (rowMode == 0) {
            row = rnd.next(1LL, min(n, 50LL));
        } else if (rowMode == 1) {
            long long around = len * rnd.next(1, 20) + rnd.next(-2, 2);
            row = max(1LL, min(n, around));
        } else if (rowMode == 2) {
            row = max(1LL, n - rnd.next(0LL, min(n - 1, 1000LL)));
        } else {
            row = rnd.next(1LL, n);
        }

        char letter = rnd.next(0, 3) == 0 ? char('A' + rnd.next(0, 25)) : rnd.any(word);
        addQuery(row, letter);
    }

    shuffle(queries.begin(), queries.end());

    println(n);
    println(word);
    println((int)queries.size());
    for (const auto& query : queries) {
        println(query.first, string(1, query.second));
    }

    return 0;
}
