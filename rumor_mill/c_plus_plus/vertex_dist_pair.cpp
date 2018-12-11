#include "vertex_dist_pair.h"

/***
 * Constructs a vertex, distance pair with the given vertex name and distance.
 * Distances which are negative are considered to be infinite.
 **/
vertex_dist_pair::vertex_dist_pair(std::string vertex, int distance)
{
  vert = vertex;
  // enforced envarient: stored dist value cannot be less than -1 
  if (distance < -1)
  {
    dist = -1;
  }
  else
  {
    dist = distance;
  }
}

/***
 * Returns the name of the vertex
 **/
std::string vertex_dist_pair::get_vertex() const
{
  return vert;
}

/***
 * Returns the distance. If distance is infinite, returns -1.
 **/
int vertex_dist_pair::get_distance() const
{
  return dist;
}

/***
 * Defines default ordering for a vertex_dist_pair object. The ordering is
 * first by distance in ascending order, then the lexicographic ordering
 * of vertex.
 **/
bool vertex_dist_pair::operator<(const vertex_dist_pair & other) const
{
  std::string str1 = vert;
  std::string str2 = other.vert;

  int dist1 = dist;
  int dist2 = other.dist;

  // if both are same, return lexicographical order
  if (dist1 == dist2)
  {
    return str1 < str2;
  }

  // if one of distances is negative (representation of infinity) will be 
  // opposite of expected ordering.
  if (dist1 < 0)
    return false;
  if (dist2 < 0)
    return true;

  // regular sorting of integers
  return dist1 < dist2;
}
