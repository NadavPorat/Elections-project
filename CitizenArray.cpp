#include "CitizenArray.h"
namespace elt 
{

	CitizenArray::CitizenArray() : ls(0), ps(1), arr(new Citizen) {}

	CitizenArray::CitizenArray(int x)
	{
		this->arr = nullptr;
		this->ls = 0;
		this->ps = 0;
	}
	CitizenArray::~CitizenArray()
	{
		if (arr != nullptr)
		{
			delete[] arr;
		}
		ls = 0;
		ps = 1;
	}

	///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
	bool CitizenArray::addCitizen(Citizen& citizen)
	{
		if (&citizen == nullptr)
		{
			return false;
		}
		if (this->ps == this->ls)
		{
			if (!resize(ps * 2))
			{
				return false;
			}
		}
		arr[ls] = citizen;
		ls += 1;
		return true;
	}

	bool CitizenArray::resize(int size)
	{
		if (size <= 0) {
			return false;
		}
		Citizen* tempCitizen = new Citizen[size];
		if (tempCitizen == nullptr)
		{
			return false;
		}
		for (int i = 0; i < ls; ++i)
		{
			tempCitizen[i] = arr[i];
		}
		arr = tempCitizen;
		this->ps = size;
		return true;
	}

	///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
	Citizen* CitizenArray::getCitizen(int id) const
	{

		int i;
		for (i = 0; i <= ls; i++) {
			if (arr[i].getID() == id)
				return (arr + i);
		}
		return nullptr;
	}

	int CitizenArray::getCitizenArrayLogSize() const
	{
		return this->ls;
	}

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	void CitizenArray::printCitizensArray() const {
		int i;
		for (i = 0; i < this->ls; i++) {
			cout << "Citizen #" << (i + 1) << " is: " << endl;

			cout << arr[i] << endl;
		}
	}

	void CitizenArray::printPartyCandidates(int delNum, char* partyName) 
	{
		cout << "Party: " << partyName << endl;
		cout << "Delegates List:" << endl;
		for (int Idx = 0; Idx < delNum && Idx < this->ls; Idx++)
		{

			if ((arr[Idx].getID() > 0) && (arr[Idx].getBirthYear() > 0))/////TODO (arr[Idx].getisCandidat() == true))
			{
				cout << arr[Idx] << endl;
			}
		}
	}

	CitizenArray& CitizenArray::operator=(CitizenArray& citArr) 
	{
		if (this != &citArr) 
		{

			for (int i = 0; i < citArr.ls; i++) 
			{
				this->arr[i] = citArr.arr[i];
			}
			this->ls = citArr.ls;
			this->ps = citArr.ps;
		}
		return *this;

	}

	Citizen* CitizenArray::getArr() const 
	{
		return arr;
	}
}