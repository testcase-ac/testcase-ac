#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string makeWord(int minLen, int maxLen, int alphabetSize) {
    int len = rnd.next(minLen, maxLen);
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('a' + rnd.next(alphabetSize));
    }
    return s;
}

vector<string> makeWords(int count, int mode) {
    vector<string> pool;
    int poolSize = count;
    int minLen = 1;
    int maxLen = 10;
    int alphabetSize = rnd.next(1, 26);

    if (mode == 0) {
        poolSize = rnd.next(1, min(count, 3));
        maxLen = rnd.next(1, 3);
        alphabetSize = rnd.next(1, 3);
    } else if (mode == 1) {
        poolSize = rnd.next(1, min(count, 5));
        minLen = maxLen = rnd.next(1, 10);
        alphabetSize = rnd.next(1, 6);
    } else if (mode == 2) {
        maxLen = rnd.next(5, 10);
    }

    for (int i = 0; i < poolSize; ++i) {
        pool.push_back(makeWord(minLen, maxLen, alphabetSize));
    }

    vector<string> words;
    for (int i = 0; i < count; ++i) {
        if (mode != 2 && rnd.next(4) == 0) {
            words.push_back(rnd.any(pool));
        } else {
            words.push_back(pool[i % poolSize]);
        }
    }
    shuffle(words.begin(), words.end());
    return words;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n, m;
    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 2) {
        n = 20;
        m = 20;
    } else if (mode == 3) {
        vector<int> sizes = {7, 11, 13, 17, 19, 20};
        n = rnd.any(sizes);
        m = rnd.any(sizes);
    } else {
        n = rnd.next(1, 20);
        m = rnd.next(1, 20);
    }

    vector<string> s = makeWords(n, mode);
    vector<string> t = makeWords(m, (mode + 1) % 3);

    vector<int> queries = {1, 2, n, m, n + 1, m + 1, 2020, 1000000000};
    int cycle = n * m / __gcd(n, m);
    queries.push_back(cycle);
    queries.push_back(cycle + 1);

    int q = rnd.next(1, 30);
    while ((int)queries.size() < q) {
        int choice = rnd.next(5);
        if (choice == 0) {
            queries.push_back(rnd.next(1, 30));
        } else if (choice == 1) {
            queries.push_back(rnd.next(max(1, cycle - 5), min(1000000000, cycle + 5)));
        } else if (choice == 2) {
            queries.push_back(rnd.next(2010, 2020));
        } else if (choice == 3) {
            queries.push_back(rnd.next(999999900, 1000000000));
        } else {
            queries.push_back(rnd.next(1, 1000000000));
        }
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(q);

    println(n, m);
    println(s);
    println(t);
    println(q);
    for (int y : queries) {
        println(y);
    }

    return 0;
}
