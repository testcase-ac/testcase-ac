#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 34);
    vector<string> words = {
        "baekjoon", "algorithm", "contest", "programming", "greedy", 
        "graph", "tree", "queue", "stack", "online", 
        "binary", "dfs", "bfs", "dp", "judge", 
        "knapsack", "radar", "civic", "madam", "refer", 
        "noon", "deified", "reviver", "racecar", "rotator", 
        "stats", "tenet", "level", "eve", "kayak", 
        "redder", "malayalam", "solos", "pop", "m"
    };
    cout<<words[dis(gen)];
}
