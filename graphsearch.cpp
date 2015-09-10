#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
//#define NDEBUG
#include <cassert>
using namespace std;
static const bool dbg = true;
#define dout if(dbg)cout
typedef vector<list<int>> adjacency_list;

template<typename T>
void print_values(T begin, T end) {
  for(auto it=begin; it!=end; ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

/**
 * Reads an adjacency list from stdin with num_vertices vertices and
 * num_edges edges. This code assumes that input can be trusted to
 * be num_vertices lines of numbers on the form:
 * num_edges_for_this_vertex destination_1, destination2, ...
 * where num_edges is non_negative and every destination is >=1.
 * This function adds an opposing edge for every edge and therefore
 * assumes that the graph is undirected.
 */
adjacency_list read_graph_edges(int num_vertices, int num_edges) {
  int num_edges_for_this_vertex;
  adjacency_list graph(num_vertices+1); // Skip the 0-index for readability
  for(int current_vertex = 1; current_vertex <= num_vertices; ++current_vertex) {
    cin >> num_edges_for_this_vertex;
    assert(num_edges_for_this_vertex >= 0);
    for(int edge_num = 0; edge_num < num_edges_for_this_vertex; ++ edge_num) {
      int destination;
      cin >> destination;
      assert(1 <= destination && destination <= num_vertices); 
      graph.at(current_vertex).push_back(destination);
      graph.at(destination).push_back(current_vertex); //Remove this line for directed graphs
    }
  }
  return graph;
}

/*
 * Performs a depth first search through the graph, starting in the last corner,
 * printing the visited vertices along the way.
 */
void depth_first_search(const adjacency_list& graph, int num_vertices, int start_vertex) {
  dout << "dfs: ";
  vector<bool> is_visited(start_vertex);
  stack<int> next_destinations;
  next_destinations.push(start_vertex);
  while(next_destinations.size()!=0) {
    int current_vertex = next_destinations.top();
    dout << current_vertex << " ";
    next_destinations.pop();
    is_visited[current_vertex] = true;
    for(auto it = graph[current_vertex].begin(); it != graph[current_vertex].end(); ++it) {
      if(!is_visited[*it]) {
        next_destinations.push(*it);
        is_visited[*it] = true;
      }
    }
  }
  dout << endl;
}

void breadth_first_search(const adjacency_list& graph, int num_vertices, int start_vertex) {
  dout << "bfs: ";
  vector<bool> is_visited(start_vertex);
  queue<int> next_destinations;
  next_destinations.push(start_vertex);
  while(next_destinations.size()!=0) {
    int current_vertex = next_destinations.front();
    dout << current_vertex << " ";
    next_destinations.pop();
    is_visited[current_vertex] = true;
    for(auto it = graph[current_vertex].begin(); it != graph[current_vertex].end(); ++it) {
      if(!is_visited[*it]) {
        next_destinations.push(*it);
        is_visited[*it] = true;
      }
    }
  }
  dout << endl;


}

int main() {
  int num_vertices, num_edges;
  cin >> num_vertices >> num_edges;
  adjacency_list graph = read_graph_edges(num_vertices, num_edges);
  depth_first_search(graph, num_vertices, 2);
  breadth_first_search(graph, num_vertices, 2);
}
