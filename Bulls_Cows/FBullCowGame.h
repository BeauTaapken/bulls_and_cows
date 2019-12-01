/* The game logic (no view code or direct user interaction)
	The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//To make the syntax unreal value
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Incorrect_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 getHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	//See constructor for initialisation
	int32 myCurrentTry;
	FString myHiddenWord;
	bool bWonGame;
	
	bool isIsogram(FString) const;
	bool isLower(FString) const;
};