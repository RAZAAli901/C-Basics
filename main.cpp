/*
Name: Raza Ali Murtaza 
Registration: L1f25BSCS0615
Section: C6
Assignment: One (Part Two - main.cpp)

Problem Statement:
8 parties participated in an election and their votes are recorded in a text
file "votes.txt". The first number is the total number of votes and every
following number is the ID of the party that received that vote (1 = PPP,
2 = PML-N, and so on). Read the votes from the file, count the votes of each
party, and write a results table and a sorted star graph into "results.txt".
The program must be class-based (class Election), use dynamic arrays, must not
use std::string or vectors, and main must not contain cin, cout or math.
*/

#include "Election.h"

// 5. Main Function
int main()
{
    printHeading("1. Constructors (default, parameterized, default argument, overloaded)");
    demonstrateConstructors();

    printHeading("2. Reading votes.txt and writing results.txt");
    Election mainElection("Main Election", 8);
    processElectionFiles(mainElection);

    printHeading("3. Setters and getters with valid and invalid values");
    demonstrateSettersAndGetters(mainElection);

    printHeading("4. Pass by value (copy constructor runs)");
    showElectionByValue(mainElection);
    showPartyVotes(mainElection, 1);

    printHeading("5. Pass by reference (original is changed)");
    updatePartyVotes(mainElection, 3, 25);
    updatePartyVotes(mainElection, 9, 10);

    printHeading("6. Pass by const reference (compare, no change)");
    Election otherElection("Other Election", 8);
    otherElection.setVotesOfParty(4, 20);
    compareElections(mainElection, otherElection);

    printHeading("7. Destructor in a separate scope");
    demonstrateScope();

    printHeading("8. Copy constructor and deep copy");
    demonstrateCopyConstructor(mainElection);

    printHeading("End of main: remaining objects are destroyed");
    return 0;
}
