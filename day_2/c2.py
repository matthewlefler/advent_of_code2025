
def is_valid(i):
    string_rep = str(i)
        
    for split in range(1, int(len(string_rep) / 2) + 1):
        flag = 1

        if(len(string_rep) % split != 0):
            continue;
        segment = string_rep[0:split]
        # print(f"{i} | {split} | {segment}")

        start = split
        while( start + split <= len(string_rep)):
            test_part = string_rep[start:start+split]
            # print(test_part)
            if(segment != test_part):
                flag = 0
                break
            start += split
        if(flag == 1):
            print(f"added: {i}")
            return i
    return 0;

with open("input.txt", "r") as file:
    content = file.read()
    ranges = [x.split("-") for x in content.split(",")]

    output = 0
    for n_range in ranges:
        i = int(n_range[0])

        print(f"{n_range[0]} to {n_range[1]}")

        for i in range(int(n_range[0]), int(n_range[1]) + 1):
            output += is_valid(i)
                 
    
    print(output)


