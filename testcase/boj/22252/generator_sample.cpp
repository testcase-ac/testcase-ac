#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Query {
    int type;
    string name;
    vector<int> values;
    int amount;
};

string makeName(int index) {
    static const vector<string> fixed = {
        "A", "z", "Cpp", "Java", "Python", "abcDEFGHIJKLMNO",
    };
    if (index < (int)fixed.size()) return fixed[index];

    string name;
    int x = index;
    do {
        name.push_back(char('a' + x % 26));
        x /= 26;
    } while (x > 0 && (int)name.size() < 15);
    return name;
}

vector<int> makeValues(int k, int mode) {
    vector<int> values;
    values.reserve(k);

    if (mode == 0) {
        int base = rnd.next(1, 20);
        for (int i = 0; i < k; ++i) values.push_back(base);
    } else if (mode == 1) {
        int start = rnd.next(1, 100000 - k + 1);
        for (int i = 0; i < k; ++i) values.push_back(start + i);
    } else if (mode == 2) {
        int start = rnd.next(k, 100000);
        for (int i = 0; i < k; ++i) values.push_back(start - i);
    } else if (mode == 3) {
        for (int i = 0; i < k; ++i) values.push_back(rnd.any(vector<int>{1, 2, 99999, 100000}));
    } else {
        int hi = rnd.next(3, 100000);
        int lo = rnd.next(1, min(hi, 50));
        for (int i = 0; i < k; ++i) values.push_back(rnd.next(lo, hi));
    }

    if (rnd.next(2)) shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(1, 35);
    int nameCount = rnd.next(1, 8);
    int mode = rnd.next(0, 4);
    int totalK = 0;
    vector<Query> queries;
    queries.reserve(q);

    for (int i = 0; i < q; ++i) {
        bool addInfo = (i == 0) || rnd.next(100) < (mode == 0 ? 70 : 55);
        int nameIndex;
        if (mode == 1 && rnd.next(100) < 70) {
            nameIndex = 0;
        } else if (mode == 2 && i + 1 == q) {
            nameIndex = min(5, nameCount - 1);
        } else {
            nameIndex = rnd.next(0, nameCount - 1);
        }

        Query query;
        query.type = addInfo ? 1 : 2;
        query.name = makeName(nameIndex);
        query.amount = 0;

        if (query.type == 1) {
            int k = rnd.next(1, mode == 3 ? 25 : 8);
            totalK += k;
            query.values = makeValues(k, rnd.next(0, 4));
        } else {
            if (mode == 4 && rnd.next(100) < 45) {
                query.amount = rnd.next(50000, 100000);
            } else {
                query.amount = rnd.next(1, 12);
            }
        }

        queries.push_back(query);
    }

    if (mode == 2 && totalK + 1 <= 1000000) {
        queries.push_back({1, "abcDEFGHIJKLMNO", makeValues(1, 3), 0});
        queries.push_back({2, "abcDEFGHIJKLMNO", {}, 100000});
    }

    println((int)queries.size());
    for (const Query& query : queries) {
        if (query.type == 1) {
            printf("1 %s %d", query.name.c_str(), (int)query.values.size());
            for (int value : query.values) printf(" %d", value);
            printf("\n");
        } else {
            println(2, query.name, query.amount);
        }
    }

    return 0;
}
