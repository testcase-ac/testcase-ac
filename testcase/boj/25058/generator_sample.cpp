#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Request = pair<int, int>;

Request randomRequest(int max_sum) {
    int len = rnd.next(1, max_sum);
    int red = rnd.next(0, len);
    return {red, len - red};
}

vector<Request> feasibleRequests(int n, int m) {
    int red_limit = rnd.next(0, n);
    int white_limit = rnd.next(0, n - red_limit);
    if (red_limit + white_limit == 0) {
        if (rnd.next(0, 1) == 0) {
            red_limit = 1;
        } else {
            white_limit = 1;
        }
    }
    vector<Request> requests;

    requests.push_back({red_limit, white_limit});
    for (int i = 1; i < m; ++i) {
        int mode = rnd.next(0, 3);
        if (mode == 0 && red_limit > 0) {
            requests.push_back({rnd.next(1, red_limit), 0});
        } else if (mode == 1 && white_limit > 0) {
            requests.push_back({0, rnd.next(1, white_limit)});
        } else {
            int red = rnd.next(0, red_limit);
            int white = rnd.next(0, white_limit);
            if (red + white == 0) {
                if (red_limit > 0) {
                    red = 1;
                } else {
                    white = 1;
                }
            }
            requests.push_back({red, white});
        }
    }

    shuffle(requests.begin(), requests.end());
    return requests;
}

vector<Request> impossibleRequests(int n, int m) {
    vector<Request> requests;
    int red_limit = rnd.next(1, min(100, n));
    int white_limit = rnd.next(max(1, n - red_limit + 1), 100);

    requests.push_back({red_limit, 0});
    requests.push_back({0, white_limit});
    for (int i = 2; i < m; ++i) {
        requests.push_back(randomRequest(min(100, max(1, n + rnd.next(0, 5)))));
    }

    shuffle(requests.begin(), requests.end());
    return requests;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    println(t);

    for (int case_index = 0; case_index < t; ++case_index) {
        int mode = rnd.next(0, 5);
        int n;
        int m;
        vector<Request> requests;

        if (mode == 0) {
            n = rnd.next(1, 5);
            m = rnd.next(1, 8);
            requests = feasibleRequests(n, m);
        } else if (mode == 1) {
            n = rnd.next(2, 20);
            m = rnd.next(2, 12);
            requests = impossibleRequests(n, m);
        } else if (mode == 2) {
            n = rnd.next(1, 30);
            m = rnd.next(1, 15);
            requests = feasibleRequests(n, m);
            for (auto& request : requests) {
                int length = request.first + request.second;
                if (rnd.next(0, 1) == 0) {
                    request.first = 0;
                    request.second = length;
                } else {
                    request.second = 0;
                    request.first = length;
                }
            }
        } else if (mode == 3) {
            n = rnd.next(80, 100);
            m = rnd.next(80, 100);
            requests = feasibleRequests(n, m);
        } else if (mode == 4) {
            n = rnd.next(1, 100);
            m = rnd.next(1, 100);
            requests.reserve(m);
            for (int i = 0; i < m; ++i) {
                requests.push_back(randomRequest(100));
            }
        } else {
            n = 100;
            m = 100;
            requests = impossibleRequests(n, m);
        }

        println(n, m);
        for (const auto& [red, white] : requests) {
            println(red, white);
        }
    }

    return 0;
}
