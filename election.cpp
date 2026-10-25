/*
Name: Raza Ali Murtaza
Registration: L1F25BSCS0615
Section: C6
Assignment: One (Part Two - Election.cpp)

Problem Statement:
8 parties participated in an election and their votes are recorded in a text
file "votes.txt". The first number is the total number of votes and every
following number is the ID of the party that received that vote (1 = PPP,
2 = PML-N, and so on). Read the votes from the file, count the votes of each
party, and write a results table and a sorted star graph into "results.txt".
The program must be class-based (class Election), use dynamic arrays, must not
use std::string or vectors, and main must not contain cin, cout or math.
*/

#include <iostream>
#include <fstream>
#include "Election.h"
using namespace std;

// 3. Class Member Function Definitions

// Private helper functions

void Election::createArrays(int parties)
{
    totalParties = parties;
    voteCounts = new int[totalParties];
    partyIds = new int[totalParties];
    partyNames = new char*[totalParties];

    for (int i = 0; i < totalParties; i++)
    {
        voteCounts[i] = 0;
        partyIds[i] = i + 1;
        partyNames[i] = nullptr;
    }
}

void Election::deleteArrays()
{
    for (int i = 0; i < totalParties; i++)
    {
        delete[] partyNames[i];
        partyNames[i] = nullptr;
    }

    delete[] partyNames;
    delete[] voteCounts;
    delete[] partyIds;
    delete[] electionName;

    partyNames = nullptr;
    voteCounts = nullptr;
    partyIds = nullptr;
    electionName = nullptr;
}

void Election::loadPartyNames()
{
    const char* knownNames[8] = {"PPP", "PML-N", "PTI", "ANP", "JIP", "JUI", "MQM", "PAT"};

    for (int i = 0; i < totalParties; i++)
    {
        if (i < 8)
        {
            partyNames[i] = duplicateText(knownNames[i]);
        }
        else
        {
            partyNames[i] = duplicateText("PARTY");
        }
    }
}

void Election::resetVoteCounts()
{
    for (int i = 0; i < totalParties; i++)
    {
        voteCounts[i] = 0;
    }

    totalVotes = 0;
}

void Election::setElectionName(const char* title)
{
    delete[] electionName;

    if (title == nullptr)
    {
        electionName = duplicateText("Election");
    }
    else
    {
        electionName = duplicateText(title);
    }
}

void Election::swapTwoIndexes(int& first, int& second) const
{
    int temporary = first;

    first = second;
    second = temporary;
}

void Election::sortIndexesByVotes(int* indexes) const
{
    for (int i = 0; i < totalParties; i++)
    {
        indexes[i] = i;
    }

    // Bubble sort on the indexes (highest votes first).
    // Swap only when strictly smaller, so equal votes keep the ID order.
    for (int pass = 0; pass < totalParties - 1; pass++)
    {
        for (int j = 0; j < totalParties - 1 - pass; j++)
        {
            if (voteCounts[indexes[j]] < voteCounts[indexes[j + 1]])
            {
                swapTwoIndexes(indexes[j], indexes[j + 1]);
            }
        }
    }
}

void Election::readTotalVotes(ifstream& inputFile)
{
    int value = 0;

    inputFile >> value;

    if (!inputFile)
    {
        cout << "Could not read the total number of votes." << endl;
        value = 0;
    }

    setTotalVotes(value);
    cout << "Total votes announced in file: " << totalVotes << endl;
}

void Election::readAllVotes(ifstream& inputFile)
{
    int partyId = 0;
    int validCount = 0;
    int invalidCount = 0;

    for (int i = 0; i < totalVotes; i++)
    {
        if (!(inputFile >> partyId))
        {
            cout << "File ended before all votes were read." << endl;
            break;
        }

        if (addVote(partyId))
        {
            validCount++;
        }
        else
        {
            invalidCount++;
        }
    }

    cout << "Valid votes counted: " << validCount << endl;
    cout << "Invalid votes ignored: " << invalidCount << endl;
}

void Election::writeStars(ofstream& outputFile, int count) const
{
    for (int i = 0; i < count; i++)
    {
        outputFile << '*';
    }

    outputFile << endl;
}

void Election::writeTableToFile(ofstream& outputFile) const
{
    writePaddedText(outputFile, "Party Name", 17);
    writePaddedText(outputFile, "Party ID", 12);
    outputFile << "Votes" << endl;
    outputFile << "----------------- ------------ --------" << endl;

    for (int i = 0; i < totalParties; i++)
    {
        writePaddedText(outputFile, partyNames[i], 17);
        outputFile << partyIds[i];
        writeSpaces(outputFile, 12 - getDigitCount(partyIds[i]));
        outputFile << voteCounts[i] << endl;
    }

    outputFile << endl;
}

void Election::writeGraphToFile(ofstream& outputFile) const
{
    int* sortedIndexes = new int[totalParties];

    sortIndexesByVotes(sortedIndexes);

    for (int i = 0; i < totalParties; i++)
    {
        int index = sortedIndexes[i];

        writePaddedText(outputFile, partyNames[index], 8);
        writeStars(outputFile, voteCounts[index]);
    }

    delete[] sortedIndexes;
}

// Constructors and destructor

Election::Election()
{
    totalVotes = 0;
    totalParties = 0;
    voteCounts = nullptr;
    partyIds = nullptr;
    partyNames = nullptr;
    electionName = nullptr;

    createArrays(8);
    loadPartyNames();
    setElectionName("Election");

    cout << "[Default constructor] called for: " << electionName << endl;
}

Election::Election(int parties, int votes)
{
    totalVotes = 0;
    totalParties = 0;
    voteCounts = nullptr;
    partyIds = nullptr;
    partyNames = nullptr;
    electionName = nullptr;

    if (parties <= 0)
    {
        cout << "Invalid number of parties. Using 8." << endl;
        parties = 8;
    }

    if (votes < 0)
    {
        cout << "Invalid total votes. Using 0." << endl;
        votes = 0;
    }

    createArrays(parties);
    loadPartyNames();
    setElectionName("Election");
    totalVotes = votes;

    cout << "[Parameterized constructor] called for: " << electionName << endl;
}

Election::Election(const char* title, int parties)
{
    totalVotes = 0;
    totalParties = 0;
    voteCounts = nullptr;
    partyIds = nullptr;
    partyNames = nullptr;
    electionName = nullptr;

    if (parties <= 0)
    {
        cout << "Invalid number of parties. Using 8." << endl;
        parties = 8;
    }

    createArrays(parties);
    loadPartyNames();
    setElectionName(title);

    cout << "[Overloaded constructor (title, parties)] called for: " << electionName << endl;
}

Election::Election(const Election& other)
{
    totalVotes = other.totalVotes;
    totalParties = 0;
    voteCounts = nullptr;
    partyIds = nullptr;
    partyNames = nullptr;
    electionName = nullptr;

    createArrays(other.totalParties);

    for (int i = 0; i < totalParties; i++)
    {
        voteCounts[i] = other.voteCounts[i];
        partyIds[i] = other.partyIds[i];
        partyNames[i] = duplicateText(other.partyNames[i]);
    }

    setElectionName(other.electionName);

    cout << "[Copy constructor] called for: " << electionName << endl;
}

Election::~Election()
{
    cout << "[Destructor] called for: " << electionName << endl;

    deleteArrays();
}

// Setters 
void Election::setTotalVotes(int votes)
{
    if (votes < 0)
    {
        cout << "Invalid total votes (" << votes << "). Old value kept." << endl;
        return;
    }

    totalVotes = votes;
}

void Election::setVotesOfParty(int partyId, int votes)
{
    if (!isValidPartyId(partyId))
    {
        cout << "Invalid party ID (" << partyId << "). Old data kept." << endl;
        return;
    }

    if (votes < 0)
    {
        cout << "Invalid vote count (" << votes << "). Old data kept." << endl;
        return;
    }

    voteCounts[partyId - 1] = votes;
}

// Getters
int Election::getTotalVotes() const
{
    return totalVotes;
}

int Election::getTotalParties() const
{
    return totalParties;
}

int Election::getVotesOfParty(int partyId) const
{
    if (!isValidPartyId(partyId))
    {
        return -1;
    }

    return voteCounts[partyId - 1];
}

int Election::getTotalCountedVotes() const
{
    int sum = 0;

    for (int i = 0; i < totalParties; i++)
    {
        sum = sum + voteCounts[i];
    }

    return sum;
}

int Election::getLeadingPartyId() const
{
    int leadingIndex = 0;

    for (int i = 1; i < totalParties; i++)
    {
        if (voteCounts[i] > voteCounts[leadingIndex])
        {
            leadingIndex = i;
        }
    }

    return partyIds[leadingIndex];
}

const char* Election::getPartyName(int partyId) const
{
    if (!isValidPartyId(partyId))
    {
        return "Unknown";
    }

    return partyNames[partyId - 1];
}

const int* Election::getVoteCountsAddress() const
{
    return voteCounts;
}

// Other member functions 

bool Election::isValidPartyId(int partyId) const
{
    if (partyId >= 1 && partyId <= totalParties)
    {
        return true;
    }

    return false;
}

bool Election::addVote(int partyId)
{
    if (!isValidPartyId(partyId))
    {
        cout << "Ignored invalid party ID in file: " << partyId << endl;
        return false;
    }

    voteCounts[partyId - 1]++;
    return true;
}

bool Election::readVotesFile(const char* fileName)
{
    ifstream inputFile;

    inputFile.open(fileName);

    if (!inputFile)
    {
        cout << "Could not open file: " << fileName << endl;
        return false;
    }

    resetVoteCounts();
    readTotalVotes(inputFile);
    readAllVotes(inputFile);
    inputFile.close();

    return true;
}

bool Election::writeResultsFile(const char* fileName) const
{
    ofstream outputFile;

    outputFile.open(fileName);

    if (!outputFile)
    {
        cout << "Could not create file: " << fileName << endl;
        return false;
    }

    writeTableToFile(outputFile);
    writeGraphToFile(outputFile);
    outputFile.close();

    return true;
}

void Election::displayInfo() const
{
    cout << "Election: " << electionName << endl;
    cout << "Announced votes: " << totalVotes << endl;

    for (int i = 0; i < totalParties; i++)
    {
        cout << "  " << partyNames[i] << " (ID " << partyIds[i] << "): " << voteCounts[i] << endl;
    }

    cout << "Counted votes: " << getTotalCountedVotes() << endl;
}

// 4. Global Function Definitions

int getTextLength(const char* text)
{
    int length = 0;

    while (text[length] != '\0')
    {
        length++;
    }

    return length;
}

int getDigitCount(int number)
{
    int digitCount = 1;
    int remaining = number;

    while (remaining >= 10)
    {
        remaining = remaining / 10;
        digitCount++;
    }

    return digitCount;
}

char* duplicateText(const char* text)
{
    int length = getTextLength(text);
    char* newText = new char[length + 1];

    copyText(newText, text);

    return newText;
}

void copyText(char* destination, const char* source)
{
    int i = 0;

    while (source[i] != '\0')
    {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0';
}

void writeSpaces(ofstream& outputFile, int count)
{
    for (int i = 0; i < count; i++)
    {
        outputFile << ' ';
    }
}

void writePaddedText(ofstream& outputFile, const char* text, int width)
{
    int spacesNeeded = width - getTextLength(text);

    outputFile << text;

    if (spacesNeeded < 1)
    {
        spacesNeeded = 1;
    }

    writeSpaces(outputFile, spacesNeeded);
}

void printHeading(const char* text)
{
    cout << endl;
    cout << "==================================================" << endl;
    cout << text << endl;
    cout << "==================================================" << endl;
}

void demonstrateConstructors()
{
    Election defaultElection;
    Election parameterizedElection(8);
    Election defaultArgumentElection(8, 45);
    Election overloadedElection("Local Election", 3);
    Election invalidElection(-2, -5);

    cout << endl;
    defaultElection.displayInfo();
    cout << endl;
    overloadedElection.displayInfo();
    cout << endl;
    cout << "Objects now go out of scope, destructors will run." << endl;
}

void demonstrateSettersAndGetters(Election& election)
{
    cout << "Setting party 3 votes to 10 (valid):" << endl;
    election.setVotesOfParty(3, 10);
    cout << "Setting party 9 votes to 10 (invalid ID):" << endl;
    election.setVotesOfParty(9, 10);
    cout << "Setting party 2 votes to -5 (negative votes):" << endl;
    election.setVotesOfParty(2, -5);
    cout << "Setting total votes to -1 (invalid):" << endl;
    election.setTotalVotes(-1);

    cout << "Getter: votes of party 3 = " << election.getVotesOfParty(3) << endl;
    cout << "Getter: votes of party 2 = " << election.getVotesOfParty(2) << endl;
    cout << "Getter: total votes = " << election.getTotalVotes() << endl;
    cout << "Getter: total parties = " << election.getTotalParties() << endl;
}

void processElectionFiles(Election& election)
{
    bool readOk = election.readVotesFile("votes.txt");

    if (!readOk)
    {
        cout << "Results were not written because votes could not be read." << endl;
        return;
    }

    bool writeOk = election.writeResultsFile("results.txt");

    if (writeOk)
    {
        cout << "results.txt written successfully." << endl;
    }

    election.displayInfo();
}

void showPartyVotes(const Election& election, int partyId)
{
    cout << "Back in main, votes of party " << partyId << " (";
    cout << election.getPartyName(partyId) << ") are still: ";
    cout << election.getVotesOfParty(partyId) << endl;
    cout << "(The function worked on a copy, so the original is unchanged.)" << endl;
}

void showElectionByValue(Election election)
{
    cout << "Inside showElectionByValue (working on a COPY):" << endl;
    election.displayInfo();
    election.setVotesOfParty(1, 0);
    cout << "Copy changed party 1 votes to 0. Leaving function..." << endl;
}

void updatePartyVotes(Election& election, int partyId, int votes)
{
    cout << "Before update, party " << partyId << " votes: " << election.getVotesOfParty(partyId) << endl;
    election.setVotesOfParty(partyId, votes);
    cout << "After update,  party " << partyId << " votes: " << election.getVotesOfParty(partyId) << endl;
    cout << "(Reference used, so the original object is changed.)" << endl;
}

void compareElections(const Election& firstElection, const Election& secondElection)
{
    int firstTotal = firstElection.getTotalCountedVotes();
    int secondTotal = secondElection.getTotalCountedVotes();

    cout << "First election total votes:  " << firstTotal << endl;
    cout << "Second election total votes: " << secondTotal << endl;
    cout << "First election leader:  " << firstElection.getPartyName(firstElection.getLeadingPartyId()) << endl;
    cout << "Second election leader: " << secondElection.getPartyName(secondElection.getLeadingPartyId()) << endl;

    if (firstTotal > secondTotal)
    {
        cout << "The first election has more votes." << endl;
    }
    else if (secondTotal > firstTotal)
    {
        cout << "The second election has more votes." << endl;
    }
    else
    {
        cout << "Both elections have the same number of votes." << endl;
    }
}

void demonstrateScope()
{
    cout << "Entering the inner block..." << endl;

    {
        Election scopedElection("Scoped Election", 4);

        scopedElection.displayInfo();
        cout << "About to leave the inner block..." << endl;
    }

    cout << "Left the inner block. The destructor message above shows it ran." << endl;
}

void demonstrateCopyConstructor(const Election& original)
{
    Election copyOne(original);
    Election copyTwo = original;

    cout << "Address of original votes array: " << original.getVoteCountsAddress() << endl;
    cout << "Address of copyOne  votes array: " << copyOne.getVoteCountsAddress() << endl;
    cout << "Address of copyTwo  votes array: " << copyTwo.getVoteCountsAddress() << endl;

    cout << "Changing party 1 votes in copyOne to 999..." << endl;
    copyOne.setVotesOfParty(1, 999);

    cout << "Original party 1 votes: " << original.getVotesOfParty(1) << endl;
    cout << "copyOne  party 1 votes: " << copyOne.getVotesOfParty(1) << endl;
    cout << "copyTwo  party 1 votes: " << copyTwo.getVotesOfParty(1) << endl;
}
