#include "testlib.h"

#include <cctype>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int n, k;
map<long long, int> available;

string trimSpaces(const string& s) {
    size_t first = 0;
    while (first < s.size() && isspace(static_cast<unsigned char>(s[first]))) {
        ++first;
    }
    size_t last = s.size();
    while (last > first && isspace(static_cast<unsigned char>(s[last - 1]))) {
        --last;
    }
    return s.substr(first, last - first);
}

long long parseInteger(const string& text, InStream& stream, int lineNo, const char* field) {
    string value = trimSpaces(text);
    if (value.empty()) {
        stream.quitf(_wa, "line %d has empty %s", lineNo, field);
    }
    size_t pos = 0;
    if (value[pos] == '+') {
        ++pos;
    }
    if (pos == value.size()) {
        stream.quitf(_wa, "line %d has malformed %s", lineNo, field);
    }
    for (; pos < value.size(); ++pos) {
        if (!isdigit(static_cast<unsigned char>(value[pos]))) {
            stream.quitf(_wa, "line %d has malformed %s: %s", lineNo, field, value.c_str());
        }
    }

    long long result = 0;
    try {
        result = stoll(value);
    } catch (...) {
        stream.quitf(_wa, "line %d has out-of-range %s: %s", lineNo, field, value.c_str());
    }
    return result;
}

vector<long long> readClaim(InStream& stream) {
    vector<long long> totals;
    totals.reserve(k);

    for (int lineNo = 1; lineNo <= k; ++lineNo) {
        string line = stream.readLine();
        size_t colon = line.find(':');
        if (colon == string::npos) {
            stream.quitf(_wa, "line %d is missing ':'", lineNo);
        }
        if (line.find(':', colon + 1) != string::npos) {
            stream.quitf(_wa, "line %d has multiple ':' characters", lineNo);
        }

        long long total = parseInteger(line.substr(0, colon), stream, lineNo, "total weight");
        if (lineNo > 1 && total <= totals.back()) {
            stream.quitf(_wa,
                         "line %d total is not strictly increasing: previous=%lld current=%lld",
                         lineNo,
                         totals.back(),
                         total);
        }

        map<long long, int> used;
        long long sum = 0;
        string rest = line.substr(colon + 1);
        stringstream ss(rest);
        string token;
        int itemNo = 0;
        while (ss >> token) {
            ++itemNo;
            long long weight = parseInteger(token, stream, lineNo, "listed weight");
            auto it = available.find(weight);
            if (it == available.end()) {
                stream.quitf(_wa, "line %d item %d uses unavailable weight %lld", lineNo, itemNo, weight);
            }
            ++used[weight];
            if (used[weight] > it->second) {
                stream.quitf(_wa,
                             "line %d item %d uses weight %lld more times than available",
                             lineNo,
                             itemNo,
                             weight);
            }
            sum += weight;
        }

        if (sum != total) {
            stream.quitf(_wa,
                         "line %d subset sum mismatch: total=%lld subset_sum=%lld",
                         lineNo,
                         total,
                         sum);
        }
        totals.push_back(total);
    }

    stream.readEof();
    return totals;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    for (int i = 0; i < n; ++i) {
        long long weight = inf.readLong();
        ++available[weight];
    }

    vector<long long> jury = readClaim(ans);
    vector<long long> participant = readClaim(ouf);

    for (int i = 0; i < k; ++i) {
        if (participant[i] != jury[i]) {
            quitf(_wa,
                  "line %d total differs from jury baseline: expected=%lld found=%lld",
                  i + 1,
                  jury[i],
                  participant[i]);
        }
    }

    quitf(_ok, "all %d subset sums match the jury baseline", k);
}
