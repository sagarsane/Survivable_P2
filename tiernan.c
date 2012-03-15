#include "tiernan.h"

void initialize_topology(){
        int i,j;
        if(!file){
                perror("Cannot Open File\n");
                exit(-1);
        }
        fseek(file,0,SEEK_SET);
        fscanf(file,"%d\n",&total_nodes);
        //printf("%d\n",total_nodes);

        g = (Node *)malloc(sizeof(Node)*total_nodes);//Initializing G[n,m]

        for(i = 0;i< total_nodes;i++){ //initialize node structure
                g[i].edge = (int *)malloc(sizeof(int) * total_nodes);
                for(j = 0;j < total_nodes;j++)
                        g[i].edge[j] = -1;
		g[i].cnt = 0;
        }

	h = (Node *)calloc(sizeof(Node),total_nodes);//Initializing H[n,m]
	for(i = 0;i< total_nodes;i++){ //initialize node structure
                h[i].edge = (int *)malloc(sizeof(int) * total_nodes);
                for(j = 0;j < total_nodes;j++)
                        h[i].edge[j] = -1;
        }
	

	p = (int *)malloc(sizeof(int) * total_nodes); //Initializing P
	for(i = 0;i<total_nodes;i++)
		p[i] = -1;
	

	visited_n = (int *)malloc(sizeof(int) * total_nodes);
	  for(i = 0;i<total_nodes;i++)
                visited_n[i] = -1;

        int temp_i = -1,temp_j = -1, faltu = -1;
        double temp_cost = 0.0f;
        while(fscanf(file,"%d %d %lf %d",&temp_i,&temp_j,&temp_cost,&faltu)!= EOF){
		g[temp_i-1].edge[g[temp_i-1].cnt] = temp_j - 1;
		g[temp_i - 1].cnt ++;
		g[temp_j-1].edge[g[temp_j-1].cnt] = temp_i - 1;
               g[temp_j - 1].cnt ++;
        }
}

int belongs_toP(int curr_val){
	int i;
	for(i = 0;i<total_nodes;i++){
		if(curr_val == p[i])
			return 1;
	}
	return 0;
}

int belongs_toH(int curr_val, int k){
	int i;
	for(i = 0;i< total_nodes;i++){
		if( curr_val == h[p[k]].edge[i])
			return 1;
	}
	return 0;
}

int belongs_toG(int k){
        int i;
        for(i = 0;i< total_nodes;i++){
                if( p[0] == g[p[k]].edge[i])
                        return 1;
        }
        return 0;
}
int length_of_circuit()
{
	int i;
	for(i=0;p[i]!=-1 && i<total_nodes;i++);
	//printf("length is: %d\n",i);
	return i;
}



int path_extension(int k){
	int j, curr_val;
	for(j = 0;j < total_nodes;j++){
		curr_val = g[p[k]].edge[j];
		if(curr_val > p[0] && !belongs_toP(curr_val) && !belongs_toH(curr_val,k)){
			//j found - extend the path
			return j;
		}
	}
	return -1;

}

void print_circuit(){
	int i;
	//printf("Circuit Formed: ");
	for(i=0;p[i] != -1 && i<total_nodes;i++){
		printf("%d\t",p[i] + 1);

	}
	printf("\n");
}


void reset_H(){
	int i,j;
	for(i = 0;i < total_nodes; i++)
		for(j=0;j<total_nodes;j++)
			h[i].edge[j] = -1;
	
}


void reset_visited(){
	int i;
	for(i=0;i<total_nodes;i++)
		visited_n[i] = -1;
}

void set_H(int k, int flag){
	int i;
	for(i = 0; i < total_nodes; i++){
		if(flag == 0)
			h[p[k]].edge[i] = -1;
		else{
			if(h[p[k-1]].edge[i] == -1){
				h[p[k-1]].edge[i] = p[k];
				return;
			}
		
		}
	}
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
	for(len=0;p[len] != -1 && len < total_nodes; len++);
	len--;
	for(i=0;i<visited_cnt;i++){
		if(visited_n[i] == p[len])
			return 0;
	}
	return 1;
}

void tiernan(int start_node, int end_node){
	int k,i,j,ckt=0;
	//p[0] = 0;
	
	for(i = start_node; i<end_node; i++){
		visited_cnt = 0;
		ckt = 0;
		k = 0;
		//printf("Current i: %d\t Current k: %d\n",i,k);
		p[0] = i;
		

		while(1){
			if((j=path_extension(k)) > -1){
				k=k+1;
				p[k] = g[p[k-1]].edge[j];
				if(k == 1){
					add_to_visited(p[k]);
				}
			}
			else{
				if(belongs_toG(k) && length_of_circuit()!=2){ //circuit confirmation
					if(check_in_visited()){
						//print_circuit();//circuit is reported
						ckt++;
					}
				}
				if(k == 0){	//vertex closure
				//	printf("For i: %d, Circuits: %d\n",i+1,ckt);
					break;
				}
				else{
					
					set_H(k,0);
					set_H(k,1);
					p[k] = -1;
					k--;				
				//	if(k < 5)
					//printf("Current K in Else: %d\n",k);
				}
			}
			
		}
		reset_H();
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
//	if(argc == 3)
//	        end_node = atoi(argv[2]);
//	else
//		end_node = total_nodes;
	start_node = atoi(argv[2]) - 1;
	gettimeofday(&p,NULL);
	if(argc == 4){
		end_node = atoi(argv[3]);
		tiernan(start_node, end_node);
	}
	else{
		tiernan(start_node, start_node + 1);
	}
	gettimeofday(&q,NULL);
	printf("Running Time is: %8ld\n\n", q.tv_usec - p.tv_usec + (q.tv_sec-p.tv_sec)*1000000);

}
