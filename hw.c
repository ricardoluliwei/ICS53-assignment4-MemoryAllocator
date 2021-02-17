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

void set_header_footer(int pos, int block_size, int status){
    if (block_size == 0)
        return;
    
    char header = 0;
    if(status == SET_ALLOCATED){
        header = block_size << 1 | SET_ALLOCATED;
    } else {
        header = block_size << 1 & SET_FREE;
    }
    heap[pos] = header;
    heap[pos + block_size - 1] = header;
    // clear the payload space
    memset(&heap[pos+1], 0, block_size - 2);
}

int read_size(char header){
    int block_size;
    block_size = (unsigned char) header >> 1;
    return block_size;
}

int read_status(char header){
    int status;
    status = (int) header & SET_ALLOCATED;
    return status;
}

void init(){
    set_header_footer(0, HEAP_SIZE, SET_FREE);
}

int def_malloc(int size){
    int p = 0;
    char header;
    int block_size;
    int block_status;
    int remain_size;
    int new_block_size;

    new_block_size = size + 2;

    while (p < HEAP_SIZE){
        header = heap[p];
        block_size = read_size(header);
        block_status = read_status(header);
        remain_size = block_size - new_block_size; // if we allocate this block, how much space remain

        // if the header size is ok and status is empty, we found a block to allocate
        if(remain_size >= 0 && block_status == 0){
            // This code works in both case: need to split or not
            set_header_footer(p, new_block_size, SET_ALLOCATED);
            set_header_footer(p + new_block_size, remain_size, SET_FREE);
            return p + 1;
        }

        p += block_size; // move p to next
    }
    
    return -1; // if no space to allocate
}


void def_free(int index){
    char header;
    char n_header;
    char p_header;
    int p_size;
    int n_size;
    int block_size;
    int new_block_size;
    int p;
   

    p = index - 1;
    header = heap[p];
    block_size = read_size(header);
    new_block_size = block_size;

    if (index - 2 >= 0){
        // previous block exists
        p_header = heap[index - 2]; // previous footer
        if(!read_status(p_header)){ // previous block is empty
            p_size = read_size(p_header);
            p -= p_size;
            new_block_size += p_size;
        }
    } 

    if (index + block_size - 1 < HEAP_SIZE){
        // next block exists
        n_header = heap[index + block_size - 1]; // next header
        if(!read_status(n_header)){ // next block is empty
            n_size = read_size(n_header);
            new_block_size += n_size;
        }
    } 
    
    set_header_footer(p, new_block_size, SET_FREE);
}


void blocklist(){
    int p = 0;
    int start;
    char header;
    int payload_size;
    char* status;

    while (p < HEAP_SIZE){
        header = heap[p];
        start = p + 1;
        payload_size = read_size(header) - 2;
        status = read_status(header) ? "allocated" : "free";
        printf("%d, %d, %s.\n", start, payload_size, status);
        p += payload_size + 2;
    }
}


void writemem(int index, char* str){
    memcpy(&heap[index], str, strlen(str));
}


void printmem(int index, int size){
    int i;
    for(i=0; i< size; i++)
        printf("%X ", heap[index + i]);
    printf("\n");
}



int main(int argc, const char * argv[]) {
    // insert code here...
    init();
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
                   buffer = strtok(NULL, spliter);
                   int size = atoi(buffer);
                   printf("%d\n", def_malloc(size));
                   continue;
               }
               if(strcmp(buffer, "free")==0){
                   buffer = strtok(NULL, spliter);
                   int index = atoi(buffer);
                   def_free(index);
                   continue;
               }
               if(strcmp(buffer, "writemem")==0){
                   buffer = strtok(NULL, spliter);
                   int index = atoi(buffer);
                   buffer = strtok(NULL, spliter);
                   writemem(index, buffer);
                   continue;
               }
               if(strcmp(buffer, "printmem")==0){
                   buffer = strtok(NULL, spliter);
                   int index = atoi(buffer);
                   buffer = strtok(NULL, spliter);
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
