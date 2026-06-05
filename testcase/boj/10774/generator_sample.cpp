#include "testlib.h"

#include <string>
#include <utility>
#include <vector>
using namespace std;

const vector<string> sizes = {"S", "M", "L"};

string sizeAtLeast(const string& jerseySize) {
    int lo = 0;
    if (jerseySize == "M") lo = 1;
    if (jerseySize == "L") lo = 2;
    return sizes[rnd.next(lo, 2)];
}

string sizeTooLargeFor(const string& jerseySize) {
    if (jerseySize == "S") return sizes[rnd.next(1, 2)];
    return "L";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int jerseyCount = rnd.next(1, 24);
    int athleteCount = rnd.next(1, 35);

    if (mode == 0) {
        jerseyCount = rnd.next(1, 10);
        athleteCount = jerseyCount;
    } else if (mode == 1) {
        jerseyCount = rnd.next(2, 18);
        athleteCount = rnd.next(jerseyCount, 35);
    } else if (mode == 2) {
        jerseyCount = rnd.next(1, 8);
        athleteCount = rnd.next(8, 35);
    } else if (mode == 3) {
        jerseyCount = rnd.next(10, 40);
        athleteCount = rnd.next(1, jerseyCount);
    }

    vector<string> jerseys(jerseyCount + 1);
    for (int j = 1; j <= jerseyCount; ++j) {
        if (mode == 4) {
            jerseys[j] = sizes[rnd.wnext(3, j % 3) % 3];
        } else {
            jerseys[j] = sizes[rnd.next(0, 2)];
        }
    }

    vector<pair<string, int>> requests;
    if (mode == 0) {
        for (int j = 1; j <= jerseyCount; ++j) {
            requests.push_back({sizeAtLeast(jerseys[j]), j});
        }
    } else if (mode == 1) {
        for (int a = 0; a < athleteCount; ++a) {
            int jersey = rnd.next(1, jerseyCount);
            requests.push_back({sizeTooLargeFor(jerseys[jersey]), jersey});
        }
    } else if (mode == 2) {
        int contested = rnd.next(1, jerseyCount);
        for (int a = 0; a < athleteCount; ++a) {
            string requested = sizes[rnd.next(0, 2)];
            int jersey = rnd.next(0, 3) == 0 ? rnd.next(1, jerseyCount) : contested;
            requests.push_back({requested, jersey});
        }
    } else if (mode == 3) {
        vector<int> order;
        for (int j = 1; j <= jerseyCount; ++j) order.push_back(j);
        shuffle(order.begin(), order.end());
        for (int a = 0; a < athleteCount; ++a) {
            int jersey = order[a];
            string requested = rnd.next(0, 1) == 0 ? sizeAtLeast(jerseys[jersey]) : sizes[rnd.next(0, 2)];
            requests.push_back({requested, jersey});
        }
    } else {
        for (int a = 0; a < athleteCount; ++a) {
            int jersey = rnd.next(1, jerseyCount);
            string requested = sizes[rnd.next(0, 2)];
            requests.push_back({requested, jersey});
        }
    }

    shuffle(requests.begin(), requests.end());

    println(jerseyCount);
    println((int)requests.size());
    for (int j = 1; j <= jerseyCount; ++j) {
        println(jerseys[j]);
    }
    for (const auto& request : requests) {
        println(request.first, request.second);
    }

    return 0;
}
