#include <iostream>
#include <list>
#include <string>
using namespace std;

int main(void){
	string s;

	cin >> s;

	list<char> v_c(s.begin(), s.end());

	auto cursor = v_c.end();

	int n;
	cin >> n;

	char order, order_character;
	for(int i = 0; i < n; i++){
		cin >> order;
		if(order == 'L'){
			if(cursor != v_c.begin()){
				cursor--;
			}
		}
		else if(order == 'D'){
			if(cursor != v_c.end()){
				cursor++;
			}
		}
		else if(order == 'B'){
			if(cursor != v_c.begin()){
				auto temp = cursor;
				cursor--;
				v_c.erase(cursor);
				cursor = temp;
			}
		}
		else if(order == 'P'){
			cin >> order_character;
			v_c.insert(cursor, order_character);
		}
	}

	for(auto &x : v_c){
		cout << x;
	}

	return 0;
}
