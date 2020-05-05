CFLAGS = -g

bin : main.o list.o producer.o consumer.o
	$(CC) $(CFLAGS) -o bin main.o list.o producer.o consumer.o -lpthread -g

main.o : main.c
	$(CC) -c main.c

list.o : list.c
	$(CC) -c list.c

producer.o : producer.c
	$(CC) -c producer.c

consumer.o : consumer.c
	$(CC) -c consumer.c

.PHONY : clean
clean :
	-rm bin main.o list.o producer.o consumer.o