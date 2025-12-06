file = "input.txt"

with open(file, "r") as file_input:
    input = file_input.read();
    nums_lines = input.split("\n")
    
    nums = []
    for line in nums_lines:
        nums.append(line.split())

    nums.pop(-1)
    
    print(nums[len(nums) - 1])
    outputs = [int(x) for x in nums[0]]
    for y in range(1, len(nums) - 1):
        for x in range(len(nums[y])):
            operator = nums[len(nums) - 1][x]
            if(operator == "+"):
                outputs[x] += int(nums[y][x])
            if(operator == "*"):
                outputs[x] *= int(nums[y][x])

    print(outputs)

    total = 0
    for number in outputs:
        total += number

    print(total)
