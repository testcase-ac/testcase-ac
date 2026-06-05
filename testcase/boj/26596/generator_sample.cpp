#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Entry {
    string name;
    int amount;
};

string ingredientName(int index, bool longName) {
    if (longName) {
        string name(50, char('A' + index % 26));
        if (index % 2) {
            name[0] = 'a';
            name[49] = 'Z';
        }
        return name;
    }

    string name = "I";
    int x = index;
    do {
        name += char('A' + x % 26);
        x /= 26;
    } while (x > 0);

    if (index % 3 == 1) name[0] = 'i';
    return name;
}

void addSplitAmount(vector<Entry>& entries, const string& name, int total) {
    while (total > 0) {
        int amount = rnd.next(1, min(100, total));
        entries.push_back({name, amount});
        total -= amount;
    }
}

int goldenPartner(int value) {
    return value * 1618 / 1000;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Entry> entries;
    int mode = rnd.next(0, 5);
    int distinct = rnd.next(1, 12);
    bool useLongNames = rnd.next(0, 9) == 0;

    if (mode == 0) {
        addSplitAmount(entries, ingredientName(0, useLongNames), rnd.next(1, 100));
    } else if (mode <= 2) {
        int base = rnd.next(1, 120);
        int partner = goldenPartner(base);
        if (partner < 1) partner = 1;

        addSplitAmount(entries, ingredientName(0, useLongNames), base);
        addSplitAmount(entries, ingredientName(1, useLongNames), partner);

        for (int i = 2; i < distinct; ++i) {
            int total = rnd.next(1, 220);
            addSplitAmount(entries, ingredientName(i, useLongNames), total);
        }
    } else if (mode == 3) {
        for (int i = 0; i < distinct; ++i) {
            int total = rnd.next(1, 90) * 2 + (i % 2);
            addSplitAmount(entries, ingredientName(i, useLongNames), total);
        }
    } else {
        int copies = rnd.next(2, 20);
        for (int i = 0; i < copies; ++i) {
            string name = ingredientName(rnd.next(0, max(1, distinct - 1)), useLongNames);
            entries.push_back({name, rnd.next(1, 100)});
        }
    }

    shuffle(entries.begin(), entries.end());

    println((int)entries.size());
    for (const Entry& entry : entries) {
        println(entry.name, entry.amount);
    }

    return 0;
}
