#include "tarjan.h"

void initialize_topology(){
        int i,j;
        if(!file){
                perror("Cannot Open File\n");
                exit(-1);
        }
        fseek(file,0,SEEK_SET);
        fscanf(file,"%d\n",&total_nodes);
        //printf("%d\n",total_nodes);

	mark = (int *)calloc(sizeof(int),total_nodes);	
        a = (Node *)malloc(sizeof(Node)*total_nodes);//Initializing G[n,m]
		
        for(i = 0;i< total_nodes;i++){ //initialize node structure
                a[i].edge = (int *)malloc(sizeof(int) * total_nodes);
                for(j = 0;j < total_nodes;j++)
                        a[i].edge[j] = -1;
		a[i].cnt = 0;
        }

	point.stk = (int *)malloc(sizeof(int) * total_nodes);
	point.top = -1;

	marked.stk = (int *)malloc(sizeof(int) * total_nodes);
	marked.top = -1;

        int temp_i = -1,temp_j = -1, faltu = -1;
        double temp_cost = 0.0f;
        while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
		a[temp_i-1].edge[a[temp_i-1].cnt] = temp_j - 1;
		a[temp_i - 1].cnt ++;
		a[temp_j-1].edge[a[temp_j-1].cnt] = temp_i - 1;
                a[temp_j - 1].cnt ++;
        }
}

int length_of_circuit()
{
        //int i;
        //for(i=0;p[i]!=-1 && i<total_nodes;i++);
        //printf("length is: %d\n",i);
        return point.top + 1;
}



void print_circuit(){
	int i;
	//printf("Circuit formed for: %d\n",s + 1);

	for(i = 0;i <= point.top;i++)
		printf("%d\t",point.stk[i] + 1);
	printf("\n");
}

void delete_w(int i,int v,int w){
	int j;
	for(j = i; j < total_nodes-1; j++){
		a[v].edge[j] = a[v].edge[j+1];
	}
	a[v].edge[j] = -1;
	
}	

int backtrack(int v){
	int f,g,w;
	f = 0;
	point.stk[++point.top] = v; // insert v onto point stack
	//printf("Top of Point: %d\n",point.stk[point.top] + 1);

	mark[v] = 1;
	marked.stk[++marked.top] = v;
	int i;
	for(i = 0;i < total_nodes && a[v].edge[i] != -1;i++){
		w = a[v].edge[i] ;
		if( w < s ) {
			delete_w(i,v,w);
		}
		else if( w == s && length_of_circuit() != 2){
			//print point stack as circuit;
			//print_circuit();
			ckt++;
			f = 1;
		}
		else if( mark[w] != 1){
			g = backtrack(w);
			f = f | g;
		}
	}
	if( f == 1){
		while( marked.stk[marked.top] != v){
			mark[marked.stk[marked.top--]] = 0;
		}
		mark[marked.stk[marked.top--]] = 0;
	}
	
	point.top--; // delete v from point stack
	return f;
}

void tarjan(int end_node){
	int i;
	int flag = 0;
	
	for(i = 0;i<total_nodes;i++)
		mark[i] = 0;
	for(i=0;i<total_nodes;i++){
		ckt = 0;
		printf("****For Current node: %d\n",i+1);
		s = i;
		flag = backtrack(i);
		printf("Ckt cnt: %d\n",ckt);
		while(marked.top != -1){
			mark[marked.stk[marked.top--]] = 0;
		}
	}
}



int main(int argc, char *argv[]){
        int i, end_node;
	
        total_nodes = -1;

        if(argc > 3 || argc < 2){
                perror("Incorrect command line arguments\n");
                exit(-1);
        }
        file = fopen(argv[1],"r");
        initialize_topology();
	if(argc == 3)
	        end_node = atoi(argv[2]);
	else
		end_node = total_nodes;

	
	tarjan(end_node);
	
	
}
