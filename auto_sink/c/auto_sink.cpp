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

string_vector linearize_graph(const adjacency_list & graph, const std::string & source);

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
  string_int_map toll_map = string_int_map(); // allows look up of tolls by city name
  adjacency_list city_graph = adjacency_list(); // an adjacency list represention of the given graph
  adjacency_list reverse_city_graph = adjacency_list(); // a reverse graph for easy lookup of sources
  
  // read in city and toll information

  // get number of cities 
  int n = 0;
  std::cin >> n;
  // read in each city
  for (int i = 0; i < n; i++)
  {
    // read in line    
    std::string city;
    int toll;
    std::cin >> city;    
    std::cin >> toll;
    
    // creat entry for toll
    toll_map.insert(std::pair<std::string,int>(city, toll));  
    
    // initialize vertice of graphs with an empty set
    city_graph.insert(std::pair<std::string, std::set<std::string> >(city, std::set<std::string>()));
    reverse_city_graph.insert(std::pair<std::string, std::set<std::string> >(city, 
      std::set<std::string>()));
  }

  // get number of highways
  int h = 0;
  std::cin >> h;
  for (int i = 0; i < h; i++)
  {
    std::string edge_from;
    std::cin >> edge_from;
    
    std::string edge_to;    
    std::cin >> edge_to;

    city_graph[edge_from].insert(edge_to);
    reverse_city_graph[edge_to].insert(edge_from);
  }

  // read in trips
  int t = 0;
  std::cin >> t;
  for (int i = 0; i < t; i++)
  { 
    std::string source;
    std::cin >> source;
    
    std::string sink;
    std::cin >> sink;
    
    // linearize graph from source, then calculate cost of trip
    string_vector linear_dag = linearize_graph(city_graph, source);
    int cost = get_trip_cost(linear_dag, reverse_city_graph, toll_map, source, sink);
    
    // print cost of trip    
    std::cout << cost << std::endl;
  }
}

/**
 * Driver method for explore. Explores the graph starting from the given vertice
 * and excludes non connected elements and elements not accesable from source. Places
 * explored vertices in linearized_dag in topological order.
 */
string_vector linearize_graph(const adjacency_list & graph, const std::string & source)
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
