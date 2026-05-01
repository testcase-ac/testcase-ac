#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Menu sizes (small, but all >= 1 as per problem constraints)
    int A = rnd.next(1, 7);
    int B = rnd.next(1, 5);
    int C = rnd.next(1, 3);

    vector<string> regName(A), specName(B), servName(C);
    vector<int> priceR(A), priceS(B);

    // Generate names (lowercase letters only, unique via prefix)
    for (int i = 0; i < A; ++i) {
        string s;
        s.push_back('r');
        s.push_back(char('a' + i));
        regName[i] = s;
    }
    for (int i = 0; i < B; ++i) {
        string s;
        s.push_back('s');
        s.push_back(char('a' + i));
        specName[i] = s;
    }
    for (int i = 0; i < C; ++i) {
        string s;
        s.push_back('v');
        s.push_back(char('a' + i));
        servName[i] = s;
    }

    // Generate prices
    for (int i = 0; i < A; ++i)
        priceR[i] = rnd.next(3, 20) * 1000; // 3000 ~ 20000
    for (int i = 0; i < B; ++i)
        priceS[i] = rnd.next(5, 30) * 1000; // 5000 ~ 30000

    // Override some for deterministic sums
    priceR[0] = 10000;
    if (A >= 2) priceR[1] = 10000;
    if (A >= 3) priceR[2] = 5000;
    if (A >= 4) priceR[3] = 7000;

    priceS[0] = 15000;
    if (B >= 2) priceS[1] = 20000;

    vector<string> order;

    auto addReg = [&](int idx, int cnt) {
        for (int k = 0; k < cnt; ++k) order.push_back(regName[idx]);
    };
    auto addSpec = [&](int idx, int cnt) {
        for (int k = 0; k < cnt; ++k) order.push_back(specName[idx]);
    };
    auto addServ = [&](int idx, int cnt) {
        for (int k = 0; k < cnt; ++k) order.push_back(servName[idx]);
    };

    int scenario = rnd.next(0, 6);

    switch (scenario) {
        case 0: {
            // Only regular menus, no special or service (always valid)
            int distinct = rnd.next(1, min(A, 4));
            vector<int> idxs;
            for (int i = 0; i < A; ++i) idxs.push_back(i);
            shuffle(idxs.begin(), idxs.end());
            for (int i = 0; i < distinct; ++i) {
                int cnt = rnd.next(1, 3);
                addReg(idxs[i], cnt);
            }
            break;
        }
        case 1: {
            // Invalid: special ordered but regular sum < 20000
            int useRegular = rnd.next(0, 1);
            if (useRegular) {
                addReg(0, 1); // 10000
                if (A >= 3 && rnd.next(0, 1) == 1) {
                    // 10000 + 5000 = 15000 < 20000
                    addReg(2, 1);
                }
            }
            // At least one special
            addSpec(0, 1);
            if (rnd.next(0, 3) == 0) addSpec(0, 1);
            break;
        }
        case 2: {
            // Valid: special ordered, regular sum >= 20000, no service
            int pattern = rnd.next(0, 1);
            if (pattern == 0) {
                addReg(0, 2); // 20000
            } else {
                int cnt = rnd.next(3, 5); // >= 3 * 10000
                addReg(0, cnt);
            }
            int which = rnd.next(0, B - 1);
            int cntS = rnd.next(1, 2);
            addSpec(which, cntS);
            break;
        }
        case 3: {
            // Invalid: service ordered but (regular + special) sum < 50000
            // 2*10000 + 15000 = 35000
            addReg(0, 2);
            addSpec(0, 1);
            addServ(0, 1);
            break;
        }
        case 4: {
            // Invalid: (regular + special) >= 50000 but more than one service
            // 2*10000 + 2*15000 = 50000
            addReg(0, 2);
            addSpec(0, 2);
            addServ(0, 2); // two services
            break;
        }
        case 5: {
            // Valid: (regular + special) >= 50000 and exactly one service
            // 2*10000 + 2*15000 = 50000
            addReg(0, 2);
            addSpec(0, 2);
            addServ(0, 1);
            break;
        }
        case 6: {
            // Valid: service ordered, no specials, regular sum >= 50000
            // 5 * 10000 = 50000
            addReg(0, 5);
            addServ(0, 1);
            break;
        }
    }

    // Ensure at least one order (should always hold, but be safe)
    if (order.empty()) {
        addReg(0, 1);
    }

    shuffle(order.begin(), order.end());

    // Output
    println(A, B, C);
    for (int i = 0; i < A; ++i)
        println(regName[i], priceR[i]);
    for (int i = 0; i < B; ++i)
        println(specName[i], priceS[i]);
    for (int i = 0; i < C; ++i)
        println(servName[i]);

    int N = (int)order.size();
    println(N);
    for (string &s : order)
        println(s);

    return 0;
}
