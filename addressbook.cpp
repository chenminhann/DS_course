#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"addressbook.pb.h"
using namespace std;

void PromptForAddress(learning::Person* person) {

    cout << "Enter person ID number: ";

    int id;

    cin>> id;

    person->set_id(id);

    cin.ignore(256, '\n');

    cout << "Enter name: ";

    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none):";

    string email;

    getline(cin, email);

    if (!email.empty()) {

        person->set_email(email);

    }

    while (true) {

        cout << "Enter a phone number (or leave blank to finish): ";

        string number;

        getline(cin, number);

        if (number.empty()) {

            break;

        }

        learning::Person::PhoneNumber* phone_number = person->add_phone();

        phone_number->set_number(number);



        cout << "Is this a mobile, home, or work phone?";

        string type;

        getline(cin, type);

        if (type == "mobile") {

            phone_number->set_type(learning::Person::MOBILE);

        } else if (type == "home") {

            phone_number->set_type(learning::Person::HOME);

        } else if (type == "work") {

            phone_number->set_type(learning::Person::WORK);

        } else {

            cout << "Unknownphone type.  Using default Home." << endl;

        }

    }

}



// Main function:  Reads the entire address book from a file,
//
//  adds one person based on user input, then writes it back out to the same file.

int main(int argc, char* argv[]) {

//   Verify that the version of the library that we linked against is
//
//  compatible with the version of the headers we compiled against.

    GOOGLE_PROTOBUF_VERIFY_VERSION;



    if (argc != 2) {

        cerr << "Usage:  " << argv[0] << "ADDRESS_BOOK_FILE" << endl;

        return -1;

    }



    learning::AddressBook address_book;


    {

        // Read the existing address book.

        fstream input(argv[1], ios::in | ios::binary);

        if (!input) {

            cout << argv[1] << ":File not found.  Creating a new file." << endl;

        } else if (!address_book.ParseFromIstream(&input)) {

            cerr << "Failedto parse address book." << endl;

            return -1;

        }

    }



    // Add an address.

    PromptForAddress(address_book.add_person());


    {

        // Write the new address book back to disk.

        fstream output(argv[1], ios::out | ios::trunc | ios::binary);

        if (!address_book.SerializeToOstream(&output)) {

            cerr << "Failedto write address book." << endl;

            return -1;

        }

    }



    //Optional:  Delete all global objects allocated by libprotobuf.

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
