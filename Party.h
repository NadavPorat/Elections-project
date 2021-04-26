#pragma once
#include "CitizenArray.h"
#include "Citizen.h"
#include "District.h"
#include <algorithm>

namespace elt
{
	class Party {
	private:
		char* PartyName;               //The Party Name
		int PartyID;                   // The Party ID
		int numOfCandidates;           // The Number of the Cnadidates in the current Party
		int sumOfVotes;                // Sum Votes for the current Party
		int numOfRepsForPresident = 0; // Number Of the Representatives For The President
		int numOfReps = 0;             // The Representatives of the Party (Updated after the election calculations)
		int headOfPartyID = 0;         // The ID of the Head Of The current Party
		Citizen* HeadOfParty;          // Pointer to the Head Of The current Party
		int len = 0;                   //The Length Of the Candidates Of the current Party
		CitizenArray* CandidatesArr;   // The Candidates Array Of the current Party

	public:
		Party();
		Party(const char* newName, Citizen* primCan);
		~Party();

		///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
		bool setNameParty(const char* _name);
		bool setSerialNum(int num);
		void setSumOfVote(int num);
		void setNumOfReps(int num);
		void setNumOfRepsForPresident(int num);
		bool setHeadOfParty(Citizen* c);

		///////////////////////////////////////////////Init Funcs////////////////////////////////////////////////
		void Add_Party(const char* partyName, int& primPartyID);
		void addCitizenAsCandidate(Citizen& citizen, District& Dis);
		void addToSumOfDeligates(int repNum);
		void addToSumOfDeligatesForPresident(int repNum);
		void addToSumOfVotes(int votesNum);
	

		///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
		char* getNameParty() const;
		Citizen* getHeadParty() const;
		int getSerialNum() const;
		bool EnoughDeligares(int numOfDel, int disNum);
		int getSumOfVote() const;
		int getheadOfPartyID() const;
		int getnumOfcandidates();
		int getNumOfRrpElected() const;
		int getNumOfRepsForPresident() const { return this->numOfRepsForPresident; };

		///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
		friend ostream& operator<<(ostream& os, const Party& dis);
		Party& operator=(Party& pty);
		void PrintCandidatesArr(int delNum, int disNum);
		void printDeligatesPerDistrict(int delNum, int disNum);

		///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
		void save(ostream& out_file) const;
		void load(istream& in);
	};
}
