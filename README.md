# Producer/Consumer Assignment #1

Hi, I'm Lamir Thompson. In this README i'll give insight on the program I wrote along with problems I've ran into when trying to figure out how to get the producer/consumer to work and the way to run this program. 

**Producer/consumer problem**
The producer/consumer problem has been around for awhile and the problem is trying to get these two files to syncronize in the buffer and use shared memory without interupting each other while the producer is placing data in the buffer and the consumer is removing data from the same buffer. So my job was to fix this syncronization issue so that they work concurrently which you can see i've done in producer.cpp and consumer.cpp these are both of the files that I was working in.

**Difficulties**
One of the biggest difficulties I faced when writing the code was trying to find out how most functions worked and semaphores in general but after getting a better understanding of how they operated then it made this project a little less hard. Another difficulty I was faced with was compiling/running my code, when running my code I would see that either or both my producer and consumer .cpp files did not work together they wern't accessing the shared memory and that was a big problem seeing that was the entire reason I was doing this project but after trials and tribulations I was able to over come the problem and got my code working as good as can be.

**How to run**
By running these 3 lines in this order into the terminal of my code it should run both of the .cpp files.

1) g++ producer.cpp -pthread -lrt -o producer
2) g++ consumer.cpp -pthread -lrt -o consumer
3) ./producer & ./consumeer &