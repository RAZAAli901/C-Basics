/*
Name:Raza Ali Murtaza
Registration: L1F25BSCS0615
Section: C6
Assignment: One (Part Two - Election.h)

Problem Statement:
8 parties participated in an election and their votes are recorded in a text
file "votes.txt". The first number is the total number of votes and every
following number is the ID of the party that received that vote (1 = PPP,
2 = PML-N, and so on). Read the votes from the file, count the votes of each
party, and write a results table and a sorted star graph into "results.txt".
The program must be class-based (class Election), use dynamic arrays, must not
use std::string or vectors, and main must not contain cin, cout or math.
*/

#ifndef ELECTION_H
#define ELECTION_H

#include <fstream>

// 1. Class Declaration
class Election
{
private:
    int totalVotes;
    int totalParties;
    int* voteCounts;
    int* partyIds;
    char** partyNames;
    char* electionName;

    void createArrays(int parties);
    void deleteArrays();
    void loadPartyNames();
    void resetVoteCounts();
    void setElectionName(const char* title);
    void swapTwoIndexes(int& first, int& second) const;
    void sortIndexesByVotes(int* indexes) const;
    void readTotalVotes(std::ifstream& inputFile);
    void readAllVotes(std::ifstream& inputFile);
    void writeStars(std::ofstream& outputFile, int count) const;
    void writeTableToFile(std::ofstream& outputFile) const;
    void writeGraphToFile(std::ofstream& outputFile) const;

public:
    // Constructors and destructor
    Election();
    Election(int parties, int votes = 0);
    Election(const char* title, int parties);
    Election(const Election& other);
    ~Election();

    // Setters
    void setTotalVotes(int votes);
    void setVotesOfParty(int partyId, int votes);

    // Getters
    int getTotalVotes() const;
    int getTotalParties() const;
    int getVotesOfParty(int partyId) const;
    int getTotalCountedVotes() const;
    int getLeadingPartyId() const;
    const char* getPartyName(int partyId) const;
    const int* getVoteCountsAddress() const;

    // Other member functions
    bool isValidPartyId(int partyId) const;
    bool addVote(int partyId);
    bool readVotesFile(const char* fileName);
    bool writeResultsFile(const char* fileName) const;
    void displayInfo() const;
};

// 2. Global Function Prototypes
int getTextLength(const char* text);
int getDigitCount(int number);
char* duplicateText(const char* text);
void copyText(char* destination, const char* source);
void writeSpaces(std::ofstream& outputFile, int count);
void writePaddedText(std::ofstream& outputFile, const char* text, int width);
void printHeading(const char* text);
void demonstrateConstructors();
void demonstrateSettersAndGetters(Election& election);
void processElectionFiles(Election& election);
void showPartyVotes(const Election& election, int partyId);
void showElectionByValue(Election election);
void updatePartyVotes(Election& election, int partyId, int votes);
void compareElections(const Election& firstElection, const Election& secondElection);
void demonstrateScope();
void demonstrateCopyConstructor(const Election& original);

#endif
