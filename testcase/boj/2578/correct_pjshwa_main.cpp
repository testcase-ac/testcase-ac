#include <cstdio>
void add_number(int, int*, bool*);
int bingo_check(int*, bool*);

int main(void){
    int bingo_board[25] = {0};
    bool bingo_on[25] = {0};
    int no_called;
    int answer;
    for(int i = 0; i < 25; i++){
    	scanf("%d", &bingo_board[i]);
    }
    for(int i = 0; i < 25; i++){
    	scanf("%d", &no_called);
    	add_number(no_called, bingo_board, bingo_on);
    	if(bingo_check(bingo_board, bingo_on) >= 3){
    		answer = i + 1;
    		break;
    	}
    }
    printf("%d", answer);
}
void add_number(int no_called, int* bingo_board, bool* bingo_on){
	for(int i = 0; i < 25; i++){
    	if(no_called == bingo_board[i]){
    		bingo_on[i] = 1;
    		break;
    	}
    }
}
int bingo_check(int* bingo_board, bool* bingo_on){
	int bingo_no = 0;
	bool bingo_ed = 0;
	for(int i = 0; i < 5; i++){
		bingo_ed = 1;
		for(int j = 0; j < 5; j++){
			if(!bingo_on[j+5*i]) bingo_ed = 0;
		}
		if(bingo_ed) bingo_no++;
		bingo_ed = 1;
		for(int j = 0; j < 5; j++){
			if(!bingo_on[5*j+i]) bingo_ed = 0;
		}
		if(bingo_ed) bingo_no++;
		
	}
	bingo_ed = 1;
	for(int j = 0; j < 5; j++){
		if(!bingo_on[6*j]) bingo_ed = 0;
	}
	if(bingo_ed) bingo_no++;
	bingo_ed = 1;
	for(int j = 0; j < 5; j++){
		if(!bingo_on[4+4*j]) bingo_ed = 0;
	}
	if(bingo_ed) bingo_no++;
	return bingo_no;
}
