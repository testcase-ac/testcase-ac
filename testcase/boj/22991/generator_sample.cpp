#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    int maxValue = rnd.next(0, 8) == 0 ? 1000000000 : rnd.next(3, 60);

    vector<pair<int, int>> requests;
    vector<pair<int, int>> buses;

    if (mode == 0) {
        int k = min(n, m);
        for (int i = 0; i < k; ++i) {
            int people = rnd.next(1, maxValue);
            int wait = rnd.next(1, maxValue);
            requests.push_back({people, wait});
            buses.push_back({rnd.next(people, maxValue), rnd.next(1, wait)});
        }
        while ((int)requests.size() < n) {
            requests.push_back({rnd.next(1, maxValue), rnd.next(1, maxValue)});
        }
        while ((int)buses.size() < m) {
            buses.push_back({rnd.next(1, maxValue), rnd.next(1, maxValue)});
        }
    } else if (mode == 1) {
        int busCapLimit = rnd.next(1, maxValue);
        int requestPeopleStart = min(maxValue, busCapLimit + rnd.next(0, maxValue - busCapLimit));
        for (int i = 0; i < n; ++i) {
            requests.push_back({rnd.next(requestPeopleStart, maxValue), rnd.next(1, maxValue)});
        }
        for (int j = 0; j < m; ++j) {
            buses.push_back({rnd.next(1, busCapLimit), rnd.next(1, maxValue)});
        }
    } else if (mode == 2) {
        int busTimeStart = rnd.next(1, maxValue);
        int requestWaitLimit = rnd.next(1, busTimeStart);
        for (int i = 0; i < n; ++i) {
            requests.push_back({rnd.next(1, maxValue), rnd.next(1, requestWaitLimit)});
        }
        for (int j = 0; j < m; ++j) {
            buses.push_back({rnd.next(1, maxValue), rnd.next(busTimeStart, maxValue)});
        }
    } else if (mode == 3) {
        int people = rnd.next(1, maxValue);
        int time = rnd.next(1, maxValue);
        for (int i = 0; i < n; ++i) {
            int deltaPeople = rnd.next(0, min(3, maxValue - people));
            int deltaTime = rnd.next(0, min(3, maxValue - time));
            requests.push_back({people + deltaPeople, time + deltaTime});
        }
        for (int j = 0; j < m; ++j) {
            int cap = max(1, people + rnd.next(-min(3, people - 1), min(3, maxValue - people)));
            int arrive = max(1, time + rnd.next(-min(3, time - 1), min(3, maxValue - time)));
            buses.push_back({cap, arrive});
        }
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
        for (int i = 0; i < n; ++i) {
            requests.push_back({rnd.next(1, 25), rnd.next(1, 25)});
        }
        for (int j = 0; j < m; ++j) {
            buses.push_back({rnd.next(1, 25), rnd.next(1, 25)});
        }
    } else {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
        vector<int> values = {1, 2, max(1, maxValue - 1), maxValue};
        for (int i = 0; i < n; ++i) {
            requests.push_back({rnd.any(values), rnd.any(values)});
        }
        for (int j = 0; j < m; ++j) {
            buses.push_back({rnd.any(values), rnd.any(values)});
        }
    }

    shuffle(requests.begin(), requests.end());
    shuffle(buses.begin(), buses.end());

    println(n, m);
    for (auto [people, wait] : requests) {
        println(people, wait);
    }
    for (auto [capacity, arrival] : buses) {
        println(capacity, arrival);
    }

    return 0;
}
