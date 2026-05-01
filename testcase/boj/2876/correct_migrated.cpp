#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<pair<int, int>> desks(N);
    for (int i = 0; i < N; i++) {
        cin >> desks[i].first >> desks[i].second;
    }

    int maxCount = 0, bestGrade = 0;
    for (int g = 1; g <= 5; g++) {
        int count = 0, tempCount = 0;
        for (int i = 0; i < N; i++) {
            if (desks[i].first == g || desks[i].second == g) {
                count++;
            } else {
                tempCount = max(tempCount, count);
                count = 0;
            }
        }
        tempCount = max(tempCount, count);
        if (tempCount > maxCount) {
            maxCount = tempCount;
            bestGrade = g;
        }
    }

    cout << maxCount << " " << bestGrade << endl;
    return 0;
}
