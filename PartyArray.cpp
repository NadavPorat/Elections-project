
#include "PartyArray.h"
using namespace std;

namespace elt
{
		///////////////////////////////////////////////Ctor////////////////////////////////////////////////
	PartyArray::PartyArray() : ls(0), ps(1), arr(new Party[1]) {}

	PartyArray::~PartyArray()
	{
		delete[] arr;
		ls = 0;
		ps = 1;
	}
		///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
	bool PartyArray::resize(int size)
	{
		if (size <= 0)
			return false;
		Party* tempP = new Party[size];
		if (tempP == nullptr)
			return false;
		for (int i = 0; i < this->ls; ++i) {
			tempP[i] = arr[i];
		}
		arr = tempP;
		this->ps = size;
		return true;
	}

	bool PartyArray::addParty(Party& val) 
	{
		if (ps == ls)
		{
			if (!resize(ps * 2))
				return false;
		}
		for (int i = 0; i < ls; ++i) 
		{

			if (arr[i].getHeadParty()->getID() == val.getHeadParty()->getID())
			{
				cout << "ERROR!! your Candidate is Already a Head Of another Party" << endl;
			}
		}
		arr[ls] = val;
		ls++;
		return true;
	}

	void PartyArray::resetDataCalc()
	{
		for (int i = 0; i < ls; i++)
		{
			arr[i].setNumOfReps(0);
			arr[i].setNumOfRepsForPresident(0);
			arr[i].setSumOfVote(0);
		}
	}

	void PartyArray::SortPartyListBySumOfDel(int n)
	{
		int i, j, minIdx;
		Party temp;

		for (i = 0; i < n; i++) {
			minIdx = i;
			for (j = i + 1; j < n; j++)
			{
				if (arr[j].getNumOfRepsForPresident() < arr[minIdx].getNumOfRepsForPresident())
					minIdx = j;
				else
				{
					temp = arr[j];
					arr[j] = arr[minIdx];
					arr[minIdx] = temp;
				}
			}
		}
	}

	void PartyArray::sortPartiesInSimpleElectionsRound(int n)
	{
		int Idx, j, minIdx;
		Party temp;

		for (Idx = 0; Idx < n; Idx++)
		{
			minIdx = Idx;
			for (j = Idx + 1; j < n; j++)
			{
				if (arr[j].getSumOfVote() < arr[minIdx].getSumOfVote())
					minIdx = j;
				else {
					temp = arr[j];
					arr[j] = arr[minIdx];
					arr[minIdx] = temp;
				}
			}
		}
	}

	///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
	int PartyArray::getPartyLogSize() const
	{
		return this->ls;
	}
	Party* PartyArray::getPArr() const {
		return arr;
	}

	bool PartyArray::isEnoughDeligates(int numOfDel, int disNum, int partyNum)
	{
		return(arr[partyNum - 1].EnoughDeligares(numOfDel, disNum));
	}

	Party* PartyArray::getParty(int SerialNum) const
	{
		for (int i = 0; i < ls; ++i)
		{
			if (arr[i].getSerialNum() == SerialNum)
				return (arr + i);
		}
		return nullptr;
	}

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	void PartyArray::printPartyArray() const
	{
		int i;

		for (i = 0; i < this->ls; i++)
		{
			cout << "Party #" << (i + 1) << " is: " << endl;
			cout << arr[i] << endl;
		}
	}

	void PartyArray::printElectedCandidates(int numOfelectors, int partySerialNum, int disSerialNum)
	{
		int size = arr[partySerialNum - 1].getnumOfcandidates();
		if (size > 0)
		{
			arr[partySerialNum - 1].printDeligatesPerDistrict(numOfelectors, disSerialNum);
		}
	}

	bool PartyArray::addToTotal(int partySerialNum, int delNum, int votesNum)
	{
		if (partySerialNum <= 0)
		{
			return false;
		}
		Party* p = getParty(partySerialNum);
		p->addToSumOfDeligatesForPresident(delNum);
		p->addToSumOfDeligates(delNum);
		p->addToSumOfVotes(votesNum);
		return true;
	}
}