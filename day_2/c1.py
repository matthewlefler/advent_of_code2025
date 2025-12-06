with open("input.txt", "r") as file:
    content = file.read()
    ranges = [x.split("-") for x in content.split(",")]

    output = 0
    for range in ranges:
        i = int(range[0])

        print(f"{range[0]} to {range[1]}")

        while( i <= int(range[1]) ):
            
            string_rep = str(i)
            if( len(string_rep) % 2 == 1 ):
                i += 1
                continue

            if( string_rep[ 0:int(len(string_rep)/2) ] == string_rep[ int(len(string_rep)/2) : int(len(string_rep)) ]):
                output += i

            i += 1
    
    print(output)
