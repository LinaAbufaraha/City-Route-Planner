#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CITIES 200
#define MAX_CITY_NAME_LENGTH 20
#define MAX_LINE_LENGTH 50

int graph[MAX_CITIES][MAX_CITIES]= {0};
char cities[MAX_CITIES][MAX_CITY_NAME_LENGTH];
int ShortestPathDijkstra;
int ShortestPathBFS;

typedef struct {
    int items[MAX_CITIES];
    int front;
    int rear;
} Queue;

// Function to create an empty queue
void initializeQueue(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if the queue is empty
bool isQueueEmpty(Queue* queue) {
    return queue->front == -1;
}

// Function to check if the queue is full
bool isQueueFull(Queue* queue) {
    return queue->rear == MAX_CITIES - 1;
}

// Function to add an item to the queue
void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) {
        printf("Queue is full, cannot enqueue.\n");
        return;
    }
    if (isQueueEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = item;
}

// Function to remove an item from the queue
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1;
    }
    int item = queue->items[queue->front];
    if (queue->front >= queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }
    return item;
}

int loadCities()
{
    FILE* file = fopen("cities.txt", "r");
    int numCities = 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* city1 = strtok(line, "\t");
        char* city2 = strtok(NULL, "\t");

        int index1 = -1;
        int index2 = -1;

        // Find or add city1 to cities array    ///////
        for (int i = 0; i < numCities; i++)
        {
            if (strcmp(city1, cities[i]) == 0)
            {
                index1 = i;
                break;
            }
        }
        if (index1 == -1)
        {
            strncpy(cities[numCities], city1, MAX_CITY_NAME_LENGTH);
            cities[numCities][MAX_CITY_NAME_LENGTH - 1] = '\0';  // Ensure null-terminated string
            index1 = numCities;
            numCities++;
        }

        // Find or add city2 to cities array
        for (int i = 0; i < numCities; i++)
        {
            if (strcmp(city2, cities[i]) == 0)
            {
                index2 = i;
                break;
            }
        }
        if (index2 == -1)
        {
            strncpy(cities[numCities], city2, MAX_CITY_NAME_LENGTH);
            cities[numCities][MAX_CITY_NAME_LENGTH - 1] = '\0';
            index2 = numCities;
            numCities++;
        }

        // Populate the graph array
        int distance;
        sscanf(strtok(NULL, "\t"), "%d", &distance);
        //printf("%d\n",distance);

        graph[index1][index2] = distance;
        graph[index2][index1] = distance;
    }

    fclose(file);

    // Print the distinct cities and their indices
    printf("Distinct cities:\n");
    for (int i = 0; i < numCities; i++)
    {
        printf("%d: %s\n", i, cities[i]);
    }

    // Print the adjacency matrix
   /* printf("Adjacency matrix:\n");
    for (int i = 0; i < numCities; i++)
    {
        for (int j = 0; j < numCities; j++)
        {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }  */
    return numCities;
}

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[], int numCities)
{
    int min = INT_MAX, minIndex;

    for (int v = 0; v < numCities; v++)
    {
        if (visited[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the shortest path from the source to the destination
void printPath(int parent[], int j, char cities[MAX_CITIES][MAX_CITY_NAME_LENGTH])
{
    if (parent[j] == -1)
    {
        printf("%s", cities[j]);
        return;
    }

    printPath(parent, parent[j], cities);
    printf(" -> %s", cities[j]);
}

// Function to find the shortest path between source and destination using Dijkstra's algorithm
void dijkstra(int src, int dest, int numCities)
{
    int dist[MAX_CITIES];
    int visited[MAX_CITIES];
    int parent[MAX_CITIES];

    for (int i = 0; i < numCities; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < numCities - 1; count++)
    {
        int u = minDistance(dist, visited, numCities);
        visited[u] = 1;

        for (int v = 0; v < numCities; v++)
        {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INT_MAX)
    {
        printf("No path found between %s and %s.\n", cities[src], cities[dest]);
    }
    else
    {
        printf("\nShortest path from %s to %s: ", cities[src], cities[dest]);
        printPath(parent, dest, cities);
        printf("\n");
        printf("Shortest distance: %d km\n", dist[dest]);
        ShortestPathDijkstra=dist[dest];
    }
}

void bfs(int source, int destination, int numCities)
{
    int distance[MAX_CITIES];
    int previous[MAX_CITIES];
    int visited[MAX_CITIES];

    for (int i = 0; i < numCities; i++)
    {
        distance[i] = -1;
        previous[i] = -1;
        visited[i] = 0;
    }

    distance[source] = 0;
    visited[source] = 1;

    Queue queue;
    initializeQueue(&queue);
    enqueue(&queue, source);

    while (!isQueueEmpty(&queue))
    {
        int current = dequeue(&queue);
        if (current == destination)
            break;

        for (int i = 0; i < numCities; i++)
        {
            if (!visited[i] && graph[current][i] > 0)
            {
                visited[i] = 1;
                distance[i] = distance[current] + graph[current][i];
                previous[i] = current;
                enqueue(&queue, i);
            }
        }
    }

    if (distance[destination] == -1)
    {
        printf("No path found from %s to %s\n", cities[source], cities[destination]);
        return;
    }

    // Reconstruct the path
    int path[MAX_CITIES];
    int pathLength = 0;
    int currentIndex = destination;

    while (currentIndex != -1)
    {
        path[pathLength] = currentIndex;
        pathLength++;
        currentIndex = previous[currentIndex];
    }

    // Print the shortest path
    printf("\nShortest path from %s to %s:\n", cities[source], cities[destination]);
    for (int i = pathLength - 1; i >= 0; i--)
    {
        printf("%s ", cities[path[i]]);
        if (i != 0)
            printf("-> ");
    }
    printf("\nDistance: %d\n", distance[destination]);
    ShortestPathBFS=distance[destination];
}

int getIndex(char city[],int numCities){

    int i;
   for ( i = 0; i < numCities; i++)
        {
            if (strcmp(city, cities[i]) == 0)
                return i;
        }
         return -1;
}

void PrintToFile(char source[],char destination[]){

    FILE* output= fopen("shortest_distance.txt", "w");

     //fprintf(output,"  \n" );
     fprintf(output,"Shortest path from %s to %s: \n",source,destination);

        fprintf(output,"\n");
        fprintf(output,"Shortest distance in Dijkstra algorithms: %d km\n",ShortestPathDijkstra);
         fprintf(output,"Shortest distance in BFS algorithms: %d km\n",ShortestPathBFS);


}


void menu(){
     printf("\n-Select option:\n\n");
     printf("1-Load cities.\n");
     printf("2-Enter source.\n");
     printf("3-Enter destination.\n");
     printf("4-Exit.\n");
}

int main()
{
    printf("Hello world!\n");
     int numCities;
    char source[20];
    char destination[20];
    int indexOfSource=0;
     int indexOfDestination=0;

    int choice;
          menu();
     scanf("%d",&choice);

     while(choice != 5){

        switch(choice){

      case 1:
               // loadCities();
                numCities=loadCities();
                 printf("The file has been read\n\n");

            break;

      case 2:
             printf("Please Enter the source city: ");
                scanf("%s",source);
                 indexOfSource= getIndex(source, numCities);
                printf("\n %s   %d  \n",source, indexOfSource);


           break;

      case 3:
           printf("Please Enter the destination town: ");
              scanf("%s",destination);
                indexOfDestination= getIndex(destination, numCities);

                 printf("dijkstra: ");
                dijkstra(indexOfSource,indexOfDestination,numCities);
                printf("BFS: ");
                bfs(indexOfSource,indexOfDestination,numCities);

           break;
      case 4:
               PrintToFile(source,destination);

           break;

         default:
         printf("error!\n");
        }
        if(choice==4){
            choice=5;
        }else{
          menu();
        scanf("%d",&choice);
        }
     }



    return 0;
}
