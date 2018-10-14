#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

enum status{

	filled,
	empty,
};

struct list {

	int value;
	struct list * next;
	enum status status;
};

struct list * list_head;

void main(){
	
	int option;
	int new_entry;
	while(1){
		printf("Enter the option \n 1.Start the list\n 2.add entry\n 3.print list\n 0.Exit\n\n option:\n");
		scanf("%d",&option);

		switch(option){



			case 1:
				if(list_head == NULL){
					
					list_head = (struct list *)malloc(sizeof(struct list));
					list_head->status = empty;
				}				
				else{
					printf("list already initialized\n\n");
				}	
				break;
			case 2:
				printf("Enter the value of entry:\t");
				scanf("%d",&new_entry);
				if(list_head == NULL){
					printf("list needs initialization\n\n");
					
				}		
				else if(list_head->status == empty){
					list_head->status = filled;
					list_head->value = new_entry;
					list_head->next  = NULL;
				}	
				else{
					struct list * new = list_head ;
					while(new->next != NULL) new = new->next;
					new->next = (struct list *)malloc(sizeof(struct list));
					new = new->next;
					new->value = new_entry;
					new->next = NULL;
				}
				break;
			case 3:
				printf("the list is \n\t");
				struct list * new = list_head ;
                                while(new != NULL){ 
					printf("%d ",new->value);
					new = new->next;
					
				}
				printf("\n");
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("invalid entry\n\n");
		}
	}
}
