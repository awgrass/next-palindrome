# next-palindrome
A C++ program to calculate the next smallest palindrome of a given number!

Input: 
An arbitrary amount of lines containing some number L each, provided via stdin.
L is an arbitrary, positiv and natural number with 0 <= digits(L) <= 1000000. No leading zeros allowed.

Output:
For each L, output the smallest palindrome larger than L.

To compile and start the program in a unix environment, one could for example head to the source folder in terminal and type:

g++ -std=c++14 next_palindrome.cpp -o palindrome && ./palindrome < tests.txt

I/O Example
{

Input:

10
1999
8199


Output:

11
2002
8228

}
