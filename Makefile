# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS  = -g -Wall
LIBS = -lsqlite3

# ****************************************************
# Targets needed to bring the executable up to date

build: main.o student.o sqlutils.o
	$(CC) $(CFLAGS) main.o sqlutils.o student.o $(LIBS) -o main
 
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
 
student.o: student.cpp 
	$(CC) $(CFLAGS) -c  student.cpp
 
sqlutils.o: sqlutils.cpp
	$(CC) $(CFLAGS) -c sqlutils.cpp

clean:
	rm *.o

cleanbuild: clean build
