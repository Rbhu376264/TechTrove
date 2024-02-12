/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA 2
******************************************************************************/
//Name:- Rbhu Gandhi 
//USC email id:- rbhugand@usc.edu
// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H', 'S', 'D', 'C'};
const char *type[13] =
    {"2", "3", "4", "5", "6", "7",
     "8", "9", "10", "J", "Q", "K", "A"};
const int value[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    /******** You complete ****************/
    for (int i = 0; i < NUM_CARDS; i++)
    {
        cards[i] = i;
    }
    for (int i = NUM_CARDS - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        swap(cards[i], cards[j]);
    }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
    /******** You complete ****************/

    if (id < 13)
    {
        cout << type[id] << '-' << suit[0] << ' ';
    }
    else if (id >= 13 && id < 26)
    {
        cout << type[id - 13] << '-' << suit[1] << ' ';
    }
    else if (id >= 26 && id < 39)
    {
        cout << type[id - 26] << '-' << suit[2] << ' ';
    }
    else if (id >= 39 && id < 52)
    {
        cout << type[id - 39] << '-' << suit[3] << ' ';
    }
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
    /******** You complete ****************/
    int x = id % 13;
    int y = -1;

    if (x == 0)
    {
        y = value[0];
    }
    else if (x == 1)
    {
        y = value[1];
    }
    else if (x == 2)
    {
        y = value[2];
    }
    else if (x == 3)
    {
        y = value[3];
    }
    else if (x == 4)
    {
        y = value[4];
    }
    else if (x == 5)
    {
        y = value[5];
    }
    else if (x == 6)
    {
        y = value[6];
    }
    else if (x == 7)
    {
        y = value[7];
    }
    else if (x == 8 || x == 9 || x == 10 || x == 11)
    {
        y = value[8];
    }
    else if (x == 12)
    {
        y = value[12];
    }

    return y;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    /******** You complete ****************/

    for (int i = 0; i < numCards; i++)
    {
        printCard(hand[i]);
    }
    cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    /******** You complete ****************/

    int sum = 0;

    for (int i = 0; i < numCards; i++)
    {
        if (sum <= 10 && cardValue(hand[i]) == 11)
        {
            sum += cardValue(hand[i]);
            // cout<<sum<<endl;
        }
        else if(sum>10 && (cardValue(hand[0]) == 11 || cardValue(hand[1]) == 11))
        {
          
           sum += cardValue(hand[i]);
            if(sum>21)
            {
              sum-=10;
            }
          
        }
        else if (sum > 10 && cardValue(hand[i]) == 11)
        {
            sum += 1;
            // cout<<sum<<endl;
        }
        else
        {
          sum += cardValue(hand[i]);
          // cout<<sum<<endl;
        }
    }

    return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char *argv[])
{
    //---------------------------------------
    // Do not change this code -- Begin
    //---------------------------------------
    if (argc < 2)
    {
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    srand(seed);

    int cards[52];
    int dhand[9];
    int phand[9];
    //---------------------------------------
    // Do not change this code -- End
    //---------------------------------------

    /******** You complete ****************/
    char input = 'y', input_1 = 's';
    int dcounter = 0;
    int pcounter = 0;

    shuffle(cards);
    while (input == 'y')
    {

        for (int i = 0; i < 4; i++)
        {
            if (i % 2 == 0)
            {

                phand[pcounter] = cards[i];
                pcounter++;
            }
            else
            {

                dhand[dcounter] = cards[i];
                dcounter++;
            }
        }

        cout << "Dealer: "<<"? ";
        printCard(dhand[1]);
        cout<< endl;
        cout << "Player: " ;
        printCard(phand[0]);
        printCard(phand[1]);
        cout<<endl;

        
        

        int pvalue = 4;
        

        while (input_1 == 's' || input_1 == 'h')
        {
            
            if (getBestScore(phand, pcounter) == 21)
            {
                
                if(getBestScore(dhand, dcounter) < 17)
                {
                  while (getBestScore(dhand, dcounter) < 17)
                  {
                      dhand[dcounter] = cards[pvalue];

                      dcounter++;

                      pvalue += 1;

                      
                  }

                }

                cout << "Dealer: ";
                printHand(dhand, dcounter);
                

                cout << "Win" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
            }
            
            cout << "Type 'h' to hit and 's' to stay:" << endl;
            cin >> input_1;

            if (input_1 == 'h')
            {
              
              
               phand[pcounter] = cards[pvalue];

                pcounter++;

                pvalue += 1;

                
                
              
              
            
              cout << "Player: ";
              printHand(phand, pcounter);
              
              if (getBestScore(phand, pcounter) > 21)
              {
                
                cout << "Player Busts" << endl;
                cout << "Lose" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
              }
              
            }

            if (input_1 == 's')
            {
              while (getBestScore(dhand, dcounter) < 17)
              {
                  dhand[dcounter] = cards[pvalue];

                  dcounter++;

                  pvalue += 1;

                  
              }

              

                cout << "Dealer: ";
                printHand(dhand, dcounter);
                

              
              if (getBestScore(dhand, dcounter) > 21)
              {
                
                cout << "Dealer Busts" << endl;
                cout << "Win" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
              }
              if (getBestScore(phand, pcounter) < getBestScore(dhand, dcounter))
              {
                cout << "Lose" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
              }

              if (getBestScore(phand, pcounter) > getBestScore(dhand, dcounter))
              { 
                cout << "Win" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
              }
              
            }
            

            if (getBestScore(phand, pcounter) > 21)
            {
                
                cout << "Player Busts" << endl;
                cout << "Lose" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
            }
            if (getBestScore(dhand, dcounter) > 21)
            {
                
                cout << "Dealer Busts" << endl;
                cout << "Win" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
            }
            if (getBestScore(phand, pcounter) == getBestScore(dhand, dcounter))
            {
                cout << "Tie" << ' ' << getBestScore(phand, pcounter) << ' ' << getBestScore(dhand, dcounter) << endl;
                break;
            }
          
        }
        pcounter = 0;
        dcounter = 0;
        pvalue = 0;
        shuffle(cards);
        cout<<endl;

        cout << "Play again? [y/n]" << endl;
        cin >> input;
    }

    return 0;
}
