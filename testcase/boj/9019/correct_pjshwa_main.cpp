#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <string>
using namespace std;

const int MAX_INT = 2147483647;

int d_function(int subject){
	return (subject * 2) % 10000;
}

int s_function(int subject){
	subject -= 1;
	if(subject < 0) subject += 10000;
	return subject;
}

int l_function(int subject){
	int first_digit = subject / 1000;
	return (subject % 1000) * 10 + first_digit;
}

int r_function(int subject){
	int last_digit = subject % 10;
	return (subject / 10) + 1000 * last_digit;
}

int main(){
	int t;
	scanf("%d", &t);
	for(int i = 0; i < t; i++){
		int a, b;
		pair<string, int> p[10000];
		for(auto &x : p){
			x = make_pair("", MAX_INT);
		}
		scanf("%d%d", &a, &b);
		p[a].second = 0;
		queue<int> q;
		q.push(a);
		while(!q.empty()){
			int fr = q.front();
			int steps = p[fr].second;
			string prev_letters = p[fr].first;
			if(fr == b){
				// for(int j = 0; j < 10000; j++){
				// 	if(p[j].second != MAX_INT){
				// 		cout << "j: " << j <<"," <<p[j].first << '\n';
				// 	}
				// }
				cout << p[fr].first << '\n';
				break;
			}
			q.pop();
			int d = d_function(fr); int s = s_function(fr); int l = l_function(fr); int r = r_function(fr);
			if(p[d].second > steps + 1){
				p[d].first = p[fr].first + "D";
				p[d].second = steps + 1;
				q.push(d);
			}
			if(p[s].second > steps + 1){
				p[s].first = p[fr].first + "S";
				p[s].second = steps + 1;
				q.push(s);
			}
			if(p[l].second > steps + 1){
				p[l].first = p[fr].first + "L";
				p[l].second = steps + 1;
				q.push(l);
			}
			if(p[r].second > steps + 1){
				p[r].first = p[fr].first + "R";
				p[r].second = steps + 1;
				q.push(r);
			}
		}
	}
}