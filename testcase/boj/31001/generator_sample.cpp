#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Company {
    int group;
    string name;
    long long price;
    long long stock = 0;
};

int roundToTen(int value) {
    return value / 10 * 10;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    long long initialCash = rnd.next(1000000, 10000000);
    long long cash = initialCash;
    int q = rnd.next(12, 70);

    int groupCount = rnd.next(1, min(5, n));
    vector<Company> initialCompanies;
    vector<Company> companies;
    vector<vector<int>> groups(101);

    for (int i = 0; i < n; ++i) {
        int group = rnd.next(1, groupCount);
        string name = string("C") + char('A' + i);
        long long price = rnd.next(0, 3000) * 10LL;
        initialCompanies.push_back({group, name, price, 0});
        companies.push_back({group, name, price, 0});
        groups[group].push_back(i);
    }

    vector<int> nonemptyGroups;
    for (int group = 1; group <= 100; ++group) {
        if (!groups[group].empty()) {
            nonemptyGroups.push_back(group);
        }
    }

    vector<string> commands;
    auto liquidationValue = [&]() {
        long long total = cash;
        for (const Company& company : companies) {
            total += company.stock * company.price;
        }
        return total;
    };

    auto addOutput = [&]() {
        int op = rnd.next(6, 7);
        commands.push_back(toString(op));
    };

    while (static_cast<int>(commands.size()) + 1 < q) {
        int mode = rnd.next(1, 100);

        if (mode <= 25) {
            int id = rnd.next(n);
            int amount = rnd.next(1, 100);
            commands.push_back("1 " + companies[id].name + " " + toString(amount));
            long long cost = companies[id].price * amount;
            if (cost <= cash) {
                cash -= cost;
                companies[id].stock += amount;
            }
        } else if (mode <= 40) {
            int id = rnd.next(n);
            int amount = rnd.next(1, 100);
            commands.push_back("2 " + companies[id].name + " " + toString(amount));
            long long sold = min<long long>(amount, companies[id].stock);
            companies[id].stock -= sold;
            cash += sold * companies[id].price;
        } else if (mode <= 58) {
            int id = rnd.next(n);
            int low = static_cast<int>(max<long long>(-5000, -companies[id].price));
            int high = 5000;
            low = roundToTen(low);
            high = roundToTen(high);
            int delta = rnd.next(low / 10, high / 10) * 10;
            commands.push_back("3 " + companies[id].name + " " + toString(delta));
            companies[id].price += delta;
        } else if (mode <= 73) {
            int group = rnd.any(nonemptyGroups);
            long long minPrice = companies[groups[group][0]].price;
            for (int id : groups[group]) {
                minPrice = min(minPrice, companies[id].price);
            }
            int low = static_cast<int>(max<long long>(-5000, -minPrice));
            int high = 5000;
            low = roundToTen(low);
            high = roundToTen(high);
            int delta = rnd.next(low / 10, high / 10) * 10;
            commands.push_back("4 " + toString(group) + " " + toString(delta));
            for (int id : groups[group]) {
                companies[id].price += delta;
            }
        } else if (mode <= 88) {
            int group = rnd.any(nonemptyGroups);
            int percent = rnd.next(-30, 30);
            commands.push_back("5 " + toString(group) + " " + toString(percent));
            for (int id : groups[group]) {
                companies[id].price = ((100 + percent) * companies[id].price / 100) / 10 * 10;
            }
        } else {
            addOutput();
        }

        ensure(liquidationValue() <= 2000000000000LL);
    }

    while (static_cast<int>(commands.size()) < q) {
        addOutput();
    }

    println(n, initialCash, q);
    for (const Company& company : initialCompanies) {
        println(company.group, company.name, company.price);
    }
    for (const string& command : commands) {
        println(command);
    }

    return 0;
}
