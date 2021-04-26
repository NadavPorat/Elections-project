#pragma once
#include "iostream"
#include "DistrictArray.h"
#include <string.h>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace elt
{
	class District;
	class Citizen {
	private:
		bool voted;               // The parameter that indicates if the current Citizen voted. 'true' if he Voted , else 'false'
		char* name;               // The Name of the current Citizen
		int  BirthYear;           // The Birth Year of the current Citizen
		int ID;                   // The Citizen's ID
		District* dis = nullptr;  // Pointer to the District of the current Citizen
		int DisID;                // The Citizen's District ID
		bool isCandidate;         // The parameter that indicates if the current Citizen is Candidate. 'true' if he is , else 'false'

	public:
		Citizen(); 
		Citizen(const Citizen& cit);
		Citizen(const char* name, int ID, int BirthYear, District* newDis);
		~Citizen();

		////////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
		void setCitDistrict(District* newDis);
		bool setID(int id);
		bool setBirthYear(int birthYear);
		bool setName(const char* name);
		bool setVote(bool vote);
		void setIsCandidate(bool b);

		////////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
		const char* getName() const;
		int getBirthYear() const;
		int getID() const;
		int getDistrictID() const;
		District* getDistrict() const;
		const bool getIsCandidate() const;
		bool getVote()const;
		int getDisIDFromFile() const;

		///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
		friend ostream& operator<<(ostream& os, const Citizen& citizen);
		Citizen& operator=(const Citizen& cit);

		///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
		void save(ostream& out) const;
		void load(istream& in);
	};
}
