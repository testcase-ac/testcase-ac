#include <stdio.h>

int main(void){

	int dwarfHeights[9];
	int sum = 0;
	for(int i = 0; i < 9; i++){
		scanf("%d", &dwarfHeights[i]);
		sum += dwarfHeights[i];
	}
	int temp;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 8 - i; j++){
			if(dwarfHeights[j] > dwarfHeights[j+1]){
				temp = dwarfHeights[j];
				dwarfHeights[j] = dwarfHeights[j+1];
				dwarfHeights[j+1] = temp;
			}
		}
	}
	int dwarfLimit = sum - 100;
	int indexes[2];
	int exit = 0;
	for(int i = 0; i < 9; i++){
		for(int j = i + 1; j < 9; j++){
			if(dwarfHeights[i] + dwarfHeights[j] == dwarfLimit){
				indexes[0] = i;
				indexes[1] = j;
				exit = 1;
				break;
			}
		}
		if(exit) break;
	}

	for(int i = 0; i < 9; i++){
		if(i != indexes[0] && i != indexes[1]) printf("%d\n", dwarfHeights[i]);
	}

	return 0;
}
