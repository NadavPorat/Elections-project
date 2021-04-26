
#include "ElectionsRound.h"

namespace elt
{
	ElectionsRound::ElectionsRound()
	{
		this->day = 0;
		this->month = 0;
		this->year = 0;
		this->kind = 0;

		CitizensArr = new CitizenArray();
		PartyArr = new PartyArray();
		DistrictArr = new DistrictArray();
	}

	ElectionsRound::ElectionsRound(int newDay, int newMonth, int newYear) : ElectionsRound()
	{
		this->day = newDay;
		this->month = newMonth;
		this->year = newYear;
	}

	ElectionsRound::~ElectionsRound()
	{
		delete[] CitizensArr;
		delete[] PartyArr;
		delete[] DistrictArr;
	}

	///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
	bool ElectionsRound::setKind(int k)
	{
		if (k != 1 && k != 2)
		{
			return false;
		}
		this->kind = k;
		return true;
	}
	bool ElectionsRound::setDistrict(District& dis)
	{

		return this->DistrictArr->addDistrict(dis);
	}

	bool ElectionsRound::setParty(Party& party)
	{
		bool valid = true;
		if (party.getHeadParty() == nullptr) 
		{
			valid = false;
		}
		if (&party == nullptr)
		{
			valid = false;
		}
		if (valid) 
		{
			this->PartyArr->addParty(party);
		}
		DistrictArr->fitPartyArrayPerDistricat(PartyArr->getPartyLogSize());
		return true;
	}

	bool ElectionsRound::setCitizen(Citizen& cit)
	{
		bool valid = true;

		if (this->CitizensArr->getCitizen(cit.getID()) != nullptr)
		{
			valid = false;
		}

		if ((&cit == nullptr) && (cit.getID() < 0))
		{
			valid = false;
		}
		if (valid)
		{
			if (!this->CitizensArr->addCitizen(cit))
			{
				return false;
			}
		}
		District* d = this->DistrictArr->getDistrict(cit.getDistrictID());
		d->setNumOfCitizen();
		return true;
	}

	void ElectionsRound::SetPartyWinnerAtDistrict()
	{
		for (int i = 0; i < (DistrictArr->getSize()); i++)
		{
			District* tempDis = DistrictArr->getDistrict(i + 1);
			int num = 0;
			int PartyWinner = tempDis->getWinnerParty(num);
			Party* p = PartyArr->getParty(PartyWinner);
			tempDis->setWinnerPartyHead(p->getHeadParty());
		}
	}

	///////////////////////////////////////////////Add Funcs////////////////////////////////////////////////
	bool ElectionsRound::addCandidate(Citizen& citizen, Party& party, District& dis)
	{
		if (citizen.getIsCandidate() == false)
		{
			party.addCitizenAsCandidate(citizen, dis);
			citizen.setIsCandidate(true);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ElectionsRound::addVote(Citizen& citizen, Party& party)
	{

		int DistrictID = citizen.getDistrictID();
		int PartyID = party.getSerialNum();
		DistrictArr->getDistrict(DistrictID)->VoteAdd(PartyID);
		CitizensArr->getCitizen(citizen.getID())->setVote(true);
		return true;
	}

	///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
	CitizenArray& ElectionsRound::getCitizenArr()
	{
		return *this->CitizensArr;
	}

	DistrictArray& ElectionsRound::getDistrictArr()
	{
		return *this->DistrictArr;
	}

	PartyArray& ElectionsRound::getPartyArr()
	{
		return *this->PartyArr;
	}

	bool ElectionsRound::getValidResult()
	{
		bool isValid = true;
		for (int i = 0; i < (DistrictArr->getSize()); i++)
		{
			District* Dis = DistrictArr->getDistrict(i + 1);
		}
		return isValid;
	}

	int ElectionsRound::getELRKind()
	{
		return this->kind;
	}

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	void ElectionsRound::PrintDistricts()
	{
		this->DistrictArr->printDistrictArray();
	}

	void ElectionsRound::PrintParties()
	{
		this->PartyArr->printPartyArray();
	}

	void ElectionsRound::PrintCitizens()
	{
		this->CitizensArr->printCitizensArray();
	}

	void ElectionsRound::calcAndSetResultInDis()
	{
		float carry = 0, MaxCarry = 0, votesPercentagePerParty, FnumOfRepsToAdd;
		int Index = 0, tempVotes, totalElectorsInDis, tempSumElctor, totalVotesInDistrict, votesForCurrParty, InumOfRepsToAdd, partySerialNumer;
		District* currDis;
		int tempPtID = 0;
		for (int i = 0; i < DistrictArr->getSize(); i++)
		{
			tempVotes = 0;
			votesPercentagePerParty = 0;
			currDis = DistrictArr->getDistrict(i + 1);
			totalElectorsInDis = currDis->getElectors();
			tempSumElctor = 0;
			totalVotesInDistrict = currDis->getTotalVotes();

			if (totalVotesInDistrict > 0) // Vote=0 ? => No Calcs Needed , Skip this part.
			{
				for (int j = 0; j < currDis->getSizePartyList(); j++)
				{
					tempPtID = PartyArr->getPArr()[j].getSerialNum();
					votesForCurrParty = currDis->getNumOfVotesPerParty(tempPtID -1);// The index of the party in votePartyList (Array) of the DISTRICT.
					votesPercentagePerParty = (static_cast<float> ((static_cast<float>(votesForCurrParty) / static_cast<float>(totalVotesInDistrict)) * 100));
					FnumOfRepsToAdd = (totalElectorsInDis * (votesPercentagePerParty / 100));
					InumOfRepsToAdd = floor(FnumOfRepsToAdd); //Using floor func to get the carry value.
					carry = FnumOfRepsToAdd - InumOfRepsToAdd;
					if (carry > MaxCarry)
					{
						MaxCarry = carry;
						Index = tempPtID; // Save the ID of the Party where we shoould add 1 elctor.

					}
					if (!currDis->getIsDivided()) 
					{
						partySerialNumer = (*currDis).getWinnerParty(tempVotes);
						if ((partySerialNumer - 1) == j)
						{
							PartyArr->getParty(partySerialNumer)->addToSumOfDeligatesForPresident(totalElectorsInDis);
						}
						PartyArr->getParty(tempPtID )->addToSumOfDeligates(InumOfRepsToAdd);
						PartyArr->getParty(tempPtID)->addToSumOfVotes(votesForCurrParty);
					}
					else
					{
						PartyArr->addToTotal(tempPtID, InumOfRepsToAdd, votesForCurrParty);
					}
					tempSumElctor = tempSumElctor + InumOfRepsToAdd;

				}
					while (tempSumElctor < totalElectorsInDis)
					{
						PartyArr->addToTotal(Index, 1, 0);
						tempSumElctor++;

					}
			}
		}
	}

	void ElectionsRound::calcAndPrintElectorsDivide()
	{
		int numOfParties = PartyArr->getPartyLogSize(); 
		int* electorsByPartyArr = new int[numOfParties]; 
		int ElcotrsInDis = 0;
		int electorsSum = 0;
		int lastMaxCarryIdx = 0;
		int indexToAddDeligates;
		int votesPercentagePerParty;
		int votesForCurrParty;
		int totalVotesInDistrict;
		int tempPtID = 0;
		float* carryArr;
		District* currD;
		carryArr = new float[numOfParties];
		for (int i = 0; i < numOfParties; i++) //reest array
		{
			carryArr[i] = 0;
			electorsByPartyArr[i] = 0;
		}
		for (int i = 0; i < (DistrictArr->getSize()); i++)
		{
			currD = DistrictArr->getDistrict(i + 1); 
			cout << "District #: " << i + 1 << endl; 

			ElcotrsInDis = currD->getElectors();
			electorsSum = 0;
			currD->calculateElectorsDividing(electorsByPartyArr, carryArr, electorsSum);
			lastMaxCarryIdx = -1;
			while (electorsSum < ElcotrsInDis)  
			{
				indexToAddDeligates = findMaxCarry(carryArr, numOfParties, lastMaxCarryIdx);
				lastMaxCarryIdx = indexToAddDeligates;
				electorsByPartyArr[indexToAddDeligates] += 1;
				electorsSum += 1;
			}

			for (int j = 0; j < numOfParties; j++)
			{
				tempPtID = PartyArr->getPArr()[j].getSerialNum();
				votesPercentagePerParty = 0;
				votesForCurrParty = currD->getNumOfVotesPerParty(tempPtID-1);//
				totalVotesInDistrict = currD->getTotalVotes();
				if (totalVotesInDistrict == 0) 
				{
					cout << "No Candidates were elected" << endl;
				}
				else {
					votesPercentagePerParty = (static_cast<float> ((static_cast<float>(votesForCurrParty) / static_cast<float>(totalVotesInDistrict)) * 100));
					PartyArr->printElectedCandidates(electorsByPartyArr[j], tempPtID, currD->GetDistrictID());
				}
				cout << "The Number of the votes to the party in this District: " << votesForCurrParty << endl;
				cout << "The Votes Percentage of the Party in this District: " << votesPercentagePerParty << "%" << endl << endl;

			}
			currD->setvotersPercentage(); //Set
			cout << "The Vote Percentage in The District is: " << currD->GetvotersPercentage() << "%" << endl << endl; //Get
		}
		delete[] electorsByPartyArr;
	}

	int ElectionsRound::findMaxCarry(float* carryArr, int size, int& lastMaxCarryIdx)
	{
		float maxCarry = carryArr[0];
		int maxIdx = 0;
		if (lastMaxCarryIdx == -1)
		{
			for (int i = 1; i < size; i++)
			{
				if (carryArr[i] > maxCarry)
				{
					maxCarry = carryArr[i];
					maxIdx = i;
				}
			}
		}
		else
		{
			for (int i = 1; i < size; i++)
			{
				if ((carryArr[i] > maxCarry))
				{
					maxCarry = carryArr[i];
					maxIdx = i;
				}
			}
		}
		carryArr[maxIdx] = 0;
		return maxIdx;
	}

	void printPrime(const PartyArray arr)
	{
		cout << "The Candidates To Prime Minister Are:" << endl;
		for (int i = 0; i < arr.getPartyLogSize(); i++)
		{
			cout << (i + 1) << endl;
			cout << arr.getParty(i)->getHeadParty() << endl;
		}
	}

	void ElectionsRound::PrintRegularELRResults()
	{
		PartyArr->resetDataCalc();    // Reset Elections Round Parameters (in case there is trash values)
		PrintElctionsDate();          // work
		SetPartyWinnerAtDistrict();   // work
		calcAndSetResultInDis();      // work
		PrintDistricts();             // work
		calcAndPrintElectorsDivide(); // work
		PartyArr->SortPartyListBySumOfDel(PartyArr->getPartyLogSize());
		cout << "_______________________________________";
		cout << "\nThe Winner Of This Elections Round is:\n";
		cout <<"~~~~"<< *(PartyArr->getPArr()[0].getHeadParty()) <<"~~~~"<< endl;
		PrintParties();
		PartyArr->resetDataCalc();
		return;
	}

	void ElectionsRound::PrintElctionsDate()
	{
		// print day month year of the current elections round
		cout << "Elections Round Date: " << endl;
		cout << day << " , " << month << " , " << year << endl;
	}

	///////////////////////////////////////////////Simple Elections Round Funcs////////////////////////////////////////////////
	SimpleElectionsRound::SimpleElectionsRound() : ElectionsRound()
	{
		District dis = District();
		DistrictArr->addDistrict(dis);
	}

	SimpleElectionsRound::~SimpleElectionsRound()
	{
	}

	void SimpleElectionsRound::setDistrictDIV()
	{
		this->getDistrictArr().getDistrict(0)->setIsDivided(true);
	}

	SimpleElectionsRound::SimpleElectionsRound(int newDay, int newMonth, int newYear, int numOfElectors) :ElectionsRound(newDay, newMonth, newYear)
	{
		District dis = *new District("LonleyDistrict", numOfElectors);
		DistrictArr->addDistrict(dis);
	}

	void SimpleElectionsRound::PrintSimpleELRResults()
	{
		PartyArr->resetDataCalc();        // Reset Elections Round Parameters (in case there is trash values)
		int totalVotesInDistrict = DistrictArr->getDArr()[0].getTotalVotes();
		int votesPercentagePerParty = 0;
		int voteForCurrParty = 0;
		int PartySize = PartyArr->getPartyLogSize();
		PrintElctionsDate();
		SetPartyWinnerAtDistrict();       // work
		calcAndSetResultInDis();
		PartyArr->sortPartiesInSimpleElectionsRound(PartyArr->getPartyLogSize());
		cout << "_______________________________________";
		cout << "\nThe winner of this election round is:\n";
		cout << "~~~~" << *(PartyArr->getPArr()[0].getHeadParty()) << "~~~~" << endl;



		for (int i = 0; i < PartySize; ++i) {  // print simple election party List
			Party partyPointer = PartyArr->getPArr()[i];
			voteForCurrParty = partyPointer.getSumOfVote();
			votesPercentagePerParty = (static_cast<float> ((static_cast<float>(voteForCurrParty) / static_cast<float>(totalVotesInDistrict)) * 100));
			cout << "Party #" << (i + 1) << " is: " << endl;
			cout << partyPointer.getNameParty();
			cout << ", The number of Representatives that elected for this Party is: " << partyPointer.getNumOfRrpElected() << endl; 
			cout << "The Number of the votes to the party: " << partyPointer.getSumOfVote();
			cout << ", The Votes Percentage of the Party is: " << votesPercentagePerParty << "%" << endl;
			cout << "The head of the Party is: " << *partyPointer.getHeadParty();
			PartyArr->printElectedCandidates(partyPointer.getNumOfRrpElected(), i + 1, 1);

		}
		PartyArr->resetDataCalc();
		return;
	}

	//TODO result

	///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
	void ElectionsRound::save(ostream& out_file)const 
	{
		out_file.write(rcastcc(&day), sizeof(int));
		out_file.write(rcastcc(&month), sizeof(int));
		out_file.write(rcastcc(&year), sizeof(int));
		out_file.write(rcastcc(&kind), sizeof(int));
		int disAmount = 0;
		disAmount = DistrictArr->getSize();
		out_file.write(rcastcc(&disAmount), sizeof(int));
		for (int i = 0; i < DistrictArr->getSize(); i++)
		{

			this->DistrictArr->getDArr()[i].save(out_file);
		}
		int ptsAmount = 0;
		ptsAmount = PartyArr->getPartyLogSize();
		out_file.write(rcastcc(&ptsAmount), sizeof(int));
		for (int i = 0; i < PartyArr->getPartyLogSize(); i++)
		{
			this->PartyArr->getPArr()[i].save(out_file);
		}
		int citsAmount = 0;
		citsAmount = this->CitizensArr->getCitizenArrayLogSize();
		out_file.write(rcastcc(&citsAmount), sizeof(int));
		for (int i = 0; i < CitizensArr->getCitizenArrayLogSize(); i++)
		{
			this->CitizensArr->getArr()[i].save(out_file);
		}
	}

	void ElectionsRound::load(istream& in)
	{
		in.read(rcastc(&day), sizeof(int));
		in.read(rcastc(&month), sizeof(int));
		in.read(rcastc(&year), sizeof(int));
		in.read(rcastc(&kind), sizeof(int));

		int disAmount = 0;
		in.read(rcastc(&disAmount), sizeof(int));
		this->DistrictArr->resize(disAmount);
		for (int i = 0; i < disAmount; i++)
		{
			this->DistrictArr->getDArr()[i].load(in);
			this->DistrictArr->setLs();
		}
		int ptsAmount = 0;
		in.read(rcastc(&ptsAmount), sizeof(int));
		this->PartyArr->resize(ptsAmount);

		for (int i = 0; i < ptsAmount; i++)
		{
			this->PartyArr->getPArr()[i].load(in);
			this->PartyArr->setLs();
		}
		int citsAmount = 0;
		in.read(rcastc(&citsAmount), sizeof(int));
		this->CitizensArr->resize(citsAmount);
		for (int i = 0; i < citsAmount; i++)
		{
			this->CitizensArr->getArr()[i].load(in);
			this->CitizensArr->setLs();
		}
	}

	void ElectionsRound::connectPointers() 
	{
		int Dsize = this->DistrictArr->getSize();
		for (int i = 0; i < Dsize; i++)
		{
			int tempId = this->DistrictArr->getDArr()[i].getwinnerId();
			this->DistrictArr->getDArr()[i].setWinnerPartyHead(CitizensArr->getCitizen(tempId));
		}
		int CsizeArr = this->CitizensArr->getCitizenArrayLogSize(); ///TODO change "getCitizenArrayLogSize" to "getSize"
		for (int i = 0; i < CsizeArr; i++)
		{
			int tempDisID = CitizensArr->getArr()[i].getDisIDFromFile();
			District* Pd = DistrictArr->getDistrict(tempDisID);
			CitizensArr->getArr()[i].setCitDistrict(Pd);
		}
		int PsizeArr = this->PartyArr->getPartyLogSize();
		for (int i = 0; i < PsizeArr; i++)///TODO change "getPartyLogSize" to "getSize"
		{
			int tempID = PartyArr->getPArr()[i].getheadOfPartyID();
			Citizen* Pc = CitizensArr->getCitizen(tempID);
			PartyArr->getPArr()[i].setHeadOfParty(Pc);
		}
	}
}
