#include<iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

int n, m;
map<string, string> words;
string str;

string str_to_hash(string str){
    string h = "";
    h += str[0]; h += str[str.length()-1];
    sort(str.begin(), str.end());
    h += str;
    return h;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	while(n--){
		cin >> str;
		words[str_to_hash(str)] = str;
	}
    cin >> m;
    while(m--){
        cin >> str;
		cout << words[str_to_hash(str)] << ' ';
    }
}
