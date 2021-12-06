def findNumberOfLIS(vector: List[int]) -> int:
  """O(n log n) patience sorting solution"""
  # stores stacks of number and number of subsequences
  piles = [[(vector[0], 1)]]
  for num in vector[1:]:
    # bisect left
    left = 0
    right = len(piles)
    while left < right:
        mid = left + (right - left) // 2
        if num > piles[mid][-1][0]:
            left = mid + 1
        else:
            right = mid
    
    # number is greater than all stacks, append new stack
    if left >= len(piles):
      # calculate number of subsequence by summing previous stack counts
      # that has number < current number
      prev = sum(card[1] for card in piles[-1] if num > card[0])
      piles.append([(num, prev)])
    
    # number is smaller than a stack, append to the stack
    elif left > 0:
      prev = sum(card[1] for card in piles[left - 1] if num > card[0])
      piles[left].append((num, prev))
    
    # number is smaller than first stack, append to the first stack
    else:
      piles[left].append((num, 1))
  
  # returns number of subsequence of last stack
  return sum(pile[1] for card in piles[-1])