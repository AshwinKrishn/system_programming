#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include  <stdlib.h>
#include "checksum.h"

enum status{

	filled,
	empty,
};

struct list {

	int value;
	uint32_t id;
	struct list * next;
	enum status status;
};

struct list * list_head;


int main(int argv , char * argc[]){


	while(1){

	static int found = 0;
	unsigned char input[256] = {'\0'};
	uint32_t final_crc = 0; 
	int new_entry,option = 0;
	
	printf("Enter the option \n 1.Start the list\n 2.add entry  \
			\n3.print list\n4.search key value pair \n 0.Exit\n\n option:\n");
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
				if(list_head == NULL){
					printf("list needs initialization\n\n");
					
				}		
				else if(list_head->status == empty){
					
					printf("Enter the string id:\t");
					scanf("%s",input);
					final_crc = crc_32(input,sizeof(input));
					
					list_head->id = final_crc;
					list_head->status = filled;
					printf("the value for the key:  ");
					
					scanf("%d",&new_entry);
					list_head->value = new_entry;
					list_head->next  = NULL;
				}	
				else{
					
					printf("Enter the string id:\t");
                                        scanf("%s",input);
                                        final_crc = crc_32(input,sizeof(input));
					
					
					printf("Enter the value of entry:\t");
					scanf("%d",&new_entry);
					struct list * new = list_head ;
					
					while(new->next != NULL) new = new->next;
					new->next = (struct list *)malloc(sizeof(struct list));
					new = new->next;
					
					new->value = new_entry;
					new->id = final_crc ;
					new->next = NULL;
				}
				break;
			case 3:
				printf("the list is\n\t");
				struct list * new = list_head ;
                                while(new != NULL){ 
					printf("ID:%x\tvalue:%d\n\t ",new->id,new->value);
					new = new->next;
					
				}

				printf("\n");
				break;
			
			case 4:
				if(list_head != NULL){
					printf("enter the key value to parse:\t");
					scanf("%s",input);
					new = list_head ;
				
					final_crc = crc_32(input,sizeof(input));
						while((new != NULL) ){
						if(new->id == final_crc){

							printf("found the ID %s and value is %d\n\n" \
								,input,new->value);
							found =1;
						}
						new = new->next;

					}
					
					if(found == 1){
						found =0;
						break;
					}
					else
						printf("key not found\n");
					
					
				}	
				else {
					printf("initialize the head\n\n");
				}
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("invalid entry\n\n");	
				break;

		}
	} 
 
}
