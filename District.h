#pragma once
#include <string>
#include <iostream>
#include "Citizen.h"

using namespace std;

namespace elt
{
	class Citizen;
	class District {
	private:
		char* DistrictName;        // District name
		int NumOfCitizen = 0;      // num of citizens in the district
		int DistrictID;            // the ID of the district
		int Electors;              // number of electors
		bool isDivided;            // 'true' if the current district is dived , else 'false'
		int sizePartyDis;          // the amount of parties in the current district
		int votersCounter;         // Count votes in the district
		float votersPercentage;    // The percentage of votes in the current district

		int* votePartyList;         //Array that keeps the votes for every party in the district
		Citizen* winnerPartyHead;   // The winning party head
		int WinnerIDF;              // to load from file


	public:
		// funcs for result
		District(); // default district builder
		District(const District& dis); // default district builder
		District(const char* _name, int  numElector);
		~District();// district distructor

		///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
		void setNumOfCitizen();
		void setVotersCounter();
		bool setvotersPercentage();
		bool setWinnerPartyHead(Citizen* c);
		void fitPartyList(int ls);
		bool setName(const char* n);
		void setIsDivided(bool b);
		int setNumOfVotesPerParty(int partySerialNum, int votes);
		///////////////////////////////////////////////Add Funcs////////////////////////////////////////////////
		void VoteAdd(int partyNum);

		///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
		int GetDistrictID() const;
		bool getIsDivided() const;
		char* getNameDistrict() const;
		int getElectors() const;
		int GetvotersPercentage();
		int getTotalVotes() const;
		int getwinnerId() const;
		int getSumVote(int partySerialNum);
		int getSizePartyList() const;
		int getWinnerParty(int& votes);
		void calculateElectorsDividing(int* arr, float* carryArr, int& electorsDivided);
		int getNumOfVotesPerParty(int partySerialNum) const;
		int* GetVoteListForParty();

		///////////////////////////////////////////////Prints Funcs////////////////////////////////////////////////
		friend ostream& operator<<(ostream& os, const District& dis);
		District& operator=(District& dis);
		Citizen* getWinnerPartyHead() const;


		///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
		void save(ostream& out);
		void load(istream& in);
	};
}