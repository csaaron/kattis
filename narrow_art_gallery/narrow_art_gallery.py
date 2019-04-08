########################################################################
# Author: Aaron Bellis
# Date: 4/5/2019
# Puprpose: Written to solve kattis problem 'Narrow Art Gallery' found 
#   at https://utah.kattis.com/problems/narrowartgallery
########################################################################

###
# Reads from standard input the values making up the galaries and number of 
# rooms to close. Calculates the maximum value which can be kept open without
# blocking off both galaries on the same row, or galaries which are diaganal to 
# to each other. Then prints the maximum value to standard output on its own line
##
def main():
    line = input('')
    split_line=line.split(' ')
    
    N = int(split_line[0]) # number of rows
    k = int(split_line[1]) # number of rooms to close
    
    values = []
    # read in values for each room
    for row in range(N):
        values.append([int(x) for x in input().split(' ')])

    input('')

    museum = Museum(values,N,k)
    print(museum.maxValue_driver())

###
# Represents a narrow museum object. Stores the values for each galary and the
# number of rooms which must be closed
##
class Museum:
    ###
    # Initializes a museum object with the following information
    # rooms: a two dimmensional array
    # rows: the number of rows of two galaries the narrow museum contains
    # num_to_close: the number of galaries which must be closed in this museum
    ##
    def __init__(self, rooms, rows, num_to_close):
        self.values = rooms #expected to be a two dimmensional list of size [rows][2]
        self.N = rows
        self.k = num_to_close

    ###
    # A driver method for the recursive maxValue method. 
    #
    # Returns the max museum value which can be maintained if k galaries are 
    # closed also guarenteeing that progress through the museum is not blocked
    ##
    def maxValue_driver(self):
        cache = {}
        return self.maxValue(0, -1, self.k, cache)

    ###
    # Returns the max museum value which can be maintained if k galaries are 
    # closed for the museum if only rooms are considered begining at row r, and
    # guarenteeing that if closing a room on row r would block progress on this 
    # row would block progress through the museum, it will not be blocked.
    #
    # r: the row to for which we will determine the max value for, considering
    #    All subsequent rows
    # uncloseableRoom: an int in the range [-1,1]
    #     -1 indicates that there is no restriction to the rooms which can be closed on this row
    #      0 indicates that room 0 cannot be closed on this row
    #      1 indicates that room 1 cannot be closed on this row
    # k: the number of rooms which still must be closed in the museum 
    # cache: a dictionary which is keyed by tupples in the form (r, uncloseableRoom, k) which stores
    #    the maxValue for the parameters (r, uncloseableRoom, k) if it has already been calculated.
    ##
    def maxValue(self, r, uncloseableRoom, k, cache):
        # Base cases 
        # we are past the last row, value is 0
        if r >= self.N:
            return 0
        
        # if we already know the answer return it
        if (r,uncloseableRoom,k) in cache:
            return cache[(r,uncloseableRoom,k)]

        # if we have to close a room
        if k == self.N - r:
           if uncloseableRoom == -1: # we can close either room
               close0 = self.values[r][0] + self.maxValue(r+1,0,k-1,cache) # close room 0 on this row
               close1 = self.values[r][1] + self.maxValue(r+1,1,k-1,cache) #close a room 1 on this row
               val = max(close0,close1)
               cache[(r,uncloseableRoom,k)] = val
               return val

           elif uncloseableRoom == 0: # we can't close room 0
               val = self.values[r][0] + self.maxValue(r+1,0,k-1,cache)
               cache[(r,uncloseableRoom,k)] = val
               return val

           elif uncloseableRoom == 1: # we can't close room 1
               val = self.values[r][1] + self.maxValue(r+1,1,k-1,cache)
               cache[(r,uncloseableRoom,k)] = val
               return val

        # we don't have to close a room
        elif 0 < k and k < self.N - r:
            if uncloseableRoom == -1:
                close0 = self.values[r][0] + self.maxValue(r+1,0,k-1,cache) # close room 0 on this row
                close1 = self.values[r][1] + self.maxValue(r+1,1,k-1,cache) #close a room 1 on this row
                dontClose = self.values[r][0] + self.values[r][1] +self.maxValue(r+1,-1,k,cache) # don't close a room
                # whatever the max of those 3 options is our answer
                val = max(close0,close1,dontClose)
                cache[(r,uncloseableRoom,k)] = val
                return val

            elif uncloseableRoom == 0:
                close0 = self.values[r][0] + self.maxValue(r+1,0,k-1,cache) # close a room on this row
                dontClose = self.values[r][0] + self.values[r][1] + self.maxValue(r+1,-1,k,cache) # don't close a room
                #return the larger of the two choices
                val = max(close0, dontClose)
                cache[(r,uncloseableRoom,k)] = val
                return val
            
            elif uncloseableRoom == 1:
                close1 = self.values[r][1] + self.maxValue(r+1,1,k-1,cache) #close a room on this row
                dontClose = self.values[r][0] + self.values[r][1] + self.maxValue(r+1,-1,k,cache) #don't close a room
                #return the larger of the two choices
                val = max(close1, dontClose)
                cache[(r,uncloseableRoom,k)] = val
                return val

        # no rooms are left to close
        elif k == 0:
            val = self.values[r][0] + self.values[r][1] + self.maxValue(r+1,-1,k,cache) # don't close a room
            cache[(r,uncloseableRoom,k)] = val
            return val

if __name__=="__main__":
    main()