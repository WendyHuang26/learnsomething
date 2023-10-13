def max_area(height):
    max_area = 0
    left, right = 0, len(height) - 1

    while left < right:
        # calculate the height and width
        h = min(height[left], height[right])
        w = right - left
        
        # update the max_area
        max_area = max(max_area, h * w)
        
        # move the pointer of the shorter line
        if height[left] < height[right]:
            left += 1
        else:
            right -= 1

    return max_area
