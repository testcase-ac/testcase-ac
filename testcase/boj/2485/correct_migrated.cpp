#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int N;
    cin >> N;

    vector<int> trees(N);

    for (int i = 0; i < N; i++) {
        cin >> trees[i];
    }
    vector<int> diffs(N - 1);
    for (int i = 1; i < N; i++) {
        diffs[i - 1] = trees[i] - trees[i - 1];
    }
    int common_gcd = diffs[0];
    for (int i = 1; i < diffs.size(); i++) {
        common_gcd = gcd(common_gcd, diffs[i]);
    }
    int count = 0;
    for (int diff : diffs) {
        count += (diff / common_gcd) - 1;
    }

    cout << count;
}
