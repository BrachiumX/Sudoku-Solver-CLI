#include <stdio.h>

int input(char *filename, int* inputarr, int* zeroarr){

	FILE *fp; 

	if(!(fp = fopen(filename, "r"))){
		printf("Error: could not open file %s\n", filename);
		return 1;
	}

	char temp;
	unsigned int counter = 0;
	unsigned int number;

	while((temp = fgetc(fp)) != EOF){
		if(((number = temp - '0') < 10) && counter < 81){
			if(number==0){
				zeroarr[counter] = 1;
			}
			inputarr[counter++] = number;
		}
	}

	if(counter < 81){
		printf("Error : not enough data\n");
		return 1;
	}

	fclose(fp);

	return 0;
}

int checkRow(int* arr, int row){

	int check[10] = {};	

	for(int i=0;i<9;i++){
		check[arr[9*row+i]]++;
	}

	for(int i=1;i<10;i++){
		if(check[i]>1){
			return 0;
		}
	}

	return 1;
}
		
int checkColumn(int* arr, int column){

	int check[10] = {};

	for(int i=0;i<9;i++){
		check[arr[9*i+column]]++;
	}

	for(int i=1;i<10;i++){
		if(check[i]>1){
			return 0;
		}
	}

	return 1;
}

int checkSquare(int* arr, int square){

	int check[10] = {};
	int start = (square/3)*27 + (square%3)*3;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			check[arr[start+i*9+j]]++;
		}
	}

	for(int i=1;i<10;i++){
		if(check[i]>1){
			return 0;
		}
	}

	return 1;
}


int check(int* arr){

	for(int i=0;i<9;i++){
		if(!checkRow(arr, i) || !checkColumn(arr, i) || !checkSquare(arr, i)){
			return 0;
		}
	}

	return 1;
}

int findFree(int curr, int* inputarr, int* zeroarr){

	for(int i=curr-1;i>-1;i--){
		if(zeroarr[i]){
			return i;
		}
	}
	return -1;
}

int solve(int* inputarr, int* zeroarr){

	int curr = 0;

	while(curr!=-1 && curr!=81){
		if(!zeroarr[curr]){
			curr++;
			continue;
		}
		else if(!inputarr[curr]){
			inputarr[curr]++;
		}

		if(inputarr[curr]==10){
			inputarr[curr] = 0;
			curr = findFree(curr, inputarr, zeroarr);
			inputarr[curr]++;
			continue;
		}

		if(check(inputarr)){
			curr++;
			continue;
		}
		else{
			inputarr[curr]++;
			continue;
		}
	}

	if(curr==-1){
		return 1;
	}
	return 0;
}

int printLine(){
	for(int i=0;i<25;i++){
		printf("─");
	}
	return 0;
}

int print(int* inputarr){

	for(int i=0;i<9;i++){
		if(i%3==0){
			printLine();
			printf("\n");
		}
		for(int j=0;j<9;j++){
			if(j%3==0){
				printf("| ");
			}
			printf("%d ",inputarr[9*i+j]);
		}
		printf("|\n");
	}
	printLine();
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]){

	int inputarr[81] = {};
	int zeroarr[81] = {};

	if(input(argv[1], inputarr, zeroarr)){
		return 1;
	}

	if(!solve(inputarr, zeroarr)){
		print(inputarr);
	}
	else{
		printf("Error: There is no valid answer\n");
		return 1;
	}
	return 0;
}
