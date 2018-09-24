from queue import Queue
from functools import cmp_to_key

###
# Reads in a data file fro the problem found at 
# https://utah.kattis.com/problems/utah.rumormill 
# and outputs the described rumor reports
# Author: Aaron Bellis
##
def main():
    # studentGraph is an undirected graph whcih may contain cycles
    # represented as an adjacency list
    student_graph = {}

    # contains the rports needed for processing
    reports = []

    # read inputs from the command line and store the graph and reports for later
    readInput(student_graph, reports)

    # do a breadth-first search and get distances from sources
    for source in reports:
        distances = breadthFirstSearch(student_graph, source)
        # sort distances
        sorted_report = sortReport(distances)
        printReportToConsole(sorted_report)


###
# Reads input from the command line and constructs a graph with students as 
# vertices and friendships as edges. Also stores the reports to be processed.
##
def readInput(graph, reports):
    # read in all vertices
    n = int(input(""))
    for i in range(n):
        #initialize vertice of graph with an empty set
        vertice = input("")
        graph[vertice] = set()
    
    # read in all edges
    f = int(input(""))
    for i in range(f):
        line = input("")
        split_line = line.split(" ")
        addEdgeToUndirectedGraph(split_line[0], split_line[1], graph)

    # read in reports
    r = int(input(""))
    for i in range(r):
        reports.append(input(""))

    return None


###
# Print one report on its own line consisting of each name followed by one space
##
def printReportToConsole(report):

    report_length = len(report)
    for i in range(report_length):
        print(report[i], end = "")
        
        # don't write space after last name
        if i < report_length -1:
            print(" ", end = "")

    print("")
    return None


###
# Takes a graph and a source and returns a dictionary keyed by the graphs
# vertices matched to their distances from source. If the distance from source
# to another vertex is infinite, the distance will be represented as -1  
##
def breadthFirstSearch(graph, source):
    # dictionary keyed by the vertice, which looks up the distance from the 
    # source all distances must be positive. Initial value and infinite is 
    # represented by -1  
    distance = {}

    # dictionary keyed by the vertice which looks up the previous node in the 
    # search. If no previous node, value will be represented by None
    previous = {}

    # initialize structures
    for key in graph:
        distance[key] = -1
        previous[key] = None
    
    # a queue for the bfs
    q = Queue()

    #start at the source
    q.put(source)
    distance[source] = 0

    while not q.empty():
        # get vertex from queue
        vertex = q.get()

        # explore each edge
        for edge in graph[vertex]:
            if distance[edge] < 0: # if distance is infinite
                q.put(edge)
                distance[edge] = distance[vertex] + 1
                previous[edge] = vertex

    # bfs is complete, return distance dictionary
    return distance


###
# Takes a dictionary containing all virtices of graph and their distances from
# the source and sorts them first by distance, then lexicographically
##
def sortReport(distances):
    sorted_report = list(distances.keys())
    sorted_report.sort(key=cmp_to_key(lambda x, y: compareReport(x, y, distances)))
    return sorted_report


###
# Takes two vertices and adds them to graph as an undirected edge 
##
def addEdgeToUndirectedGraph(vertice1, vertice2, graph):
    graph[vertice1].add(vertice2)
    graph[vertice2].add(vertice1)
    return None


###
# Compares two strings. If the distance of str1 is greater than the distance of str2
# from the source, returns 1. If the distance of str2 is greater than the distance
# from str1, returns -1. If the distances are equal, returns the result of
# comparing str1 to str2.
##
def compareReport(str1, str2, distance):
    dist1 = distance[str1]
    dist2 = distance[str2]
     
    # if both are same return lexicographical order
    if dist1 == dist2:
        if str1 < str2:
            return -1
        elif str1 > str2:
            return 1
        else:
            return 0

    # if the distance of one is negative, then at least one of them is infinity
    # this means a negative number from dist1 should be bigger than dist2
    if dist1 < 0:
        return 1
    # if dist2 is negative, dist1 should come before it
    if dist2 < 0:
        return -1

    # this is regular sorting because neither is infinite
    if dist1 < dist2:
        return -1 
    else:
        return 1


###
# runs the main function when the program is launched
##
if __name__=="__main__":
    main()