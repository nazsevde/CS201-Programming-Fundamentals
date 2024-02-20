#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "movie.h"
using namespace std;

vector<Movie> createlist() {
	int index;
	string fileName, inputs;
	vector<Movie> movies;
	Movie m;
	cin >> fileName;
	ifstream inFile;
	inFile.open(fileName);
	while (inFile.fail()) {
		cout << "Please check filename! Enter a correct movie list filename: ";
		cin >> fileName;
		inFile.open(fileName);
	}

	while (getline(inFile, inputs)) {
		while (inputs.find('\r') != std::string::npos) {
			inputs.erase(inputs.find('\r'), 1);
		}
		for (int i = 0; i < inputs.size(); i++) {
			if (isdigit(inputs[i])) {
				index = i;
				i = inputs.size();
			}
		}
		m.setName(inputs.substr(0, index - 1));
		m.setYear(stoi(inputs.substr(index, 4)));
		m.setGenre(inputs.substr(index + 5, inputs.length() - index - 5));
		movies.push_back(m);
	}
	return movies;
}

void sortlist(vector<Movie>& mylist) {
	int size = mylist.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (mylist[j].getYear() == mylist[j + 1].getYear()) {
				if (mylist[j].getName() > mylist[j + 1].getName()) {
					Movie temp = mylist[j];
					mylist[j] = mylist[j + 1];
					mylist[j + 1] = temp;
				}
			}
			else if (mylist[j].getYear() < mylist[j + 1].getYear()) {
				Movie temp = mylist[j];
				mylist[j] = mylist[j + 1];
				mylist[j + 1] = temp;
			}
		}
	}
}

int main() {
	cout << "Welcome to the movie recommender program!" << endl << endl;
	cout << "Please enter the movie list filename: ";
	vector<Movie> movies = createlist();
	sortlist(movies);
	int size = movies.size();

	cout << "Please select your action:" << endl;
	cout << "1. Select the genre of the movie that you want to watch" << endl;
	cout << "2. Select the year of the movie that you want to watch" << endl;
	cout << "3. Exit program" << endl << endl;
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	while (choice != 3) {
		if (choice == 1) {
			bool isfound = false;
			string genre, tmp;
			cout << "Please enter the genre of the movie you want to watch: ";
			cin >> genre;
			tmp = genre;
			for (int i = 0; i < genre.size(); i++) {
				if (genre[i] >= 'A' && genre[i] <= 'Z') {
					genre[i] = genre[i] + 32;
				}
			}
			if (genre.find('-') == string::npos) {
				genre[0] = genre[0] - 32;
			}
			else {
				genre[0] = genre[0] - 32;
				for (int i = 1; i < genre.size() - 1; i++) {
					if (genre[i] == '-')
						genre[i + 1] = genre[i + 1] - 32;
				}
			}
			for (int i = 0; i < size; i++) {
				if (movies[i].getGenre() == genre) {
					isfound = true;
					i = size;
				}
			}
			cout << endl;
			if (isfound) {
				cout << tmp << " movies from newest to oldest:" << endl;
				for (int i = 0; i < size; i++) {
					if (movies[i].getGenre() == genre) {
						cout << "Movie name: " << movies[i].getName() << " Release Year: " << movies[i].getYear() << endl;
					}
				}
			}
			else {
				cout << "There are no " << tmp << " movies!" << endl;
			}
		}
		else if (choice == 2) {
			bool isfound = false;
			string input;
			cout << "Please enter the year of the movie you want to watch: ";
			cin >> input;
			if (input.find('-') == string::npos) {
				int year = stoi(input);
				for (int i = 0; i < size; i++) {
					if (movies[i].getYear() == year) {
						isfound = true;
						i = size;
					}
				}
				if (isfound) {
					cout << "Movies released in " << year << " from A to Z:" << endl;
					for (int i = 0; i < size; i++) {
						if (movies[i].getYear() == year) {
							cout << "Movie name: " << movies[i].getName() << " Genre: " << movies[i].getGenre() << endl;
						}
					}
				}
				else {
					cout << "There are no movies released in " << year << "!" << endl;
				}
			}
			else {
				int first = stoi(input.substr(0, input.find('-')));
				int second = stoi(input.substr(input.find('-') + 1));
				for (int i = 0; i < size; i++) {
					if (movies[i].getYear() >= first && movies[i].getYear() <= second) {
						isfound = true;
						i = size;
					}
				}
				if (isfound) {
					cout << "Movies released between the years " << input << " from A to Z with decreasing year ordering:" << endl;
					for (int i = 0; i < size; i++) {
						if (movies[i].getYear() >= first && movies[i].getYear() <= second) {
							cout << "Movie name: " << movies[i].getName() << " Release Year: " << movies[i].getYear() << " Genre: " << movies[i].getGenre() << endl;
						}
					}
				}
				else {
					cout << "There are no movies released between " << input << "!" << endl;
				}
			}
		}
		else {
			cout << "Invalid action!" << endl;
		}
		cout << endl << "Enter your choice: ";
		cin >> choice;
	}
	cout << "Thank you..." << endl;
	return 0;
}
