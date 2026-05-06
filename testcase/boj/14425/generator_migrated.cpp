#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <chrono>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    vector<string> sample = {
        "baekjoononlinejudge", "startlink", "codeplus", "sundaycoding", "codingsh", 
        "baekjoon", "codeplus", "codeminus", "startlink", "starlink", "sundaycoding", 
        "codingsh", "codinghs", "sondaycoding", "startrink", "icerink", "programming", 
        "algorithm", "datastructures", "contest", "debugging", "compiler", "binarytree"
    };
    
    auto now = chrono::high_resolution_clock::now();
    unsigned seed = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    srand(seed);
    
    int N = rand() % 10 + 1;
    int M = rand() % 10 + 1;
    
    cout << N << " " << M << endl;
    
    unordered_set<string> setN;
    unordered_set<string> setM;
    
    for (int i = 0; i < N; ++i) {
        while (true) {
            int idx = rand() % sample.size();
            if (setN.find(sample[idx]) == setN.end()) {
                setN.insert(sample[idx]);
                cout << sample[idx] << endl;
                break;
            }
        }
    }
    
    for (int i = 0; i < M; ++i) {
        while (true) {
            int idx = rand() % sample.size();
            if (setM.find(sample[idx]) == setM.end()) {
                setM.insert(sample[idx]);
                cout << sample[idx] << endl;
                break;
            }
        }
    }
    
    return 0;
}
