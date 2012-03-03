#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<math.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>
#define INF 999999.0f
typedef struct node_{
	int *edge;
	int cnt;
}Node;


typedef struct stack_{
	int *stk;
	int top;	

}Stack;


Node *a;
Stack point,marked;
FILE *file;
int total_nodes,s,ckt;
int *visited_n,visited_cnt;
int *mark;
void initialize_topology();
