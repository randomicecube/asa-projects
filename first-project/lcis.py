# Python 3 Program to find length of the  
# Longest Common Increasing Subsequence (LCIS) 
  
# Returns the length and the LCIS of two 
# arrays arr1[0..n-1] and arr2[0..m-1] 
def LCIS(arr1, n, arr2, m): 
  
    # table[j] is going to store length of LCIS 
    # ending with arr2[j]. We initialize it as 0, 
    table = [0] * m 
    for j in range(m): 
        table[j] = 0
  
    # Traverse all elements of arr1[] 
    for i in range(n): 
      
        # Initialize current length of LCIS 
        current = 0
  
        # For each element of arr1[],  
        # traverse all elements of arr2[]. 
        for j in range(m): 
              
            # If both the array have same elements. 
            # Note that we don't break the loop here. 
            if (arr1[i] == arr2[j]): 
                if (current + 1 > table[j]): 
                    table[j] = current + 1
  
            # Now seek for previous smaller common 
            # element for current element of arr1  
            if (arr1[i] > arr2[j]): 
                if (table[j] > current): 
                    current = table[j] 
  
    # The maximum value in table[]  
    # is out result 
    result = 0
    print("table is " + str(table))
    count = 0
    for i in range(m):
        if (table[i] > result):
            print("mudou para " + str(table[i]))
            result = table[i]
            count = 1
        elif (table[i] == result):
            count += 1
    print("count is " + str(count))
          
  
    return result 
  
# Driver Code 
if __name__ == "__main__": 
      
    arr1 = [1,1,1,2,2] 
    arr2 = [2,2,2,2,2] 
  
    n = len(arr1) 
    m = len(arr2) 
  
    print("Length of LCIS is",  
           LCIS(arr1, n, arr2, m)) 
  
# This code is contributed by ita_c 