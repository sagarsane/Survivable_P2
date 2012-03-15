#include "johnson.h"

void print_graph(){
	int i,j;
	for(i=0;i<total_nodes;i++){
		printf("Node: %d - ",i + 1);
		for(j=0;j < a[i].cnt; j++)
			printf("%d\t",a[i].edge[j] + 1);
		printf("\t Count is: %d\n",a[i].cnt);
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

	blocked = (int *)calloc(sizeof(int),total_nodes);


        g = (Node *)malloc(sizeof(Node)*total_nodes);//Initializing G[n,m]
		
        for(i = 0;i< total_nodes;i++){ //initialize node structure
                g[i].edge = (int *)malloc(sizeof(int) * total_nodes);
                for(j = 0;j < total_nodes;j++)
                        g[i].edge[j] = 0;
        }

	a = (Node *)malloc(sizeof(Node)*total_nodes);//Initializing G[n,m]

        for(i = 0;i< total_nodes;i++){ //initialize node structure
                a[i].edge = (int *)malloc(sizeof(int) * total_nodes);
                for(j = 0;j < total_nodes;j++)
                        a[i].edge[j] = -1;
		a[i].cnt = 0;
        }


        b = (Node *)malloc(sizeof(Node)*total_nodes);//Initializing G[n,m]
        for(i = 0;i< total_nodes;i++){ //initialize node structure
                b[i].edge = (int *)malloc(sizeof(int) * total_nodes);
                for(j = 0;j < total_nodes;j++)
                        b[i].edge[j] = -1;
                b[i].cnt = 0;
        }


	stack.stk = (int *)malloc(sizeof(int) * total_nodes);
	stack.top = -1;

	visited_n = (int *)malloc(sizeof(int)*total_nodes);
	for(i=0;i<total_nodes;i++)
		visited_n[i]= -1;
	

	int temp_i = -1,temp_j = -1, faltu = -1;
        double temp_cost = 0.0f;

     /*   while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
                g[temp_i-1].edge[temp_j-1] = 1;
                //g[temp_i - 1].cnt ++;
                g[temp_j-1].edge[temp_i-1]=1;
               //g[temp_j - 1].cnt ++;
        }*/
	while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
                a[temp_i-1].edge[a[temp_i-1].cnt] = temp_j - 1;
                a[temp_i - 1].cnt ++;
                a[temp_j-1].edge[a[temp_j-1].cnt] = temp_i - 1;
                a[temp_j - 1].cnt ++;
        }

	//print_graph();
}


int length_of_circuit()
{
        return stack.top + 1;
}



void print_circuit(){
	int i;
//	printf("Circuit formed for: %d and top is %d\n",s + 1,stack.top);

	for(i = 0;i <= stack.top;i++){
		printf("%d\t",stack.stk[i] + 1);
	//	if(i > total_nodes)
	//	printf("i: %d :-o top: %d\n",i,stack.top);
	//	printf("\n");
	}
	printf("\n");
}

void delete_fromB(int r,int pos){

	int j;

	for(j = pos; j < total_nodes-1; j++){
		b[r].edge[j] = b[r].edge[j+1];
	}
	b[r].cnt--;
	b[r].edge[j] = -1;
	
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
                if(visited_n[i] == stack.stk[stack.top])
                        return 0;
        }
        return 1;
}


void reset_visited(){
        int i;
        for(i=0;i<total_nodes;i++)
                visited_n[i] = -1;
}


int belongs_toB(int r,int val){
	int i;
	for(i = 0;i < b[r].cnt; i++){
		if(b[r].edge[i] == val)
			return 1;
	}
	return 0;
}


void add_toB(int r, int val){
	b[r].edge[b[r].cnt++] = val;
}



void unblock(int u){
	int i,w;
	blocked[u] = 0;
//	printf("current u is %d and count is %d\n",u,b[u].cnt);
	for(i = 0; i < b[u].cnt; i++){
		w = b[u].edge[i];
		//if(stack.top>10)
		//	printf("deleting w: %d\n",w);
		delete_fromB(u,i);
		i--;
		if(blocked[w] == 1)
			unblock(w);
	}
}

void printB(){
	int i,j;
	for(i=0;i<total_nodes;i++){
                printf("Node: %d\t - ",i + 1);
                for(j=0;j < b[i].cnt; j++)
                        printf("%d\t",b[i].edge[j] + 1);
                printf("\t Count is: %d\n",b[i].cnt);
        }
}

int circuit(int v){
	int f,w,i;
//	printf("current vetrex is %d\n",v);
	f = 0;
/*	for(i=0;i<stack.top;i++)
		fprintf(stderr,"  ");
	fprintf(stderr,"stacked %d\n",v);*/
	stack.stk[++stack.top] = v;
	
	if(stack.top == 1)
		add_to_visited(v);
	blocked[v] = 1;
	for(i=0;i < a[v].cnt;i++){
		w = a[v].edge[i];
		if(w == s)
		{
			if(check_in_visited() && length_of_circuit() > 2)
			{ 
				//printB();
				//print_circuit();
				ckt++;
				//getchar();
			}
			f = 1;
			
		}
		else if( blocked[w] != 1){// && w>s){
			if(circuit(w)==1)
				f = 1;
		}
	}
	if(f == 1){
//		if(v==5)
//			printf("Unblocking node 5\n");
		unblock(v);
	}
	else{
		for(i = 0; i < a[v].cnt; i++){
			w = a[v].edge[i];
			if(belongs_toB(w,v) == 0)
				add_toB(w,v);
		}
	}
	stack.stk[stack.top--] = -1;
/*	for(i=0;i<stack.top;i++)
		fprintf(stderr,"  ");
	fprintf(stderr,"unstacked %d\n",v);*/
	return f;
}


void dfs(int start)
{
        int i;
        visited_n[start]=1;
        a[s].edge[a[s].cnt++]=start;
        for(i=0;i<total_nodes;i++){
                if(visited_n[i] == -1 && g[start].edge[i] == 1)
                        dfs(i);
        }


}
void print_ak(int i)
{
        int j;
        for(j=0;j<total_nodes;j++)
                printf("%d ",a[i].edge[j]+1);
        printf("\n");
}
void find_ak(int cur_val)
{
	if(cur_val==0)
		return;	
	else{
		int i,j,k;
		int prev_val=cur_val-1;
		for(i=0;i<total_nodes;i++)
		{
			a[prev_val].edge[i] = -1;
		}
		a[prev_val].cnt = 0;
		for(i=cur_val;i<total_nodes;i++)
			for(j=0;j<a[i].cnt;j++)
				if(a[i].edge[j] == prev_val){
					for(k=j;k < total_nodes-1;k++){
						a[i].edge[k] = a[i].edge[k+1];
					}
					a[i].cnt--;
					a[i].edge[k] = -1;
					break;
				}
					
	}
}
		

void johnson(int start_node, int end_node){
	int i,j;
	int flag = 0;
	

	for(i=start_node;i<end_node;i++){
		visited_cnt = 0;
		ckt = 0;
		//stack.top=-1;
		//printf("****For Current node: %d\n",i+1);
		s = i;

		//dfs(i);
                //printf("dfs for %d node: ",i+1);
		find_ak(i);
	//	print_graph();
		//getchar();
//		printf("Circuits are\n");
                //print_ak(i);

		for(j = 0;j<total_nodes;j++){
	                b[i].edge[j] = -1;
			blocked[j] = 0;
		}
		b[i].cnt =0;
		flag = circuit(i);
		
		//printf("Ckt cnt: %d\n",ckt);
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
	start_node = atoi(argv[2]) -1;
	
	for(i = 0;i < start_node;i++)
		find_ak(i);

	gettimeofday(&p,NULL);
	if(argc == 4){
	        end_node = atoi(argv[3]);
		johnson(start_node, end_node);
	}
	else{
		johnson(start_node, start_node + 1);
	}
	gettimeofday(&q,NULL);
	printf("Running Time is: %8ld\n\n", q.tv_usec - p.tv_usec + (q.tv_sec-p.tv_sec)*1000000);

}
