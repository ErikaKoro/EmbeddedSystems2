import statistics


def manipulate_files(path_to_file_prod, path_to_file_con0, path_to_file_con1, path_to_file_con2, path_to_file_con3):

    # open a file in read mode
    file_prod = open(path_to_file_prod, 'r')
    file_con0 = open(path_to_file_con0, 'r')
    file_con1 = open(path_to_file_con1, 'r')
    file_con2 = open(path_to_file_con2, 'r')
    file_con3 = open(path_to_file_con3, 'r')

    # read the file for producer times
    lines_prod = file_prod.readlines()

    # read the file for consumer 0 times
    lines_con0 = file_con0.readlines()

    # read the file for consumer 1 times
    lines_con1 = file_con1.readlines()

    # read the file for consumer 2 times
    lines_con2 = file_con2.readlines()

    # read the file for consumer 3 times
    lines_con3 = file_con3.readlines()


    if(path_to_file_prod == "execution_times_all/producer_all.txt"):
        # pop the first 5 lines
        lines_prod.pop(0)
        lines_prod.pop(0)
        lines_prod.pop(0)
        lines_prod.pop(0)
        lines_prod.pop(0)

        # pop
        lines_prod.pop(3599)  # newline character
        lines_prod.pop(3599)  # period
        lines_prod.pop(3599)  # drift counter

        # pop
        lines_prod.pop(39599)  # newline character
        lines_prod.pop(39599)  # period
        lines_prod.pop(39599)  # drift counter

    # remove the '\n' from each line for producer times
    lines_prod = [x.strip() for x in lines_prod]

    # remove the '\n' from each line for consumer 0 times
    lines_con0 = [x.strip() for x in lines_con0]

    # remove the '\n' from each line for consumer 1 times
    lines_con1 = [x.strip() for x in lines_con1]

    # remove the '\n' from each line for consumer 2 times
    lines_con2 = [x.strip() for x in lines_con2]

    # remove the '\n' from each line for consumer 3 times
    lines_con3 = [x.strip() for x in lines_con3]

    if(path_to_file_prod != "execution_times_all/producer_all.txt"):
        # pop the first 5 lines in the producer file
        lines_prod.pop(0)
        lines_prod.pop(0)
        lines_prod.pop(0)
        lines_prod.pop(0)
        lines_prod.pop(0)

    # convert the list of strings to list of integers
    lines_prod = [int(x) for x in lines_prod]

    #convert the list of strings to list of integers for consumer 0
    lines_con0 = [int(x) for x in lines_con0]

    #convert the list of strings to list of integers for consumer 1
    lines_con1 = [int(x) for x in lines_con1]

    #convert the list of strings to list of integers for consumer 2
    lines_con2 = [int(x) for x in lines_con2]

    #convert the list of strings to list of integers for consumer 3
    lines_con3 = [int(x) for x in lines_con3]

    # concatenate the lists
    lines_con_total = lines_con0 + lines_con1 + lines_con2 + lines_con3

    # find the mimimum value
    min_value = min(lines_prod)  # for producer times
    min_value_con = min(lines_con_total)  # for consumer times


    # find the maximum value
    max_value = max(lines_prod)  # for producer times
    max_value_con = max(lines_con_total) # for consumer times

    # find the average value of the list
    avg_value = sum(lines_prod)/len(lines_prod) # for producer times
    avg_value_con = sum(lines_con_total)/len(lines_con_total) # for consumer times

    # find the standard deviation
    std_value = statistics.stdev(lines_prod) # for producer times
    std_value_con = statistics.stdev(lines_con_total) # for consumer times

    # find the median
    median_value = statistics.median(lines_prod) # for producer times
    median_value_con = statistics.median(lines_con_total) # for consumer times

    # print the results
    print("PRODUCER TIMES:")
    print("Min: ", min_value)
    print("Max: ", max_value)
    print("Average: ", avg_value)
    print("Standard deviation: ", std_value)
    print("Median: ", median_value)

    print("CONSUMER TIMES:")
    print("Min: ", min_value_con)
    print("Max: ", max_value_con)
    print("Average: ", avg_value_con)
    print("Standard deviation: ", std_value_con)
    print("Median: ", median_value_con)



if __name__ == '__main__':

    print("Results for timer 3 with period 10ms:")

    manipulate_files('execution_times_10ms/producer_10ms.txt',
                     'execution_times_10ms/consumer_0.txt',
                     'execution_times_10ms/consumer_1.txt',
                     'execution_times_10ms/consumer_2.txt',
                     'execution_times_10ms/consumer_3.txt')

    print("\n\nResults for timer 2 with period 100ms:")

    manipulate_files('execution_times_100ms/producer_100ms.txt',
                        'execution_times_100ms/consumer_0.txt',
                        'execution_times_100ms/consumer_1.txt',
                        'execution_times_100ms/consumer_2.txt',
                        'execution_times_100ms/consumer_3.txt')

    print("\n\nResults for timer 1 with period 1000ms:")

    manipulate_files('execution_times_1000ms/producer_1000ms.txt',
                        'execution_times_1000ms/consumer_0.txt',
                        'execution_times_1000ms/consumer_1.txt',
                        'execution_times_1000ms/consumer_2.txt',
                        'execution_times_1000ms/consumer_3.txt')

    print("\n\nResults for all timers:")

    manipulate_files('execution_times_all/producer_all.txt',
                        'execution_times_all/consumer_0.txt',
                        'execution_times_all/consumer_1.txt',
                        'execution_times_all/consumer_2.txt',
                        'execution_times_all/consumer_3.txt')

    


    
                    
    
