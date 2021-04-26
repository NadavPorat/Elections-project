
#pragma once
#include "Party.h"

namespace elt
{
	//Citizen arrays class
	class PartyArray
	{
	private:
		Party* arr;
		int ls = 0;
		int ps = 0;

	public:
		///////////////////////////////////////////////Ctor////////////////////////////////////////////////
		PartyArray();
		~PartyArray();

		///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
		bool resize(int size);
		void setLs() { this->ls += 1; };
		bool addParty(Party& val);
		bool addToTotal(int partySerialNum, int delNum, int votesNum);
		void SortPartyListBySumOfDel(int n);
		void sortPartiesInSimpleElectionsRound(int n);
		void resetDataCalc();

		///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
		Party* getParty(int idx) const;
		Party* getPArr() const;
		int getPartyLogSize() const;
		bool isEnoughDeligates(int numOfDel, int disNum, int partyNum);

		///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
		void printPartyArray() const;
		void printElectedCandidates(int numOfelectors, int partySerialNum, int disSerialNum);
	};
}