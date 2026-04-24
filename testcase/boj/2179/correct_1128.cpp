#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    cin.ignore(); // To ignore the newline after reading n

    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        getline(cin, words[i]);
    }

    int lastOverlap = 0;
    for (int l = 1; l <= 100; ++l) {
        set<string> prefixSet;
        bool overlapped = false;
        for (const string& w : words) {
            if (w.length() < l) continue;
            string prefix = w.substr(0, l);
            if (prefixSet.find(prefix) != prefixSet.end()) {
                overlapped = true;
                lastOverlap = l;
                break;
            }
            prefixSet.insert(prefix);
        }
        if (!overlapped) {
            break;
        }
    }

    map<string, vector<int>> prefixMap;
    for (int i = 0; i < n; ++i) {
        const string& w = words[i];
        if (w.length() < lastOverlap) continue;
        string prefix = w.substr(0, lastOverlap);
        prefixMap[prefix].push_back(i);
    }

    vector<vector<int>> prefixListSorted;
    for (const auto& pair : prefixMap) {
        if (pair.second.size() >= 2) {
            prefixListSorted.push_back(pair.second);
        }
    }

    sort(prefixListSorted.begin(), prefixListSorted.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

    cout << words[prefixListSorted[0][0]] << endl;
    cout << words[prefixListSorted[0][1]] << endl;
}

int main() {
    solve();
    return 0;
}
