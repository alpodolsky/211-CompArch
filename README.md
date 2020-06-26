# pa1:
This assignment was meant to introduce us to coding in C by doing a variety of assignments.
# First: Array and Sorting
- You have to write a program that will read an array from a file and sort the given array. You will
return the array sorted with all odd numbers in ascending order at the front followed by all even
numbers in descending order.
- You can use any sorting algorithm you know or wish to use. However, you cannot use the library
sort functions. You should write your own sort function.

Input-Output format: Your program will take a file name as an input. The first line in the
file provides the total number of values in the array. The second line will contain a list of numbers
separated by tabs. For example a sample input file “file1.txt” is:
file1.txt:
6
25 10 1 99 4 2
Your output will be a sorted lis of numbers, odd numbers in ascending order and then even numbers
in descending order, each separated by tabs.
$./first file1.txt
1 25 99 10 4 2
1

We will not give you improperly formatted files. You can assume all your input files will be in
proper format as above.

# Second: Hash table
  This assignment had us make hash tables that had 10000 buckets to start, no rehash implementation was required so in theory, elements could continuously map to the same entry in the hashtable:

- A hash table can be implemented in many ways in C. You must find a simple way to implement
a hash table structure where you have easy access to the buckets through the hash function. As
a reminder, a hash table is a structure that has a number of buckets for elements to ”hash” into.
- You will determine where the element falls in the table using a hash function we describe below.
- You must not do a linear search of the 10,000 element array. We will not award any credit for
O(n) time implementation of searches or insertions in the common case.
- For this problem, you will be using the following hash function: key modulo the number of
buckets.

Input format: This program takes a file name as argument from the command line. The file
contains successive lines of input. Each line contains a character, either ‘i’ or ‘s’, followed by a tab
and then an integer. For each line that starts with ‘i’, your program should insert that number in
the hash table if it is not present. If the line starts with a ‘s’, your program should search the hash
table for that value.

Output format: For each line in the input file, your program should print the status/result
of that operation. For an insert, the program should print “inserted” if the value is inserted or
“duplicate” if the value is already present. For a search, the program should print ”present” or
“absent” based on the outcome of the search. You can assume that the program inputs will have
proper structure.

Example Execution: Let’s assume we have a text file with the following contents:
file1.txt:
i 10
i 12
s 10
i 10
s 5
Then the result will be:
2
$./second file.txt
inserted
inserted
present
duplicate
absent

# Third: Bit function
  In this exercise, you have to write a program that will read a number followed by a series of bit
operations from a file and perform the given oeprations sequentially on the number. The operations
are as follows:
- set(x, n, v): sets the nth bit of the number x to v
- comp(x, n, v): sets the value of the nth bit of x to its complement (1 if 0 and 0 if 1)
- get(x, n, v): returns the value of the nth bit of the number x.
- The least significant bit (LSB) is considered to be index 0.

- For this exercise, you must use logical operations to implement the three functions.
- You are not allowed to use any arithmetic operations or math library functions.

Input format: Your program will take the file name as input. The first line in the file provides
the value of the number x to be manipulated. This number should be considered an unsigned
short. The following lines will contain the operations to manipulate the number. To simplify
parsing, the format of the operations will always be the command name followed by 2 numbers,
separated by tabs. For the set(x, n, v) command, the value of the second input number (v) will
always be either 0 or 1. For the comp(x, n) and get(x, n) commands the value of the second
input number will always be 0 and can be ignored. Note that the changes to x are cumulative,
rather than each instruction operating independently on the original x.

Output format: Your output for comp and set commands will be the resulting value of the
number x after each opeartion, each on a new line. For get commands, the output should be the
requested bit’s value.

Example Execution: For example, a sample input file file1.txt contains the following (except
the annotation comments):
file1.txt:
5 # x = 5
get 0 0 # get(x, 0), ignoring second value (0)
comp 0 0 # comp(x, 0), ignoring second value (0)
set 1 1 # set(x, 1, 1)
The result of the sample run is:
$./third file1.txt
3
1
4
6

# bomb lab:
a project meant to expose us to using GDB debugging, and looking at assembly to understand the function of a program in order to become familiar with translating assembly into C and vice versa.

#pa3:
Cache simulation
