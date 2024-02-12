CC = g++
CFLAGS = -g -Wall -Werror
WORKOBJ = course.o student.o passfailcourse.o scalecourse.o

all: $(WORKOBJ) record1 record2

clean:
	rm -f *.o record1 record2

course.o: course.cpp course.h
	$(CC) $(CFLAGS) course.cpp -c -o course.o
	
student.o: student.cpp student.h course.o
	$(CC) $(CFLAGS) student.cpp -c -o student.o
	
passfailcourse.o: passfailcourse.cpp passfailcourse.h course.o
	$(CC) $(CFLAGS) passfailcourse.cpp -c -o passfailcourse.o

scalecourse.o: scalecourse.cpp scalecourse.h course.o
	$(CC) $(CFLAGS) scalecourse.cpp -c -o scalecourse.o

record1: record1.cpp course.o student.o passfailcourse.o scalecourse.o
	$(CC) $(CFLAGS) record1.cpp $(WORKOBJ) -o record1

record2: record2.cpp course.o student.o passfailcourse.o scalecourse.o
	$(CC) $(CFLAGS) record2.cpp $(WORKOBJ) -o record2

record3: record3.cpp course.o student.o passfailcourse.o scalecourse.o
	$(CC) $(CFLAGS) record3.cpp $(WORKOBJ) -o record3