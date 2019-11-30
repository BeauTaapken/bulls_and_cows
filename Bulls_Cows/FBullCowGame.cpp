#include "pch.h"
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return myMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return myCurrentTry; }

int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bWonGame; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	
	myMaxTries = MAX_TRIES;
	myHiddenWord = HIDDEN_WORD;
	myCurrentTry = 1;
	bWonGame = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	//If guess isn't an isogram, return error
	if(false)
	{
		return EGuessStatus::Not_Isogram;
	}
	//If guess isn't all lowercase
	else if(false)
	{
		return EGuessStatus::Not_Lowercase;
	}
	//If the guess length is wrong
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
			//If they match then
			if(myHiddenWord[hwChar] == guess[gwChar])
			{
				//Increment bulls if they are in the same place
				if(gwChar == hwChar)
				{
					bullCowCount.bulls++;
				}
				//increment cows if not
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
