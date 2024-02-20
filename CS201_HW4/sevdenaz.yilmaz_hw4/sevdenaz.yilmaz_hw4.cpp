#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
using namespace std;

struct movie {
	string name;
	int year;
	string genre;
};

vector<movie> createList(string inputs) {
	vector<movie> movies;
	movie m;
	inputs = inputs + "|";
	int size = inputs.size();
	int j = 0, k = 0;
	for (int i = 0; i < size; i++) {
		if (inputs[i] == '|') {
			for (; j < i; j++) {
				if (inputs[j] == ';') {
					m.name = inputs.substr(k, j - k);
					m.year = stoi(inputs.substr(j + 1, 4));
					m.genre = inputs.substr(j + 6, i - j - 6);
					j = i;
					k = j + 1;
					movies.push_back(m);
				}
			}
		}
	}
	return movies;
}

void sortList(vector<movie>& myList) {
	int size = myList.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (myList[j].year == myList[j + 1].year) {
				if (myList[j].name > myList[j + 1].name) {
					movie temp = myList[j];
					myList[j] = myList[j + 1];
					myList[j + 1] = temp;
				}
			}
			else if (myList[j].year < myList[j + 1].year) {
				movie temp = myList[j];
				myList[j] = myList[j + 1];
				myList[j + 1] = temp;
			}
		}
	}
}

int main() {
	cout << "Welcome to the movie recommender program!" << endl << endl;
	cout << "Please enter the movie, year and genre list:" << endl;
	string inputs;
	cin >> inputs;
	vector<movie> movies = createList(inputs);
	sortList(movies);
	int size = movies.size();

	cout << endl << "Please select your action:" << endl;
	cout << "1. Select the genre of the movie that you want to watch" << endl;
	cout << "2. Select the year of the movie that you want to watch" << endl;
	cout << "3. Choose a random movie" << endl;
	cout << "4. Exit program" << endl << endl;
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	while (choice != 4) {
		if (choice == 1) {
			bool isFound = false;
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
				if (movies[i].genre == genre) {
					isFound = true;
					i = size;
				}
			}
			cout << endl;
			if (isFound) {
				cout << tmp << " movies from newest to oldest:" << endl;
				for (int i = 0; i < size; i++) {
					if (movies[i].genre == genre) {
						cout << "Movie name: " << movies[i].name << " Release Year: " << movies[i].year << endl;
					}
				}
			}
			else {
				cout << "There are no " << tmp << " movies!" << endl;
			}
		}
		else if (choice == 2) {
			bool isFound = false;
			string input;
			cout << "Please enter the year of the movie you want to watch: ";
			cin >> input;
			if (input.find('-') == string::npos) {
				int year = stoi(input);
				for (int i = 0; i < size; i++) {
					if (movies[i].year == year) {
						isFound = true;
						i = size;
					}
				}
				if (isFound) {
					cout << "Movies released in " << year << " from A to Z:" << endl;
					for (int i = 0; i < size; i++) {
						if (movies[i].year == year) {
							cout << "Movie name: " << movies[i].name << " Genre: " << movies[i].genre << endl;
						}
					}
				}
				else {
					cout << "There are no movies released in " << year <<"!" << endl;
				}
			}
			else {
				int first = stoi(input.substr(0, input.find('-')));
				int second = stoi(input.substr(input.find('-') + 1));
				for (int i = 0; i < size; i++) {
					if (movies[i].year >= first && movies[i].year <= second) {
						isFound = true;
						i = size;
					}
				}
				if (isFound) {
					cout << "Movies released between the years " << input << " from A to Z with decreasing year ordering:" << endl;
					for (int i = 0; i < size; i++) {
						if (movies[i].year >= first && movies[i].year <= second) {
							cout << "Movie name: " << movies[i].name << " Release Year: " << movies[i].year << " Genre: " << movies[i].genre << endl;
						}
					}
				}
				else {
					cout << "There are no movies released between " << input << "!" << endl;
				}
			}
		}
		else if (choice == 3) {
			RandGen rndom;
			int random = rndom.RandInt(0, size - 1);
			cout << "Movie name: " << movies[random].name << " Release Year: " << movies[random].year << " Genre: " << movies[random].genre << endl;
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