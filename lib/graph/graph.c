#include <stdlib.h>

#include "graph.h"
#include "./../list/list.h"

#define INFINITY 4.3e+9F; // max 4 bytes value

Graph *graph_create(int size){

    Graph *graph = malloc(sizeof(graph));

    if(graph == NULL){
        return NULL;
    }

    graph->vertices = size;

    // neighbours is a 2d Matrix
    List **neighbours = calloc(size, sizeof(List*));

    if(neighbours == NULL){
        return NULL;
    }

    graph->neighbours = neighbours;

    return graph;

}
void graph_destroy(Graph *graph){

    if(graph == NULL){
        return;
    }

    for(int i = 0; i < graph->vertices; i++){
        List *neighbour = graph->neighbours[i];
        if(neighbour == NULL){
            continue; // Forces next iteration
        }

        list_destroy(neighbour); // Deleting all the neighbors
    }

    // Freeing Memory
    free(graph->neighbours);
    free(graph);

}
void graph_add_edge(Graph *graph, int node1, int node2, float weight){

    int verticesCount = graph->vertices;

    if(graph == NULL || (node1 < 0 || node1 >= verticesCount) || (node2 < 0 || node2 >= verticesCount)){
        return;
    }

    List *neighbour = graph->neighbours[node1]; // defines the source node's neighbors
    if(neighbour == NULL){
        neighbour = list_create();
        if(neighbour == NULL){
            return;
        }
        graph->neighbours[node1] = neighbour; // if there are no neighbors sets the node neigbors to an empty list
    }

    Edge *edge = malloc(sizeof(Edge)); // create a new edge
    edge->node = node2; // sets the target node
    edge->weight = weight;

    list_append(neighbour, edge);

}

/// @brief Performs the Dijkstra algorithm on a graph
/// @param graph The graph on which the algorithm is performed
/// @param node1 The source node
/// @param node2 The target node
/// @returns The shortest distance from the source node to the target node | -1 if no path is found
float graph_dijkstra(Graph *graph, int node1, int node2){

    int vertices = graph->vertices;

    if(graph == NULL || (node1 < 0 || node1 >= vertices) || (node2 < 0 || node2 >= vertices)){
        return -1;
    }

    Edge *minEdge = malloc(sizeof(Edge));
    if(minEdge == NULL){
        return -1;
    }

    float distances[vertices];
    int explored[vertices]; // keeps track of all explored nodes : 1 -> explored | 0 -> unexplored

    if(distances == NULL || explored == NULL){
        return -1;
    }

    // initial conditions
    for(int i = 0; i < vertices; i++){
        distances[i] = INFINITY;
        explored[i] = 0;
    }

    // setting up the source node values
    distances[node1] = 0;
    explored[node1] = 1;

    List *currentNeighbours = graph->neighbours[node1];

    float currentDistance = 0; // current distance from source node

    while(currentNeighbours != NULL){

        // Update all distances to the source by looping through all the current node's neighbours
        for(ListNode *neighbourNode = currentNeighbours->debut; neighbourNode != NULL; neighbourNode = neighbourNode->next){
            Edge *edge = (Edge*) neighbourNode->value;

            float totalDistance = currentDistance + edge->weight;

            // if that neigbour hasn't been visited and the calculated distance is less than it's current distanec
            if(explored[edge->node] == 0 && totalDistance < distances[edge->node]){

                distances[edge->node] = totalDistance; // we update the distance for that edge
            }
        }

        // Find the node with smallest distance
        minEdge->node = -1;
        minEdge->weight = INFINITY;
        for(int i = 0; i < vertices; i++){
            if(explored[i] == 0 && distances[i] < minEdge->weight){
                minEdge->node = i;
                minEdge->weight = distances[i];
            }
        }

        explored[minEdge->node] = 1; 

        if(minEdge->node == node2){
            break; // The distance to the target has been found
        }

        currentNeighbours = graph->neighbours[minEdge->node]; // Continue the search from that node
        currentDistance = minEdge->weight; // Update the current distance to the source node
    }

    free(minEdge);

    if(explored[node2] == 0){
        return -1; // No path exists
    }
    else{
        return distances[node2]; // returns the shortest distance to the target
    }
}