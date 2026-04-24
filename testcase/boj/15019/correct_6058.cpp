#include <bits/stdc++.h>
using namespace std;

bool done[1500000];

int main(){
	int people, length;
	cin>>people>>length;

	queue<int> qu;
	while(people--) {
		string str;
		cin>>str;
		int num = 0;
		for ( int j = 0 ; j < length ; ++j ) {
			num *= 2;
			if ( str[j] == '1' ) {
				++num;
			}
		}
		done[num] = true;
		qu.push(num);
	}

	int last;
	while(!qu.empty()) {
		int current = qu.front();
		qu.pop();
		last = current;

		int current_copy = current;
		int least = 1;
		for ( int i = 0 ; i < length ; ++i ) {
			int next;
			if ( current_copy % 2 == 0 ) {
				next = current + least;
			} else {
				next = current - least;
			}

			if ( !done[next] ) {
				done[next] = true;
				qu.push(next);
			}

			least *= 2;
			current_copy /= 2;
		}
	}

	stack<int> stk;
	for ( int i = 0 ; i < length ; ++i ) {
		stk.push(last % 2);
		last /= 2;
	}

	while(!stk.empty()) {
		cout<<stk.top();
		stk.pop();
	}
}
