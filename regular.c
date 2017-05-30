#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Generates union of d random matchings of the complete graph
// (used in applications as a d-regular random graph)
// Author: C.E. Tsourakakis
// Compile: gcc -o regular regular.c


const int N=10; // number of nodes
const int d=3; // degree of "(d,d+1)-regular graph"
const int E=(d+1)*N;

int eList[E][2];
int M;  // actual number of edges, if N even, is d*N

typedef struct{
	int* arr; 
	int n; // number of elements
}permutation;

void print_perm(permutation* p){ 
	for(int i = 0 ; i < p->n;i++)
		printf("%d ", p->arr[i]);
	printf("\n"); 
}

// generates a random permutation of elements 0,..,n-1  
void knuth_shuffle(permutation* p)
{
    srand(time(NULL));
    for (int i = 0; i < p->n; i++){
        // choose index uniformly in [i, n-1]
        int r  = rand() % (p->n-i) + i;
        int swap = p->arr[r];
        p->arr[r] = p->arr[i];
        p->arr[i] = swap;
    }
}


void print_Edges()
{
    for(int i = 0;i<M;i++)
        printf("%d\t%d\n",eList[i][0],eList[i][1]);
    
}


int main(int argc, char** argv)
{
    int* arr;
	arr = (int*)malloc(N*sizeof(int));
	for(int i = 0; i < N;  i++)
		arr[i] = i; 
	permutation* p = (permutation*) malloc( sizeof(permutation));
	p->n=N;
	p->arr = arr; 
	//print_perm(p);
    
    int counter = 0;
    for(int i=0; i<d;i++){
        knuth_shuffle(p);
        // print_perm(p);  // diagnostics
        for(int j = 0; j< floor(N/2); j++){
            if( p->arr[2*j] < p->arr[2*j+1]){
                eList[counter][0] =p->arr[2*j];
                eList[counter][1] =p->arr[2*j+1];
            }
            else{
                eList[counter][0] =p->arr[2*j+1];
                eList[counter][1] =p->arr[2*j];
          }
        counter+=1;
        }
        if(N%2!=0){
            int r  = rand() % (N-1);
            eList[counter][0] = N-1;
            eList[counter][1] = r;
            counter+=1;
        }
        M = counter;
        
    }
    //printf("Total number of edges %d\n",M); // diagnostics
    printf("%d\t%d\n",N,M); // redirect to outputs
    print_Edges(); // redirect to output
	return 0;
}
	 
