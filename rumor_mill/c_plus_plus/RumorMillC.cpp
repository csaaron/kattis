#include "vertex_dist_pair.h"
#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

/***************************************************************************/
typedef std::set<std::string> string_set;
typedef std::map<std::string, string_set> set_map;
typedef std::map<std::string, int> int_map;
typedef std::map<std::string, std::string> string_map;
typedef std::vector<std::string> string_vector;
typedef std::queue<std::string> string_queue;
typedef std::set<vertex_dist_pair> vert_dist_set;

/***************************************************************************/
void read_input(set_map & graph, string_vector & reports, std::istream & stream);
void print_report(const string_vector & report);
int_map breadth_first_search(const set_map & graph, const std::string & source);
string_vector sort_report(const int_map & distances);
void add_edge_to_undirected_graph(const std::string & vertice1, const std::string & vertice2, set_map & graph);

/***************************************************************************/


 /***
  * Reads in a data file from the problem found at
  * https://utah.kattis.com/problems/utah.rumormill
  * and outputs the described rumor reports.
  * If no command line argument is given, reads input from the commandline
  * else, attempts to read input from the filename given as the first commandline
  * argument.
  **/
int main(int argc, char** argv)
{
  
  // student_graph is an undirected graph which may contain cycles
  // represented as an adjacency list
  set_map student_graph;

  // contains the reports needed for processing
  string_vector reports;

  // read inputs and store the graph and 
  // reports for later processing
  
  if (argc > 1)
  {
    std::ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile)
    {
      exit(1); // exit with error
    }

    read_input(student_graph, reports, inFile);

    inFile.close();
  }
  else
  {
    read_input(student_graph, reports, std::cin);
  }

  string_vector::iterator it = reports.begin();
  string_vector::iterator end = reports.end();
  // get source from reports
  for (it; it != end; it++)
  {
    // git a map of distances from source
    int_map distances = breadth_first_search(student_graph, *it);

    // sort distances
    string_vector sorted_report = sort_report(distances);
    print_report(sorted_report);
  }
}

/***
 * Reads input from the command line and constructs a graph with students as
 * vertices and friendships as edges. Also stores the reports to be processed.
 **/
void read_input(set_map & graph, string_vector & reports, std::istream & stream)
{
  // read in all vertices
  int n;
  stream >> n;
  for (int i = 0; i < n; i++)
  {
    // initialize vertice of graph with an empty set
    std::string vertex;
    stream >> vertex;
    graph[vertex] = string_set();
  }

  // read in all edges
  int f;
  stream >> f;
  for (int i = 0; i < f; i++)
  {
    std::string vertex1;
    std::string vertex2;
    stream >> vertex1;
    stream >> vertex2;
    add_edge_to_undirected_graph(vertex1, vertex2, graph);
  }

  // read in reports
  int r;
  stream >> r;
  for (int i = 0; i < r; i++)
  {
    std::string source;
    stream >> source;
    reports.push_back(source);
  }
}


/***
 * Print one report on its own line consisting of each name followed by one space
 **/
void print_report(const string_vector & report)
{
  int report_length = report.size();
  for (int i = 0; i < report_length; i++)
  {
    std::cout << report[i];
    if (i < report_length - 1)
    {
      std::cout << " ";
    }
  }

  std::cout << std::endl;
}

/***
 * Takes a graph and a source and returns a int_map keyed by the graphs
 * vertices matched to their distances from source. If the distance from source
 * to another vertex is infinite, the distance will be represented as -1
 **/
int_map breadth_first_search(const set_map & graph, const std::string & source)
{
  int_map distances;
  string_map previous;

  // initialize distances and previous
  set_map::const_iterator it = graph.begin();
  set_map::const_iterator end = graph.end();
  for (it; it != end; it++)
  {
    distances[it->first] = -1;
    previous[it->first] = "";
  }

  // a queue for the bfs
  string_queue q;

  //start at the given source
  q.push(source);
  distances[source] = 0;

  while (!q.empty())
  {
    // get the vertex from the queue
    std::string vertex = q.front();
    q.pop();

    // explore each edge
    string_set::const_iterator edge = graph.at(vertex).begin();
    string_set::const_iterator end = graph.at(vertex).end();

    for (edge; edge != end; edge++)
    {
      // if distance is still infinite 
      if (distances.at(*edge) < 0) // this is the problem
      {
        q.push(*edge);
        distances[*edge] = distances[vertex] + 1;
        previous[*edge] = vertex;
      }
    }
  }

  return distances;
}

/***
 * Takes an int_map containing all vertices of graph and their distances from
 * the source and sorts them first by distance, then lexicographically
 **/
string_vector sort_report(const int_map & distances)
{
  // initialize vector with keys from distances
  vert_dist_set sorted_set;
  {
    int_map::const_iterator it = distances.begin();
    int_map::const_iterator end = distances.end();
    for (it; it != end; it++)
    {
      vertex_dist_pair pair(it->first, it->second);
      sorted_set.insert(pair);
    }
  }

  string_vector report;
  {
    vert_dist_set::const_iterator it = sorted_set.begin();
    vert_dist_set::const_iterator end = sorted_set.end();
    for (it; it != end; it++)
    {
      report.push_back(it->get_vertex());
    }
  }

  return report;
}

/***
 * Takes two vertices and adds them to graph as an undirected edge
 **/
void add_edge_to_undirected_graph(const std::string & vertice1, const std::string & vertice2, set_map & graph)
{
  graph[vertice1].insert(vertice2);
  graph[vertice2].insert(vertice1);
}