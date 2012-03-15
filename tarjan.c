#include "tarjan.h"


void print_graph(){
	int i,j;
	for(i=0;i<total_nodes;i++){
		printf("Node: %d\t - ",i + 1);
		for(j=0;j < a[i].cnt; j++)
			printf("%d\t",a[i].edge[j] + 1);
		printf("\n");
	}
}
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

        
	visited_n = (int *)malloc(sizeof(int) * total_nodes);
	int temp_i = -1,temp_j = -1, faltu = -1;
        double temp_cost = 0.0f;
        while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
		a[temp_i - 1].edge[a[temp_i-1].cnt] = temp_j - 1;
		a[temp_i - 1].cnt ++;
		a[temp_j-1].edge[a[temp_j-1].cnt] = temp_i - 1;
                a[temp_j - 1].cnt ++;
        }

	//print_graph();
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


void add_to_visited(int val){
        int i;
        for(i=0;i<visited_cnt;i++)
                if(visited_n[i] == val)
                        return;
        visited_n[visited_cnt++] = val;
}

int check_in_visited(){
        int len,i;
        for(i=0;i<visited_cnt;i++){
                if(visited_n[i] == point.stk[point.top])
                        return 0;
        }
        return 1;
}


void reset_visited(){
        int i;
        for(i=0;i<total_nodes;i++)
                visited_n[i] = -1;
}



int backtrack(int v){
	int f,g,w;
	f = 0;
	point.stk[++point.top] = v; // insert v onto point stack
	//printf("Top of Point: %d\n",point.stk[point.top] + 1);
	if(point.top == 1){
		//if(s == 4)	
		//	printf("Added %d to visited\n",v + 1);
		add_to_visited(v);
	}
	mark[v] = 1;
	marked.stk[++marked.top] = v;
	int i;
	for(i = 0;i < total_nodes && a[v].edge[i] != -1;i++){
		w = a[v].edge[i] ;
		//if((s == 4 || s == 2) && (v == s))
			//printf("current w: %d\n",w + 1);
		if( w < s ) {
			delete_w(i--,v,w);
		}
		else if( w == s && length_of_circuit() != 2){
			//print point stack as circuit;
			if(check_in_visited()){
				//print_circuit();
				ckt++;
			}
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

		
	point.stk[point.top--] = -1; // delete v from point stack
	return f;
}

void tarjan(int start_node, int end_node){
	int i;
	int flag = 0;
	
	for(i = 0;i<total_nodes;i++)
		mark[i] = 0;
	for(i=start_node;i<end_node;i++){
		visited_cnt = 0;
		ckt = 0;
		//printf("****For Current node: %d\n",i+1);
		s = i;
		flag = backtrack(i);
		//printf("Ckt cnt: %d\n",ckt);
		while(marked.top != -1){
			mark[marked.stk[marked.top--]] = 0;
		}
		reset_visited();
	}
}



int main(int argc, char *argv[]){
        int i, start_node, end_node;
	struct timeval p,q;	
        total_nodes = -1;

        if(argc > 4 || argc < 3){
                perror("Incorrect command line arguments\n");
                exit(-1);
        }
        file = fopen(argv[1],"r");
        initialize_topology();
	start_node = atoi(argv[2]) - 1;

	gettimeofday(&p,NULL);
	if(argc == 4){
	        end_node = atoi(argv[3]);
		tarjan(start_node, end_node);
	}
	else{
		//end_node = total_nodes;
		tarjan(start_node, start_node +1);
	}
	gettimeofday(&q,NULL);
	printf("Running Time is: %8ld\n\n", q.tv_usec - p.tv_usec + (q.tv_sec-p.tv_sec)*1000000);
	
}
