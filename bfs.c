#include<stdio.h>
#include<stdlib.h>
#define MAX 10

struct list{
  int data;
  struct list *next;
};

struct queue{
  int head, tail;
  int val[MAX];
}q;

struct list *addEdge(struct list *currentNode, int vertex){
  struct list *newNode;
  newNode = (struct list *)malloc(sizeof(struct list));

  newNode->data = vertex;
  newNode->next = currentNode;

  return newNode;
}

void Enqueue(int s){
   if (q.head == MAX-1){
	printf("Queue full!!\n");
	return;
   }
   else{
	q.head += 1;
	q.val[q.head] = s;
   }
}

int Dequeue(){
  if (q.head == -1){
	printf("Queue empty!!\n");
	return -1;
  }
  else{
	q.tail += 1;
	int u = q.val[q.tail];
	return u;
  }
}

void BreadthFirstSearch(struct list *adjacencyList[], int distance[], char color[], int vertices, int s, int parent[]){
  int i;
  struct list *traverse;
  for(i = 1; i <= vertices; i++){
	if (i == s)
	   continue;
	else{
	   color[i] = 'w';
	   parent[i] = 0;
	   distance[i] = 0;
	}
  }
  color[s] = 'g';
  parent[s] = 0;
  distance[s] = 0;
  
  q.head = -1; q.tail = -1;
  Enqueue(s);
  while(q.head != q.tail){
	int u = Dequeue();
	traverse = adjacencyList[u];
	while(traverse){
	   if (color[traverse->data] == 'w'){
		color[traverse->data] = 'g';
		parent[traverse->data] = u;
		distance[traverse->data] = distance[u] + 1;
		Enqueue(traverse->data);
	   }
	   traverse = traverse->next;
	}
  }
}

int main(int argc, char **argv){
  int vertices, edges, v1, v2, i;
  printf("Enter number of vertices and edges: ");
  scanf("%d %d", &vertices, &edges);

  struct list *adjacencyList[vertices+1], *traverse;
  for(i = 1; i <= vertices; i++)
	adjacencyList[i] = NULL;

  printf("Enter edge info:\n");
  for(i = 1; i <= edges; i++){
	scanf("%d %d", &v1, &v2);
	if (v1 <= 0 || v2 <= 0 || v1 > vertices || v2 > vertices){
	   printf("Invalid input!!\n");
	   break;
	}
	else{
	   adjacencyList[v1] = addEdge(adjacencyList[v1], v2);
	   adjacencyList[v2] = addEdge(adjacencyList[v2], v1);	
	}
  }

  for(i = 1; i <= vertices; i++){
	traverse = adjacencyList[i];
	printf("adjacencyList[%d]-->", i);
	while(traverse){
	   printf("%d-->", traverse->data);
	   traverse = traverse->next;
	}
	printf("END\n");
  }

  int parent[vertices+1], distance[vertices+1], sv;
  char color[vertices+1];
  printf("Enter source vertex: ");
  scanf("%d", &sv);

  BreadthFirstSearch(adjacencyList, distance, color, vertices, sv, parent);

  printf("BFS traversal!!\n");
  for(i = 1; i <= vertices; i++)
	printf("Vertex: %d, Color: %c, parent: %d, distance: %d\n", i, color[i], parent[i], distance[i]);
  

  return 0;
}
