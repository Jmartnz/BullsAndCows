#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

#pragma once
#define TMap std::map

// Make syntax Unreal-friendly
using FText = std::string;
using FString = std::string;
using int32 = int;

struct FBullCowCount { int32 Bulls; int32 Cows; };
enum class EGuessValidity { OK, INVALID_LENGTH, INVALID_CASE, INVALID_ISOGRAM };

class FBullCowGame {
private:
	FString WordToGuess;
	FString IsogramDictionary[60] = { 
		"coin", "money", "flower", "lion", "sand", "work", "milk"
		"fish", "meal", "dice", "sprint", "bread", "time", "maths",
		"sport", "mouse", "house", "pencil", "bike", "light", "game",
		"paint", "fight", "cake", "swim", "adult", "party", "smoke", "water",
		"earth", "land", "fire", "dark", "soul", "weapon", "bird", "hand", "mark",
		"code", "jump", "easy", "silk", "lemon", "orange", "blue", "white", "black",
		"pink", "vegan", "wine", "crime", "night", "friend", "basket", "brown", "luck",
		"rock", "stock", "snail", "tiger"
	};
	int32 CurrentTry;
	FBullCowCount BullsAndCows;
public:
	// Constructors
	FBullCowGame();
	// Getters & Setters
	FString GetWordToGuess() const;
	void SetWordToGuess(FString WordToGuess);
	const FString* GetIsogramDictionary() const;
	int32 GetMaxGuessTries() const;
	int32 GetCurrentTry() const;
	void SetCurrentTry(int32 CurrentTry);
	FBullCowCount GetFBullCowCount() const;
	void SetFBullCowCount(int32 Bulls, int32 Cows);
	// Game logic
	void Reset();
	FString GetRandomIsogramFromDictionary() const;
	void SubmitGuess(FString Guess);
	EGuessValidity getGuessValidity(FString Guess) const;
	bool HasValidLength(FString Guess) const;
	bool IsLowercase(FString Guess) const;
	bool IsValidIsogram(FString Isogram) const;
	bool IsGameWon() const;
};