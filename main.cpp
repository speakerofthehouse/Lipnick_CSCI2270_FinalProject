#include <iostream>
#include <fstream>
#include <string>
#include "rbtree.h"

int main(int argc, char* argv[]) {
	RBTree *tree = new RBTree();

	// optionally create tree from command line argument
	if (argv[1]) {
		std::ifstream file;
		file.open(argv[1]);
		if (file.is_open()) {
			std::string line = "";
			while (std::getline(file, line)) {
				tree->insert(line);
			}
			file.close();
		}
		else {
			std::cout << "Could not open file." << std::endl;
		}
	}

	// run menu
	bool quit = false;
	while (!quit) {
		std::cout << "======Main Menu======" << std::endl;
		std::cout << "1. Add a person" << std::endl;
		std::cout << "2. Add persons from file" << std::endl;
		std::cout << "3. Find a person" << std::endl;
		std::cout << "4. Delete a person" << std::endl;
		std::cout << "5. Print list of people" << std::endl;
		std::cout << "6. Print red nodes" << std::endl;
		std::cout << "7. Print black nodes" << std::endl;
		std::cout << "8. Quit" << std::endl;

		std::string selection = "";
		std::cin >> selection;

		if (selection == "1") {
			std::cout << "Name: ";
			std::cin.ignore();
			std::string name = "";
			std::getline(std::cin, name);
			tree->insert(name);
		}
		else if (selection == "2") {
			std::cout << "File must be a .txt file with each name on a single line." << std::endl;
			std::cout << "Enter file name or enter Q to return to main menu." << std::endl;
			std::cin.ignore();
			std::string filename = "";
			std::getline(std::cin, filename);
			if (filename == "Q") {
				std::cout << "Going back to menu." << std::endl;
			}
			else {
				std::ifstream file;
				file.open(filename);
				if (file.is_open()) {
					std::string line = "";
					while (std::getline(file, line)) {
						tree->insert(line);
					}
					file.close();
				}
				else {
					std::cout << "Could not open file." << std::endl;
				}
			}
		}
		else if (selection == "3") {
			std::cout << "Name: ";
			std::cin.ignore();
			std::string name = "";
			std::getline(std::cin, name);
			node* searched = tree->search(name);
			if (searched != NULL) {
				if (searched->key != "nullNode") {
					std::cout << searched->key << " found." << std::endl;
				}
				else {
					std::cout << "Person not found." << std::endl;
				}
			}
			else {
				std::cout << "No nodes found." << std::endl;
			}
		}
		else if (selection == "4") {
			std::cout << "This feature is still in development." << std::endl;
			std::cout << "Name: ";
			std::cin.ignore();
			std::string name = "";
			std::getline(std::cin, name);
			tree->deleteNode(name);
		}
		else if (selection == "5") {
			tree->printTree();
		}
		else if (selection == "6") {
			tree->printRedNodes();
		}
		else if (selection == "7") {
			tree->printBlackNodes();
		}
		else if (selection == "8") {
			quit = true;
			std::cout << "Goodbye!" << std::endl;
		}
		else {
			std::cout << "Selection not understood. Please try again." << std::endl;
		}
	}

	return 0;
}
