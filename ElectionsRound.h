#pragma once
#include <iostream>
#include "CitizenArray.h"
#include "DistrictArray.h"
#include "PartyArray.h"


namespace elt
{		///////////////////////////////////////////////Base Class ElectionsRound////////////////////////////////////////////////

	class ElectionsRound
	{
	protected:
		int day, month, year;        // The Date Of The current Elections Round
		int kind;                    // The Kind Of the Elections Round. 1 = Regular , 2 = Simple , else 0.
		CitizenArray* CitizensArr;   // Pointer to CitizenArray - keep the Citizens in it's 'arr' parameter
		PartyArray* PartyArr;        // Pointer to PartyArray - keep the Parties in it's 'arr' parameter
		DistrictArray* DistrictArr;  // Pointer to DistrictA - keep the Citizens in it's 'arr' parameter
	public:
		ElectionsRound();
		~ElectionsRound();
		ElectionsRound(int newDay, int mewMonth, int newYear); //Build ElectionsRound by inputs: day , month , year

		///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
		bool setDistrict(District& Dis);
		bool setParty(Party& party);
		bool setCitizen(Citizen& cit);
		void SetPartyWinnerAtDistrict();
		virtual void setDistrictDIV() {};
		bool setKind(int k);

		///////////////////////////////////////////////Add Funcs////////////////////////////////////////////////
		bool addCandidate(Citizen& citizen, Party& party, District& dis);
		bool addVote(Citizen& citizen, Party& party);

		///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
		CitizenArray& getCitizenArr();
		DistrictArray& getDistrictArr();
		PartyArray& getPartyArr();
		bool getValidResult();
		int getELRKind();

		///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
		void PrintDistricts();
		void PrintParties();
		void PrintCitizens();
		void PrintRegularELRResults();
		void PrintElctionsDate();
		void calcAndSetResultInDis();
		void calcAndPrintElectorsDivide();
		int findMaxCarry(float* carryArr, int size, int& lastMaxCarryIdx);

		///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
		void load(istream& in);
		void save(ostream& out_file)const;
		void connectPointers();
	};


		///////////////////////////////////////////////Child Class SimpleElectionsRound////////////////////////////////////////////////
	class SimpleElectionsRound : public ElectionsRound
	{
	public:
		SimpleElectionsRound();
		~SimpleElectionsRound();
		SimpleElectionsRound(int newDay, int mewMonth, int newYear, int elector);
		void setDistrictDIV();
		void PrintSimpleELRResults();
	};
}