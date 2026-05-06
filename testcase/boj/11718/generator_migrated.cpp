#include <iostream>
#include <random>
#include <vector>
#include <string>
using namespace std;

vector<string> words = {
    "BaekJoon", "Algorithm", "Contest", "Dynamic Programming", "Greedy", "Graph", "Tree",
    "Queue", "Stack", "PriorityQueue", "BinarySearch", "DFS", "BFS", "Memoization", "Divide And Conquer",
    "MatheMatics", "BitMask", "Set", "Map", "Segment Tree", "HashMap", "Sliding Window", "PrefixSum", 
    "Binary Search Tree", "Union Find", "Topological Sort", "KnapSack", "LIS", "Sieve", "Two Pointer", 
    "BackTracking", "String Matching", "Game Theory", "String", "Simulation", "Recursion"
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> num_dis(1, 7);
    uniform_int_distribution<> word_dis(0, words.size() - 1);
    uniform_int_distribution<> num_to_append(1, 9);

    int num_words = num_dis(gen);
    vector<string> selected_words;

    for (int i = 0; i < num_words; ++i) {
        string selected_word = words[word_dis(gen)];
        selected_word += to_string(num_to_append(gen));
        selected_words.push_back(selected_word);
    }
    for (const auto& word : selected_words) {
        cout << word << endl;
    }
    return 0;
}
