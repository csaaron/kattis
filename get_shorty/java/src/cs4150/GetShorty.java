/**
 * Java Solution for kattis GetShorty found at 
 * https://utah.kattis.com/problems/getshorty
 * Author Aaron Bellis. 
 * Requires WeightedContainer.java found in this package
 */
package cs4150;

import java.io.Console;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Set;

import javax.swing.plaf.synth.SynthSpinnerUI;

public class GetShorty
{

	public static void main (String[] args)
	{
		ArrayList<HashMap<Integer, HashMap<Integer, Double>>> testCases;
		readInput();
	}

	/**
	 * Prints the result of the GetShorty search
	 */
	private static void printResult (double result)
	{
		System.out.printf("%.4f\n", result);
	}

	/**
	 * Reads input from the command line and constructs all graphs, with the
	 * intersections as nodes, and corridors as edges. Returns a list of all
	 * graphs
	 */
	private static void readInput ()
	{
		// storage for all graphs from input
		ArrayList<HashMap<Integer, HashMap<Integer, Double>>> graphs;
		graphs = new ArrayList<HashMap<Integer, HashMap<Integer, Double>>>();

		int numOfIntersections = -1;
		int numOfCorridors = -1;

		// make sure scanner is closed
		try (Scanner console = new Scanner(System.in))
		{
			while (numOfCorridors != 0 && numOfIntersections != 0)
			{

				String[] line = console.nextLine().split(" ");
				numOfIntersections = Integer.parseInt(line[0]);
				numOfCorridors = Integer.parseInt(line[line.length - 1]);

				// create storage for a single graph
				HashMap<Integer, HashMap<Integer, Double>> intersections;
				intersections = new HashMap<Integer, HashMap<Integer, Double>>();
				// read in all corridors
				for (int i = 0; i < numOfCorridors; i++)
				{
					// read the line and split it up
					String[] corridor = console.nextLine().split(" ");

					// parse line into data
					int entrance = Integer.parseInt(corridor[0]);
					int exit = Integer.parseInt(corridor[1]);

					double factor = Double.parseDouble(corridor[2]);

					// add the corridor to the graph
					addCorridor(entrance, exit, factor, intersections);
				}

				if (!intersections.isEmpty())
				{
					double result = dijkstraSearch(intersections, 0, numOfIntersections - 1);
					printResult(result);
				}
			}
		}

	}

	/**
	 * Adds a corridor to the graph represented by intersections.
	 */
	private static void addCorridor (int entrance, int exit, double factor,
			HashMap<Integer, HashMap<Integer, Double>> intersections)
	{
		addEdgeToDirectedGraph(entrance, exit, factor, intersections);
		addEdgeToDirectedGraph(exit, entrance, factor, intersections);
	}

	/**
	 * Takes two integers representing vectors in weightedGraph along with a
	 * weight and adds an edge from vectorA to VectorB with the corresponding
	 * weight to the graph.
	 */
	private static void addEdgeToDirectedGraph (int vectorA, int vectorB, double weight,
			HashMap<Integer, HashMap<Integer, Double>> weightedGraph)
	{

		if (weightedGraph.containsKey(vectorA))
		{
			HashMap<Integer, Double> edges = weightedGraph.get(vectorA);
			edges.put(vectorB, weight);
		}
		else
		{
			HashMap<Integer, Double> edges = new HashMap<Integer, Double>();
			edges.put(vectorB, weight);
			weightedGraph.put(vectorA, edges);
		}
	}

	/**
	 * Takes in a weightedGraph and traverses it using Dijkstra's algorithm.
	 * Returns when the algorithm can no longer continue or the goal is reached.
	 * Returns the cheapest cost of traversing the graph from sourceVector to
	 * goalVector
	 * 
	 * @param weightedGraph
	 *            - a graph with weights between 0 and 1
	 * @param source
	 *            - the vector to begin the search
	 * @param goal
	 *            - the vector to end the search
	 * @return the cost of traversing the graph
	 */
	private static double dijkstraSearch (HashMap<Integer, HashMap<Integer, Double>> weightedGraph,
			int sourceVector, int goalVector)
	{
		// dictionary keyed by the name of the vector, which looks up the
		// distance from the source
		// all distances must be positive, initial value, infinity, is
		// represented by -1
		HashMap<Integer, Double> distance = new HashMap<Integer, Double>(weightedGraph.size());

		// dictionary keyed by the name of the vector which looks up the
		// previous node in the search
		// if no previous node, value will be represented by -1
		HashMap<Integer, Integer> previous = new HashMap<Integer, Integer>(weightedGraph.size());

		// initialize the structures
		Set<Integer> graphKeys = weightedGraph.keySet();
		for (Integer key : graphKeys)
		{
			distance.put(key, 0.0);
			previous.put(key, -1);
		}

		// a PriorityQueue used to perform Dijkstra's algorithm
		PriorityQueue<WeightedContainer> queue;
		queue = new PriorityQueue<WeightedContainer>();
		// add source of search to queue
		insertOrChange(sourceVector, 1.0, queue);
		distance.put(sourceVector, 1.0);

		while (!queue.isEmpty())
		{
			// get the vertex
			WeightedContainer current = queue.poll();
			int u = current.getName();
			double w = current.getWeight();

			// explore each edge
			HashMap<Integer, Double> edges = weightedGraph.get(u);

			for (int v : edges.keySet())
			{
				double newDistance = distance.get(u) * edges.get(v);
				if (distance.get(v) < newDistance) // if distance
				{
					
					distance.put(v, newDistance);
					previous.put(v, u);
					insertOrChange(v, distance.get(v), queue);

				}
			}
		}
			// dijkstras is complete, return distance element of goal element;
			return distance.get(goalVector);
		
	}

	/**
	 * If vertex is already in queue, updates its value. Else adds vertex to
	 * queue.
	 */
	private static void insertOrChange (int vertex, double weight,
			PriorityQueue<WeightedContainer> queue)
	{
		WeightedContainer container = new WeightedContainer(vertex, weight);
		if (queue.contains(container))
		{
			queue.remove(container);
		}
		queue.add(container);
	}

}
