# Banker's Algorithm Assignment #2

Hi, I'm Lamir Thompson. In this README I'll give insight on the program I coded along with problems I've run into when trying to figure out how to get the Banker's Algorithm to work and the way to run this program. 

## Banker's Algorithm (deadlock avoidance)
With the Banker's Algorithm the main purpose of it is to avoid getting into a deadlock. The Bankeer's algorithm has a fixed number of recourses and processes. Given the assignment my job was to see if the system is in a safe state and I've came to the conclusion yes, the system is in a safe state. The safe sequence is: P1 -> P3 -> P4 -> P0 -> P2.

## Difficulties
While I was coding for this project I was having trouble trying to see if the system was a safe state or not. When I was compiling the code the output was telling me it was not safe but based onthe question given in the assignment it didnt seem right so I went over the code again and i seen errors that could affect the output of the code and oncw I fixed those errors I got a different output which seems like the correct one.

# How to run
By running these 2 lines in this order into the terminal of my code it should run the banker.cpp file.

1) g++ banker.cpp -o bank.o
2) ./bank.o