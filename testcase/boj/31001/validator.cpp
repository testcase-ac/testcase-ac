#include "testlib.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_PRICE = 2000000000LL;
    const long long MAX_TOTAL = 2000000000000LL;

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    long long cash = inf.readLong(1000000LL, 10000000LL, "M");
    inf.readSpace();
    int q = inf.readInt(1, 500, "Q");
    inf.readEoln();

    vector<int> group(n);
    vector<long long> price(n);
    vector<long long> stock(n, 0);
    vector<vector<int>> companiesInGroup(101);
    map<string, int> idByName;

    for (int i = 0; i < n; ++i) {
        group[i] = inf.readInt(1, 100, "G");
        inf.readSpace();
        string name = inf.readToken("[A-Za-z]{1,30}", "H");
        inf.readSpace();
        price[i] = inf.readLong(0LL, 30000LL, "P");
        inf.readEoln();

        ensuref(price[i] % 10 == 0, "initial price at company %d is not a multiple of 10: %lld", i + 1, price[i]);
        ensuref(idByName.emplace(name, i).second, "duplicate company name: %s", name.c_str());
        companiesInGroup[group[i]].push_back(i);
    }

    auto liquidationValue = [&]() -> __int128_t {
        __int128_t total = cash;
        for (int i = 0; i < n; ++i) {
            total += static_cast<__int128_t>(stock[i]) * price[i];
        }
        return total;
    };

    auto checkGlobalState = [&](int commandIndex) {
        for (int i = 0; i < n; ++i) {
            ensuref(0 <= price[i] && price[i] <= MAX_PRICE,
                    "price of company %d after command %d is out of range: %lld",
                    i + 1,
                    commandIndex,
                    price[i]);
        }
        ensuref(liquidationValue() <= MAX_TOTAL,
                "liquidation value after command %d exceeds %lld",
                commandIndex,
                MAX_TOTAL);
    };

    bool hasOutputCommand = false;
    for (int commandIndex = 1; commandIndex <= q; ++commandIndex) {
        int op = inf.readInt(1, 7, "menu");

        if (op == 1) {
            inf.readSpace();
            string name = inf.readToken("[A-Za-z]{1,30}", "A");
            inf.readSpace();
            int amount = inf.readInt(1, 100, "B");
            inf.readEoln();

            auto it = idByName.find(name);
            ensuref(it != idByName.end(), "unknown company in buy command %d: %s", commandIndex, name.c_str());
            int id = it->second;
            long long cost = price[id] * amount;
            if (cost <= cash) {
                cash -= cost;
                stock[id] += amount;
            }
        } else if (op == 2) {
            inf.readSpace();
            string name = inf.readToken("[A-Za-z]{1,30}", "A");
            inf.readSpace();
            int amount = inf.readInt(1, 100, "B");
            inf.readEoln();

            auto it = idByName.find(name);
            ensuref(it != idByName.end(), "unknown company in sell command %d: %s", commandIndex, name.c_str());
            int id = it->second;
            long long sold = min<long long>(amount, stock[id]);
            stock[id] -= sold;
            cash += sold * price[id];
        } else if (op == 3) {
            inf.readSpace();
            string name = inf.readToken("[A-Za-z]{1,30}", "A");
            inf.readSpace();
            int delta = inf.readInt(-5000, 5000, "C");
            inf.readEoln();
            ensuref(delta % 10 == 0, "price delta in command %d is not a multiple of 10: %d", commandIndex, delta);

            auto it = idByName.find(name);
            ensuref(it != idByName.end(), "unknown company in price command %d: %s", commandIndex, name.c_str());
            price[it->second] += delta;
        } else if (op == 4) {
            inf.readSpace();
            int targetGroup = inf.readInt(1, 100, "D");
            inf.readSpace();
            int delta = inf.readInt(-5000, 5000, "C");
            inf.readEoln();
            ensuref(delta % 10 == 0, "group price delta in command %d is not a multiple of 10: %d", commandIndex, delta);
            ensuref(!companiesInGroup[targetGroup].empty(), "group %d is empty in command %d", targetGroup, commandIndex);

            for (int id : companiesInGroup[targetGroup]) {
                price[id] += delta;
            }
        } else if (op == 5) {
            inf.readSpace();
            int targetGroup = inf.readInt(1, 100, "D");
            inf.readSpace();
            int percent = inf.readInt(-30, 30, "E");
            inf.readEoln();
            ensuref(!companiesInGroup[targetGroup].empty(), "group %d is empty in command %d", targetGroup, commandIndex);

            for (int id : companiesInGroup[targetGroup]) {
                price[id] = ((100 + percent) * price[id] / 100) / 10 * 10;
            }
        } else {
            inf.readEoln();
            hasOutputCommand = true;
        }

        checkGlobalState(commandIndex);
    }

    ensuref(hasOutputCommand, "there must be at least one menu 6 or menu 7 command");
    inf.readEof();
    return 0;
}
