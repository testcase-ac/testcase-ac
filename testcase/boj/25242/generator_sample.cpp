#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string stationName(int index) {
    string name;
    do {
        name.push_back(char('A' + index % 26));
        index /= 26;
    } while (index > 0);
    reverse(name.begin(), name.end());
    return name;
}

void addStation(vector<string>& line, const string& station) {
    if (find(line.begin(), line.end(), station) == line.end()) {
        line.push_back(station);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int nextName = 0;
    vector<vector<string>> lines;
    vector<string> transfers;

    auto fresh = [&]() {
        return stationName(nextName++);
    };

    auto makeLine = [&](int size) {
        vector<string> line;
        for (int i = 0; i < size; ++i) {
            line.push_back(fresh());
        }
        return line;
    };

    int n = rnd.next(1, 9);
    if (mode == 0) {
        n = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            lines.push_back(makeLine(rnd.next(2, 8)));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        string hub = fresh();
        transfers.push_back(hub);
        for (int i = 0; i < n; ++i) {
            vector<string> line = makeLine(rnd.next(2, 6));
            line.insert(line.begin() + rnd.next(0, (int)line.size()), hub);
            lines.push_back(line);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 8);
        for (int i = 0; i + 1 < n; ++i) {
            transfers.push_back(fresh());
        }
        for (int i = 0; i < n; ++i) {
            vector<string> line;
            if (i > 0) addStation(line, transfers[i - 1]);
            int privateLeft = rnd.next(1, 4);
            for (int j = 0; j < privateLeft; ++j) addStation(line, fresh());
            if (i + 1 < n) addStation(line, transfers[i]);
            int privateRight = rnd.next(0, 3);
            for (int j = 0; j < privateRight; ++j) addStation(line, fresh());
            lines.push_back(line);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 9);
        int transferCount = rnd.next(2, min(5, n));
        for (int i = 0; i < transferCount; ++i) {
            transfers.push_back(fresh());
        }
        for (int i = 0; i < n; ++i) {
            vector<string> line = makeLine(rnd.next(2, 5));
            int attach = rnd.next(1, min(3, transferCount));
            vector<int> order(transferCount);
            for (int j = 0; j < transferCount; ++j) order[j] = j;
            shuffle(order.begin(), order.end());
            for (int j = 0; j < attach; ++j) {
                line.insert(line.begin() + rnd.next(0, (int)line.size()), transfers[order[j]]);
            }
            lines.push_back(line);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            vector<string> line = makeLine(rnd.next(6, 14));
            if (i > 0) {
                string shared = lines.back()[rnd.next(0, (int)lines.back().size() - 1)];
                line[rnd.next(0, (int)line.size() - 1)] = shared;
                transfers.push_back(shared);
            }
            lines.push_back(line);
        }
    } else {
        n = rnd.next(6, 12);
        int components = rnd.next(2, 4);
        vector<string> hubs;
        for (int i = 0; i < components; ++i) {
            hubs.push_back(fresh());
            transfers.push_back(hubs.back());
        }
        for (int i = 0; i < n; ++i) {
            vector<string> line = makeLine(rnd.next(2, 6));
            string hub = hubs[i % components];
            line.insert(line.begin() + rnd.next(0, (int)line.size()), hub);
            lines.push_back(line);
        }
    }

    vector<string> allStations;
    set<string> seen;
    for (const auto& line : lines) {
        for (const string& station : line) {
            if (seen.insert(station).second) {
                allStations.push_back(station);
            }
        }
    }

    int q = rnd.next(1, 18);
    vector<pair<string, string>> queries;
    for (int i = 0; i < q; ++i) {
        string from;
        string to;
        if (i == 0 && !transfers.empty()) {
            from = rnd.any(transfers);
            to = rnd.any(allStations);
        } else if (i == 1 && rnd.next(0, 1) == 0) {
            from = rnd.any(allStations);
            to = from;
        } else {
            from = rnd.any(allStations);
            to = rnd.any(allStations);
        }
        queries.push_back({from, to});
    }

    println((int)lines.size(), (int)queries.size());
    for (const auto& line : lines) {
        printf("%d", (int)line.size());
        for (const string& station : line) {
            printf(" %s", station.c_str());
        }
        printf("\n");
    }
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
