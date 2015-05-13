/*
Database Input File Generator.
Written by Andrew Hill.

You can change any of the min/max values for the RNGs like this:

std::uniform_int_distribution<int> dist(MIN_GOES_HERE,MAX_GOES_HERE);

These can be any value. Some values generate incorrect numbers though, so check the file before
using it as an input.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <time.h>
std::string intToString(int input);
std::string randomPhoneNumber();
std::string randomID();
std::string randomHouseNumber();
std::string randomZip();
std::vector<std::string> readFile(std::ifstream &input);
int main(int argc, char *argv[]) {
	int numOfContacts = 50; // Change this to change the number of contacts that are generated.
	// Seeds the RNG.
	srand(time(NULL)); 

	// Input streams for the different categories.
	std::ifstream stateInput("StateList.txt");	
	std::ifstream cityInput("CitiesList.txt");
	std::ifstream firstNames("FirstName.txt");
	std::ifstream lastNames("LastName.txt");
	std::ifstream companies("CompaniesList.txt");
	std::ifstream streets("Streets.txt");

	// Reads each file into a vector of strings.
	std::vector<std::string> States = readFile(stateInput);	
	std::vector<std::string> Cities = readFile(cityInput);
	std::vector<std::string> FNames = readFile(firstNames);
	std::vector<std::string> LNames = readFile(lastNames);
	std::vector<std::string> Companies = readFile(companies);
	std::vector<std::string> Streets = readFile(streets);
	std::vector<std::string> emailSuffixes{ "comcast.net", "gmail.com", "icloud.com","yahoo.com" };

	// Output file stream.
	std::ofstream output;
	
	// Pass the name of the output file as a command line argument.
	if (argc < 2) {
		output.open(argv[1]); // Replace this with the name of the output file if you're not running it from a command line.
	}
	else {
		output.open("output.txt");
	}
	// Main loop.
	for (int i = 0; i < numOfContacts; i++) {
		std::string FirstName = FNames.at(rand() % FNames.size());	// Strings to hold First Name and Last Name so they can be used again in the Email address.
		std::string LastName = LNames.at(rand() % LNames.size());
		output << randomID() << std::endl;				// Random ID Number.
		output << FirstName << std::endl;				// First Name.
		output << FNames.at(rand() % FNames.size()) << std::endl;  	// First Name vector chooses a random entry to be a Middle Name.
		output << LastName << std::endl;				// Last Name.
		output << Companies.at(rand() % Companies.size()) << std::endl;	// Chooses a random company
		output << randomPhoneNumber() << std::endl;			// Home Phone.	(These all use the same function)
		output << randomPhoneNumber() << std::endl;			// Office Phone.
		output << LastName << "." << FirstName << "@" << emailSuffixes.at(rand() % 4) << std::endl;	// Random Email.
		output << randomPhoneNumber() << std::endl;			// Cell Phone.
		output << randomHouseNumber() << " " << Streets.at(rand() % Streets.size()) << " Street"  << std::endl;	// Street Address
		output << Cities.at(rand() % Cities.size()) << std::endl;	// City.
		output << States.at(rand() % States.size()) << std::endl;	// State.
		output << randomZip() <<std::endl;				// Zip code.
		output << "United States of America" << std::endl;		// Country.
		output << "|" << std::endl;					// Delimiter.
	}
	

	return 0;
}


// Makes a random phone number. 
std::string randomPhoneNumber() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_int_distribution<int> dist(1000000000,2000000000);
	int randomInt = dist(generator);
	return intToString(randomInt);
}

// Makes a random Zip Code.
std::string randomZip() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_int_distribution<int> dist(10000, 99999);
	int randomInt = dist(generator);
	return intToString(randomInt);
}

// Makes a random ID. 
// Theoretically there could be ID conflicts here, but I haven't found any yet.
std::string randomID() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_int_distribution<int> dist(100000000,120000000);
	int randomInt = dist(generator);
	return intToString(randomInt);
}

// Generates a random House Number.
std::string randomHouseNumber() {
	std::random_device seed;
	std::mt19937 generator(seed());
	std::uniform_int_distribution<int> dist(1000,9999);
	int randomInt = dist(generator);
	return intToString(randomInt);
}

// Reads a file when given an input stream.
std::vector<std::string> readFile(std::ifstream &input) {
	std::vector<std::string> returnVector;
	std::string currentLine;
	while (!input.eof()) {
		getline(input, currentLine);
		returnVector.push_back(currentLine);
	}
	input.close();
	return returnVector;
}

// Converts an int to a string.
std::string intToString(int input) {
	std::stringstream stream;
	stream << input;
	return stream.str();
}
