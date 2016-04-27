--------------------
Summary
--------------------
This is a C++ implementation of a Red-Black Tree.  It is designed to store names of people. It can take a command line argument (first position) of a text file and add those names to the tree.  Each name should be on its own line in the text file.  When the program runs, there is a menu that displays where a user can add new names to the tree, search for an existing name, print the tree, ect...


--------------------
How to Run
--------------------
To run the program, download the files and compile them in the terminal using the "g++ *cpp" command. To run the program use the "./a.out" command.  Alternatively a command line argument can be passed when running the program, for example "./a.out names.txt".  This will build a tree upon initialization using the names in the names.txt file.

The text file must have each name on a separate line. An example is provided with rest of the files.


--------------------
Dependencies
--------------------
There are no external dependencies beyond C++.


--------------------
System Requirements
--------------------
C++ 11 is required to run this program.  The program was developed in a Mac environment, and may not run correctly on other systems.


--------------------
Group Members
--------------------
Jeffrey Lipnick


--------------------
Contributors
--------------------
Jeffrey Lipnick


--------------------
Open issues/bugs
--------------------
The delete function is not yet completed.  A segmentation fault occurs after deleting more than one node.  It seems to be coming from the color balancing algorithm.