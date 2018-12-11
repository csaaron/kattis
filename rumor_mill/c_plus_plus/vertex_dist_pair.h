#ifndef VERTEX_DIST_PAIR_H
#define VERTEX_DIST_PAIR_H

#include <string>


class vertex_dist_pair
{
  std::string vert;
  // enforced envarient: stored dist value cannot be less than -1 
  int dist;

public:
  /***
   * Constructs a vertex, distance pair with the given vertex name and distance.
   * Distances which are negative are considered to be infinite and are stored as -1.
   **/
  vertex_dist_pair(std::string vertex, int distance);

  /***
   * Returns the name of the vertex
   **/
  std::string get_vertex() const;

  /***
   * Returns the distance
   **/
  int get_distance() const;

  /***
   * Defines default ordering for a vertex_dist_pair object. The ordering is
   * first by distance in ascending order, then the lexicographic ordering
   * of vertex.
   **/
  bool operator< (const vertex_dist_pair & other) const;

};

#endif
