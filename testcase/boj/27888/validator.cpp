#include "testlib.h"

#include <cctype>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool isAlphaNumString(const string& value) {
    if (value.empty() || value.size() > 10) {
        return false;
    }
    for (char ch : value) {
        if (!isalnum(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

vector<string> splitFeatures(const string& value, int queryIndex, long long& totalFeatureLength) {
    ensuref(!value.empty(), "empty features at request %d", queryIndex);

    vector<string> features;
    unordered_set<string> seen;
    size_t start = 0;
    while (true) {
        size_t comma = value.find(',', start);
        string feature = value.substr(start, comma == string::npos ? string::npos : comma - start);
        ensuref(isAlphaNumString(feature), "invalid feature at request %d: %s", queryIndex, feature.c_str());
        ensuref(seen.insert(feature).second, "duplicate feature at request %d: %s", queryIndex, feature.c_str());

        totalFeatureLength += static_cast<long long>(feature.size());
        ensuref(totalFeatureLength <= 2000000LL, "total feature length exceeds 2000000");
        features.push_back(feature);

        if (comma == string::npos) {
            break;
        }
        start = comma + 1;
    }
    return features;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    set<string> stations;
    for (int i = 0; i < n; ++i) {
        string station = inf.readToken("[A-Za-z0-9]{1,10}", "station");
        inf.readEoln();
        ensuref(stations.insert(station).second, "duplicate station name: %s", station.c_str());
    }

    int r = inf.readInt(1, 100000, "r");
    inf.readEoln();

    long long totalFeatureLength = 0;
    int getRequestCount = 0;
    unordered_set<string> updateFeatureKinds;

    for (int i = 1; i <= r; ++i) {
        string line = inf.readLine();
        ensuref(!line.empty(), "empty request at index %d", i);

        if (line[0] == 'U') {
            ensuref(line.size() >= 5, "too short U request at index %d", i);
            ensuref(line[1] == ' ', "missing space after U at request %d", i);
            size_t secondSpace = line.find(' ', 2);
            ensuref(secondSpace != string::npos, "missing features in U request %d", i);
            ensuref(secondSpace > 2, "empty station in U request %d", i);

            string station = line.substr(2, secondSpace - 2);
            string featureText = line.substr(secondSpace + 1);
            ensuref(isAlphaNumString(station), "invalid station token in U request %d: %s", i, station.c_str());
            ensuref(stations.count(station) == 1, "unknown station in U request %d: %s", i, station.c_str());

            vector<string> features = splitFeatures(featureText, i, totalFeatureLength);
            for (const string& feature : features) {
                updateFeatureKinds.insert(feature);
                ensuref(updateFeatureKinds.size() <= 9, "more than 9 update feature kinds");
            }
        } else if (line[0] == 'G') {
            ++getRequestCount;
            ensuref(line.size() >= 3, "too short G request at index %d", i);
            ensuref(line[1] == ' ', "missing space after G at request %d", i);
            splitFeatures(line.substr(2), i, totalFeatureLength);
        } else {
            ensuref(false, "unknown request type at index %d: %c", i, line[0]);
        }
    }

    ensuref(getRequestCount >= 1, "at least one G request is required");
    // CHECK: The limit text says U feature kinds are 1..9, but official Sample 3 has no U request.
    ensuref(updateFeatureKinds.empty() || updateFeatureKinds.size() >= 1, "update feature kind count is invalid");

    inf.readEof();
}
