// Written by Aaron Bellis Kattis RumorMill problem found at https://utah.kattis.com/problems/utah.rumormill

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RumorMill
{
    class Program
    {
        /// <summary>
        /// Rumor Mill reads students, friends and needed reports from console then prints in the order
        /// rumors are spread the results of the spread rumor. 
        /// </summary>
        static void Main(string[] args)
        {
            // studentGraph is an undirected graph which may contain cycles
            // represented as an adjacency list.
            Dictionary<string, HashSet<string>> studentGraph = new Dictionary<string, HashSet<string>>();

            // reports contains the reports needed for processing by the rumormill problem
            LinkedList<string> reports = new LinkedList<string>();

            // read inputs from the command line and store the graph 
            // and reports for later.
            ReadInput(studentGraph, reports);

            // do a breadth-first search and get distances from sources 
            foreach (string source in reports)
            {
                Dictionary<string, int> distances = BreadthFirstSearch(studentGraph, source);
                // sort distances
                List<string> sortedReport = SortReport(distances);
                PrintReportToConsole(sortedReport);
            }

        }

        /// <summary>
        /// Prints each name in the report followed by a space to the console on its own line
        /// </summary>
        private static void PrintReportToConsole(List<string> report)
        {
            for (int i = 0; i < report.Count; i++)
            {
                Console.Write(report[i]);

                // don't write a space after the last output
                if (i < report.Count - 1)
                {
                    Console.Write(" ");
                }
            }

            Console.WriteLine();
        }

        /// <summary>
        /// Takes a dictionary containing all virtices of graph and their distances from the sorce and 
        /// sorts them first by distance, then lexicographically
        /// </summary>
        private static List<string> SortReport(Dictionary<string, int> distances)
        {
            List<string> sortedReport = new List<string>(distances.Keys);
            sortedReport.Sort((x, y) => ReportComparer(x, y, distances));
            return sortedReport;
        }

        /// <summary>
        /// Reads input from the command line and constructs a graph, with the students as nodes, and 
        /// friendships as edges. Also stores the reports needed to be processed
        /// </summary>
        private static void ReadInput(Dictionary<string, HashSet<string>> students, LinkedList<string> reports)
        {

            // get number of students
            int n = 0;
            int.TryParse(Console.ReadLine(), out n);
            // check for malformed input
            if (n < 1)
            {
                throw new FormatException();
            }

            // read in all students
            for (int i = 0; i < n; i++)
            {
                // read the line and split it up
                string student = Console.ReadLine();

                // add the student to the graph
                HashSet<string> edges = new HashSet<string>();
                students.Add(student, edges);
            }

            int f = -1;
            int.TryParse(Console.ReadLine(), out f);

            // check for malformed input
            if (f < 0)
            {
                throw new FormatException();
            }

            // read all the friends
            for (int i = 0; i < f; i++)
            {
                // read the line and split it up
                string line = Console.ReadLine();
                string[] tokens = line.Split(' ');

                // parse the friends
                string student = tokens[0];
                string friend = tokens[tokens.Length - 1];

                AddFriendshipToGraph(students, student, friend);
            }

            // read reports
            int r = 0;
            int.TryParse(Console.ReadLine(), out r);

            // check for malformed input
            if (r < 1)
            {
                throw new FormatException();
            }

            // read all the reports
            for (int i = 0; i < r; i++)
            {
                // read the line and split it up
                string report = Console.ReadLine();

                reports.AddLast(report);
            }
        }

        /// <summary>
        /// Takes two strings which represents friends and adds them to the graph as an 
        /// undirected edge. 
        /// </summary>
        private static void AddFriendshipToGraph(Dictionary<string, HashSet<string>> graph, 
            string friend1, string friend2)
        {

            HashSet<string> edges;
            if (graph.TryGetValue(friend1, out edges))
            {
                edges.Add(friend2);
            }

            if (graph.TryGetValue(friend2, out edges))
            {
                edges.Add(friend1);
            }
        }

        /// <summary>
        /// takes a graph and a source and returns a dictionary keyed by the graphs vertices and looks up 
        /// their distances. If the distance from source to another vertex is infinite, the distance will
        /// be represented as -1
        /// </summary>
        private static Dictionary<string, int> BreadthFirstSearch(Dictionary<string, HashSet<string>> graph, string source)
        {
            // dictionary keyed by the name of the student, which looks up the distance from the source
            // all distances must be positive, initial value, infinity, is represented by -1
            Dictionary<string, int> distance = new Dictionary<string, int>();

            // dictionary keyed by the name of the student which looks up the previous node in the search
            // if no previous node, value will be represented by null
            Dictionary<string, string> previous = new Dictionary<string, string>();

            // initialize the structures
            foreach (string key in graph.Keys)
            {
                distance.Add(key, -1);
                previous.Add(key, null);
            }

            // a queue used to perform the breadth first search
            Queue<string> queue = new Queue<string>();
            // add source of search to queue
            queue.Enqueue(source);
            // distance from source should be 0
            distance[source] = 0;
            
            while (queue.Count != 0)
            {
                // get the virtex
                string vertex = queue.Dequeue();

                // explore each edge
                HashSet<string> edges = graph[vertex];
                foreach (string edge in edges)
                {

                    if (distance[edge] < 0) // if distance is infinity
                    {
                        queue.Enqueue(edge);
                        distance[edge] = distance[vertex] + 1;
                        previous[edge] = vertex;
                    }
                }
            }

            // bfs is now complete, return the distance dictionary
            return distance;
        }

        /// <summary>
        /// compares two strings. If the distance of x is greater than the distance of y from the 
        /// source returns 1. If the distance of y is greater than the distance from x, returns -1.
        /// If the distances are equal returns the result of string.Compare(x,y)
        /// </summary>
        private static int ReportComparer(string x, string y, Dictionary<string, int> distance)
        {
            int distX = distance[x];
            int distY = distance[y];

            // if both are the same return lexicographical order
            if (distX == distY)
            {
                return string.Compare(x, y);
            }

            // at least one is not negative and because representation says -1 is infinity this looks inverse
            // check for negatives
            if (distX < 0)
            {
                return 1;
            }

            if (distY < 0)
            {
                return -1;
            }

            // both are at least 0 and not equal
            if (distX < distY)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
            
    }
}
