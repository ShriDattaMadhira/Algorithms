//
//  main.cpp
//  Push-Relabel-C++
//
//  Created by Shri Datta Madhira on 4/22/21.
//

#include <iostream>
#include <vector>

using namespace std;
  
struct Edge
{
    int flow, capacity, u, v;
  
    Edge(int flow, int capacity, int u, int v)
    {
        this->flow = flow;
        this->capacity = capacity;
        this->u = u;
        this->v = v;
    }
};

struct Vertex
{
    int height, excess;
  
    Vertex(int h, int e)
    {
        this->height = h;
        this->excess = e;
    }
};

class Graph
{
    int V;
    vector<Vertex> vertexes;
    vector<Edge> edges;
    
    bool push(int u);
    void relabel(int u);
    // initialize preflow
    void preflow(int s);
    void updateReverseEdgeFlow(int i, int flow);
  
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    int getMaxFlow(int s, int t);
};
  
Graph::Graph(int V)
{
    this->V = V;
    // All vertices are initialized with 0 height and 0 excess flow
    for (int i = 0; i < V; i++)
        vertexes.push_back(Vertex(0, 0));
}
  
void Graph::addEdge(int u, int v, int capacity)
{
    // flow is initialized with 0 for all edge
    edges.push_back(Edge(0, capacity, u, v));
}
  
void Graph::preflow(int s)
{
    // Making h(s) = |V| and h(V-{s}) = 0.
    vertexes[s].height = int(vertexes.size());
    
    for (int i = 0; i < edges.size(); i++)
    {
        // If current edge goes from source
        if (edges[i].u == s)
        {
            // Flow is equal to capacity
            edges[i].flow = edges[i].capacity;
            // Initialize excess flow for adjacent v
            vertexes[edges[i].v].excess += edges[i].flow;
            // Add an edge from v to s in residual graph with capacity equal to 0
            edges.push_back(Edge(-edges[i].flow, 0, edges[i].v, s));
        }
    }
}
  
// returns index of overflowing Vertex
int vertex_with_excess(vector<Vertex>& ver)
{
    for (int i = 1; i < ver.size() - 1; i++)
       if (ver[i].excess > 0)
            return i;
    return -1;
}
  
// Update reverse flow for flow added on ith Edge
void Graph::updateReverseEdgeFlow(int i, int flow)
{
    int u = edges[i].v, v = edges[i].u;
  
    for (int j = 0; j < edges.size(); j++)
    {
        if (edges[j].v == v && edges[j].u == u)
        {
            edges[j].flow -= flow;
            return;
        }
    }
    // adding a new reverse Edge in residual graph.
    edges.push_back(Edge(0, flow, u, v));
}
  
// To push flow from overflowing vertex u.
bool Graph::push(int u)
{
    // Traverse through all edges to find an adj(u) to which flow can be pushed.
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].u == u)
        {
            // Checking if the edge is already saturated or not.
            if (edges[i].flow == edges[i].capacity)
                continue;
  
            // Checking the height constraint.
            if (vertexes[u].height > vertexes[edges[i].v].height)
            {
                // Push minimum of residual capacity on edge and excess flow.
                int flow = min(edges[i].capacity - edges[i].flow, vertexes[u].excess);
                // Reduce excess flow for overflowing vertex.
                vertexes[u].excess -= flow;
                // Increase excess flow for adjacent.
                vertexes[edges[i].v].excess += flow;
                // Increase the flow across the chosen edge.
                edges[i].flow += flow;
                // Add residual flow (With capacity 0 and negative flow).
                updateReverseEdgeFlow(i, flow);
                return true;
            }
        }
    }
    return false;
}
  
// function to relabel vertex u
void Graph::relabel(int u)
{
    // Initialize minimum height of an adjacent
    int mh = INT_MAX;
    // Find the adjacent with minimum height
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].u == u)
        {
            // if flow is equal to capacity then no relabeling
            if (edges[i].flow == edges[i].capacity)
                continue;
            // Update minimum height
            if (vertexes[edges[i].v].height < mh)
            {
                mh = vertexes[edges[i].v].height;
                // updating height of u
                vertexes[u].height = mh + 1;
  
            }
        }
    }
}
  
//printing maximum flow of graph
int Graph::getMaxFlow(int s, int t)
{
    preflow(s);
    // loop untill none of the Vertex is in overflow
    while (vertex_with_excess(vertexes) != -1)
    {
        int u = vertex_with_excess(vertexes);
        if (!push(u))
            relabel(u);
    }
    //.back() returns last Vertex, whose e_flow will be final maximum flow
    return vertexes.back().excess;
}

int main(int argc, const char * argv[]) {
    int V = 6;
    Graph g(V);
  
    // Creating above shown flow network
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(2, 1, 4);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 12);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);
  
    // Initialize source and sink
    int s = 0, t = 5;
  
    cout << "Maximum flow is " << g.getMaxFlow(s, t) << endl;
    return 0;
}
