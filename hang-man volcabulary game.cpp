#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string.h>
#include <ctype.h>

using namespace std;

const int SIZE = 10;

void ran(char word[SIZE][1000], char out[SIZE][1000]);
void print_game(char blanks[], int mistakes, char used[], int times);
char get_guessed(char used[]);
int game_over(int times, int mistakes, char blank[], char word[]);
void set_word(char target[], char word_bank[][50]);
void hangman(char word_bank[SIZE][1000]);

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	srand(time(NULL));
	char word[SIZE][1000] = { NULL };
	for (int i = 0; i < SIZE; i++)
	{
		fin >> word[i];
	}
	char out[SIZE][1000] = { NULL };
	
	ran(word, out);

	for (int i = 0; i < SIZE; i++)
	{
		if (out[i][0] != NULL)
		{
			fout << out[i] << endl;
			hangman(out);
		}
	}
	return 0;
}

void ran(char word[SIZE][1000], char out[SIZE][1000])
{
	for (int i = 0; i < SIZE; i++)
	{
		int random = rand() % (SIZE - i);
		int x = 0;
		while (random >= 0)
		{
			if (out[x][0] == NULL)
			{
				random--;
				x++;
			}
			else
			{
				x++;
			}
		}
		for (int j = 0; j < 1000; j++)
		{
			out[x - 1][j] = word[i][j];
		}

	}
}

void set_word(char target[], char word_bank[][1000])
{
	srand(time(NULL));
	int w = rand() % SIZE + 1;
	for (int i = 0; i < 50; i++)
	{
		target[i] = word_bank[w][i];
	}
}

void print_game(char blanks[], int mistakes, char used[], int times)
{
	for (int i = 0; i < strlen(blanks); i++)
	{
		cout << blanks[i] << " ";
	}
	cout << "\n";
	cout << "You have " << times - mistakes << " times left." << "\n";
	cout << "You have used:" << used << "\n";
}

char get_guessed(char used[])
{
	cout << "Guess a letter:";
	char guess;
	cin >> guess;
	guess = tolower(guess);
	if (guess >= 97 && guess <= 122)
	{
		for (int i = 0; i < 27; i++)
		{
			if (guess == used[i])
			{
				cout << "You have guessed it.\n";
				return get_guessed(used);
			}
		}
		return guess;
	}
	else
	{
		cout << "You must guess a letter.\n";
		return get_guessed(used);
	}
}

int game_over(int times, int mistakes, char blank[], char word[])
{
	if (times == mistakes)
	{
		return 1;
	}
	if (strcmp(blank, word) == 0)
	{
		return 2;
	}
	return 0;
}

void hangman(char word_bank[SIZE][1000])
{
	char target[50];
	char blanks[50];
	char used[27];
	int endcheck = 0;
	char guess = 'a';

	int times = 10;  //max mistakes
	bool again = 0;
	while (again == 0)
	{
		int mistakes = 0;
		set_word(target, word_bank);
		for (int i = 0; i < 27; i++)
		{
			used[i] = '\0';
		}
		for (int i = 0; i < strlen(target); i++)
		{
			blanks[i] = '_';
		}
		blanks[strlen(target)] = '\0';
		while (game_over(times, mistakes, blanks, target) == 0)
		{
			endcheck = 0;
			print_game(blanks, mistakes, used, times);
			guess = get_guessed(used);
			for (int i = 0; i < strlen(target); i++)
			{
				if (guess == target[i])
				{
					blanks[i] = guess;
					for (int i = 0; i < 27; i++)
					{
						if (used[i] == '\0')
						{
							used[i] = guess;
							endcheck++;
							break;
						}
					}
				}
			}
			if (endcheck == 0)
			{
				for (int i = 0; i < 27; i++)
				{
					if (used[i] == '\0')
					{
						used[i] = guess;
						break;
					}
				}
				mistakes++;
				cout << "Not include in that word.\n";
			}
		}

		if (game_over(times, mistakes, blanks, target) == 2)
			cout << "You win!" << "\n";
		else
		{
			cout << "You lose.\n";
			cout << "The word is " << target << "\n";
		}
		cout << "Do you want to play again(y for yes,n for no)?";
		char answer;
		cin >> answer;
		if (answer == 'n')
			again = 1;
	}
	system("pause");
}