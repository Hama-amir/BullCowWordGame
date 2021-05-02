// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
// #include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    Isograms = GetValidWords(Words);

    SetupGame();    
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcoming Players
    PrintLine(TEXT("Welcome to the Bull Cows Game!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = (HiddenWord.Len() * 2);
    HintsGiven = 0;
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); 
    // PrintLine(TEXT("The HiddenWord is: %s. \n"), *HiddenWord); // Debug Line
    PrintLine(TEXT("You Have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompt Player to Guesss
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("CONGRATULATIONS YOUSSEF!\nYOU ARE RIGHT!\n I wove yuyu"));
        EndGame();
        return;
    }

    // if hints are less 2 then provide user with hint and decrease life
    // if hints are ==2 and user asks for hint then stop user with prompt
    
    if (AskForHint(Guess, HiddenWord))
    {
        return;
    }
    

    if (Guess.Len() != HiddenWord.Len())  // check if not the right amount of characters
    {
        PrintLine(TEXT("The Hidden Word is %i characters long."), HiddenWord.Len());
        PrintLine(TEXT("Guess again!"));
        return;
    }    

    if (!IsIsogram(Guess)) // Check if Isogram
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }
    
        /* 
        if right amount of characters but wrong word, 
        Decrease life, 
        then print the following.
                                                    */

    --Lives; // Remove Life

    FBullCowCount Score = GetBullCows(Guess);

    if (Lives > 1) 
    {
        PrintLine(TEXT("Sorry, that is the wrong word, try again."));
        PrintLine(TEXT("You have %i lives left"), Lives);
        
        // Show Players bulls and cows
        PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
        return;
    } 

    if (Lives == 1)
    {
        PrintLine(TEXT("Sorry, that is the wrong word, try again."));
        PrintLine(TEXT("You have %i life left"), Lives);
        
        // Show Players bulls and cows
        PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
        return;
    }
    
    if (Lives == 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no more lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparision = Index + 1; Comparision < Word.Len(); Comparision++)
        {
            if (Word[Index] == Word[Comparision])
            {
                return false;
            }   
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        } 
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }   
    }
    return Count;
}

bool UBullCowCartridge::AskForHint(const FString& AskHint, const FString& RealWord)
{   
    int32 LetterNumber = HintsGiven;    // Depending on the HintNumber, that is the Letter you will give the player
    int32 NumberOfHints = 2;            // you can set this how you want, it is how many hints you want to allow!

    if (AskHint == "h")                 // if player types only the letter "h"
    {
        if (HintsGiven < NumberOfHints)
        {
            PrintLine(TEXT("You have asked for a Hint,\nThe %i letter is: %c"), LetterNumber + 1, RealWord[LetterNumber]); // add 1 so it doesnt show 0
            Lives = Lives - 2;          // asking for hints is a little pricey XD

            PrintLine(TEXT("You have lost 2 lives for that hint\nYou now have %i Lives"), Lives);
            HintsGiven++;
            return true;
        }

        if (HintsGiven == NumberOfHints)
        {
            PrintLine(TEXT("You already used your %i hints"), NumberOfHints);
            return true;
        }
    }
    return false;
}