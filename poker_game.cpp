#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <set>
#include <string>
#include <functional>
#include <iterator>
#include <stdexcept>

using namespace std;

struct Card {
	char newSuit;
	char newCardno;
};

void populateDeck(vector<Card> &Deck);
void shuffle(vector<Card> &Deck);
void swap(Card& A, Card& B);
void printDeck(const vector<Card> &Deck);
int createPlayers();
int dealHands(const vector<Card> &Deck, vector<vector<Card>> &hands, const int &noplayers);
void dealFlop(const vector<Card> &Deck, vector<Card> &faceup, int &position);
void dealTurn(const vector<Card> &Deck, vector<Card> &faceup, int &position);
void dealRiver(const vector<Card> &Deck, vector<Card> &faceup, int &position);
void constructScores(const vector<vector<Card>> &hands, const vector<Card> &faceup, const int &noplayers);
void cardPermutations(int combos[][5]);
void clearLast(vector<vector<Card>> &hands, vector<Card> &faceup, const int &noplayers);

int main() {
	vector<Card> Deck;
	vector<vector<Card>> hands;
	vector<Card> faceup;
	int noofplayers;
	int position;
	char answer;

	populateDeck(Deck);
	printDeck(Deck);
	shuffle(Deck);
	printDeck(Deck);

	cin.exceptions(ios_base::failbit);
	noofplayers = createPlayers();

	do {
		shuffle(Deck);
		position = dealHands(Deck, hands, noofplayers);
		dealFlop(Deck, faceup, position);
		dealTurn(Deck, faceup, position);
		dealRiver(Deck, faceup, position);

		for (auto i : faceup) {
			cout << i.newCardno << " " << i.newSuit << "  ";
		}
		cout << "\n\n";
		constructScores(hands, faceup, noofplayers);
		clearLast(hands, faceup, noofplayers);
		do {
			cout << "\nWant to play another rounnd? (Y/N)";
			cin >> answer;
		} while ((answer != 'y') && (answer != 'Y') && (answer != 'N') && (answer != 'n'));
	} while ((answer == 'y') || (answer == 'Y'));

	return 0;
}


void populateDeck(vector<Card> &Deck) {
	if (Deck.size() > 0) {
		for (int i = 0; i < Deck.size(); ++i) {
			Deck.pop_back();
		}
	}
	Card newCard;
	char suit[] = { (char)3, (char)4, (char)5, (char)6 };
	char cardno[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			newCard.newSuit = suit[i];
			newCard.newCardno = cardno[j];
			Deck.push_back(newCard);
		}
	}
}

void printDeck(const vector<Card> &Deck) {
	for (int i = 0; i < 52; ++i) {
		cout << Deck[i].newCardno << " " << Deck[i].newSuit << endl;
	}
	cout << endl;
}

void swap(Card &A, Card &B) {
	Card temp = A;
	A = B;
	B = temp;
}

void shuffle(vector<Card> &Deck) {
	for (int i = 0; i < 52; ++i) {
		swap(Deck[i], Deck[(rand() + time(0)) % 52]);
	}
}

int createPlayers() {
	int noplayers;
	do {
		cout << "How many players would you like to enter? ";
		try {
			cin >> noplayers;
		}
		catch (exception e) {
			cout << "You didn't enter an integer\n";
			cin.clear();
			cin.ignore(100, '\n');
			noplayers = 0;
		}
		if ((noplayers < 2) || (noplayers > 10)) {
			cout << "Please enter a number of players between 2-10";
		}
	} while ((noplayers < 2) || (noplayers > 10));
	return noplayers;
}

int dealHands(const vector<Card> &Deck, vector<vector<Card>> &hands, const int &noplayers) {
	int position = 0;

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < noplayers; ++j) {
			hands.push_back(vector<Card>());
			hands[j].push_back(Deck[position]);
			++position;
		}
	}

	for (int i = 0; i < noplayers; ++i) {
		cout << "Hand " << i;
		for (int j = 0; j < 2; ++j) {
			cout << ": " << hands[i][j].newCardno << " " << hands[i][j].newSuit << "  ";
		}
		cout << "\n\n";
	}

	return position;
}

void dealFlop(const vector<Card> &Deck, vector<Card> &faceup, int &position) {
	++position;
	for (int i = 0; i < 3; ++i) {
		faceup.push_back(Deck[position]);
		++position;
	}
}

void dealTurn(const vector<Card> &Deck, vector<Card> &faceup, int &position) {
	++position;
	faceup.push_back(Deck[position]);
	++position;
}

void dealRiver(const vector<Card> &Deck, vector<Card> &faceup, int &position) {
	++position;
	faceup.push_back(Deck[position]);
	++position;
}

void cardPermutations(int combos[][5]) {
	int allcards[7] = { 0, 1, 2, 3, 4, 5, 6 };
	string temp = "";
	set<string> combinations;

	for (int j = 1; j < 7; ++j) {
		for (int k = 1; k < 7; ++k) {
			if (allcards[k] != allcards[j]) {
				temp += (allcards[k] + 48);
			}
		}
		if (temp != "") {
			combinations.insert(temp);
			temp = "";
		}
	}
	for (int i = 0; i < 7; ++i) {
		for (int k = 1; k < 7; ++k) {
			for (int j = 0; j < 7; ++j) {
				if ((j != k) && (i != j) && (i != k)) {
					temp += (allcards[j] + 48);
				}
			}
			if (temp != "") {
				combinations.insert(temp);
				temp = "";
			}
		}
	}

	int count = 0;
	for (auto i : combinations) {
		for (int j = 0; j < 5; ++j) {
			combos[count][j] = (int)(i[j] - 48);
		}
		++count;
	}
}

void constructScores(const vector<vector<Card>> &hands, const vector<Card> &faceup, const int &noplayers) {
	int npermutations[21][5];
	cardPermutations(npermutations);
	Card hriver[7];
	Card cpermutations[21][5];
	int points[21][2];
	vector<vector<Card>> hscore;
	vector<multiset<int, greater<int>>> cardnos;
	vector<int> mostarray;
	int highest[7] = { 0, 0, 0, 0, 0, 0, 0 };
	vector<int> winningplayer;

	for (int j = 0; j < 5; ++j) {
		hriver[j + 2] = faceup[j];
	}

	for (int i = 0; i < noplayers; ++i) {
		int most[2] = { 0, 0 };
		for (int i = 0; i < 21; ++i) {
			for (int j = 0; j < 2; ++j) {
				points[i][j] = 0;
			}
		}
		for (int j = 0; j < 2; ++j) {
			hriver[j] = hands[i][j];
		}
		for (int k = 0; k < 21; ++k) {
			for (int l = 0; l < 5; ++l) {
				cpermutations[k][l] = hriver[npermutations[k][l]];
			}
		}
	

		for (int k = 0; k < 21; ++k) {
			if ((cpermutations[k][0].newSuit == cpermutations[k][1].newSuit) && (cpermutations[k][0].newSuit == cpermutations[k][2].newSuit) && (cpermutations[k][0].newSuit == cpermutations[k][3].newSuit) &&
				(cpermutations[k][0].newSuit == cpermutations[k][4].newSuit)) { //flush
				points[k][0] += 1024;
			}
			set<int> straight;
			for (int l = 0; l < 5; ++l) {
				switch (cpermutations[k][l].newCardno) {
				case 'A': straight.insert(1); straight.insert(14); break;
				case '2': straight.insert(2); break;
				case '3': straight.insert(3); break;
				case '4': straight.insert(4); break;
				case '5': straight.insert(5); break;
				case '6': straight.insert(6); break;
				case '7': straight.insert(7); break;
				case '8': straight.insert(8); break;
				case '9': straight.insert(9); break;
				case 'T': straight.insert(10); break;
				case 'J': straight.insert(11); break;
				case 'Q': straight.insert(12); break;
				case 'K': straight.insert(13); break;
				}
				if (straight.size() >= 5) {
					int strait[5];
					int strai2[5] = { 0,0,0,0,0 };
					int m = 0; int n = -1;
					for (auto i2 : straight) {
						if (m <= 4) {
							strait[m] = i2;
						}
						if ((n >= 0) && (n <= 4)) {
							strai2[n] = i2;
						}
						++m;
						++n;
					}
					m = 4; n = 4;
					while (m > 0) {
						if (strait[m] - strait[m - 1] == 1) {
							--m;
						}
						else {
							m = -1;
						}
					}
					if (straight.size() == 6) {
						while (n > 0) {
							if (strai2[n] - strai2[n - 1] == 1) {
								--n;
							}
							else {
								n = -1;
							}
						}
					}
					if (n == 0) {
						for (int i2 = 0; i2 < 5; ++i2) {
							strait[i2] = strai2[i2];
						}
					}
					if ((m == 0) || (n == 0)) { //straight 
						points[k][0] += 256;
						if ((cpermutations[k][0].newSuit == cpermutations[k][1].newSuit) && (cpermutations[k][0].newSuit == cpermutations[k][2].newSuit) && (cpermutations[k][0].newSuit == cpermutations[k][3].newSuit) &&
							(cpermutations[k][0].newSuit == cpermutations[k][4].newSuit)) { //straight flush
							points[k][0] += 65536;
						}
					}
				}
			}

			for (int l = 0; l < 5; ++l) {
				for (int m = 0; m < 5; ++m) {
					if ((l != m) && (l < m)) {
						if (cpermutations[k][l].newCardno == cpermutations[k][m].newCardno) { //pair
							points[k][0] += 4;
							for (int n = 0; n < 5; ++n) {
								if ((l != m) && (m != n) && (l < m) && (m < n)) {
									if ((cpermutations[k][l].newCardno == cpermutations[k][m].newCardno) && (cpermutations[k][l].newCardno == cpermutations[k][n].newCardno)) { //triples
										points[k][0] += 64;
									}
								}
								for (int o = 0; o < 5; ++o) {
									if ((l != m) && (l != n) && (l != o) && (m != n) && (m != o) && (n != o) && (l < m) && (n < o)) {
										if ((cpermutations[k][l].newCardno == cpermutations[k][m].newCardno) && (cpermutations[k][n].newCardno == cpermutations[k][o].newCardno)) { //two pair
											points[k][0] += 16;
											for (int p = 0; p < 5; ++p) {
												if ((o != p) && (p != m) && (p != n) && (p != l) && (l == 0)) {
													if ((cpermutations[k][l].newCardno == cpermutations[k][p].newCardno) || (cpermutations[k][p].newCardno == cpermutations[k][o].newCardno)) { //full house
														points[k][0] += 4096;
													}
												}
											}
										}
										if ((cpermutations[k][l].newCardno == cpermutations[k][m].newCardno) && (cpermutations[k][n].newCardno == cpermutations[k][o].newCardno)
											&& (cpermutations[k][n].newCardno == cpermutations[k][l].newCardno) && ((l == 0) || (l == 1)) && ((m == 1) || (m == 2)) && ((n == 2) || (n == 3)) && ((o == 3) || (o == 4))) { //four of a kind
											points[k][0] += 16384;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (int k = 0; k < 21; ++k) {
			if (points[k][0] > most[0]) {
				most[0] = points[k][0];
			}
		}

		mostarray.push_back(most[0]);

		for (int k = 0; k < 21; ++k) {
			if ((((most[0] >= 0) && (most[0] < 4)) && ((points[k][0] >= 0) && (points[k][0] < 4))) //High Card
				|| (((most[0] >= 4) && (most[0] < 16)) && ((points[k][0] >= 4) && (points[k][0] < 16))) //Pair
				|| (((most[0] >= 16) && (most[0] < 64)) && ((points[k][0] >= 16) && (points[k][0] < 64))) //Two pair
				|| (((most[0] >= 64) && (most[0] < 256)) && ((points[k][0] >= 64) && (points[k][0] < 256))) //Triple
				|| (((most[0] >= 256) && (most[0] < 1024)) && ((points[k][0] >= 256) && (points[k][0] < 1024))) //Straight
				|| (((most[0] >= 1024) && (most[0] < 4096)) && ((points[k][0] >= 1024) && (points[k][0] < 4096))) //Flush
				|| (((most[0] >= 4096) && (most[0] < 16384)) && ((points[k][0] >= 4096) && (points[k][0] < 16384))) //Full House
				|| (((most[0] >= 16384) && (most[0] < 65536)) && ((points[k][0] >= 16384) && (points[k][0] < 65536))) //Four of a kind
				|| ((most[0] >= 65536) && (points[k][0] >= 65536))) { //Straight Flush
				for (int l = 0; l < 5; ++l) {
					switch (cpermutations[k][l].newCardno) {
					case 'A': points[k][1] += 14; break;
					case '2': points[k][1] += 2; break;
					case '3': points[k][1] += 3; break;
					case '4': points[k][1] += 4; break;
					case '5': points[k][1] += 5; break;
					case '6': points[k][1] += 6; break;
					case '7': points[k][1] += 7; break;
					case '8': points[k][1] += 8; break;
					case '9': points[k][1] += 9; break;
					case 'T': points[k][1] += 10; break;
					case 'J': points[k][1] += 11; break;
					case 'Q': points[k][1] += 12; break;
					case 'K': points[k][1] += 13; break;
					}
				}
			}
		}

		for (int k = 0; k < 21; ++k) {
			if (points[k][1] > most[1]) {
				most[1] = points[k][1];
			}
		}
		for (int k = 0; k < 21; ++k) {
			if (points[k][1] == most[1]) {
				hscore.push_back(vector<Card>());
				for (int l = 0; l < 5; ++l) {
					hscore[i].push_back(cpermutations[k][l]);
				}
				break;
			}
		}

		cout << "\nPlayer " << i << ": ";
		for (int k = 0; k < 5; ++k) {
			cout << hscore[i][k].newCardno << " " << hscore[i][k].newSuit << "  ";
		}
		if (most[0] >= 65536) {
			cout << "Straight flush!\n";
		}
		else if (most[0] >= 16384) {
			cout << "Four of a kind!\n";
		}
		else if (most[0] >= 4096) {
			cout << "Full house!\n";
		}
		else if (most[0] >= 1024) {
			cout << "Flush!\n";
		}
		else if (most[0] >= 256) {
			cout << "Straight!\n";
		}
		else if (most[0] >= 64) {
			cout << "Triple!\n";
		}
		else if (most[0] >= 16) {
			cout << "Two pair!\n";
		}
		else if (most[0] >= 4) {
			cout << "A pair!\n";
		}
		else {
			cout << "High card\n";
		}
	}

	for (int i = 0; i < noplayers; ++i) {
		if (mostarray[i] > highest[0]) {
			highest[0] = mostarray[i];
		}
	}

	int h = 0;
	for (int i = 0; i < noplayers; ++i) {
		if ((((highest[0] >= 0) && (highest[0] < 4)) && ((mostarray[i] >= 0) && (mostarray[i] < 4))) //High Card
			|| (((highest[0] >= 4) && (highest[0] < 16)) && ((mostarray[i] >= 4) && (mostarray[i] < 16))) //Pair
			|| (((highest[0] >= 16) && (highest[0] < 64)) && ((mostarray[i] >= 16) && (mostarray[i] < 64))) //Two pair
			|| (((highest[0] >= 64) && (highest[0] < 256)) && ((mostarray[i] >= 64) && (mostarray[i] < 256))) //Triple
			|| (((highest[0] >= 256) && (highest[0] < 1024)) && ((mostarray[i] >= 256) && (mostarray[i] < 1024))) //Straight
			|| (((highest[0] >= 1024) && (highest[0] < 4096)) && ((mostarray[i] >= 1024) && (mostarray[i] < 4096))) //Flush
			|| (((highest[0] >= 4096) && (highest[0] < 16384)) && ((mostarray[i] >= 4096) && (mostarray[i] < 16384))) //Full House
			|| (((highest[0] >= 16384) && (highest[0] < 65536)) && ((mostarray[i] >= 16384) && (mostarray[i] < 65536))) //Four of a kind
			|| ((highest[0] >= 65536) && (mostarray[i] >= 65536))) { //Straight Flush
			cardnos.push_back(multiset<int, greater<int>>());
			winningplayer.push_back(i);
			for (int j = 0; j < 5; ++j) {
				switch (hscore[i][j].newCardno) {
					case 'A': cardnos[h].insert(14); break;
					case '2': cardnos[h].insert(2); break;
					case '3': cardnos[h].insert(3); break;
					case '4': cardnos[h].insert(4); break;
					case '5': cardnos[h].insert(5); break;
					case '6': cardnos[h].insert(6); break;
					case '7': cardnos[h].insert(7); break;
					case '8': cardnos[h].insert(8); break;
					case '9': cardnos[h].insert(9); break;
					case 'T': cardnos[h].insert(10); break;
					case 'J': cardnos[h].insert(11); break;
					case 'Q': cardnos[h].insert(12); break;
					case 'K': cardnos[h].insert(13); break;
				}
			}
			++h;
		}
	}
	
	for (int i = 0; i < h; ++i) {
		multiset<int, greater<int>>::iterator iter;
		iter = cardnos[i].begin();
		int j = 1;
		while (iter != cardnos[i].end()) {
			if (*iter > highest[j]) {
				highest[j] = *iter;
			}
			++j;
			++iter;
		}
	}

	int g = 0;
	for (int i = 1; i < 5; ++i) {
		for (int j = 0; j < h; ++j) {
			multiset<int, greater<int>>::iterator iter;
			iter = cardnos[j].begin();
			for (int k = 0; k < (i - 1); ++k) {
				++iter;
			}
			if (*iter == highest[i]) {
				++g;
				highest[6] = j;
			}
		}
		if (g == 1) {
			break;
		}
	}

	cout << "The winning hand is player " << winningplayer[highest[6]] << "!" << endl; /*NB: This does not yet display the true winning hand, except in the case of straights, flushes, straight flushes,
																					   or in the case where one player has a higher order winning hand (i.e triple vs a pair)*/
}

void clearLast(vector<vector<Card>> &hands, vector<Card> &faceup, const int &noplayers) {
	for (int i = 0; i < noplayers; ++i) {
		for (int j = 0; j < 2; ++j) {
			hands[i].pop_back();
		}
	}

	for (int i = 0; i < 5; ++i) {
		faceup.pop_back();
	}
}
