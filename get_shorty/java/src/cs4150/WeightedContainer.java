/**
 * Java Solution for kattis GetShorty found at 
 * https://utah.kattis.com/problems/getshorty
 * Author Aaron Bellis. 
 * Requires WeightedContainer.java found in this package
 */
package cs4150;

/**
 * A WeightedContainer is a container which holds an object or name
 * and stores an associated weight. 
 */
public class WeightedContainer implements Comparable
{
	private int vectorName;
	private double vectorWeight;
	
	/**
	 * Creates a Weighted Container with the given name and weight
	 */
	public WeightedContainer (int name, double weight)
	{
		vectorName = name;
		vectorWeight = weight;
	}
	
	/**
	 * Returns the name of this vector
	 */
	public int getName ()
	{
		return vectorName;
	}
	
	/**
	 * returns the weight of this vector
	 */
	public double getWeight()
	{
		return vectorWeight;
	}
	
	/**
	 * Sets the weight of this vector to the given weight
	 */
	public void setWeight(double weight)
	{
		vectorWeight = weight;
	}
	
	/**
	 * Compares this WeightedContainer to arg0 based on weight. If The weight of 
	 * this container is less than that of arg0 returns -1, if it is greater returns 1
	 * if they are equal returns 0.
	 * 
	 * If arg0 is null or not an instance of WeightedContainer, throws new 
	 * IllegalArgumentException
	 */
	@Override
	public int compareTo (Object arg0)
	{
		if (arg0 == null || !(arg0 instanceof WeightedContainer))
		{
			throw new IllegalArgumentException("Cannot compare this object to null or another type");
		}
		
		WeightedContainer other = (WeightedContainer)arg0;
		if (vectorWeight < other.vectorWeight)
		{
			return 1;
		}
		else if (vectorWeight > other.vectorWeight)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	
	/**
	 * Two containers are equal if their names are the same.
	 */
	@Override
	public boolean equals(Object o)
	{
		if (o == null || !(o instanceof WeightedContainer))
		{
			return false;
		}
		
		WeightedContainer other = (WeightedContainer)o;
		
		return vectorName == other.getName();
		
	}
	
	/**
	 * Two containers are equal if their names are the same, therefore
	 * two containers with the same name should have the same hash code
	 */
	@Override
	public int hashCode()
	{
		return vectorName;
	}

}
