//
//  main.c
//  53-Assignment4
//
//  Created by Tony on 2021/2/14.
//

#include <stdio.h>
#include <limits.h>
#include "stdlib.h"
#include "string.h"
#define MAX_LINE 80
#define SET_FREE -2
#define SET_ALLOCATED 1

unsigned char heap[127];

void def_malloc(int size){
    int newsz = size|SET_ALLOCATED;
};
void def_free(int index){
    int size = heap[index]&SET_FREE;
};
void blocklist(){};
void writemem(int index, char* str){
    memcpy(&heap[index], &str, strlen(str));
};
void printmem(int index, int size){
    char hexnumber[2];
    int i;
    for(i=0; i< size; i++){
        int ASC = (int) heap[index];
        int firstbit = ASC /16;
        hexnumber[0] = firstbit + 48;
        int rem = ASC%16;
        if(rem <10){
            hexnumber[1] = rem +48;
        }else{
            hexnumber[1] = rem + 55;
        }
        printf("%s ", hexnumber);
    }
    printf("\n");
};



int main(int argc, const char * argv[]) {
    // insert code here...
    char input[800], *buffer;
        //int bufsize = MAX_LINE;
        char* spliter = " \n";
        while (1) // while loop to get user input
           {
               printf("> ");
               memset(input, 0, 80);
               fgets(input, (sizeof input / sizeof input[0]), stdin);
               if(input[strlen(input)-1] == '\n') input[strlen(input)-1]=0;
               if(strcmp(input, "quit") == 0){break;}
               buffer = strtok(input, spliter);
               if(strcmp(buffer, "malloc")==0){
                   int size = atoi(buffer);
                   def_malloc(size);
                   continue;
               }
               if(strcmp(buffer, "free")==0){
                   int index = atoi(buffer);
                   def_free(index);
                   continue;
               }
               if(strcmp(buffer, "writemem")==0){
                   int index = atoi(buffer);
                   buffer = strtok(input, spliter);
                   char* input = buffer;
                   writemem(index, input);
                   continue;
               }
               if(strcmp(buffer, "printmem")==0){
                   int index = atoi(buffer);
                   buffer = strtok(input, spliter);
                   int size = atoi(buffer);
                   printmem(index, size);
                   continue;
               }
               if(strcmp(buffer, "blocklist")==0){
                   blocklist();
                   continue;
               }
           }
        return 0;
}
