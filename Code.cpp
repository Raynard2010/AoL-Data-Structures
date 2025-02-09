#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
	char ch;
	bool word;
	char definition[1001];
	struct tnode *next[26];
};

void release(struct tnode **root){
	char newWord[101];
	char newDef[1001];
	
	bool valid = 0;
	
	while(!valid){
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", &newWord);
		getchar();
		
		if(strlen(newWord) <= 1) continue;
		
		bool space = 0;
		
		for(int i = 0; i < strlen(newWord); i++){
			if(newWord[i] == ' '){
				space = 1;
				break;
			}
		}
		
		if(space) continue;
		
		valid = 1;
	}
	
	valid = 0;
	
	while(!valid){
		printf("Input a new slang word description [Must be more than 2 words]: ");
		scanf("%[^\n]", &newDef);
		getchar();
		
		int nspace = 0;
		
		for(int i = 0; i < strlen(newDef); i++){
			if(newDef[i] == ' ') nspace++;
		}		
		
		if(nspace < 2) continue;		
		
		valid = 1;
	}
	
	struct tnode *curr = *root;
	
	bool exist = 1;

	for(int i = 0; i < strlen(newWord); i++){
		if(curr->next[newWord[i] - 97] != NULL){
			curr = curr->next[newWord[i] - 97];
		}
		else{
			struct tnode *temp = (struct tnode*) malloc(sizeof(struct tnode));
			for(int i = 0; i < 26; i++) temp->next[i] = NULL;
	
			temp->ch = newWord[i];
			temp->word = 0;
			curr->next[newWord[i] - 97] = temp;
	
			if(i == strlen(newWord) - 1){
				temp->word = 1;
				strcpy(temp->definition, newDef);
			}
	
			curr = temp;
			
			exist = 0;
		}
	}

	if(exist){
		strcpy(curr->definition, newDef);
		printf("\nSuccessfully updated a slang word.\n");
	}
	else{
		printf("\nSuccessfully released new slang word.\n");
	}
	
	printf("\n");
}

void search(struct tnode **root){
	char wordSearch[101];
	
	bool valid = 0;
	
	while(!valid){
		printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", &wordSearch);
		getchar();
		
		if(strlen(wordSearch) <= 1) continue;
		
		bool space = 0;
		
		for(int i = 0; i < strlen(wordSearch); i++){
			if(wordSearch[i] == ' '){
				space = 1;
				break;
			}
		}
		
		if(space) continue;
		
		valid = 1;
	}
	
	bool exist = 1;
	
	struct tnode *curr = *root;
	
	for(int i = 0; i < strlen(wordSearch); i++){
		curr = curr->next[wordSearch[i] - 97];
		if(curr == NULL){
			exist = 0;
			break;
		}
		
		if(i == strlen(wordSearch) - 1){
			if(curr->word == 0) exist = 0;
			break;
		}
	}
	
	if(!exist) printf("There is no word \"%s\" in the dictionary.\n\n", wordSearch);
	else{
		printf("Slang word: %s\n", wordSearch);
		printf("Description: %s\n\n", curr->definition);
	}
}

int num = 1;
void display(struct tnode **root, char words[], int level){
	struct tnode *curr = *root;
	if(curr->word){
		words[level] = '\0';
		printf("%d. %s\n", num, words);
		num++;
	}
	
	for(int i = 0; i < 26; i++){
		if(curr->next[i] != NULL){
			words[level] = i + 'a';
			display(&curr->next[i], words, level + 1);
		}
	}
}

void displayPrefix(struct tnode **root, char prefixSearch[], char words[], int level){
	struct tnode *curr = *root;
	if(curr->word){
		words[level] = '\0';
		printf("%d. %s%s\n", num, prefixSearch, words);
		num++;
	}
	
	for(int i = 0; i < 26; i++){
		if(curr->next[i] != NULL){
			words[level] = i + 'a';
			displayPrefix(&curr->next[i], prefixSearch, words, level + 1);
		}
	}
}

void viewprefix(struct tnode **root){
	char prefixSearch[101];
		
	printf("Input a prefix to be searched: ");
	scanf("%[^\n]", &prefixSearch);
	getchar();
	
	bool exist = 1;
	
	struct tnode *curr = *root;
	
	for(int i = 0; i < strlen(prefixSearch); i++){
		curr = curr->next[prefixSearch[i] - 97];
		if(curr == NULL){
			exist = 0;
			break;
		}
	}
	
	if(!exist) printf("There is no prefix \"%s\" in the dictionary.\n\n", prefixSearch);
	else{
		int level = 0;
		char words[101] = {};
	
		displayPrefix(&curr, prefixSearch, words, level);
	}
	
	num = 1;
	
	printf("\n");
}

void viewall(struct tnode **root){
	struct tnode *curr = *root;
	
	bool empty = 1;
	
	for(int i = 0; i < 26; i++){
		if(curr->next[i] != NULL){
			empty = 0;
			break;
		}
	}
	
	if(empty){
		printf("There is no slang word yet in the dictionary.\n\n");
		return;
	}
	
	int level = 0;
	char words[101] = {};
	
	display(&curr, words, level);

	num = 1;
	
	printf("\n");
}

int main(){
	struct tnode *root = (struct tnode*) malloc(sizeof(struct tnode));
	root->word = 0;
	for(int i = 0; i < 26; i++) root->next[i] = NULL;
	
	int nchoice = 0;
	
	while(nchoice != 5){
		printf("Choose one of the option\n");
		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang words\n");
		printf("5. Exit\n");
		
		printf("Input your choice: ");
		scanf("%d", &nchoice);
		getchar();
		
		switch(nchoice){
			case(1):
				release(&root);
				break;
			case(2):
				search(&root);
				break;
			case(3):
				viewprefix(&root);
				break;
			case(4):
				viewall(&root);
				break;
		}
	}
	
	printf("Thank you... Have a nice day :)\n");
	
	return 0;
}
