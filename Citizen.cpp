
#include <iostream>
#include <cstring>
#include "Citizen.h"
using namespace std;


///////////////////////////////////////////////Citizen////////////////////////////////////////////////
namespace elt {
	Citizen::Citizen() :name(), ID(0), BirthYear(0), voted(false), isCandidate(false), DisID(0)
	{
	}

	Citizen::Citizen(const Citizen& cit) : name(cit.name), ID(cit.ID), BirthYear(cit.BirthYear), voted(cit.voted), isCandidate(cit.isCandidate), dis(cit.dis)
	{ 
	}

	Citizen::Citizen(const char* _name, int _ID, int _BirthYear, District* newDis) : Citizen()
	{

		if (!setName(_name))
			cout << "ERROR! Couldn't set Name";         
		if (!setBirthYear(_BirthYear))
			cout << "ERROR! Couldn't set BirthYear";   
		if (!setID(_ID))
		{
			cout << "ERROR! Couldn't set ID";        
		}
		if (!setVote(false))
			cout << "ERROR! Couldn't set Vote";   
		setCitDistrict(newDis);
	}

	Citizen::~Citizen()
	{
		if (name != nullptr)
		{
			delete[] name;

		}
	}

	///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
	void Citizen::setCitDistrict(District* newDis)
	{
		this->dis = newDis;
	}

	bool Citizen::setID(int id)
	{
		if (id < 0)
		{
			return false;
		}
		this->ID = id;
		return true;
	}

	bool Citizen::setBirthYear(int birthYear)
	{
		if (birthYear < 1000 || birthYear>2020)
		{
			return false;
		}
		else {
			this->BirthYear = birthYear;
			return true;
		}
	}

	bool Citizen::setVote(bool vote)
	{
		this->voted = vote;
		return true;
	}

	bool Citizen::setName(const char* n)
	{
		if (n == nullptr)
		{
			return false;
		}

		int size = strlen(n) + 1;
		name = new char[size];
		memcpy(name, n, size);
		return true;
	}

	void Citizen::setIsCandidate(bool b)
	{
		this->isCandidate = b;
		return;
	}

	///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
	const char* Citizen::getName() const
	{
		return name;
	}

	int Citizen::getBirthYear() const
	{
		return BirthYear;
	}

	int Citizen::getID() const
	{
		return ID;
	}
	int Citizen::getDisIDFromFile() const 
	{
		return DisID;
	}


	int Citizen::getDistrictID() const
	{
		return dis->GetDistrictID();
	}

	District* Citizen::getDistrict() const
	{
		return this->dis;
	}

	bool Citizen::getVote() const
	{
		return voted;
	}

	const bool Citizen::getIsCandidate() const
	{
		return isCandidate;
	}

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		os << "Citizen's name: " << citizen.getName();
		os << ", Citizen's ID: " << citizen.ID;
		os << ", Citizen's Year of Birth: " << citizen.BirthYear;
		os << " ,Citizen's District ID: " << (citizen.getDistrictID()) << endl;
		return os;
	}

	Citizen& Citizen::operator=(const Citizen& cit)
	{
		if (this != &cit)
		{
			this->setIsCandidate(cit.getIsCandidate());
			this->setVote(cit.getVote());
			this->setName(cit.getName());
			this->setID(cit.getID());
			this->setBirthYear(cit.getBirthYear());
			this->setCitDistrict(cit.dis);
		}
		return *this;
	}

	///////////////////////////////////////////////File Funcs////////////////////////////////////////////////
	void Citizen::save(ostream& out) const
	{
		int nameLen = strlen(getName());
		out.write(rcastcc(&nameLen), sizeof(int));
		for (int i = 0; i < nameLen; ++i) 
		{
			out.write(rcastcc(&this->name[i]), sizeof(char));
		}
		out.write(rcastcc(&ID), sizeof(ID));
		out.write(rcastcc(&BirthYear), sizeof(BirthYear));
		out.write(rcastcc(&voted), sizeof(voted));
		out.write(rcastcc(&isCandidate), sizeof(isCandidate));
		int tempDisID = dis->GetDistrictID();
		out.write(rcastcc(&tempDisID), sizeof(int));
	}

	void Citizen::load(istream& in)
	{
		int nameLen = 0;
		in.read(rcastc(&nameLen), sizeof(nameLen));
		this->name = new char[nameLen + 1];
		for (int i = 0; i < nameLen; ++i)
		{
			in.read(rcastc(&name[i]), sizeof(name[i]));
		}
		this->name[nameLen] = '\0';
		in.read(rcastc(&this->ID), sizeof(this->ID));
		in.read(rcastc(&this->BirthYear), sizeof(this->BirthYear));
		in.read(rcastc(&this->voted), sizeof(this->voted));
		in.read(rcastc(&this->isCandidate), sizeof(isCandidate));
		in.read(rcastc(&this->DisID), sizeof(int));
	}
}
