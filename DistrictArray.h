#pragma once
#include "iostream"
#include "District.h"
#include "Citizen.h"
#include <algorithm>

using namespace std;

namespace elt 
{
	class District;
	class DistrictArray 
	{
	private:
		District* arr;
		int ls = 0;
		int ps = 1;
	public:
		DistrictArray();
		~DistrictArray();

		///////////////////////////////////////////////Set Funcs////////////////////////////////////////////////
		bool resize(int size);
		void setLs() { this->ls += 1; };
		bool addDistrict(District& dis);
		bool fitPartyArrayPerDistricat(int partysNum);

		///////////////////////////////////////////////Get Funcs////////////////////////////////////////////////
		District* getDistrict(int num);
		int getSize() const;
		District* getDArr() const;

		///////////////////////////////////////////////Print Funcs////////////////////////////////////////////////
		void printDistrictArray() const;
	};
}

