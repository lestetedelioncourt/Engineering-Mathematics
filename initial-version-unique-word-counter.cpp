/*First program I designed*/
/*NB - ALL INCREMENTING ARRAYS CAN NOW BE REPLACED WITH VECTORS. NO NEED FOR CHAR ARRAY AS .at() FUNCTION SOLVES
	SAME PROBLEM. NO NEED FOR LINE ARRAY AS CAN PROCESS DATA DIRECTLY FROM STRING LINE. CAN USE IN-BUILT BUBBLE 
	SORT FOR VECTOR INSTEAD OF MANUAL SORT, SO NO SEPARATE ARRAYS NEEDED. TWO VECTORS NEEDED IN TOTAL.
	tolower() FUNCTION CAN BE USED TO CONVERT CHARS TO LOWER CASE - REQUIRES HEADER <CCTYPE>*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


int main(){
	fstream Myfile; //text file to be read
	string L[6000]; //store for lines of text
	fstream Newfile; //File for writing most popular words and how often they are used (words used more than once)
	int n = 0;  
	int d = 0; 
	int a = 0; 
	int Total = 0; //used to determine how many characters store in line store string array L
	char *Myarray; //pointer for dynamic char array created on basis of total characters determined by total 
	string *Word, *Word2;  
	//pointers for dynamic arrays used as stores for unique words, two are needed to increment array size whilst  
	//preserving contents of old one. 
	/*NB: Use of function can increment array size without need for second array*/
	int *Money, *Money2;
	//above store for count related to word usage for each unique word, two are needed to increment array size
	//whilst preserving contents of old one
	int *M; //int array for storing most popular words
	string *N; //string array for storing most popular words

	Myfile.open("ssa.txt", ios::out | ios::in | ios::app); //opens file for reading input
	/*Myfile << "This is what's written in the file." << endl;
	Myfile << "This is what I expect to output" << endl;
	Myfile.close();*/
	string Line; //string variable for storing lines
	if (Myfile.is_open()){
		while (getline(Myfile, Line)){
			L[n] = Line + " "; //gets lines of text from input file, stores in string array
			n++;
		}
	}
	else{
		cout << "The file is closed"; 
	}

	cout << "n = " << n << endl;
	Myfile.close(); //closes file

	for (int k = 0; k < n; k++){
		//cout << "Length of string L[" << a << "] is " << L[a].length() << endl;
		Total = Total + L[k].length();
	}

	Myarray = new char[Total]; //total number of characters used to initialise char array
	d = 0; //d in this case used to denote position of char array

	for (int k = 0; k < n; k++){ //crawls line string array
		int c = L[k].length(); //stores line length
		for (int b = 0; b < c; b++){ //crawls character elements for length of each line string
			Myarray[d] = L[k].at(b); //inserts character element into char array
			switch (Myarray[d]){
				//finds cases of special characters, changes into to standard ascii
			case (char)145: Myarray[d] = char(96); 
				break;
			case (char)146: Myarray[d] = char(39);
				break;
			case (char)147: Myarray[d] = char(34);
				break;
			case (char)148: Myarray[d] = char(34);
				break;
			}
			if ((Myarray[d] >= (char)65) && (Myarray[d] <= (char)90)){ //if character is upper case
				int H = (int)Myarray[d]; //stores ascii value for upper case character as an integer
				H = H + 32; //changes to ascii value for lower case, ascii value for upper case + 32
				Myarray[d] = (char)H; //lower case character placed into array position
				/*NB - CAN USE tolower() FUNCTION*/
			}
			d++; //moves to next position
		}
	}

	/*NB - CAN READ STRAIGHT FROM LINE ARRRAY USING ABOVE LOOPS AND .at(). NO NEED FOR CHAR ARRAY*/
	
	for (int y = 0; y < 100; y++){
		cout << Myarray[y];
	}

	cout << "\n\nCharacter count (including spaces) = " << Total << endl;

	int Array = 1; //initial size of usage count and unique word arrays
	
	//creates new arrays for storing word usage counts. two needed, one for incrementing, one for transferring 
	//stored values to incremented array
	Money = new int[Array];
	Money2 = new int[Array];

	for (int x = 0; x < Array; x++){
		Money[x] = 0;
		Money2[x] = 0;
	} //initializes values
	
	//creates new arrays for storing unique words. two needed, one for incrementing, one for transferring stored
	//values to incremented array
	Word = new string[Array];
	Word2 = new string[Array];
	
	n = 0; //n variable used to simultaneously crawl up 'unique word' array and usage count arrays as entries added 
	d = 0; 
	a = 0;
	/*d and a are required to crawl the character array, when a finds the end of word case ' ', '.', etc.
	a will denote the position of the case and position d will denote the start of the word, i.e. if the
	first word is "this", a will stop at position 4, and d will be at position 0. For the next word d will
	start at position 5, and a will crawl the char array until it finds the next end of word case. d will be 
	used to crawl up the array to confirm a letter is present to indicate the start of a word*/

	for (n = 0; n < Array; n++){
		delete[] Word; //deletes old array
		Word = new string[Array]; //creates new 'unque word' string array incremented in size
		delete[] Money; //deletes old array
		Money = new int[Array]; //creates new 'word instance count' int array incremented in size
		for (int x = 0; x < Array; x++){
			Money[x] = 0;
		}//initialization - possible problem running without initialization?
		for (int k = 0; k < n; k++){
			Word[k] = Word2[k]; //transfers contents of old word array to new incremented array 
			Money[k] = Money2[k]; //transfers contents of old count array to new incrememted array
		}
		//below code searches character array for next space
		while (a < Total){
			a++;
			switch (Myarray[a]){ //potential cases indicating a word end
			case ' ':
			case '?':
			case '!':
			case ',':
			case '.':
			case '"':
			case '-':
			case ';':
			case ')':
			case (char)133:
			case (char)160: 
			case (char)39:
				int b = 0; 
//b is used to crawl the char array between myarray[d] (start of the word) and myarray[a] (end of the word)
				int c = 0;
//c is used to crawl the word array to find out if there is already a matching word entry
				if ((Myarray[a - 1] >= 'a') && (Myarray[a - 1] <= 'z')){ 
				//finds if word end signifier is preceded by a letter
					do{
						if ((Myarray[d] >= 'a') && (Myarray[d] <= 'z')){
							//finds if position d indicates start of word 
							Array++;
							for (b = d; b < a; b++){ 
								Word[n] = Word[n] + Myarray[b];	//the word is added as a new entry
							}
						}
						else d++; //else crawl up char array to find start of word
					} while (b < a); //until word entry has been completed
					d = a + 1; // d moves to start of the next potential word after word end detected
					if (Word[n] == "s"){ //check to see if word is just a case of 's
						Word[n].clear(); //clears entry
						n--;
						Array--;
						//for decreasing the size of the array
					}
					/*else{
						cout << "Word [" << n << "] = " << Word[n] << endl;
					}*/
					for (c = 0; c < n; c++){
						if (Word[n] == Word[c]){ //if match is fonund in word string array
							Word[n].clear(); //clears entry made in array
							Money[c]++; //counts instances of word in program
							c = n + 1; //c prepares for next entry
							n--; 
							Array--; //for decreasing the size of the array
						}
					}
					if (c == n){ //if no match is found
						Money[n] = Money[n] + 1; //add usage count to array slot
						cout << "Word2 [" << n << "] = " << Word[n] << endl;
						//display new addition to unique word array
					}
				}
				if (b > 0){
					a = Total +1;
				}// breaks out of the while loop
			}
		}
		a = d; //sets a to the potential starting position of the next word
		n++; //next potential empty slot of unique word array
		
		/*below runs for the purpose of incrementing the array*/
		delete[] Word2; //deletes old array
		Word2 = new string[Array]; //creates new 'unque word' string array incremented in size
		delete[] Money2; //deletes old array
		Money2 = new int[Array]; //creates new 'word instance count' int array incremented in size
		for (int x = 0; x < Array; x++){
			Money2[x] = 0; 
		}//initialization - possible problem running without initialization?
		for (int k = 0; k < n; k++){
			Word2[k] = Word[k]; //transfers contents of old word array to new incremented array 
			Money2[k] = Money[k]; //transfers contents of old count array to new incrememted array
		}
		//below code searches character array for next space
		while (a < Total){
			a++;
			switch (Myarray[a]){
			case ' ':
			case '?':
			case '!':
			case ',':
			case '.':
			case '"':
			case '-':
			case ':':
			case ';':
			case ')':
			case (char)133:
			case (char)160:
			case (char)39:
				int b = 0;
//b is used to crawl the char array between myarray[d] (start of the word) and myarray[a] (end of the word)
				int c = 0;
//c is used to crawl the word array to find out if there is already a matching word entry
				if ((Myarray[a - 1] >= 'a') && (Myarray[a - 1] <= 'z')){ 
				//finds if word end signifier is preceded by a letter
					do{
						if ((Myarray[d] >= 'a') && (Myarray[d] <= 'z')){
							//finds if position d indicates start of word 
							Array++;
							for (b = d; b < a; b++){
								Word2[n] = Word2[n] + Myarray[b]; //the word is added as a new entry
							}
						}
						else {
							d++; //else crawl up char array to find start of word
						}
					} while (b < a); //until word entry has been completed
					d = a + 1; // d moves to start of the next potential word after word end detected
					if (Word2[n] == "s"){ //check to see if word is just a case of 's
						Word2[n].clear(); //clears entry
						n--;
						Array--;
						//for decreasing the size of the array						
					}
					/*else{
						cout << "Word2 [" << n << "] = " << Word2[n] << endl;
					}*/
					for (c = 0; c < n; c++){
						if (Word2[n] == Word2[c]){ //if match is fonund in word string array
							Word2[n].clear(); //clears entry made in array
							Money2[c]++; //counts instances of word in program
							c = n + 1; //c prepares for next entry
							n--;
							Array--; //for decreasing the size of the array
						}
					}
					if (c == n){ //if no match is found
						Money2[n] = Money2[n] + 1; //add usage count to array slot
						cout << "Word2 [" << n << "] = " << Word2[n] << endl;
						//display new addition to word array
					}
				}
				if (b > 0){
					a = Total + 1; //breaks while loop
				}
			}
		}
		a = d; //sets a at starting position of next potemtial word
	}

	cout << "ok\n";
	//code always ends with Word2 and Money2 array holding most recent version.
	delete[] Word; 
	delete[] Money;
	delete[] Myarray; //char array no longer needed
	
	Newfile.open("uni4.txt", ios::in | ios::out | ios::app); //opens newfile for writing

	for (int k = 0; k < n; k++){
		Newfile << Word2[k] << " " << Money2[k] << endl; //writes results to newfile 
	}

	int Most = 0; //sets up int to be used to store the vslue of the highest word usage count

	M = new int[n]; //n is size of unique words collected
	N = new string[n];

	cout << "alright\n";

	/*entire for loop and if-else statement = manual bubble sort algorithm*/
	for (int x = 0; x < n; x++){
	//if {current word usage count is highest, it goes in position 0 - everything else gets shifted down a place}
		if (Money2[x] >= Most){ 
			Most = Money2[x];  
			if (x != 0){
				for (int b = x; b > 0; b--){  
					M[b] = M[b - 1]; //every other word usage count shifts down shifts down
					N[b] = N[b - 1]; //every other unique word shifts down
				}
			}
			M[0] = Most; //new highest word usage count in position 1
			N[0] = Word2[x]; //associated unique word goes into that position
		}
		else{
			//else crawl down array, if current usage count is bigger or equal to count curently in array slot, it 
			//goes in that position and everything else is shifted down a place
			for (int b = 0; b < x; b++){
				if (Money2[x] >= M[b]){
					for (int c = x; c > b; c--){
						M[c] = M[c - 1]; //every other usage count stored shifts down
						N[c] = N[c - 1]; //every other unique word stored shifts down
					}
					M[b] = Money2[x]; //current word usage count goes into size ordered position
					N[b] = Word2[x]; //associated unique word also goes into postion
					b = n +1;
				}
			}
		}
	}

	for (int x = 0; x < 300; x++){
		cout << N[x] << " = " << M[x] << "times\n"; 
		//outputs 300 most used words in order of how often they are used
	}

	Newfile.close(); //closes newfile

	return 0;
}