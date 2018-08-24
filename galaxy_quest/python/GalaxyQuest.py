# Python solution to kattis galaxyquest problem found at https://utah.kattis.com/problems/utah.galaxyquest
# Author: Aaron Bellis 

def main():
    # get first line which containes n and k
    line = input("")
    split_line = line.split(" ")
    d = int(split_line[0])
    k = int(split_line[1])

    # read all input into stars
    stars = []
    for i in range(k):
        line = input("")
        split_line = line.split(" ")
        s = star(int(split_line[0]), int(split_line[1]))
        stars.append(s)

    majority = findMajority(stars, d)
    if majority == "NO":
        print(majority)
    else:
        print(count(stars,majority, d))

# takes the cartesian coordinates of two points (x1,y1) and (x2, y2) and 
# returns true if the distance between the two is less than or equal to d
# else returns false
def within_distance(x1, y1, x2, y2, d):
    return (x1 - x2)**2 + (y1 - y2)**2 <= d**2

# Takes in an array, arr and returns the majority element if there is one
def findMajority(arr, distance):
    if len(arr) == 0:
        return "NO"
    elif len(arr) == 1:
        return arr[0]

    x = findMajority(findAPrime(arr, distance), distance)
    if x == "NO":
        if len(arr) % 2 != 0:
            y_count = count(arr, arr[len(arr)-1], distance)
            if y_count > len(arr)/2:
                return arr[len(arr)-1]
            else:
                return "NO"
        else:
            return "NO"
    else:
        x_count = count(arr, x, distance)
        if x_count > len(arr)/2:
            return x
        else:
            return "NO"

# makes |arr|/2 pairs of arr. If the elements of the pairs are different, throw 
# them both away, else keep one of the elements and discard the other. If there
# is a leftover element, call it y and discard it. Returns Kept elements called A'
def findAPrime(arr, distance):
    APrime = []
    i = 0
    while (len(arr) - i > 1):
        starA = arr[i]
        starB = arr[i+1]
        if within_distance(starA.x, starA.y, starB.x, starB.y, distance):
            APrime.append(starA)
        i += 2

    return APrime

# Counts the number of element in arr
def count(arr, element, distance):
    cnt = 0
    for el in arr:
        if within_distance(element.x, element.y, el.x, el.y, distance):
            cnt+=1
    
    return cnt

#Class to hold star x and y coordinates
class star:
    def __init__(self, x_coord, y_coord):
        self.x = x_coord
        self.y = y_coord

if __name__=="__main__":
    main()
