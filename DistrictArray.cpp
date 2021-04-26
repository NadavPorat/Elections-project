#include "DistrictArray.h"

namespace elt
{

	DistrictArray::DistrictArray() :ls(0), ps(1), arr(new District[1]) {}

	DistrictArray::~DistrictArray()
	{
		delete[] arr;
		ls = 0;
		ps = 1;
	}
	///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
	bool DistrictArray::addDistrict(District& dis)
	{
		if (&dis == nullptr)
		{
			return false;
		}
		if (this->ps == this->ls)
		{
			ps *= 2;
			if (!resize(ps))
			{
				return false;
			}
		}
		arr[ls] = dis;
		this->ls += 1;
		return true;

	}

	bool DistrictArray::resize(int size)
	{
		if (size <= 0)
		{
			return false;
		}
		District* tempDistrict = new District[size];
		if (tempDistrict == nullptr)
		{
			return false;
		}
		for (int i = 0; i < this->ls; ++i) {
			tempDistrict[i] = arr[i];
		}
		arr = tempDistrict;
		this->ps = size;
		return true;
	}

	bool DistrictArray::fitPartyArrayPerDistricat(int partysNum)
	{
		if (partysNum <= 0)
		{
			return false;
		}
		for (int i = 0; i < ls; i++)
		{
			if (arr[i].getSizePartyList() < partysNum) 
			{
				arr[i].fitPartyList(partysNum);

			}
		}
		return true;
	}

	///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
	District* DistrictArray::getDistrict(int num)
	{

		int i;
		for (i = 0; i <= ls; i++)
		{
			if (arr[i].GetDistrictID() == num)
				return (arr + i);
		}
		return nullptr;
	}

	District* DistrictArray::getDArr() const
	{
		return arr;
	}


	int DistrictArray::getSize() const
	{
		return this->ls;
	}

	///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
	void DistrictArray::printDistrictArray() const
	{
		int i;
		for (i = 0; i < this->ls; i++)
		{
			cout << "District #" << (i + 1) << " is: " << endl;
			cout << arr[i] << endl;
		}
	}
}