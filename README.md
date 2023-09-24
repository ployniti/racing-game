# racing-game
This project experiment with using templates (generic programming), operator overload, and exception handling in a racing program with inheritance. 
The main data structure used in this program is a doubly linked list to mimick the race tracks.

# Specification
Design a program that allows the users to race different types of vehicles on different terrain or tracks, simulating different race types.

# Hierarchy Design

<p align="center">
  <img width="1152" alt="uml" src="https://github.com/ployniti/racing-game/assets/145937137/eda5e71a-54fe-4cd6-a8ec-cca419bfb7fd">
</p >

From the base vehicle class, I derived three different vehicle types: supercar, touring car, and buggies. These have unique data members from the base class and from each other. 
And, thus, unique member functions to work with those data members such as honking the horn on a touring car or setting the turbo mode for a supercar.

In the base vehicle class is where I have most of the operators I wanted to overload since that is where the data members I want to perform the operations on are. 
The operators I overloaded were for operations such as to compare the current speed of the vehicle using the + or += operators, 
to compare the current speed of the racing vehicles using the <, <=, >, and >= operators, 
to display the vehicle’s status using the << operator, to set the name of the vehicle using the >> operator, 
and to check if two vehicles are of the same caliber and thus could be used to race against each other using the == and != to compare their max speed.

# Compile Instructions
Run `g++ *.cpp` in terminal.

# Run Instructions
Run `./a.out` in terminal.
