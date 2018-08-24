###
# Reads in a data file for the problem found at https://utah.kattis.com/problems/utah.autosink
# and determines the minimum cost of each given trip
##
def main():

    # create a dictionary of cities and tolls
    toll_dictionary = {}
    # may as well get adjacency list representation of graph 
    city_graph = {}
    # a reverse graph for easy lookup of sources
    reverse_city_graph = {}
    
    # read in city and toll information
    
    # get number of cities
    n = int(input(""))
    for i in range(n):
        line = input("") 
        split_line = line.split(" ")
        #add city and toll to dictionary
        toll_dictionary[split_line[0]] = int(split_line[1])
        #initialize vertice of graph with an empty set
        city_graph[split_line[0]] = set()
        reverse_city_graph[split_line[0]] = set()

    # read number of highways
    h = int(input(""))

    # create adjacency list representation of graph from highways
    for i in range(h):
        line = input("")
        split_line = line.split(" ")
        # get a set of all edges leading from city
        edges = city_graph[split_line[0]]
        # add edge to set
        edges.add(split_line[1])

        # create the reverse graph
        reverse_edges = reverse_city_graph[split_line[1]]
        reverse_edges.add(split_line[0])

    # read number of trips
    t = int(input(""))

    # calculate cost of all trips
    for i in range(t):
        line = input("")
        split_line = line.split(" ")
        linearDag = linearizePartialGraph(city_graph, split_line[0])
        cost = getMinToll(linearDag, reverse_city_graph, toll_dictionary, split_line[0], split_line[1])
        print(cost)


###
# Driver method for explore. Explores the graph starting from the given vertice
# and excludes non connected elements and elements not accesable from source
##
def linearizePartialGraph(Graph, source):
    # if graph is empty, return 0
    if len(Graph) is 0:
        return set();
    if source not in Graph:
        return set();

    #create a set for visited vertice
    visited = set()
    #create storage for a linearized dag
    linearized_dag = []

    # explore from source
    explore(Graph, source, visited, linearized_dag)
    
    # reverse graph so it is in topological order
    linearized_dag.reverse()
    # return linearized dag
    return linearized_dag

###
# Recursively explores all unexplored edges leading from vertice and places discovered vertices
# into reverse_linearized_dag in reverse topological order.
##
def explore(Graph, vertice, visited, reverse_linearized_dag):
    # mark vertice as visited
    visited.add(vertice)
    
    # do previsit action none in this case

    # for each edge (v, u) in E (set of edges from v)
    edges = Graph[vertice]
    for u in edges:
        if u not in visited:
            explore(Graph, u, visited, reverse_linearized_dag)

    # do post visit action
    reverse_linearized_dag.append(vertice)


###
# Returns the minimum cost to travel from source to sink. If source == sink 
# cost is 0. If it is not possible to travel from source to sink returns NO
##
def getMinToll(linear_graph, reverse_graph,  tolls, source, sink):
    # if sink is not in linear_graph  can return no
    if sink not in linear_graph:
        return "NO"
    
    # if source == sink, no need to check further
    if source == sink:
        return 0

    source_index = int(linear_graph.index(source))
    sink_index = int(linear_graph.index(sink))

    if sink_index < source_index:
        return "NO"
    
    #initialize a cost dictionary
    cost_dictionary = {}
    MAX_INT = 2147483647
    for city in linear_graph:
        cost_dictionary[city] = MAX_INT
    cost_dictionary[source] = 0
    
    for i in range(1, len(linear_graph)):
        city = linear_graph[i]
        
        # get sources from reverse_graph
        sources = reverse_graph[city]
        
        source_cost = getLowestCostSource(sources, cost_dictionary)

        if source_cost is "NO":
            cost_dictionary[city] = "NO"
        else:
            # cost = toll of this city + the lesser cost of its sources
            cost = tolls[city]
            cost += source_cost
            cost_dictionary[city] = cost
    
    # at this point we should have taken care of all possible reasons that a trip isn't
    # possible and we can return the cost of this trip
    return cost_dictionary[sink]

### 
# returns value of the lowest cost source. If no sources exist in cost_dictionary, returns 0
##
def getLowestCostSource(sources, cost_dictionary):
    if len(sources) < 1:
        return "NO"

    # initialize s_cost to max int
    source_cost = 2147483647
    encounter_no = False

    # find the lowest cost
    for s in sources:
        if s in cost_dictionary and cost_dictionary[s] is "NO":
            encounter_no = True
        elif s in cost_dictionary and cost_dictionary[s] < source_cost:
            source_cost = cost_dictionary[s]
    
    # if the max cost is still set and we haven't found a no in the cost dictionary
    if source_cost is 2147483647 and not encounter_no:
        source_cost = 0
    # if the max cost is still set and we have found a no in the cost dictionary
    elif source_cost is 2147483647 and encounter_no:
        source_cost = "NO"

    return source_cost

## runs the main function when program is run
if __name__=="__main__":
    main()
