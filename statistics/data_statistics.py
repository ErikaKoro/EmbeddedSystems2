import statistics
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns


##
# @brief This function reads the data from the producer file
#
# @param path_to_file The path to the file
#
# @return The list of integers read from the file
#
def read_data_consumer(path_to_file):
    # open a file in read mode
    file = open(path_to_file, 'r')

    # the data in the file are stoed one integer per line
    # read the file and store the data in a list
    lines = file.readlines()

    # remove the '\n' from each line
    lines = [x.strip() for x in lines]

    # convert the list of strings to list of integers
    lines = [int(x) for x in lines]

    # return the list
    return lines


##
# @brief This function reads the data from the producer file
#
# @param path_to_file The path to the file
#
# @return A tupple with the periods the errors and the lines (periods, errors, lines)
#
def read_data_producer(path_to_file):
    # open a file in read mode
    file = open(path_to_file, 'r')

    # the first number is the number of producers
    number_of_producers = int(file.readline().strip())

    # the second numer is the execution time
    execution_time = int(file.readline().strip())

    # read the empty line
    file.readline()
    
    periods = []
    errors = []
    lines = []

    for i in range(number_of_producers):
        # read the timer period
        periods.append(int(file.readline().strip()))

        # read the drift counter for the timer
        errors.append(int(file.readline().strip()))

        timer_lines = []

        # read until the empty line or the end of the file
        while True:
            line = file.readline().strip()
            if line == "" or line == None:
                break
            else:
                timer_lines.append(int(line))
        
        lines.append(timer_lines)
     

    # return the list
    return (periods, errors, lines)


##
# @brief This function creates a figure with the distribution of the lines
#
# @param lines The list of lines
# @param error The drift counter
# @param period The timer period
#
def createFigureCons(lines, cons_id, filename='', title=''):
    print("Consumer: ", cons_id)
    print("Min: ", min(lines))
    print("Max: ", max(lines))
    print("Average: ", sum(lines)/len(lines))
    print("Standard deviation: ", statistics.stdev(lines))
    print("Median: ", statistics.median(lines))
    print("Number of lines: ", len(lines))
    print("\n\n")

    # create a figure
    fig = plt.figure()

    fig.set_size_inches(8, 6)

    sns.set_style('whitegrid')

    sns.kdeplot(np.array(lines), bw_method=0.5, fill=True, label="cons: " + str(cons_id))

    # add the median line
    median_string = "{:.2f}".format(statistics.median(lines))
    plt.axvline(statistics.median(lines), color='C1', linestyle='dashed', linewidth=1, label='Median = ' + median_string + ' ms')

    # add the mean line with value label
    mean_string = "{:.2f}".format(sum(lines)/len(lines))
    plt.axvline(sum(lines)/len(lines), color='C0', linestyle='solid', linewidth=1, label='Mean = ' + mean_string + ' ms')

    # add the standard deviation to the legend
    std_string = "{:.2f}".format(statistics.stdev(lines))
    plt.plot([], [], ' ', label='Standard deviation = ' + std_string + ' ms')

    # add the legend
    plt.legend()

    # set the title
    plt.title('Consumer times distribution consumer: ' + str(cons_id) + title)

    # save the figure
    fig.savefig('distribution_lines_cons' + filename + str(cons_id) + '.png', dpi=300)

    # clear the figure
    fig.clear()


##
# @brief This function creates a figure with the distribution of the lines
#
# @param lines The list of lines
# @param error The drift counter
# @param period The timer period
#
def createFigure(lines, error, period, filename='', title=''):
    print("Period: ", period)
    print("Drift counter: ", error)
    print("Min: ", min(lines))
    print("Max: ", max(lines))
    print("Average: ", sum(lines)/len(lines))
    print("Standard deviation: ", statistics.stdev(lines))
    print("Median: ", statistics.median(lines))
    print("Number of lines: ", len(lines))
    print("\n\n")

    # create a figure
    fig = plt.figure()

    fig.set_size_inches(8, 6)

    sns.set_style('whitegrid')

    sns.kdeplot(np.array(lines), bw_method=0.5, fill=True, label=str(period) + " ms")

    # add the median line
    median_string = "{:.2f}".format(statistics.median(lines))
    plt.axvline(statistics.median(lines), color='C1', linestyle='dashed', linewidth=1, label='Median = ' + median_string + ' ms')

    # add the mean line with value label
    mean_string = "{:.2f}".format(sum(lines)/len(lines))
    plt.axvline(sum(lines)/len(lines), color='C0', linestyle='solid', linewidth=1, label='Mean = ' + mean_string + ' ms')

    # add the standard deviation to the legend
    std_string = "{:.2f}".format(statistics.stdev(lines))
    plt.plot([], [], ' ', label='Standard deviation = ' + std_string + ' ms')

    # add the legend
    plt.legend()

    # set the title
    plt.title('Produce times distribution for period ' + str(period) + ' ms ' + title)

    # save the figure
    fig.savefig('distribution_lines_' + filename + str(period) + '.png', dpi=300)

    # clear the figure
    fig.clear()
    

def createDualFigure(lines_1, lines_2, error_1, error_2, period_1, period_2, filename=''):

    # create a figure with the two distributions in two subplots
    fig = plt.figure()

    fig.set_size_inches(8, 6)

    sns.set_style('whitegrid')

    # create the first subplot
    ax1 = fig.add_subplot(211)

    sns.kdeplot(np.array(lines_1), bw_method=0.5, fill=True, label=str(period_1) + " ms")

    # add the median line
    median_string = "{:.2f}".format(statistics.median(lines_1))
    plt.axvline(statistics.median(lines_1), color='C1', linestyle='dashed', linewidth=1, label='Median = ' + median_string + ' ms')

    # add the mean line with value label
    mean_string = "{:.2f}".format(sum(lines_1)/len(lines_1))
    plt.axvline(sum(lines_1)/len(lines_1), color='C0', linestyle='solid', linewidth=1, label='Mean = ' + mean_string + ' ms')

    # add the standard deviation to the legend
    std_string = "{:.2f}".format(statistics.stdev(lines_1))
    plt.plot([], [], ' ', label='Standard deviation = ' + std_string + ' ms')

    # add the legend
    plt.legend()

    # set the title
    plt.title('Produce times distribution for period ' + str(period_1) + ' ms (all timers)')

    plt.subplots_adjust(hspace=0.5)

    # create the second subplot
    ax2 = fig.add_subplot(212)

    sns.kdeplot(np.array(lines_2), bw_method=0.5, fill=True, label=str(period_2) + " ms (single timer)")

    # add the median line
    median_string = "{:.2f}".format(statistics.median(lines_2))
    plt.axvline(statistics.median(lines_2), color='C1', linestyle='dashed', linewidth=1, label='Median = ' + median_string + ' ms')

    # add the mean line with value label
    mean_string = "{:.2f}".format(sum(lines_2)/len(lines_2))
    plt.axvline(sum(lines_2)/len(lines_2), color='C0', linestyle='solid', linewidth=1, label='Mean = ' + mean_string + ' ms')

    # add the standard deviation to the legend
    std_string = "{:.2f}".format(statistics.stdev(lines_2))
    plt.plot([], [], ' ', label='Standard deviation = ' + std_string + ' ms')

    # add the legend
    plt.legend()

    # set the title
    plt.title('Produce times distribution for period ' + str(period_2) + ' ms')

    # save the figure
    fig.savefig('distribution_lines_' + filename + str(period_1) + '_' + str(period_2) + '.png', dpi=300)

    # clear the figure
    fig.clear()



if __name__ == '__main__':
    consumer_0 = read_data_consumer('statistics/execution_times_all/consumer_0.txt')
    consumer_1 = read_data_consumer('statistics/execution_times_all/consumer_1.txt')
    consumer_2 = read_data_consumer('statistics/execution_times_all/consumer_2.txt')
    consumer_3 = read_data_consumer('statistics/execution_times_all/consumer_3.txt')

    # convert lines from us to ms
    consumer_0 = [x/1000 for x in consumer_0]
    consumer_1 = [x/1000 for x in consumer_1]
    consumer_2 = [x/1000 for x in consumer_2]
    consumer_3 = [x/1000 for x in consumer_3]

    createFigureCons(consumer_0, 0, title='(all timers)', filename='all_')
    createFigureCons(consumer_1, 1, title='(all timers)', filename='all_')
    createFigureCons(consumer_2, 2, title='(all timers)', filename='all_')
    createFigureCons(consumer_3, 3, title='(all timers)', filename='all_')


    consumer_10_0 = read_data_consumer('statistics/execution_times_10ms/consumer_0.txt')
    consumer_10_1 = read_data_consumer('statistics/execution_times_10ms/consumer_1.txt')
    consumer_10_2 = read_data_consumer('statistics/execution_times_10ms/consumer_2.txt')
    consumer_10_3 = read_data_consumer('statistics/execution_times_10ms/consumer_3.txt')

    # convert lines from us to ms
    consumer_10_0 = [x/1000 for x in consumer_10_0]
    consumer_10_1 = [x/1000 for x in consumer_10_1]
    consumer_10_2 = [x/1000 for x in consumer_10_2]
    consumer_10_3 = [x/1000 for x in consumer_10_3]

    createFigureCons(consumer_10_0, 0, title='(single timer)', filename='10ms_')
    createFigureCons(consumer_10_1, 1, title='(single timer)', filename='10ms_')
    createFigureCons(consumer_10_2, 2, title='(single timer)', filename='10ms_')
    createFigureCons(consumer_10_3, 3, title='(single timer)', filename='10ms_')


    exit(0)

    print("Consumer 0:")
    print("Min: ", min(consumer_0))
    print("Max: ", max(consumer_0))
    print("Average: ", sum(consumer_0)/len(consumer_0))
    print("Standard deviation: ", statistics.stdev(consumer_0))
    print("Median: ", statistics.median(consumer_0))

    print("\n\n")

    print("Consumer 1:")
    print("Min: ", min(consumer_1))
    print("Max: ", max(consumer_1))
    print("Average: ", sum(consumer_1)/len(consumer_1))
    print("Standard deviation: ", statistics.stdev(consumer_1))
    print("Median: ", statistics.median(consumer_1))

    print("\n\n")

    print("Consumer 2:")
    print("Min: ", min(consumer_2))
    print("Max: ", max(consumer_2))
    print("Average: ", sum(consumer_2)/len(consumer_2))
    print("Standard deviation: ", statistics.stdev(consumer_2))
    print("Median: ", statistics.median(consumer_2))

    print("\n\n")

    print("Consumer 3:")
    print("Min: ", min(consumer_3))
    print("Max: ", max(consumer_3))
    print("Average: ", sum(consumer_3)/len(consumer_3))
    print("Standard deviation: ", statistics.stdev(consumer_3))
    print("Median: ", statistics.median(consumer_3))

    print("\n\n")

    # read the data from the producer file
    periods_all, errors_all, lines_all = read_data_producer('statistics/execution_times_all/producer_all.txt')

    period_10, errors_10, lines_10 = read_data_producer('statistics/execution_times_10ms/producer_10ms.txt')
    period_100, errors_100, lines_100 = read_data_producer('statistics/execution_times_100ms/producer_100ms.txt')
    period_1000, errors_1000, lines_1000 = read_data_producer('statistics/execution_times_1000ms/producer_1000ms.txt')

    #convert lines from us to ms
    for i in range(len(lines_all)):
        lines_all[i] = [x/1000 for x in lines_all[i]]

    for i in range(len(lines_10)):
        lines_10[i] = [x/1000 for x in lines_10[i]]

    for i in range(len(lines_100)):
        lines_100[i] = [x/1000 for x in lines_100[i]]

    for i in range(len(lines_1000)):
        lines_1000[i] = [x/1000 for x in lines_1000[i]]

    print("\n\n")
    createFigure(lines_10[0], errors_10[0], period_10[0], title='(single timer)')
    createFigure(lines_100[0], errors_100[0], period_100[0], title='(single timer)')
    createFigure(lines_1000[0], errors_1000[0], period_1000[0], title='(single timer)')

    createFigure(lines_all[0], errors_all[0], periods_all[0], filename='all_', title='(all timers)')
    createFigure(lines_all[1], errors_all[1], periods_all[1], filename='all_', title='(all timers)')
    createFigure(lines_all[2], errors_all[2], periods_all[2], filename='all_', title='(all timers)')

    createDualFigure(lines_all[0], lines_1000[0], errors_all[0], errors_1000[0], periods_all[0], period_1000[0], 'comparison_')
    createDualFigure(lines_all[1], lines_100[0], errors_all[1], errors_100[0], periods_all[1], period_100[0], 'comparison_')
    createDualFigure(lines_all[2], lines_10[0], errors_all[2], errors_10[0], periods_all[2], period_10[0], 'comparison_')
    
    # command to create venv in the current directory: python3 -m venv venv
    # command to activate venv: source venv/bin/activate
