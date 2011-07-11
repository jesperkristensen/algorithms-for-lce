File structure:

== MISC ==

main.c
    Contains the "main" function
timer.cpp/h
    Functions for timing on different platforms
types.h
    Typedefs of commonly used types, such as integers of known size.

== ALGORITHMS ==

algorithm.h
    Interface for an LCE algorithm, defines the Algorithm class
alg*.cpp/h
    Implementation of an LCE algorithm, subclasses the Algorithm class

== STRINGS ==

string.h
    Interface for at string
str.cpp/h
    Generation of a string
    Creates a global function to initialize a given "string" struct based on
    some parameters.
build*.cpp/h
    Algorithms for creating Suffix Arrays and Longest Common Prefix arrays.

== PERFORMANCE TESTS ==

test*.cpp/h
    Tests a given algorithm on a given string using a specific pattern of
    LCE-queries.
graph*.cpp/h
    Tests a set of algorithms over a varying parameter, and prints a
    CSV-formatted matrix of measurements suitable for 2D plotting.

== CORRECTNESS TESTS ==

correctness.cpp/h
    Tests that all the implemented algorithms agrees on the LCE value for a
    given input.
functionalRest.cpp/h
    Some arbitrary functional tests
