/* solution to https://utah.kattis.com/problems/utah.galaxyquest written by Aaron Bellis 6/11/2018 */

#include <vector>
#include <iostream>

using namespace std;

struct star
{
  int x;
  int y;
};

/**
 * Helper method to determin if star has negative coordinates.
 *
 * Returns true if one coordinate of s are negative, else returns false.
 */
bool is_null_star(const star & s)
{
  return s.x < 0 || s.y < 0;
}

/**
 * takes the cartesian coordinates of two points (x1,y1) and (x2, y2) and 
 * returns true if the distance between the two is less than or equal to d
 * else returns false
 */
bool within_distance(int x1, int y1, int x2, int y2, int d)
{
  long long x_squared = static_cast<long long>(x1) - static_cast<long long>(x2);
  x_squared *= x_squared;

  long long y_squared = static_cast<long long>(y1) - static_cast<long long>(y2);
  y_squared *= y_squared;

  long long d_squared = static_cast<long long>(d);
  d_squared *= d_squared;

  return x_squared + y_squared <= d_squared;
}


/**
 * Counts the number of star instances in stars that are within distance of element. 
 */
int count(const vector<star> & stars, const star & element, int distance)
{

  vector<star>::const_iterator it = stars.begin();  
  vector<star>::const_iterator end = stars.end();  
  
  int count = 0;
  for (it; it != end; it++)
  {
    if (within_distance(it->x, it->y, element.x, element.y, distance))
    {
      count++;
    }
  }  

  return count;
}

/**
 * makes |stars|/2 pairs from stars. If the elements of the pairs are different,
 * throw them both away, else keep one of the elements and discard the other. If
 * there is a leftover element, call it y and discard it.  
 *
 * Returns kept elements as a vector<star> called A' (a_prime)
 */
vector<star> find_a_prime(const vector<star> & stars, int distance)
{
  // iterators to beginning and ending of stars
  vector<star>::const_iterator it = stars.begin();
  vector<star>::const_iterator end = stars.end();
  
  // an iterator to the element after it
  vector<star>::const_iterator second = stars.begin();
  second++;
  
  // a vector to store A'
  vector<star> a_prime;
  
  // it steps by 2
  for (it; it != end && second != end; it++, it++)
  {
    // keep the first one if both are within distance
    if (within_distance(it->x, it->y, second->x, second->y, distance))
    {
      a_prime.push_back(*it);
    }
    
    // make sure second points ahead of it.
    second++;
    second++;
  }
  
  return a_prime;
}

/**
 * Takes in a vector made up of star structs and returns the majority
 * element if one exists, else returns a star with coordinates (-1, -1).
 */
star find_majority(const vector<star> & stars, int distance)
{
  // definition of a star that doesn't exist in PU
  star null_star = {-1, -1};
  
  // base cases for recursive call
  if (stars.empty())
  {
    return null_star;
  }
  else if (stars.size() == 1)
  {
    return stars[0];
  }
  
  // recursive call to find_majority, using A' as vector
  star x = find_majority(find_a_prime(stars, distance), distance);
  int stars_size = stars.size();
  
  // if no majority element was found
  if (is_null_star(x))
  {
    //see if stars is odd in size
    if (stars_size % 2 != 0)
    {
      // count elements of y in stars
      int y_count = count(stars, stars[stars_size - 1], distance);
      if (y_count > (stars_size/2))
      {
        // y is majority element, return it
        return stars[stars_size - 1];
      }
      else
      {
        // y is not majority element, none is found
        return null_star;
      }
    }
    else
    {
      // stars is even in size, no candidate for y and no majority element was found
      return null_star;
    }
  }
  else
  {
    // majority element returned something, count it in stars to see if it is majority
    int x_count = count(stars, x, distance);
    if (x_count > (stars_size/2))
    {
      return x;
    }
    else
    {
      return null_star;
    }
  }
  
}

/**
 * reads in data from command line representing stars in a PU and determines if there is a 
 * galaxy containing more than half the stars. If there is, prints the number of stars in that
 * galaxy to the command line, else prints 'NO'
 */
int main(int argc, char** argv)
{
  int distance, k;
  cin >> distance;
  cin >> k;
  
  // read all input into stars
  vector<star> stars;
  for (int i = 0; i < k; i++)
  {
    // read in coordinates for star
    int x, y;
    cin >> x;
    cin >> y;
    
    // create a star with input as coordinates
    star s = {x, y};
    
    // add star to stars
    stars.push_back(s);
  }
  
  star majority = find_majority(stars, distance);
  if (is_null_star(majority))
  {
    cout << "NO" << endl;
  }
  else
  {
    cout << count(stars, majority, distance) << endl;
  }  
}

 
