# CPU-Event-Simulation
Discrete-time CPU Event Handling Simulation in C

# How does it work?
Given a csv file containing CPU jobs, this event simulation will simulate the order of handling of a CPU based on time and priority, and print the processed jobs to standard output. The simulation uses a min-heap as a priority queue to keep track of priorities when reading jobs.

The input csv columns, in order, represent:
ID, Priority, Arrival Time, Processing Time

The output columns, in order, represent:
ID, Arrival Time, Processing Time, Finish Time, Waiting Time

# How to use
To download the project on a linux system, open your terminal and type in the following command:
    
    $ git clone https://github.com/mozilla/pdf.js.git
    
Once downloaded, navigate to the ``src`` directory and compile the simulation using the command:
    
    $ gcc simulation.c

Finally, you can test the simulation with any one of the jobs in the ``jobs`` directory using the following command (you may use ``testjobs2.csv`` or replace the entire argument with another csv file):

    $ ./a.out ../testjobs1.csv

