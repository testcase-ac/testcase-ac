#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 18);
    long long g = (mode == 3) ? rnd.any(vector<long long>{1, 2, 999999999, 1000000000})
                              : rnd.next(1, 30);

    int cowCount = 1;
    if (mode == 1) cowCount = rnd.next(2, 5);
    if (mode == 2) cowCount = rnd.next(3, 8);
    if (mode == 3) cowCount = rnd.next(1, 4);

    vector<int> cows;
    for (int i = 0; i < cowCount; ++i) {
        if (rnd.next(0, 9) == 0) {
            cows.push_back(rnd.next(1, 1000000000));
        } else {
            cows.push_back(i + 1);
        }
    }
    sort(cows.begin(), cows.end());
    cows.erase(unique(cows.begin(), cows.end()), cows.end());
    cowCount = (int)cows.size();

    set<int> usedDays;
    vector<int> days;
    while ((int)days.size() < n) {
        int day = rnd.next(1, 1000000);
        if (usedDays.insert(day).second) days.push_back(day);
    }
    sort(days.begin(), days.end());

    map<int, long long> milk;
    for (int cow : cows) milk[cow] = g;

    vector<tuple<int, int, long long>> events;
    for (int i = 0; i < n; ++i) {
        int cow = rnd.any(cows);
        long long current = milk[cow];
        long long target = current;

        if (mode == 0) {
            cow = cows[0];
            current = milk[cow];
            long long low = max(0LL, g - 5);
            long long high = min(1000000000LL, g + 5);
            target = rnd.next((int)low, (int)high);
        } else if (mode == 1) {
            long long offset = rnd.any(vector<long long>{-2, -1, 0, 1, 2, 3});
            target = min(1000000000LL, max(0LL, g + offset));
        } else if (mode == 2) {
            int step = rnd.next(-7, 7);
            while (step == 0) step = rnd.next(-7, 7);
            target = min(1000000000LL, max(0LL, current + step));
        } else {
            target = rnd.any(vector<long long>{0, 1, g, 999999999, 1000000000});
        }

        if (target == current) {
            if (current < 1000000000LL) ++target;
            else --target;
        }

        long long change = target - current;
        events.emplace_back(days[i], cow, change);
        milk[cow] = target;
    }

    shuffle(events.begin(), events.end());

    println(n, g);
    for (auto [day, cow, change] : events) {
        printf("%d %d %+lld\n", day, cow, change);
    }

    return 0;
}
