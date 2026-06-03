#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeName(const string& prefix, int index) {
    string value = prefix + to_string(index);
    if (value.size() > 10) {
        value.resize(10);
    }
    return value;
}

vector<string> pickFeatures(const vector<string>& pool, int count) {
    vector<string> shuffled = pool;
    shuffle(shuffled.begin(), shuffled.end());
    shuffled.resize(count);
    return shuffled;
}

string joinFeatures(const vector<string>& features) {
    string result = features[0];
    for (int i = 1; i < static_cast<int>(features.size()); ++i) {
        result += ",";
        result += features[i];
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 3 : 12);

    vector<string> stationPrefixes = {"S", "st", "Ga", "N", "z"};
    vector<string> stations;
    string stationPrefix = rnd.any(stationPrefixes);
    for (int i = 0; i < n; ++i) {
        stations.push_back(makeName(stationPrefix, i));
    }
    shuffle(stations.begin(), stations.end());

    vector<string> updatePool = {"a", "b2", "Deep", "Line7", "x9", "Kami", "red", "slow", "Z"};
    vector<string> queryOnlyPool = {"ghost", "Q", "near", "tokyo", "none", "Extra"};

    int updateKinds = mode == 5 ? 0 : rnd.next(1, 9);
    vector<string> activeFeatures(updatePool.begin(), updatePool.begin() + updateKinds);

    struct Request {
        char type;
        string station;
        vector<string> features;
    };

    vector<Request> requests;
    int r = rnd.next(1, mode == 5 ? 8 : 24);
    int getCount = 0;

    for (int i = 0; i < r; ++i) {
        bool makeGet = mode == 5 || i == r - 1 || rnd.next(0, 99) < (mode == 0 ? 70 : 35);
        if (makeGet) {
            vector<string> pool = activeFeatures;
            if (mode == 1 || rnd.next(0, 99) < 35) {
                pool.insert(pool.end(), queryOnlyPool.begin(), queryOnlyPool.end());
            }
            if (pool.empty()) {
                pool = queryOnlyPool;
            }
            int maxCount = min<int>(pool.size(), mode == 2 ? 5 : 3);
            requests.push_back({'G', "", pickFeatures(pool, rnd.next(1, maxCount))});
            ++getCount;
        } else {
            int maxCount = min<int>(activeFeatures.size(), mode == 3 ? 9 : 4);
            requests.push_back({'U', rnd.any(stations), pickFeatures(activeFeatures, rnd.next(1, maxCount))});
        }
    }

    if (getCount == 0) {
        requests.back() = {'G', "", pickFeatures(activeFeatures, 1)};
    }

    println(n);
    for (const string& station : stations) {
        println(station);
    }

    println(static_cast<int>(requests.size()));
    for (const Request& request : requests) {
        if (request.type == 'U') {
            println("U", request.station, joinFeatures(request.features));
        } else {
            println("G", joinFeatures(request.features));
        }
    }

    return 0;
}
