#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void registerDonor();
void saveDonorsToFile();
void loadDonorsFromFile();
void searchDonorsByBloodType();
void removeDonor();


	struct Donor {
    	string name;
    	int age;
    	string bloodType;
    	string address; 
    	string contactNumber;
	};

	vector<Donor> donorList;
	
	
	int main() {
	
    	loadDonorsFromFile();
	
    	int choice;
    while(true){
        
        cout << "\n******** Blood Donation Management System ********\n\n";
    	cout << "1. Find blood donors by Blood Type\n";
    	cout << "2. Register as a Blood Donor\n";
    	cout << "3. Remove yourself from the Donor List\n";
    	cout << "4. Exit\n";
        
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchDonorsByBloodType();
                break;
            case 2:
                registerDonor();
                break;
            case 3:
                removeDonor();
                break;
            case 4:
            	cout << "\nExiting Program...\n";
            	return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
		
    return 0;
}


void registerDonor() {
    	Donor newDonor;

    	cout << "\nEnter your name: ";
    	cin.ignore();
    	getline(cin, newDonor.name);
    	cout << "Enter your age ( Should be in between 18 - 50 ): ";
		cin >> newDonor.age;
    	if(newDonor.age < 18 || newDonor.age > 50){
			cout << "Donor age should be in between ( 18 - 50 )\n";
		}
		else{
			cout << "Enter your blood type (e.g., A+, B-, O+): ";
    	cin >> newDonor.bloodType;
    	cout << "Enter your address: ";
    	cin.ignore();
    	getline(cin, newDonor.address);
    	cout << "Enter your contact number: ";
    	getline(cin, newDonor.contactNumber);

    	donorList.push_back(newDonor);
    	saveDonorsToFile();
    	cout << "\nDonor registered successfully!\n";
		}	
}
	
	
	void saveDonorsToFile() {
    	ofstream outputFile("donors.txt");

    if (outputFile.is_open()) {
        for (int i = 0; i < donorList.size(); i++) {
            outputFile << donorList[i].name << " " << donorList[i].age << " " << donorList[i].bloodType << " " << donorList[i].address 
			<< " " << donorList[i].contactNumber << endl;
        }
        outputFile.close();
    }
}


	void loadDonorsFromFile() {
    	ifstream inputFile("donors.txt");
	
    if (inputFile.is_open()) {
        Donor temp;
        while (inputFile >> temp.name >> temp.age >> temp.bloodType >> temp.address >> temp.contactNumber) {
            donorList.push_back(temp);
        }
        inputFile.close();
    }
}


	void searchDonorsByBloodType() {
    	string bloodType;
    	cout << "\nEnter the blood type to search for (e.g., A+, B-, O+): ";
    	cin >> bloodType;

    int found2 = 1;
    cout << "\n********** Donors with blood type " << bloodType << " **************\n";
    for (int i = 0; i < donorList.size(); i++) {
        if (donorList[i].bloodType == bloodType) {
            cout << "\nName: " << donorList[i].name << "\nAge: " << donorList[i].age << "\nBlood Type: " <<  donorList[i].bloodType 
			<< "\nAddress: " << donorList[i].address << "\nContact: " << donorList[i].contactNumber << endl;
            found2++;
        }
    }

    if (found2 == 1) {
        cout << "\nNo donors found with blood type " << bloodType << ".\n";
    }
}


	void removeDonor() {
    	string nameToRemove;
    	cout << "\nEnter the name of the donor you want to remove: ";
    	cin.ignore()
;    	getline(cin, nameToRemove);

    int found = 1;
    for (int i = 0; i < donorList.size(); i++) {
        if (donorList[i].name == nameToRemove) {
            donorList.erase(donorList.begin() + i);
            found++;
            break;
        }
    }

    if (found != 1) {
        saveDonorsToFile();
        cout << "\nDonor removed successfully!\n";
    } else {
        cout << "\nDonor not found.\n";
    }
}



