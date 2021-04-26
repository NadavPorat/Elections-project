#pragma once
#include "Citizen.h"
#include "iostream"
using namespace std;

namespace elt
{
	//Citizen arrays class
	class CitizenArray 
	{
	private:
		Citizen* arr;
		int ls = 0;
		int ps = 1;

	public:
		CitizenArray();
		CitizenArray(int x);
		~CitizenArray();

		////////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
		bool addCitizen(Citizen& citizen);
		bool resize(int size);
		void setLs() { this->ls += 1; };

		////////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
		Citizen* getCitizen(int id) const;
		Citizen* getArr() const;
		int getCitizenArrayLogSize() const;

		////////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
		void printPartyCandidates(int delNum, char* partyName);
		void printCitizensArray() const;
		CitizenArray& operator=(CitizenArray& cit);

	};
}