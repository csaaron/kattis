#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>

#define MAX_INT 2147483647

/****** typedefs for complicated data types ******/

typedef std::map<std::string, int> string_int_map;
typedef std::vector<std::string> string_vector;
typedef std::map<std::string, std::set<std::string> > adjacency_list;

/****** pre declared methods ******/

void linearize_graph(const adjacency_list & graph, const std::string & source, 
  string_vector linearized_dag);

void explore(const adjacency_list & graph, const std::string & vertice, string_vector & visited,
  string_vector & reverse_linearized_dag);

int get_trip_cost(const string_vector & linear_graph, const adjacency_list & reverse_graph,
  const string_int_map & tolls, const std::string & source, const std::string & sink);

int get_lowest_cost_source(const std::set<std::string> & sources, const string_int_map & cost_map);

/****** method definitions ******/

/**
 * Reads in a data file from std input stream for the problem found at
 * https://utah.kattis.com/problems/utah.autosink
 * and determines the minimum cost of each given trip
 */
int main(int argc, char** argv)
{

}

/**
 * Driver method for explore. Explores the graph starting from the given vertice
 * and excludes non connected elements and elements not accesable from source. Places
 * explored vertices in linearized_dag in topological order.
 */
void linearize_graph(const adjacency_list & graph, const std::string & source, 
  string_vector linearized_dag)
{

}

/**
 * Recursively explores all unexplored edges leading from vertice and places discovered vertices
 * into reverse_linearized_dag in reverse topological order.
 */
void explore(const adjacency_list & graph, const std::string & vertice, string_vector & visited,
  string_vector & reverse_linearized_dag)
{

}

/**
 * Returns the minimum cost to travel from source to sink. If source == sink 
 * cost is 0. If it is not possible to travel from source to sink returns MAX_INT
 */
int get_trip_cost(const string_vector & linear_graph, const adjacency_list & reverse_graph,
  const string_int_map & tolls, const std::string & source, const std::string & sink)
{

}

/**
 * returns value of the lowest cost source. If no sources exist in cost_dictionary, returns
 * MAX_INT
 */ 
int get_lowest_cost_source(const std::set<std::string> & sources, const string_int_map & cost_map)
{

}
