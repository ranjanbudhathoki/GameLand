
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
#include<time.h>
#include<cmath>
#include<string>

using namespace std;


//function and constant declaration for level 1 
const int SIZE = 5, NBSIZE = 26;

void userInput(char userAnswer[], int SIZE);
void generate_random_character(char unscramble[], char randomScrambled[], char randomUnscrambled[]);
bool checkAnswer(char userAnswer[], int SIZE, char randomUnscrambled[]);
void filling_array(char unscramble[NBSIZE]);
void print(bool matchStatus);
void levelOne();
void levelTwo();
void levelThree();

//function and const declaration for level 2
const int GUESSES = 10, PASSWORD_SIZE = 3;

void fillArray(int password[PASSWORD_SIZE]);
void displayPassword(int password[PASSWORD_SIZE]);
string cardColor(int password[PASSWORD_SIZE], int userGuess);


//function and const declaration for level 3
const int Xcoordinate = 60;
const int Ycoordinate = 15;

void drawBoard();
void getNewBoard(int minimumDistance, int& userX, int& userY, int pearlArray[Ycoordinate][Xcoordinate]);
void getRandomPearls(int pearls[3][2]);
bool isValidMove(int x, int y);
void enterPlayerMove(int& xCoordinate, int& yCoordinate);
string makeMove(int pearls[3][2], int filled[Ycoordinate][Xcoordinate]);
void showInstructions();
int minDistance(int distance[3], int userX, int userY);
void levelThree();

//global variable for level 3
int pearls[3][2];
char board[Xcoordinate][Ycoordinate];
int randomNumber[3][2];
int pearlArray[Ycoordinate][Xcoordinate] = { 1 };
int filled[Ycoordinate][Xcoordinate] = { 0 };

int main()
{
	levelOne();
	cout << endl;
	levelTwo();
	cout << endl;
	cout << endl;
	levelThree();

	return 0;
}

void levelOne()
{
	srand((int)time(NULL));   //seeding

	char unscramble[NBSIZE];
	char randomScrambled[SIZE];
	char randomUnscrambled[SIZE];
	char userAnswer[SIZE];

	filling_array(unscramble);

	generate_random_character(unscramble, randomScrambled, randomUnscrambled);  //calling generate random char function

	// Asking for user input
	userInput(userAnswer, SIZE);
	bool matchStatus = checkAnswer(userAnswer, SIZE, randomUnscrambled);
	print(matchStatus);
}

// filling the array with character A-Z
void filling_array(char unscramble[NBSIZE])
{
	for (int i = 0; i < NBSIZE; i++)
		unscramble[i] = char('A' + i);
}

//generating random character from th unscrambled array
void generate_random_character(char unscramble[], char randomScrambled[], char randomUnscrambled[])
{
	cout << "Guard: Hello, Here is your magic word. Could you unscramble it? ";
	int randomNumber;
	for (int i = 0; i < SIZE; i++)
	{
		randomNumber = rand() % 26;
		randomScrambled[i] = unscramble[randomNumber];  // random number goes to the location of unscrambled
		randomUnscrambled[i] = unscramble[25 - randomNumber];  //random uncrambled equals the value of random number from Z-A
		cout << randomScrambled[i];
	}
	cout << endl;
}

//taking user answer 
void userInput(char userAnswer[], int SIZE) {
	cout << "Player: ";

	for (int i = 0; i < SIZE; ++i) {
		cin >> userAnswer[i];
		userAnswer[i] = toupper(char(userAnswer[i]));    // taking user answer to upper case
	}
}
bool checkAnswer(char userAnswer[], int SIZE, char randomUnscrambled[])
{
	// checking if the user's answer matches the scrambled letter
	bool matches = true;
	if (sizeof(userAnswer) != sizeof(randomUnscrambled))  //if size doesnot matches it is not true
		return false;
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (randomUnscrambled[i] != userAnswer[i])  // checking if userAnswer is equal to scramble value or not
			{
				matches = false;
				return matches;
			}
		}
		return matches;
	}
}

//printing result based on match status
void print(bool matchStatus)
{
	if (matchStatus)
		cout << "Guard:Congratulations. You may traverse the bridge in peace." << endl;
	else
		cout << "Guard:Wrong answer. I will enjoy watching my lovely piranhas eat you." << endl;
}

void levelTwo()
{
	// Seeding the random number generator with the current time
	srand(static_cast<unsigned int>(time(0)));

	// Declareing and initializeiling the password array
	int password[PASSWORD_SIZE];
	fillArray(password);

	// Displaying the color code for feedback to the user
	cout << "Orange\tOne digit is correct but in the wrong position." << endl;
	cout << "Green\tOne digit is correct and is in the right position." << endl;
	cout << "Red\tNo digit is correct." << endl;
	cout << endl;

	// Displaying the correct password (for testing purposes)
	displayPassword(password);
	cout << "You have 10 guesses to get it." << endl;

	// Looping for the number of guesses allowed
	for (int g = 0; g < GUESSES; g++)
	{
		int userGuess;
		cout << "Guess #" << g + 1 << ": ";
		cin >> userGuess;

		// Getting feedback on the user's guess
		string result = cardColor(password, userGuess);
		cout << result << endl;

		// Checking if the user has guessed the correct password
		if (result.find("Green Green Green") != string::npos)
		{
			cout << "Congratulations! You've cracked the password and entered GameLand!" << endl;
			cout << "You won a chest full of gold and you may pass to the next game." << endl;
			cout << "Be prepared, you have a princess to save. Have a nice play!" << endl;
			// Exiting the loop if the correct password is guessed
			break;
		}
	}

	// Displaying the correct password if the user couldn't guess it
	displayPassword(password);

}

// Function to fill the password array with unique digits
void fillArray(int password[PASSWORD_SIZE])
{
	for (int i = 0; i < PASSWORD_SIZE;)
	{
		int randomNum = rand() % 9 + 1;
		// Checking if the random number is not already in the array
		if (find(password, password + i, randomNum) == (password + i))
		{
			password[i] = randomNum;
			++i;
		}
	}
}

// Function to provide feedback on the user's guess
string cardColor(int password[PASSWORD_SIZE], int userGuess)
{
	string card;
	int userDigits[PASSWORD_SIZE];

	// Extracting individual digits from the user's guess
	for (int i = PASSWORD_SIZE - 1; i >= 0; i--)
	{
		userDigits[i] = userGuess % 10;
		userGuess /= 10;
	}

	// Compareing each digit and provide feedback based on the color code
	for (int i = 0; i < PASSWORD_SIZE; i++)
	{
		if (userDigits[i] == password[i])
		{
			card += "Green ";
		}
		else if (find(password, password + PASSWORD_SIZE, userDigits[i]) != password + PASSWORD_SIZE)
		{
			card += "Orange ";
		}
		else
		{
			card += "Red ";
		}
	}

	return card;
}

// Function to display the correct password
void displayPassword(int password[PASSWORD_SIZE])
{
	cout << "The correct password was: ";
	for (int i = 0; i < PASSWORD_SIZE; i++)
	{
		cout << password[i];
	}
	cout << endl;
}

void levelThree()
{
	// Seed the random number generator with the current time
	srand((time(NULL)));

	int userInput;
	cout << "Guard: Welcome the dark lake. Would you like to view the instructions? (type 1 for yes / 2 for no)." << endl;
	cin >> userInput;

	if (userInput == 1)
	{
		showInstructions();
		cin >> userInput;
		if (userInput == 2)
		{
			drawBoard();
		}
	}
	else if (userInput == 2)
	{
			drawBoard();
	}
	getRandomPearls(pearls);

	int psDevice = 16;
	int nbPearls = 3;
	cout << "You have " << psDevice << " PS devices left." << endl;
	cout << nbPearls << " pearls remaining." << endl;

	do
	{
		makeMove(pearls, filled);
		psDevice--;
		cout << "You have " << psDevice << " PS devices left." << endl;
	} while (psDevice != 0);
}

// Display game instructions
void showInstructions()
{
	cout << "There are 3 pearls to collect. You have 16 pearl sensors (PS devices) to find them." << endl;
	cout << "If you can find the 3 rare pearls and give them to the mighty dragon, you can save the princess." << endl;
	cout << "If not, your lovely princess will be imprisoned forever." << endl;
	cout << endl;
	cout << "\n (Type 2 for Game View: ";

}

// Generate random coordinates for the pearls
void getRandomPearls(int pearls[3][2])
{
	cout << "Random Pearls: ";
	for (int i = 0; i < 3; i++)
	{
		pearls[i][0] = rand() % 60;
		int x1 = pearls[i][0];	// just for ease
		pearls[i][1] = rand() % 15;
		int y1 = pearls[i][1];	// just for ease
		cout << "(" << x1 << "," << y1 << ")";
	}
	cout << endl;
}

// Draw the initial game board
void drawBoard()
{
	int randNum;

	cout << "          1         2         3         4         5         " << endl;
	cout << setw(3);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 10; j++)
			cout << j;

	cout << endl;
	for (int i = 0; i < Ycoordinate; i++)
	{
		cout << setw(2) << i;
		for (int j = 0; j < Xcoordinate; j++)
		{
			randNum = rand() % 2;
			if (randNum == 0)
			{
				board[j][i] = '`';
				cout << board[j][i];
			}
			else
			{
				board[j][i] = '~';
				cout << board[j][i];
			}
		}
		cout << setw(2) << i;
		cout << endl;
	}

	cout << setw(3);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 10; j++)
			cout << j;

	cout << endl;
	cout << "           1         2         3         4         5        " << endl;
	cout << endl;
}

// Take user input for coordinates
void enterPlayerMove(int& x, int& y)
{
	do
	{
		cout << " X - coordinate: ";
		cin >> x;
		if (x == -1)
			break;
		cout << " Y - coordinate: ";
		cin >> y;
	} while (!isValidMove(x, y));
}

// Check if the move is valid
bool isValidMove(int x, int y)
{
	return x >= 0 && x < Xcoordinate && y >= 0 && y < Ycoordinate;
}

// Calculate minimum distance to pearls
int minDistance(int distance[3], int userX, int userY)
{
	for (int i = 0; i < 3; i++)
	{
		distance[i] = sqrt(pow(userX - pearls[i][0], 2) + pow(userY - pearls[i][1], 2));
		cout << distance[i] << " ";
	}
	// Find the minimum distance
	int minimumDistance = distance[0];
	int minIndex = 0;

	for (int i = 1; i < 3; i++)
		if (distance[i] < minimumDistance)
			minimumDistance = distance[i];

	cout << " Min distance: " << minimumDistance << endl;

	return minimumDistance;
}

// Perform player's move and update the board
string makeMove(int pearls[3][2], int filled[Ycoordinate][Xcoordinate])
{
	int nbPearls = 3;
	int nbPSdevice = 16;
	int userX, userY;
	int distance[3];
	string game;

	enterPlayerMove(userX, userY);
	int minimumDistance = minDistance(distance, userX, userY);
	filled[userY][userX] = minimumDistance;
	pearlArray[userY][userX] = minimumDistance;
	getNewBoard(minimumDistance, userX, userY, filled);

	if (minimumDistance == 0)
		game = "You have found a pearls.";
	else
		game = "Pearl detected at the distance of " + to_string(minimumDistance) + " .";

	
	return game;

}
// Update the board based on the player's move
void getNewBoard(int minimumDistance, int& userX, int& userY, int pearlArray[Ycoordinate][Xcoordinate])
{
	int randNum;
	if (minimumDistance == 0)
	{
		pearlArray[userY][userX] = minimumDistance;
	}
	cout << "          1         2         3         4         5         " << endl;
	cout << setw(3);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 10; j++)
			cout << j;

	cout << endl;

	for (int i = 0; i < Ycoordinate; i++)
	{
		cout << setw(2) << i;
		for (int j = 0; j < Xcoordinate; j++)
		{
			randNum = rand() % 2;

			if (filled[i][j] != 0)
				cout << filled[i][j];  // Print distance as integer

			if (randNum == 0)
				cout << '`';
			else
				cout << '~';
		}
		cout << setw(2) << i << endl;
	}

	cout << setw(3);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 10; j++)
			cout << j;

	cout << endl;
	cout << "           1         2         3         4         5        " << endl;
	cout << endl;
}






