#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string ticket(int value) {
    ostringstream out;
    out << setw(6) << setfill('0') << value;
    return out.str();
}

void addTicket(set<int>& used, vector<string>& tickets, int value) {
    if (used.insert(value).second) {
        tickets.push_back(ticket(value));
    }
}

int withSuffix(int suffix, int modulo) {
    int prefixLimit = 1000000 / modulo;
    return rnd.next(0, prefixLimit - 1) * modulo + suffix;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> used;
    vector<string> tickets;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        while ((int)tickets.size() < n) {
            addTicket(used, tickets, rnd.next(0, 999999));
        }
    } else if (mode == 1) {
        int suffix = rnd.next(0, 99);
        int n = rnd.next(6, 18);
        while ((int)tickets.size() < n) {
            addTicket(used, tickets, withSuffix(suffix, 100));
        }
    } else if (mode == 2) {
        int suffix4 = rnd.next(0, 9999);
        int n = rnd.next(5, 15);
        while ((int)tickets.size() < n) {
            addTicket(used, tickets, withSuffix(suffix4, 10000));
        }
    } else if (mode == 3) {
        vector<int> suffixes;
        while ((int)suffixes.size() < 6) {
            int suffix = rnd.next(0, 99);
            if (find(suffixes.begin(), suffixes.end(), suffix) == suffixes.end()) {
                suffixes.push_back(suffix);
            }
        }

        for (int suffix : suffixes) {
            int count = rnd.next(1, 5);
            for (int i = 0; i < count; ++i) {
                addTicket(used, tickets, withSuffix(suffix, 100));
            }
        }
    } else {
        int n = rnd.next(20, 60);
        for (int value = 0; value <= 999999 && (int)tickets.size() < n; ++value) {
            if (rnd.next(0, 3) == 0) {
                addTicket(used, tickets, value);
            }
        }
        while ((int)tickets.size() < n) {
            addTicket(used, tickets, rnd.next(0, 999999));
        }
    }

    shuffle(tickets.begin(), tickets.end());

    println((int)tickets.size());
    for (const string& s : tickets) {
        println(s);
    }

    return 0;
}
