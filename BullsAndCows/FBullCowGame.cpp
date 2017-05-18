#include "FBullCowGame.h"

// Constructors
FBullCowGame::FBullCowGame()
{
	this->Reset();	
}

// Getters
FString FBullCowGame::GetWordToGuess() const { return this->WordToGuess; }
const FString* FBullCowGame::GetIsogramDictionary() const { return this->IsogramDictionary; }
int32 FBullCowGame::GetMaxGuessTries() const { 
	int32 GuessLength = this->WordToGuess.length();
	if (GuessLength <= 3) {
		return 5;
	}
	else if (GuessLength == 4 || GuessLength == 5) {
		return 10;
	}
	else {
		return (GuessLength * 2);
	}
}
int32 FBullCowGame::GetCurrentTry() const { return this->CurrentTry; }
FBullCowCount FBullCowGame::GetFBullCowCount() const { return this->BullsAndCows; }

// Setters
void FBullCowGame::SetWordToGuess(FString WordToGuess) { this->WordToGuess = WordToGuess; }
void FBullCowGame::SetCurrentTry(int32 CurrentTry) { this->CurrentTry = CurrentTry; }
void FBullCowGame::SetFBullCowCount(int32 Bulls, int32 Cows) { this->BullsAndCows = { Bulls, Cows }; }

// Game logic
void FBullCowGame::Reset()
{
	srand(time(0));
	this->CurrentTry = 1;
	this->BullsAndCows = { 0, 0 };
	this->WordToGuess = GetRandomIsogramFromDictionary();
}

FString FBullCowGame::GetRandomIsogramFromDictionary() const
{
	int32 MaxRandomNumer = this->IsogramDictionary->length();
	int32 RandomNumber = (rand() % MaxRandomNumer) + 1;
	return this->IsogramDictionary[RandomNumber];
}

void FBullCowGame::SubmitGuess(FString Guess)
{
	this->CurrentTry++;

	int32 GuessLength = Guess.length();
	for (int32 i = 0; i < GuessLength; i++) {
		if (Guess[i] == WordToGuess[i]) {
			this->BullsAndCows.Bulls++;
		} else {
			for (int32 j = 0; j < GuessLength; j++) {
				if (Guess[i] == WordToGuess[j]) {
					this->BullsAndCows.Cows++;
				}
			}
		}
	}

	return;
}

EGuessValidity FBullCowGame::getGuessValidity(FString Guess) const
{
	if (!HasValidLength(Guess)) {
		return EGuessValidity::INVALID_LENGTH;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessValidity::INVALID_CASE;
	}
	else if (!IsValidIsogram(Guess)) {
		return EGuessValidity::INVALID_ISOGRAM;
	}

	return EGuessValidity::OK;
}

bool FBullCowGame::HasValidLength(FString Guess) const
{
	return (this->WordToGuess.length() == Guess.length());
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		if(!islower(Letter))
			return false;
	}
	return true;
}

bool FBullCowGame::IsValidIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }
	TMap<char, bool> Map;
	for (auto Letter : Guess) {
		if (Map[Letter]) {
			return false;
		}
		else {
			Map[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsGameWon() const
{
	return (this->BullsAndCows.Bulls >= this->WordToGuess.length());
}