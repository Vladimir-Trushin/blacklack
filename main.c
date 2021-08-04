#include <stdio.h>
#include <stdlib.h>
#include "list_card.h"
#include "game.h"

int player_score;
int dealer_score;
int bet;

Node *deck;
Node *player_hand;
Node *dealer_hand;
char choose;    // Take card or open up
char exit_game; // Continue the game (Y)es or (N)o

int main(void)
{
    deck = list_init_deck();
    player_hand = NULL;
    dealer_hand = NULL;
    choose = 0;
    exit_game = 0;

    player_score = 1000;
    dealer_score = 1000;

    while (1)
    {
        game_start();

        if (list_value_cards(player_hand) == 21) // blackjack
        {
            puts("\n\n----------End round----------\n");
            game_show_cards();
            puts("");
            printf("!!!-BlackJack-!!!\n");
            printf("You win the round!!!\n");

            if ((bet * 1.5) <= dealer_score) // Take 150% from bet
            {
                player_score += (bet * 1.5);
                dealer_score -= (bet * 1.5);
            }
            else
            {
                player_score += dealer_score; // if dealer don't have enough mony
                dealer_score = 0;
            }

            list_return_deck(&deck, &player_hand);
            list_return_deck(&deck, &dealer_hand);
        }
        else
        {
            game_show_cards_dealer_one();
            game_take_card();
            game_dealer_take_cards();
        }

        if (player_score < 10) // dealer win
        {
            puts("\n<----------END---------->");
            printf("Your score  : %d\n", player_score);
            printf("Dealer score: %d\n", dealer_score);
            puts("\n!!!-Dealer win the game-!!!\n");
            list_free(&player_hand);
            list_free(&dealer_hand);
            list_free(&deck);
            exit(0);
        }

        if (dealer_score < 10) // player win
        {
            puts("\n<----------END---------->");
            printf("Your score  : %d\n", player_score);
            printf("Dealer score: %d\n", dealer_score);
            puts("\n!!!-You win the game-!!!\n");
            list_free(&player_hand);
            list_free(&dealer_hand);
            list_free(&deck);
            exit(0);
        }

        while (1) // exit game on the end of round
        {
            while (getchar() != '\n') // clean the buffer
                ;

            printf("\nYou want to continue the game (Y)es or (N)o: ");
            exit_game = getchar();
            if ((exit_game == 'y') || (exit_game == 'Y') || (exit_game == 'n') || (exit_game == 'N'))
                break;
        }

        if (exit_game == 'n' || exit_game == 'N')
        {
            puts("\n<----------END---------->");
            printf("Your score  : %d\n", player_score);
            printf("Dealer score: %d\n", dealer_score);
            list_free(&player_hand);
            list_free(&dealer_hand);
            list_free(&deck);
            exit(0);
        }
    }

    return 0;
}