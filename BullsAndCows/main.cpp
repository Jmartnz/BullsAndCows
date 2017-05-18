#include <iostream>
#include <string>
#include <stdlib.h>
#include "FBullCowGame.h"

// Make syntax Unreal-friendly
using FText = std::string;
using FString = std::string;
using int32 = int;

void PrintGameIntro();
void PlayGame();
void PrintEnterGuessMessage();
FText GetGuess();
void PrintInvalidLengthError();
void PrintInvalidCaseError();
void PrintInvalidIsogramError();
void PrintBullsAndCowsGraphics(FBullCowCount BullsAndCows);
void PrintWinMessage();
void PrintGameOverMessage();
bool AskToPlayAgain();
void ClearScreen();

FBullCowGame BCGame;

int main()
{
	// Constants
	const FString GAME_VERSION = "1.0";
	const FString GAME_AUTHOR = "Jmartnz";
	const FString CONSOLE_TITLE = "title Bulls and Cows Game v1.0 - Jmartnz";
	const FString CONSOLE_COLOR = "color 0a";
	constexpr int32 MAX_GUESS_TRIES = 10;
	
	// Variables
	BCGame = FBullCowGame();
	bool bPlayAgain = false;

	// Console configuration
	system(CONSOLE_TITLE.data());
	system(CONSOLE_COLOR.data());

	// Game start
	do {
		PrintGameIntro();
		PlayGame();
		if (BCGame.IsGameWon()) {
			PrintWinMessage();
		} else { 
			PrintGameOverMessage();
		}
		bPlayAgain = AskToPlayAgain();
		if (bPlayAgain) { 
			BCGame.Reset();
		}
		ClearScreen();
	} while (bPlayAgain);

	// Game end
	return 0;
}

void PrintGameIntro()
{
	int32 WordLength = BCGame.GetWordToGuess().length();

	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;
	std::cout << "To win the game, you will have to guess a hidden isogram with X number of letters." << std::endl;
	std::cout << "An isogram is a word with no repeating letters. For example: coin, heat or shine." << std::endl;
	std::cout << "If the word you enter has some letter in common with the hidden isogram, you will get a cow." << std::endl;
	std::cout << "Furthermore, if this letter is on the same position, you will get a bull!" << std::endl;
	std::cout << std::endl;
	std::cout << "The game ends when you find the hidden isogram or you run out of tries. So, think carefully your next move!";

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "    ((...))             L...L" << std::endl;
	std::cout << "    ( O O )            < o o >" << std::endl;
	std::cout << "     \\   /              \\   /" << std::endl;
	std::cout << "     (`_`)               ^_^" << std::endl;
	std::cout << std::endl;
	std::cout << "    Bulls: 0           Cows: 0";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Can you guess the " << WordLength << " letter isogram I'm thinking of in less than " 
		<< BCGame.GetMaxGuessTries() << " tries?" << std::endl;
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	EGuessValidity GuessValidity;
	bool bGameOver = false;
	int32 MaxGuessTries = BCGame.GetMaxGuessTries();
	
	for (int32 i = 0; i < MaxGuessTries && !bGameOver; i++) {

		FText Guess = "";

		do {
			PrintEnterGuessMessage();
			Guess = GetGuess();
			GuessValidity = BCGame.getGuessValidity(Guess);
			switch (GuessValidity) {
				case EGuessValidity::INVALID_LENGTH:
					PrintInvalidLengthError();
					break;
				case EGuessValidity::INVALID_CASE:
					PrintInvalidCaseError();
					break;
				case EGuessValidity::INVALID_ISOGRAM:
					PrintInvalidIsogramError();
					break;
				default:
					// TODO Add some default behavior for valid guesses
					break;
			}
		} while (GuessValidity != EGuessValidity::OK);

		BCGame.SubmitGuess(Guess);
		bGameOver = BCGame.IsGameWon();

		if (!bGameOver) {
			PrintBullsAndCowsGraphics(BCGame.GetFBullCowCount());
			BCGame.SetFBullCowCount(0, 0);
		}
	}

	return;
}

void PrintEnterGuessMessage()
{
	std::cout << "Try " << BCGame.GetCurrentTry() << " of "
		<< BCGame.GetMaxGuessTries() << ". Enter your guess: ";
	return;
}

std::string GetGuess()
{
	FText Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

void PrintInvalidLengthError()
{
	std::cout << "You've entered a word with invalid length! Please, choose a word with " << BCGame.GetWordToGuess().length() << " letters.";
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

void PrintInvalidCaseError()
{
	std::cout << "You've entered a word with some uppercase letter(s)! Please, use lowercase letters only.";
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

void PrintInvalidIsogramError()
{
	std::cout << "You've entered an invalid isogram! Please, choose a word with no repeating letters.";
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

void PrintBullsAndCowsGraphics(FBullCowCount BullsAndCows)
{
	std::cout << std::endl;
	std::cout << "    ((...))             L...L" << std::endl;
	std::cout << "    ( O O )            < o o >" << std::endl;
	std::cout << "     \\   /              \\   /" << std::endl;
	std::cout << "     (`_`)               ^_^" << std::endl;
	std::cout << std::endl;
	std::cout << "    Bulls: " << BullsAndCows.Bulls << "           Cows: " << BullsAndCows.Cows;
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

void PrintWinMessage()
{
	std::cout << std::endl;
	std::cout << "Congratulations! You have found the word!" << std::endl;
	return;
}

void PrintGameOverMessage()
{
	std::cout << std::endl;
	std::cout << "Aww... You've ran out of tries! It is GAME OVER." << std::endl;
	return;
}

bool AskToPlayAgain()
{
	std::cout << std::endl;
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void ClearScreen()
{
	system("cls");
	return;
}