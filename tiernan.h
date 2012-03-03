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




Node *g,*h;
FILE *file;
int *p;
int *visited_n,visited_cnt;
int total_nodes;

void initialize_topology();
