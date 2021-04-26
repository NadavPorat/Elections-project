
#include "GeneralHeader.h"

namespace elt
{
	void readCitizen(ElectionsRound& er)
	{
		bool flag = true;
		char name[NAMELEN];
		cin.ignore(); 

		cout << "Enter The Name Of The Citizen: ";
		cin.getline(name, NAMELEN);

		int ID;
		cout << "Enter The ID: ";

		cin >> ID;
		int BirthYear;
		cout << "Enter The Birth Year:  ";
		cin >> BirthYear;

		int DistrictID;
		cout << "Enter The District ID: ";
		cin >> DistrictID;

		District* dis = er.getDistrictArr().getDistrict(DistrictID);

		if (dis == nullptr)
			flag = false;

		if (er.getCitizenArr().getCitizen(ID) != nullptr)
			flag = false;

		Citizen temp(name, ID, BirthYear, dis);

		if (flag)
		{
			er.setCitizen(temp);
		}
		else
		{
			cout << "ERROR! The input didn't received " << endl;
		}
	}

	void readDistrict(ElectionsRound& er)
	{
		bool flag = true;
		bool isDivided;

		char name[NAMELEN];
		cin.ignore(); 
		cout << "Enter the name of the district: ";
		cin.getline(name, NAMELEN);

		int numEle;
		cout << "Enter Number of the Electors: ";
		cin >> numEle;
		if (numEle < 0) {
			flag = false;
		}
		int div;
		cout << "Enter The Kind of the District (1 = Divided , or 2 = United):" << endl;
		cin >> div;
		while (div != 1 && div != 2)
		{
			cout << "The Kind Of the District is invalid. Please choose 1 for Divided Dstrict or 2 for United District " << endl;
			cin >> div;
		}
		if (div == 1)
		{
			isDivided = true;
		}
		else
		{
			isDivided = false;
		}
		District temp(name, numEle);
		temp.setIsDivided(isDivided);
		er.setDistrict(temp);
	}

	void read_Party(ElectionsRound& er)
	{

		static int index = 1;
		char partyName[NAMELEN];

		cin.ignore(); 
		cout << "Enter the name of the party: ";
		cin.getline(partyName, NAMELEN);
		int primParty;
		cout << "Enter the ID of the Candidate for the head of the party: ";
		cin >> primParty;

		Citizen* headOfParty = er.getCitizenArr().getCitizen(primParty);

		if (headOfParty == nullptr)
		{
			cout << "The head of the party isn't initialized " << endl;
		}
		else
		{
			Party temp(partyName, headOfParty);

			int size = er.getPartyArr().getPartyLogSize();
			temp.setSerialNum(index);
			index++;
			er.setParty(temp);
		}
	}

	void read_Candidate(ElectionsRound& er)
	{
		int tempId, partyNum, districtId;
		Citizen* candidate;
		Party* party;
		District* district;

		cout << "Enter the ID of the Candidate: ";
		cin >> tempId;

		cout << "Enter the party ID: ";
		cin >> partyNum;

		cout << "Enter the district ID: ";
		cin >> districtId;
		if (partyNum > (er.getPartyArr().getPartyLogSize()))
		{
			cout << "The Party does not exist  " << endl;
			return;

		}
		candidate= er.getCitizenArr().getCitizen(tempId);

		if (&candidate == nullptr)
		{
			cout << "The Citizen does not exist " << endl;
			return;

		}
		party = er.getPartyArr().getParty(partyNum);
		if (&party == nullptr)
		{
			cout << "The Party does not exist  " << endl;
			return;
		}

		district = er.getDistrictArr().getDistrict(districtId);

		if (&district == nullptr)
		{
			cout << "The district does not exist  " << endl;
			return;
		}

		if (!(er.addCandidate(*candidate, *party, *district)))
		{
			cout << "ERROR! Couldn't add Candidate " << endl;
			return;
		}
	}

	void vote(ElectionsRound& er)
	{
		int tempId;
		cout << "To Vote: " << endl;
		cout << "Please Enter Your Personal ID: ";
		cin >> tempId;
		cout << endl;

		int partyNum;
		cout << "Please Enter the party ID: ";
		cout << endl;
		cin >> partyNum;


		Citizen* can = er.getCitizenArr().getCitizen(tempId);

		Party* party = er.getPartyArr().getParty(partyNum);
		if (can == nullptr || party == nullptr)
		{
			cout << "The Citizen or The Party doesn't exist, please try again.";
			return;
		}
		if (can->getVote())
		{
			cout << "ERROR! You Already Voted " << endl;
			return;
		}
		else
		{
			if (!er.addVote(*can, *party))
			{
				cout << "ERROR! Couldn't add Vote " << endl;
			}
		}
		return;
	}

	void ResultsR(ElectionsRound& er)
	{
		er.PrintRegularELRResults();
		return;
	}

	void PrintMainMenu()
	{
		cout << "Choose your action according to the numbers in the Menu:" << endl;

		cout << "1. Add District" << endl;
		cout << "2. Add Citizen" << endl;
		cout << "3. Add Party" << endl;
		cout << "4. Add Candidate" << endl;
		cout << "5. Show Districts List" << endl;
		cout << "6. Show Citizens List" << endl;
		cout << "7. Show Parties List" << endl;
		cout << "8. Vote" << endl;
		cout << "9. Show Elections Result" << endl;
		cout << "10. Exit" << endl;
		cout << "11. Save Elections Round to file" << endl;
		cout << "12. Load Elections Round from file" << endl;
		return;
	}

	void PrintFirstMenu()
	{
		cout << "Choose your action according to the numbers in the Menu:" << endl;

		cout << "1. Create New Elections Round" << endl;
		cout << "2. Load Elections Round" << endl;
		cout << "3. Exit" << endl;
		return;
	}

	void readCitizenS(SimpleElectionsRound& er)
	{
		bool flag = true;
		char name[NAMELEN];
		int ID, BirthYear, DistrictID;
		District* dis;
		cin.ignore(); 
		cout << "Enter The Name Of The Citizen: ";
		cin.getline(name, NAMELEN);

		cout << "Enter The ID: ";

		cin >> ID;
		cout << "Enter The Birth Year:  ";
		cin >> BirthYear;

		DistrictID = 1;
	    dis = er.getDistrictArr().getDistrict(DistrictID);
		if (er.getCitizenArr().getCitizen(ID) != nullptr)
			flag = false;

		Citizen temp(name, ID, BirthYear, dis);

		if (flag)
		{
			er.setCitizen(temp);
		}
		else
		{
			cout << "ERROR! The input didn't received " << endl;
		}
		return;
	}

	void read_CandidateS(SimpleElectionsRound& er)
	{
		int tempId;
		cout << "Enter the ID of the Candidate: ";
		cin >> tempId;

		int partyNum;
		cout << "Enter the party ID: ";
		cin >> partyNum;

		Citizen* can = er.getCitizenArr().getCitizen(tempId);

		if (&can == nullptr)
		{
			cout << "The Citizen does not exist " << endl;
		}
		if (partyNum > (er.getPartyArr().getPartyLogSize()))
		{
			cout << "The Party does not exist  " << endl;
			return;
			

		}
		Party* party = er.getPartyArr().getParty(partyNum); 
		if (&party == nullptr) 
		{
			return;
		}

		int DistrictID = 1;

		District* district = er.getDistrictArr().getDistrict(DistrictID);

		if (!(er.addCandidate(*can, *party, *district)))
		{
			cout << "ERROR! Couldn't add Candidate " << endl;
			return;
		}
	}

	void ResultsS(SimpleElectionsRound& er)
	{
		er.PrintSimpleELRResults();
		return;
	}
}