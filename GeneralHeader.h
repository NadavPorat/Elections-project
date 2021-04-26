///////////////////////////////////////////////The General Header////////////////////////////////////////////////
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "Citizen.h"
#include "ElectionsRound.h"
#include "District.h"
#include "Party.h"

///////////////////////////////////////////////Enums////////////////////////////////////////////////
// Enums for the First menu:
enum class func
{
	f1 = 1, //"1. Create New Elections Round"
	f2,     //"2. Load Elections Round"
	f3      //"3. Exit"
};

// Enums for the main menu:
enum class action
{
	ac1 = 1, //"1. Add District"
	ac2,     //"2. Add Citizen"
	ac3,     //"3. Add Party"
	ac4,     //"4. Add Candidate"
	ac5,     //"5. Show Districts List"
	ac6,     //"6. Show Citizens List"
	ac7,     //"7. Show Parties List"
	ac8,     //"8. Vote"
	ac9,     //"9. Show Elections Result"
	ac10,    //"10. Exit"
	ac11,    //"11. Save Elections Round to file"
	ac12     //"12. Load Elections Round from file"
};

constexpr int NAMELEN{ 1024 };//MAX NAME LENGTH - used especialy for 'names'

using namespace std;
namespace elt
{
	///////////////////////////////////////////////Regular Funcs////////////////////////////////////////////////
	void readCitizen(ElectionsRound& er);
	void readDistrict(ElectionsRound& er);
	void read_Candidate(ElectionsRound& er);
	void read_Party(ElectionsRound& er);
	void vote(ElectionsRound& er);
	void ResultsR(ElectionsRound& er);

	///////////////////////////////////////////////Simple Elections Round Funcs////////////////////////////////////////////////
	void readCitizenS(SimpleElectionsRound& er);
	void read_CandidateS(SimpleElectionsRound& er);
	void ResultsS(SimpleElectionsRound& er);

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	void PrintMainMenu();
	void PrintFirstMenu();
}