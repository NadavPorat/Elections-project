#include "District.h"

///////////////////////////////////////////////District////////////////////////////////////////////////
namespace elt
{
	District::District() :DistrictName(nullptr), DistrictID(1), NumOfCitizen(0), Electors(0), votersPercentage(0), votersCounter(0), WinnerIDF(0),
		votePartyList(new int[1]), winnerPartyHead(nullptr), sizePartyDis(0), isDivided(false)
	{
		votePartyList[0] = 0;
	}

	District::District(const District& dis)
	{
		this->DistrictName = dis.DistrictName;
		this->DistrictID = dis.DistrictID;
		this->NumOfCitizen = dis.NumOfCitizen;
		this->Electors = dis.Electors;
		this->votersPercentage = dis.votersPercentage;
		this->votersCounter = dis.votersCounter;
		this->WinnerIDF = dis.WinnerIDF;
		this->votePartyList = dis.votePartyList;
		this->winnerPartyHead = dis.winnerPartyHead;
		this->sizePartyDis = dis.sizePartyDis;
		this->isDivided = dis.isDivided;
	}

	District::District(const char* _name, int  numElector) :District()
	{
		static int index = 1;
		int size = strlen(_name) + 1;
		this->DistrictName = new char[size + 1];
		for (int i = 0; i < size; i++) {
			this->DistrictName[i] = _name[i];
		}
		this->DistrictName[size] = '\0';
		this->Electors = numElector;
		this->DistrictID = index;
		index++;
		this->winnerPartyHead = nullptr;
	}

	District::~District() // District obj distruction
	{
		if (DistrictName != nullptr)
		{
			delete[] DistrictName;
			delete[] votePartyList;
		}

	}

	///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
	void District::setNumOfCitizen()
	{
		this->NumOfCitizen += 1;
		return;
	}

	void District::setIsDivided(bool b)
	{
		this->isDivided = b;
		return;
	}

	void District::setVotersCounter()
	{
		this->votersCounter += 1;
	}

	bool  District::setvotersPercentage()
	{
		if (votersCounter == 0)
		{
			votersPercentage = 0;
			return false;
		}
		else
		{
			votersPercentage = (static_cast<float>(static_cast<float>(votersCounter) / static_cast<float>(NumOfCitizen)) * 100);
		}
		if (votersPercentage < 0)
			return false;
		return true;
	}

	bool District::setWinnerPartyHead(Citizen* c)
	{
		if (c == nullptr)
		{
			return false;
		}
		winnerPartyHead = c;
		WinnerIDF = c->getID();
		return true;
	}

	bool District::setName(const char* n)
	{
		if (n == nullptr)
		{
			return false;
		}

		int size = strlen(n) + 1;
		if (DistrictName) 
		{
			delete[] DistrictName;
		}
		DistrictName = new char[size];
		memcpy(DistrictName, n, size);
		return true;
	}

	///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
	int District::getWinnerParty(int& votes)
	{
		int max = votePartyList[0], Index = 1;

		for (int i = 0; i < sizePartyDis; i++)
		{
			if (votePartyList[i] > max)
			{
				max = votePartyList[i];
				Index = i + 1;
			}
		}
		votes = votePartyList[Index - 1];
		return Index;
	}

	int District::GetDistrictID() const
	{
		return this->DistrictID;
	}
	bool District::getIsDivided() const
	{
		return this->isDivided;
	}

	int District::GetvotersPercentage()
	{
		return this->votersPercentage;
	}

	int District::getElectors() const
	{
		return this->Electors;
	}

	int* District::GetVoteListForParty()
	{
		return this->votePartyList;
	}

	Citizen* District::getWinnerPartyHead() const
	{
		return winnerPartyHead;
	}

	int District::getSumVote(int partySerialNum)
	{
		return votePartyList[partySerialNum - 1];
	}

	int District::getSizePartyList() const
	{
		return sizePartyDis;
	}

	int District::getwinnerId() const 
	{
		return WinnerIDF;
	}

	///////////////////////////////////////////////Add Funcs////////////////////////////////////////////////
	void District::VoteAdd(int partyNum)
	{
		this->votePartyList[partyNum - 1] += 1;
		this->votersCounter++;
	}

	void District::fitPartyList(int ls)
	{
		int* temp = new int[ls];

		for (int i = 0; i < ls; i++)
		{
			temp[i] = 0;
		}
		for (int i = 0; i < sizePartyDis; i++)
		{
			temp[i] = votePartyList[i];
		}
		sizePartyDis = ls;
		votePartyList = temp;
	}

	void District::calculateElectorsDividing(int* arr, float* carryArr, int& electorsDivided)
	{
		float votesByElector = 0, votesForCurrParty = 0;
		int electorsCounter = 0;
		int electorsNum, VotesInDistrict;
		for (int j = 0; j <= sizePartyDis; j++)
		{
			electorsNum = Electors;
			VotesInDistrict = votersCounter;
			votesByElector = static_cast<float>(VotesInDistrict) / static_cast<float>(electorsNum);
			votesForCurrParty = static_cast<float> (this->getNumOfVotesPerParty(j));
			electorsCounter = 0;
			while (votesForCurrParty > votesByElector)
			{
				electorsCounter++;
				votesForCurrParty = votesForCurrParty - votesByElector;
			}

			if ((votesForCurrParty == votesByElector) && (votesForCurrParty > 0))
			{
				electorsCounter++;
				votesForCurrParty = votesForCurrParty - votesByElector;
			}
			arr[j] += electorsCounter;
			electorsDivided += electorsCounter;
			carryArr[j] = votesForCurrParty;
		}
	}

	int District::setNumOfVotesPerParty(int partySerialNum , int votes) 
	{
		return votePartyList[partySerialNum] = votes;
	}

	int District::getNumOfVotesPerParty(int partySerialNum) const
	{
		return votePartyList[partySerialNum];
	}

	int District::getTotalVotes() const
	{
		return votersCounter;
	}

	char* District::getNameDistrict() const {
		return DistrictName;
	}

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	ostream& operator<<(ostream& os, const District& dis)
	{
		if ((dis.getWinnerPartyHead() == nullptr) || (dis.getTotalVotes() == 0))
		{
			os << "District Name: " << dis.getNameDistrict();
			os << ", Serial Number: " << dis.DistrictID;
			if (dis.getIsDivided())
			{
				os << ", District Type: Divided ";
			}
			else
			{
				os << ", District Type: United ";
			}
			os << ", Number of Electors: " << dis.Electors << endl;
		}
		else
		{
			os << "Distrcit Name: " << dis.getNameDistrict();
			if (dis.getIsDivided()) {
				os << ", District Type: Divided ";
			}
			else {
				os << ", District Type: United ";
			}
			os << "Number of Electors: " << dis.Electors << endl;
			os << "Winner: " << endl;
			os << (*dis.winnerPartyHead) << endl;
		}
		return os;
	}


	District& District::operator=(District& dis)
	{
		if (this != &dis) {
			this->setName(dis.DistrictName);
			this->NumOfCitizen = dis.NumOfCitizen;
			this->DistrictID = dis.DistrictID;
			this->Electors = dis.Electors;
			this->votePartyList = dis.votePartyList;
			this->sizePartyDis = dis.sizePartyDis;
			this->votersPercentage = dis.votersPercentage;
			this->votersCounter - dis.votersCounter;
			this->winnerPartyHead = dis.winnerPartyHead;
			this->isDivided = dis.isDivided;
		}
		return *this;
	}

	///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
	void District::save(ostream& out) {

		int nameLen = strlen(getNameDistrict());
		out.write(rcastcc(&nameLen), sizeof(int));
		for (int i = 0; i < nameLen; ++i)
		{
			out.write(rcastcc(&this->DistrictName[i]), sizeof(char));
		}
		out.write(rcastcc(&this->DistrictID), sizeof(int));
		out.write(rcastcc(&this->isDivided), sizeof(bool));
		out.write(rcastcc(&this->Electors), sizeof(int));

		out.write(rcastc(&this->NumOfCitizen), sizeof(int));
		out.write(rcastc(&this->sizePartyDis), sizeof(int));
		out.write(rcastc(&this->votersCounter), sizeof(int));
		out.write(rcastc(&this->votersPercentage), sizeof(float));
		int tempWinnerId = this->winnerPartyHead->getID();
		out.write(rcastc(&tempWinnerId), sizeof(int));
		for (int i = 0; i < sizePartyDis; ++i) 
		{
			int tempVote = this->votePartyList[i];
			out.write(rcastc(&tempVote), sizeof(int));
			tempVote = 0;
		}

	}

	void District::load(istream& in)
	{
		int nameLen = 0;

		in.read(rcastc(&nameLen), sizeof(int));
		this->DistrictName = new char[nameLen + 1];
		for (int i = 0; i < nameLen; ++i)
		{
			in.read(rcastc(&DistrictName[i]), sizeof(char));
		}
		this->DistrictName[nameLen] = '\0';
		in.read(rcastc(&this->DistrictID), sizeof(int));
		in.read(rcastc(&this->isDivided), sizeof(bool));
		in.read(rcastc(&this->Electors), sizeof(int));
		in.read(rcastc(&this->NumOfCitizen), sizeof(int));
		in.read(rcastc(&this->sizePartyDis), sizeof(int));
		in.read(rcastc(&this->votersCounter), sizeof(int));
		in.read(rcastc(&this->votersPercentage), sizeof(float));
		in.read(rcastc(&this->WinnerIDF), sizeof(int));
		this->votePartyList = new int[sizePartyDis];

		for (int i = 0; i < sizePartyDis; ++i) 
		{
			int tempVote = 0;  ///TODO
			in.read(rcastc(&tempVote), sizeof(int));
			if (tempVote >= 0)
				votePartyList[i] = tempVote;
		}
	}
}