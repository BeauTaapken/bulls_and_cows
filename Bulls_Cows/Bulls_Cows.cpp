// Bulls_Cows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintAnswer(FText Guess);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;//Instance of the FBullCowGame.cpp file

//The entry point for the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

}

//Introduce the game
void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.getHiddenWordLength() << " letter isogram I'm thinking off?\n";
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset();

	//Loop asking for guesses while the game is NOT won
	//And there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText guess = GetValidGuess();

		//Submit valid guess to the game
		FBullCowCount bullCowCount = BCGame.SubmitValidGuess(guess);
		
		std::cout << "Bulls = " << bullCowCount.bulls;
		std::cout << ". Cows = " << bullCowCount.cows << "\n\n";
	}

	PrintGameSummary();
}

//Loop until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus status = EGuessStatus::Invalid_Status;
	FText guess = "";
	do
	{
		//Get a guess from the player
		std::cout << "Try " << BCGame.GetCurrentTry() << std::endl << "Give me a guess: ";
		std::getline(std::cin, guess);

		status = BCGame.CheckGuessValidity(guess);
		switch (status)
		{
		case EGuessStatus::Incorrect_Length:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram(word with no double usage of letters)\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please only give answers in lower case\n";
			break;
		case EGuessStatus::OK:
			break;
		default:
			std::cout << "Unhandled status in GetValidGuess function\n";
			break;
		}
		std::cout << std::endl;
	}
	while (status != EGuessStatus::OK);
	return guess;
}

void PrintAnswer(FText Guess)
{
	//Print the guess back
	std::cout << "you're answer was: " << Guess << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText response = "";
	std::getline(std::cin, response);
	std::cout << std::endl;
	return (response[0] == 'y' || response[0] == 'Y');
}

void PrintGameSummary()
{
	if(BCGame.IsGameWon())
	{
		std::cout << "Congrats, you won the game in " << BCGame.GetCurrentTry() << " tries.\n";
	}
	else
	{
		std::cout << "Better luck next time.\n";
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
