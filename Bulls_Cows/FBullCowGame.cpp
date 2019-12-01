#include "pch.h"
#pragma once
#include "FBullCowGame.h"
#include <map>
#include <cctype>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } //Default constructor

int32 FBullCowGame::GetCurrentTry() const { return myCurrentTry; }

int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bWonGame; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[getHiddenWordLength()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; //This MUST be an isogram

	myHiddenWord = HIDDEN_WORD;
	myCurrentTry = 1;
	bWonGame = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if(!isIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!isLower(guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if(guess.length() != getHiddenWordLength())
	{
		return EGuessStatus::Incorrect_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//Receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	myCurrentTry++;
	FBullCowCount bullCowCount;
	int32 WordLength = myHiddenWord.length();//Assuming same length as guess
	
	//Loop through all letters in the hidden word
	for(int32 gwChar = 0; gwChar < WordLength; gwChar++)
	{
		//Compare letters against guess
		for(int32 hwChar = 0; hwChar < WordLength; hwChar++)
		{
			if(myHiddenWord[hwChar] == guess[gwChar])
			{
				if(gwChar == hwChar)
				{
					bullCowCount.bulls++;
				}
				else
				{
					bullCowCount.cows++;
				}
			}
		}
	}

	if(bullCowCount.bulls == WordLength)
	{
		bWonGame = true;
	}
	else
	{
		bWonGame = false;
	}
	
	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const
{
	//Treat 0 and 1 letter words as isograms
	if(word.length() <= 1) { return true; }

	//Setup map
	TMap<char, bool> letterSeen;

	//For all letters of the word
	for(auto letter : word)
	{
		letter = tolower(letter);
		if(letterSeen[letter])
		{
			return false;
		}
		letterSeen[letter] = true;
	}
	return true;
}

bool FBullCowGame::isLower(FString word) const
{
	//For all letter of the word
	for(auto letter : word)
	{
		if(letter != tolower(letter))
		{
			return false;
		}
	}
	
	return true;
}
