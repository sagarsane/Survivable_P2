#include "johnson.h"


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
        while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
		g[temp_i - 1].edge[temp_j-1] = 1;
		g[temp_j-1].edge[temp_i-1] = 1;
        }

	//print_graph();
}


int length_of_circuit()
{
        //int i;
        //for(i=0;p[i]!=-1 && i<total_nodes;i++);
        //printf("length is: %d\n",i);
        return stack.top + 1;
}



void print_circuit(){
	int i;
	//printf("Circuit formed for: %d\n",s + 1);

	for(i = 0;i <= stack.top;i++)
		printf("%d\t",stack.stk[i] + 1);
	printf("\n");
}

void delete_fromB(int r,int val){

	int j;
	int pos;
	for(pos = 0; pos < a[r].cnt; pos++)
		if(a[r].edge[pos] == val)
			break;
	if(pos == a[r].cnt){
		printf(":(\n");
		exit(0);
	}

	for(j = pos; j < total_nodes-1; j++){
		a[r].edge[j] = a[r].edge[j+1];
	}
	a[r].edge[j] = -1;
	
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
	int i,j;
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
	int w;
	blocked[u] = 0;
	for(w = 0; w < b[u].cnt; w++){
		delete_fromB(u,w);
		if(blocked[w] == 1)
			unblock(w);
	}
}

int circuit(int v){
	int f,w,i;
	printf("current vetrex is %d\n",v);
	f = 0;
	stack.stk[++stack.top] = v;
	blocked[v] = 1;
	for(i=0;i < total_nodes && a[v].edge[i] != -1;i++){
		w = a[v].edge[i];
		if(w == s && length_of_circuit() > 2)
		{
			if(check_in_visited())
				print_circuit();
			f = 1;
		}
		else if( blocked[w] != 1 && w>s){
			if(circuit(w))
				f = 1;
		}
	}
	if(f == 1){
		unblock(v);
	}
	else{
		for(w = 0; w < total_nodes && a[v].edge[w] != -1; w++){
			if(!belongs_toB(w,v))
				add_toB(w,v);
		}
	}
	stack.stk[stack.top--] = -1;
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

		

void johnson(int end_node){
	int i,j;
	int flag = 0;
	

	for(i=0;i<total_nodes;i++){
		visited_cnt = 0;
		ckt = 0;
		printf("****For Current node: %d\n",i+1);
		s = i;

		dfs(i);
                reset_visited();
                printf("dfs for %d node: ",i+1);
                print_ak(i);

		for(j = 0;j<total_nodes;j++){
	                b[i].edge[j] = -1;
			blocked[j] = 0;
		}
		flag = circuit(i);
		
		//printf("Ckt cnt: %d\n",ckt);
		reset_visited();
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

	johnson(end_node);
	
}
