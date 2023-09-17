#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Contact
{
    std::string name;
    std::string phoneNumber;
    std::string email;
};

void addContact(std::vector<Contact> &phoneBook)
{
    Contact newContact;
    std::cout << "Enter name: ";
    std::cin >> newContact.name;
    std::cout << "Enter phone number: ";
    std::cin >> newContact.phoneNumber;
    std::cout << "Enter email address: ";
    std::cin >> newContact.email;

    phoneBook.push_back(newContact);
    std::cout << "Contact added successfully!" << std::endl;
}

void removeContact(std::vector<Contact> &phoneBook)
{
    std::string searchName;
    std::cout << "Enter the name of the contact to remove: ";
    std::cin >> searchName;

    bool contactFound = false;
    for (auto it = phoneBook.begin(); it != phoneBook.end(); ++it)
    {
        if (it->name == searchName)
        {
            phoneBook.erase(it);
            contactFound = true;
            break;
        }
    }

    if (contactFound)
    {
        std::cout << "Contact removed successfully!" << std::endl;
    }
    else
    {
        std::cout << "Contact not found!" << std::endl;
    }
}

void searchContact(const std::vector<Contact> &phoneBook)
{
    std::string searchName;
    std::cout << "Enter the name of the contact to search: ";
    std::cin >> searchName;

    bool contactFound = false;
    for (const auto &contact : phoneBook)
    {
        if (contact.name == searchName)
        {
            std::cout << "Name: " << contact.name << std::endl;
            std::cout << "Phone Number: " << contact.phoneNumber << std::endl;
            std::cout << "Email: " << contact.email << std::endl;
            contactFound = true;
            break;
        }
    }

    if (!contactFound)
    {
        std::cout << "Contact not found!" << std::endl;
    }
}

void displayContacts(const std::vector<Contact> &phoneBook)
{
    std::cout << "Phone Book Contacts:" << std::endl;
    for (const auto &contact : phoneBook)
    {
        std::cout << "Name: " << contact.name << std::endl;
        std::cout << "Phone Number: " << contact.phoneNumber << std::endl;
        std::cout << "Email: " << contact.email << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}

void saveContacts(const std::vector<Contact> &phoneBook, const std::string &filename)
{
    std::ofstream outputFile(filename);
    if (outputFile.is_open())
    {
        for (const auto &contact : phoneBook)
        {
            outputFile << contact.name << "," << contact.phoneNumber << "," << contact.email << std::endl;
        }
        outputFile.close();
        std::cout << "Phone book saved successfully!" << std::endl;
    }
    else
    {
        std::cout << "Error opening the file for saving." << std::endl;
    }
}

void loadContacts(std::vector<Contact> &phoneBook, const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        phoneBook.clear();

        std::string line;
        while (std::getline(inputFile, line))
        {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos)
            {
                Contact contact;
                contact.name = line.substr(0, pos1);
                contact.phoneNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
                contact.email = line.substr(pos2 + 1);
                phoneBook.push_back(contact);
            }
        }

        inputFile.close();
        std::cout << "Phone book loaded successfully!" << std::endl;
    }
    else
    {
        std::cout << "Error opening the file for loading." << std::endl;
    }
}

int main()
{
    std::vector<Contact> phoneBook;
    std::string filename = "phonebook.txt";

    loadContacts(phoneBook, filename);

    while (true)
    {
        std::cout << "Phone Book Menu:" << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. Remove Contact" << std::endl;
        std::cout << "3. Search Contact" << std::endl;
        std::cout << "4. Display Contacts" << std::endl;
        std::cout << "5. Save Contacts" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice (1-6): ";

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            addContact(phoneBook);
            break;
        case 2:
            removeContact(phoneBook);
            break;
        case 3:
            searchContact(phoneBook);
            break;
        case 4:
            displayContacts(phoneBook);
            break;
        case 5:
            saveContacts(phoneBook, filename);
            break;
        case 6:
            saveContacts(phoneBook, filename);
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;
    }
}
