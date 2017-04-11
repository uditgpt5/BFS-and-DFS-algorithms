#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

struct list{
  int data;
  struct list *next;
};

struct list *addEdge(struct list *currentNode, int vertex){
  struct list *newNode;
  newNode = (struct list *)malloc(sizeof(struct list));

  newNode->data = vertex;
  newNode->next = currentNode;

  return newNode;
}

struct stack{
  int stk[MAXSIZE]; 
  int top;
}s;

void Push(int sv){
  if (s.top == MAXSIZE-1)
	return;
  else{
	s.top += 1;
	s.stk[s.top] = sv;
  }
}

int pop(){
  if (s.top == -1)
	return 0;
  else{
	int n = s.stk[s.top];
	s.top -= 1;
	return n;
  }
}

void DFS_visit(struct list *adjacencyList[], int parent[], char color[]){
  int u = pop();
  struct list *traverse;
  traverse = adjacencyList[u];

  while(traverse){
	if (color[traverse->data] == 'w'){
	   color[traverse->data] = 'g';
	   parent[traverse->data] = u;
	   Push(traverse->data);
	   DFS_visit(adjacencyList, parent, color);
	}
	traverse = traverse->next;
  }
}

void DepthFirstSearch(struct list *adjacencyList[], int parent[], char color[], int vertices, int sourceVertex){
  int i;
  for(i = 1; i <= vertices; i++){
 	if (i == sourceVertex)
	   continue;
	else{
	   color[i] = 'w';
	   parent[i] = 0;
	}
  }
  color[sourceVertex] = 'g';
  parent[sourceVertex] = 0;

  s.top = -1;
  Push(sourceVertex);
  while(s.top != -1)
	DFS_visit(adjacencyList, parent, color);
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
	   printf("Invalid input\n");
	   break;
	}
	else {
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

  int parent[vertices+1], sourceVertex, j;
  char color[vertices+1];

  printf("Enter source vertex: ");
  scanf("%d", &sourceVertex);
  DepthFirstSearch(adjacencyList, parent, color, vertices, sourceVertex);

  printf("DFS traversal:\n");
  for(j = 1; j <= vertices; j++)
	printf("Vertex: %d, Parent: %d, Color: %c\n", j, parent[j], color[j]);

  return 0;
}
