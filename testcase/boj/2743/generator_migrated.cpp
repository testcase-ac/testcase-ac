#include <iostream>
#include <vector>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> str_dis(0, 41);
    vector<string> words = {
        "baekjoon", "codeforces", "algorithm", "data", "structure", "programming", "contest", "problem", 
        "solution", "input", "output", "testcase", "example", "judge", "submission", "compile", "debug", 
        "runtime", "time", "space", "complexity", "optimization", "greedy", "dynamic", "programming", 
        "divide", "conquer", "graph", "tree", "search", "sort", "bfs", "dfs", "dp", "bitmask", "segment", 
        "union", "find", "heap", "priority", "queue", "stack", "deque", "map", "set", "hash", "bit", "shiftpsh", "sprout", "pulljima"};
    string selected_word = words[str_dis(gen)];
    uniform_int_distribution<> num_dis(1, selected_word.size()); 
    cout << selected_word << endl;
    return 0;
}
