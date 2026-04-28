#include <cstdio>
#include <vector>
using namespace std;

int main(){
	int y, x;
	scanf("%d%d", &y, &x);

	int field[x*y];
	for(int i = 0; i < x*y; i++){
		scanf("%1d", &field[i]);
	}

	vector<int> vector_array[10];
	int line = 0;
	int max_square = 1;
	while(line < y){
		int index = 0;
		while(index < x){
			vector_array[field[x*line+index]].push_back(index);
			index++;
		}
		for(int number = 0; number < 10; number++){
			int size = vector_array[number].size();
			if(size > 1){
				for(int i = 0; i < size - 1; i++){
					for(int j = i+1; j < size; j++){
						int index_1 = vector_array[number][i];
						int index_2 = vector_array[number][j];
						int diff = index_2 - index_1; 
						if(line + diff < y && field[(line+diff)*x+index_1] == number && field[(line+diff)*x+index_2] == number){
							// is a square
							// printf("number: %d, line: %d, index_1: %d, index_2: %d, square: %d\n", number, line, index_1, index_2, (diff+1)*(diff+1));
							if(max_square < (diff+1)*(diff+1)) max_square = (diff+1)*(diff+1);
						}
					}
				}
			}
		}
		for(int number = 0; number < 10; number++){
			vector_array[number].clear();
		}
		line++;
	}
	printf("%d\n", max_square);
}