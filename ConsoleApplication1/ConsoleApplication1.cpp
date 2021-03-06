// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//
#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include "FBullCowGame.h"             
//using namespace std;

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game
void PrintGameSummary();

int32 main()
{
	bool bPlayAgain = false;
	do{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//for (int32 count = 1; count <= MaxTries; count++) {
	while( !BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls : " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows : " << BullCowCount.Cows << std::endl;
	}


	//TODO summarize the game
	PrintGameSummary(); 
	return;
}

void PrintIntro() {
	
	std::cout << "\nWelcome to Bulls and Cows, a word fun game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I`am thinking of ? \n";
	std::cout << std::endl;
	return;
}

FText GetValidGuess() {
	FString Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << " Enter your Guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_isogram:
			std::cout << "Please enter word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n";
			break;
		default:
			//return Guess;
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with a same hidden word(y/n)?";
	FString Responce = "";
	std::getline(std::cin, Responce);
	return (Responce[0] == 'y') || (Responce[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.isGameWon()) {
		std::cout << "WELL DONE YOU WIN \n";
	}
	else {
		std::cout << "Better luck next time \n";
	}
}
