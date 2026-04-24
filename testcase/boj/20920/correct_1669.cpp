#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    
    unordered_map<string, int> freq;
    for(int i = 0; i < N; i++){
        string word;
        cin >> word;
        if(word.size() >= M)
            freq[word]++;
    }
    
    vector<pair<string, int>> words;
    for(auto &p : freq) {
        words.push_back({p.first, p.second});
    }
    
    sort(words.begin(), words.end(), [](const pair<string,int>& a, const pair<string,int>& b){
        if(a.second != b.second)
            return a.second > b.second;
        if(a.first.size() != b.first.size())
            return a.first.size() > b.first.size();
        return a.first < b.first;
    });
    
    for(auto &p : words){
        cout << p.first << "\n";
    }
    
    return 0;
}
