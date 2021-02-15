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
#define HEAP_SIZE 127

unsigned char heap[HEAP_SIZE];

void set_header_footer(int pos, int size, int status){
    if (size == 0)
        return;
    
    int8_t header = 0;
    if(status == SET_ALLOCATED){
        header = size | SET_ALLOCATED;
    } else {
        header = size & SET_FREE;
    }
    heap[pos] = header;
    heap[pos + size - 1] = header;
    // clear the payload space
    memset(&heap[pos+1], 0, size - 2);
}

int read_size(int8_t header){
    int size;
    size = (int) header & SET_FREE;
    return size;
}

int read_status(int8_t header){
    int status;
    status = (int) header & SET_ALLOCATED;
    return status;
}

void init(){
    memset(heap, 0, HEAP_SIZE);
    set_header_footer(0, HEAP_SIZE, SET_FREE);
}

int def_malloc(int size){
    int p = 0;
    int8_t header;
    int h_size;
    int h_status;
    int remain_size;
    int new_size;

    new_size = size + 2;

    while (p < HEAP_SIZE){
        header = heap[p];
        h_size = read_size(header);
        h_status = read_status(status);
        remain_size = h_size - new_size; // if we allocate this block, how much space remain

        // if the header size is ok and status is empty, we found a block to allocate
        if(remain_size > 0 && h_status == 0){
            // This code works in both case: need to split or not
            set_header_footer(p, new_size, SET_ALLOCATED);
            set_header_footer(p + new_size, remain_size, SET_FREE);
            return p + 1;
        }

        p += h_size; // move p to next
    }
    
    return -1; // if no space to allocate
}


void def_free(int index){
    int size = heap[index]&SET_FREE;
}


void blocklist(){};


void writemem(int index, char* str){
    memcpy(&heap[index], &str, strlen(str));
}


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
}



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
