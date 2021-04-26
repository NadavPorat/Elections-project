/**************************************************************************************
Project by:
1. Lior Roife  , ID: 206257826
2. Nadav Porat , ID: 311119374

 **************************************************************************************/
#include "GeneralHeader.h"
using namespace std;
using namespace elt;

///////////////////////////////////////////////Main////////////////////////////////////////////////
int main()
{
	ElectionsRound* election;
	int FirstChoice;   // The action the user choose from the first menu
	PrintFirstMenu();  // Show first menu
	cin >> FirstChoice;
	while (FirstChoice != 1 && FirstChoice != 2 && FirstChoice != 3)
	{
		cout << "Wrong Input Number for The Choice. Please Choose '1' or '2' or '3'" << endl;
		cin >> FirstChoice;
	}
	system("cls");
	switch (FirstChoice) 
	{        
	///////////////////////////////////////////////Case 1////////////////////////////////////////////////
		case static_cast<int>(func::f1) : // Make new elections Round
			int d, m, y;
			int kind;
			cout << "Please enter the Day , Month , Year and the Kind (1 or 2) of the Elections Round " << endl;
			cin >> d;
			cin >> m;
			cin >> y;
			cin >> kind;
			while (kind != 1 && kind != 2) 
			{
				cout << "Wrong Input Number for The Elections Round Kind. Please Choose '1' or '2'" << endl;
				cin >> kind;
			}
			if (kind == 1) 
			{
				election = new ElectionsRound(d, m, y);
				election->setKind(kind);
			}
			else 
			{
				int electors = 0;
				cout << "Please enter Number of Electors:";
				cin >> electors;
				election = new SimpleElectionsRound(d, m, y, electors);
				election->setKind(kind);
			}
			PrintMainMenu();  // Show main menu
			int Choice;       // the action the user choose
			cin >> Choice;    // user's choice
			while (Choice != 10) 
			{
				system("cls");
				switch (Choice)//Switch case 'Choice'

				{
					case static_cast<int>(action::ac1) :
						if (kind == 1) 
						{
							readDistrict(*election);
						}
						else 
						{
							cout << "ERROR! Couldn't add District in Simple Election Round'" << endl;
						}
					break;
					case static_cast<int>(action::ac2) :
						if (kind == 1)
							readCitizen(*election);
						else
							readCitizenS(*(SimpleElectionsRound*)election);
						break;
						case static_cast<int>(action::ac3) :
							read_Party(*election);
							break;
							case static_cast<int>(action::ac4) :
								if (kind == 1)
									read_Candidate(*election);
								else
									read_CandidateS(*(SimpleElectionsRound*)election);
								break;
								case static_cast<int>(action::ac5) :
									election->PrintDistricts();
									break;
									case static_cast<int>(action::ac6) :
										election->PrintCitizens();
										break;
										case static_cast<int>(action::ac7) :
											election->PrintParties();
											break;
											case static_cast<int>(action::ac8) :
												vote(*election);
												break;
												case static_cast<int>(action::ac9) : 
												{
													if (kind == 1) 
													{
														ResultsR(*election);
														election->getPartyArr().resetDataCalc();
													}
													else 
													{
														ResultsS(*(SimpleElectionsRound*)election);
													}
												}
												break;
												case static_cast<int>(action::ac10) :
													break;
													case static_cast<int>(action::ac11) ://Save elections Round
													{
														election->getPartyArr().resetDataCalc();// Reset Elections Round Parameters (in case there is trash values)
														election->SetPartyWinnerAtDistrict();   // work
														election->calcAndSetResultInDis(); 
														char FileName[100]; // Should make const parameter for the NAME LEN
														cout << "Please Enter the File Name:" << endl;
														cin >> FileName;
														ofstream ExtractFile(FileName, ios::binary);
														if (!ExtractFile)
														{
															cout << "Can't open the file!" << endl;
															return 0;
														}
														election->save(ExtractFile);
														ExtractFile.close();
													}
													break;
													case static_cast<int>(action::ac12) : //Load elections Round
													{
														char FileName[NAMELEN];
														cout << "Please Enter the File Name " << endl;
														cin >> FileName;
														ifstream LoadFile(FileName, ios::binary);
														if (!LoadFile) {
															cout << "Can't open the file!" << endl;
															exit(1);
														}
														election = new ElectionsRound();
														election->load(LoadFile);
														election->connectPointers(); // Connect the Pointers After Loading a file
														LoadFile.close();
													}
													break;
													default:
														cout << "Wrong input choice" << endl;
				}//end switch (Choice)
				cout << endl;
				PrintMainMenu();
				cin >> Choice; //Next choice
			}//end while (choice!=10)
			cout << "Good Bye " << endl;
			break;
	///////////////////////////////////////////////Case 2////////////////////////////////////////////////
			case static_cast<int>(func::f2) : //Load elections round ( input : 'file name')

			{
				char FileName[NAMELEN]; // Should be LEN NAME parameter
				cout << "Please Enter the File Name " << endl;
				cin >> FileName;
				ifstream LoadFile(FileName, ios::binary);
				if (!LoadFile)
				{
					cout << "Can't open the file!" << endl;
					exit(1);
				}
				election = new ElectionsRound();
				election->load(LoadFile);
				election->connectPointers(); // connect The Pointers After Load
				LoadFile.close();
				PrintMainMenu();// Show main menu
				int Choice;     // the action the user choose
				cin >> Choice;  // user's choice
				while (Choice != 10)
				{
				//	system("cls");
					switch (Choice)//Switch case 'Choice'

					{
						case static_cast<int>(action::ac1) :
							if (election->getELRKind() == 1)
							{
								readDistrict(*election);
							}
							else
							{
								cout << "ERROR! Couldn't add District in 'Simple Election Round'" << endl;
							}
						break;
						case static_cast<int>(action::ac2) :
							if (election->getELRKind() == 1)
								readCitizen(*election);
							else
								readCitizenS(*(SimpleElectionsRound*)election);
							break;
							case static_cast<int>(action::ac3) :
								read_Party(*election);
								break;
								case static_cast<int>(action::ac4) :
									if (election->getELRKind() == 1)
										read_Candidate(*election);
									else
										read_CandidateS(*(SimpleElectionsRound*)election);
									break;
									case static_cast<int>(action::ac5) :
										election->PrintDistricts();
										break;
										case static_cast<int>(action::ac6) :
											election->PrintCitizens();
											break;
											case static_cast<int>(action::ac7) :
												election->PrintParties();
												break;
												case static_cast<int>(action::ac8) :
													vote(*election);
													break;
													case static_cast<int>(action::ac9) :
													{
														if (election->getELRKind() == 1)
														{
															ResultsR(*election);
															election->getPartyArr().resetDataCalc();
														}
														else 
														{
															ResultsS(*(SimpleElectionsRound*)election);
														}
													}
													break;
													case static_cast<int>(action::ac10) :
														break;
														case static_cast<int>(action::ac11) ://Save elections Round
														{
														election->getPartyArr().resetDataCalc();// Reset Elections Round Parameters (in case there is trash values)
														election->SetPartyWinnerAtDistrict();   //work
														election->calcAndSetResultInDis(); 
															char FileName[NAMELEN]; // Should make const parameter for the NAME LEN
															cout << "Please Enter the File Name:" << endl;
															cin >> FileName;
															ofstream ExtractFile(FileName, ios::binary);
															if (!ExtractFile) {
																cout << "Can't open the file!" << endl;
																return 0;
															}
															election->save(ExtractFile);
															ExtractFile.close();
														}
														break;
														case static_cast<int>(action::ac12) : //Load elections Round
														{
															char FileName[NAMELEN];
															cout << "Please Enter the File Name " << endl;
															cin >> FileName;
															ifstream LoadFile(FileName, ios::binary);
															if (!LoadFile) {
																cout << "Can't open the file!" << endl;
																exit(1);
															}
															election = new ElectionsRound();
															election->load(LoadFile);
															election->connectPointers(); // connect The Pointers After Lode
															LoadFile.close();
														}
														break;
														default:
															cout << "Wrong input choice" << endl;
					}//end switch (Choice)
					cout << endl;
					PrintMainMenu();
					cin >> Choice; //Next choice
				}//end while (choice!=10)
				cout << "Good Bye " << endl;			
			}
				break;
	///////////////////////////////////////////////Case 3////////////////////////////////////////////////
				case static_cast<int>(func::f3) :
					exit(1);
				break;
				default:
					cout << "Wrong input choice" << endl;
	}
	return 0;
}