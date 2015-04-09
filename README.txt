COMP 4380
Assignment 4

Evan Spearman 	(7690987)
Johnny Xie 		(7694754)

Github Repository: https://github.com/BurningKoy/DB-Impl

Question 1

	Implemented By: Evan Spearman
	Developed With: Microsoft Visual Studio 2013

	To Build:

		Option 1:
			Use the Makefile in Q1/
			IMPORTANT: This requires a version of g++ which has support for C++11

		Option 2:
			Use the Microsoft Visual Studio 2013 solution provided in Q1/
			This was tested with the configuration Debug x64

	To Run:

		Same as specified in the assignment

			BPlusTree 1 Q1command.txt

	Expected Behaviour:

		The program runs as specified in the assignment specification using the test data from the assignment specification.

Question 2
	
	Implemented By: Johnny Xie
	Developed With: Mingw g++

	This program is compiled using C++ 11. The flag has been set in the makefile using g++ compiler.

	Instructions:
	1. Compile and run using the makefile.
	2. Type ./q2 <PageSize> <Number of Buffer pages> <Input file>

	Example:
	>make
	>q2 <PageSize> <Number of Buffer pages> <Input file>

	passN.txts made to represent intermediates in merge sort.
	These represent temporary files, beware of large sample sizes..

Question 3

	Implemented By: Evan Spearman
	Developed With: Microsoft Visual Studio 2013

	To Build:

		Option 1:
			Use the Makefile in Q3/
			IMPORTANT: This requires a version of g++ which has support for C++11

		Option 2:
			Use the Microsoft Visual Studio 2013 solution provided in Q3/
			This was tested with the configuration Debug Win32

	To Run:

		Same as specified in the assignment

			Join Students.txt Enrolled.txt Q3aux.txt

	Expected Behaviour:

		The program runs as specified in the assignment specification using the test data from the assignment specification.