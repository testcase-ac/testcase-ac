#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(3, 6); // N between 3 and 6 inclusive
    int M = rnd.next(10, 50); // M between 10 and 50 inclusive
    
    vector<int> numbers;
    
    // Generate three numbers a, b, c such that their sum <= M
    int maxValue = M / 3;
    if (maxValue == 0) maxValue = 1;
    int a = rnd.next(1, maxValue);
    int b = rnd.next(1, maxValue);
    int c = rnd.next(1, maxValue);
    while (a + b + c > M) {
        a = rnd.next(1, maxValue);
        b = rnd.next(1, maxValue);
        c = rnd.next(1, maxValue);
    }
    numbers.push_back(a);
    numbers.push_back(b);
    numbers.push_back(c);
    
    set<int> used;
    used.insert(a);
    used.insert(b);
    used.insert(c);
    
    // Generate N - 3 more distinct positive integers less than 100
    while ((int)numbers.size() < N) {
        int num = rnd.next(1, 99); // less than 100
        if (used.count(num) == 0) {
            numbers.push_back(num);
            used.insert(num);
        }
    }
    
    // Shuffle the numbers
    shuffle(numbers.begin(), numbers.end());
    
    // Output N and M
    println(N, M);
    
    // Output the numbers
    for (int i = 0; i < N; i++) {
        cout << numbers[i];
        if (i != N - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}
