all: main clean

clean: main
	-rm *.o
	-rm *.a
main.o:
	-gcc -c main.c -o main.o


myTerm.o:
	-gcc -c myTerm.c -o myTerm.o
myTerm.a: myTerm.o
	-ar cr libmyTerm.a myTerm.o
mySimpleComputer.o:
	-gcc -c mySimpleComputer.c -o mySimpleComputer.o
mySimpleComputer.a: mySimpleComputer.o
	-ar cr libmySimpleComputer.a mySimpleComputer.o
myBigChars.o:
	-gcc -c myBigChars.c -o myBigChars.o
myBigChars.a: myBigChars.o
	-ar cr libmyBigChars.a myBigChars.o
myInterface.o:
	-gcc -c myInterface.c -o myInterface.o
myInterface.a: myInterface.o
	-ar cr libmyInterface.a myInterface.o
myReadkey.o:
	-gcc -c myReadkey.c -o myReadkey.o
myReadkey.a: myReadkey.o
	-ar cr libmyReadkey.a myReadkey.o
mySignal.o:
	-gcc -c mySignal.c -o mySignal.o
mySignal.a: mySignal.o
	-ar cr libmySignal.a mySignal.o
main: main.o   myTerm.a mySimpleComputer.a myBigChars.a myInterface.a myReadkey.a mySignal.a
	-gcc -o Program *.o
	
start:
	-./Program


