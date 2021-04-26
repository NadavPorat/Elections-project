#include "Party.h"

using namespace std;

///////////////////////////////////////////////Party////////////////////////////////////////////////
namespace elt 
{
	Party::Party() : PartyName(nullptr), HeadOfParty(nullptr), PartyID(0), CandidatesArr(nullptr), numOfCandidates(0),
		sumOfVotes(0), numOfRepsForPresident(0), numOfReps(0), headOfPartyID(0)
	{
	}

	Party::Party(const char* newName, Citizen* primCan) : Party() 
	{
		static int serial = 1;
		int size = strlen(newName) + 1;
		PartyName = new char[size];
		memcpy(PartyName, newName, size);
		this->HeadOfParty = primCan;
		this->numOfCandidates = 0;
		this->PartyID = serial;
		serial++;
		primCan->setIsCandidate(true);
	}

	Party::~Party() 
	{
		if (PartyName != nullptr) 
		{
			delete[] PartyName;
			delete[] CandidatesArr;
		}
	}

	///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
	bool Party::setNameParty(const char* n) 
	{
		if (n == nullptr) {
			return false;
		}
		int size;
		size = strlen(n) + 1;
		PartyName = new char[size];
		memcpy(PartyName, n, size);
		return true;
	}

	bool Party::setSerialNum(int num) {
		if (num < 0)
			return false;
		PartyID = num;
		return true;
	}

	bool Party::setHeadOfParty(Citizen* c) {
		if (c == nullptr)
			return false;
		else {
			HeadOfParty = c;
			return true;
		}
	}

	void Party::setSumOfVote(int num)
	{
		this->sumOfVotes = num;
	}
	void Party::setNumOfReps(int num)
	{
		this->numOfReps = num;
	}
	void Party::setNumOfRepsForPresident(int num)
	{
		this->numOfRepsForPresident = num;
	}

	///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
	char* Party::getNameParty() const {
		return PartyName;
	}

	Citizen* Party::getHeadParty() const {
		return HeadOfParty;
	}

	int Party::getSerialNum() const {
		return PartyID;
	}

	int Party::getSumOfVote() const
	{
		return sumOfVotes;
	}

	bool Party::EnoughDeligares(int numOfDel, int disNum)
	{
		return ((CandidatesArr[disNum - 1].getCitizenArrayLogSize()) >= numOfDel);
	}

	int Party::getnumOfcandidates()
	{
		return numOfCandidates;
	}
	int Party::getheadOfPartyID() const
	{
		return headOfPartyID;
	}
	int Party::getNumOfRrpElected() const
	{
		return this->numOfReps;
	}

	///////////////////////////////////////////////Add Funcs////////////////////////////////////////////////
	void Party::addCitizenAsCandidate(Citizen& citizen, District& Dis) 
	{
		int i;
		int numDis = Dis.GetDistrictID();

		if (len == 0) {
			CandidatesArr = new CitizenArray[1];
			len = 1;
		}
		if (len < numDis)
		{
			CitizenArray* newCandidatesArr = new CitizenArray[numDis];
			for (i = 0; i < numDis; i++) 
			{
				CitizenArray tmp(0);
				newCandidatesArr[i] = tmp;
			}
			for (i = 0; i < len; i++)
			{
				newCandidatesArr[i] = CandidatesArr[i];
			}
			CandidatesArr = newCandidatesArr;
			len = numDis;
		}
		CandidatesArr[numDis - 1].addCitizen(citizen);
		citizen.setIsCandidate(true);
		numOfCandidates += 1;
	}

	Party& Party::operator=(Party& pty) 
	{
		if (this != &pty) {
			setNameParty(pty.PartyName);
			HeadOfParty = pty.HeadOfParty;
			PartyID = pty.PartyID;
			CitizenArray* CandidatesArr = pty.CandidatesArr;
			numOfCandidates = pty.numOfCandidates;
			sumOfVotes = pty.sumOfVotes;
			len = pty.len;
			numOfRepsForPresident = pty.numOfRepsForPresident;
			numOfReps = pty.numOfReps;
		}
		return *this;
	}

	void Party::addToSumOfDeligates(int repNum)
	{
		numOfReps = numOfReps + repNum;
	}

	void Party::addToSumOfDeligatesForPresident(int repNum)
	{
		numOfRepsForPresident = numOfRepsForPresident + repNum;

	}

	void Party::addToSumOfVotes(int votesNum)
	{
		sumOfVotes = sumOfVotes + votesNum;
	}

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	ostream& operator<<(ostream& os, const Party& party) 
	{
		if (party.getSumOfVote() == 0) {
			os << "Party Name: " << party.getNameParty();
			os << ", Serial number: " << party.PartyID << endl;
			os << "The Candidate to the Prime Minister is : ";
			os << *(party.HeadOfParty) << endl;
		}
		else {
			os << "Party Name: " << party.PartyName << endl;
			os << "The Candidate to the Prime Minister is: " << endl;
			os << *(party.HeadOfParty) << endl;
			os << "Sum of Candidates that Elected: " << party.numOfReps << endl;
			os << "Sum of votes in all Districts to this Party: " << party.sumOfVotes << endl;
		}
		return os;
	}

	void Party::PrintCandidatesArr(int delNum, int disNum) {
		CandidatesArr[disNum - 1].printPartyCandidates(delNum, PartyName);
	}

	void Party::printDeligatesPerDistrict(int delNum, int disNum) 
	{
		if (len < disNum - 1) {
			cout << "No Candidts In this District" << endl;
			return;
		}
		int size = CandidatesArr[disNum - 1].getCitizenArrayLogSize();
		if (size != 0) {
			CandidatesArr[disNum - 1].printPartyCandidates(delNum, PartyName);
		}
	}

	///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
	void Party::save(ostream& out_file) const
	{
		int sizeN = strlen(PartyName);
		int id;
		out_file.write(rcastcc(&sizeN), sizeof(int));
		for (int i = 0; i < sizeN; ++i) {
			out_file.write(rcastcc(&this->PartyName[i]), sizeof(char));
		}
		out_file.write(rcastcc(&this->PartyID), sizeof(int));
		out_file.write(rcastcc(&this->numOfCandidates), sizeof(int));
		out_file.write(rcastcc(&this->sumOfVotes), sizeof(int));
		out_file.write(rcastcc(&this->len), sizeof(int));
		out_file.write(rcastcc(&this->numOfRepsForPresident), sizeof(int));
		out_file.write(rcastcc(&this->numOfReps), sizeof(int));
		id = this->HeadOfParty->getID();
		out_file.write(rcastcc(&id), sizeof(int));
		for (int i = 0; i < this->len; ++i)
		{
			int CanArrInternalLS = CandidatesArr[i].getCitizenArrayLogSize();
			out_file.write(rcastcc(&CanArrInternalLS), sizeof(int));
			for (int j = 0; j < CanArrInternalLS; ++j) {
				CandidatesArr[i].getArr()[j].save(out_file);
			}
		}
	}

	void Party::load(istream& in)
	{
		int CanArrInternalLS = 0;
		int nameLen = 0;
		in.read(rcastc(&nameLen), sizeof(int));
		this->PartyName = new char[nameLen + 1];
		for (int i = 0; i < nameLen; ++i) {
			in.read(rcastc(&PartyName[i]), sizeof(char));
		}
		this->PartyName[nameLen] = '\0';
		in.read(rcastc(&this->PartyID), sizeof(int));
		in.read(rcastc(&this->numOfCandidates), sizeof(int));
		in.read(rcastc(&this->sumOfVotes), sizeof(int));
		in.read(rcastc(&this->len), sizeof(int));
		in.read(rcastc(&this->numOfRepsForPresident), sizeof(int));
		in.read(rcastc(&this->numOfReps), sizeof(int));
		in.read(rcastc(&this->headOfPartyID), sizeof(float));
		this->CandidatesArr = new CitizenArray[len];
		for (int i = 0; i < len; ++i)
		{
			in.read(rcastc(&CanArrInternalLS), sizeof(int));
			for (int j = 0; j < CanArrInternalLS; ++j) {
				this->CandidatesArr[i].getArr()[j].load(in);
			}
		}
	}
}