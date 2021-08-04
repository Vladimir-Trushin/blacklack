#include <stdio.h>
#include <stdlib.h>
#include "list_card.h"
#include "game.h"

extern int player_score;
extern int dealer_score;
extern int bet;

extern Node *deck;
extern Node *player_hand;
extern Node *dealer_hand;
extern char choose;

////-------------------------------------------------
// Start a round, ask a player to set a bet and takes
// two cards for player and dealer
void game_start(void)
{
    printf("\n----------Start round----------\n");

    printf("Your score  : %d\n", player_score);
    printf("Dealer score: %d\n", dealer_score);

    while (1)
    {
        printf("Choose your bet: minimum 10, multiple 10 and less from player and dealer score: ");
        int check = scanf("%d", &bet);
        if ((check == 1) && (bet % 10 == 0) && (bet <= player_score) && (bet <= dealer_score) && (bet >= 10))
            break;

        while (getchar() != '\n')
            ;
    }

    puts("");

    list_set_hand(&player_hand, list_pop_deck(&deck)); //
    list_set_hand(&player_hand, list_pop_deck(&deck)); // the player takes two cards

    list_set_hand(&dealer_hand, list_pop_deck(&deck)); //
    list_set_hand(&dealer_hand, list_pop_deck(&deck)); // the dealer takes two cards
}

////-------------------------------------------------
// Player show all cards and dealer show one card
void game_show_cards_dealer_one(void)
{
    printf("Dealer cards: \n");
    list_print_card(dealer_hand);
    printf("Value: %d\n", dealer_hand->value);

    puts("\n");

    printf("Player cards: \n");
    list_print_all_cards(player_hand);
    printf("Value: %d\n", list_value_cards(player_hand));
}

////-------------------------------------------------
// Show player's and dealer's cards
void game_show_cards(void)
{
    printf("Dealer cards: \n");
    list_print_all_cards(dealer_hand);
    printf("Value: %d\n", list_value_cards(dealer_hand));

    puts("\n");

    printf("Player cards: \n");
    list_print_all_cards(player_hand);
    printf("Value: %d\n", list_value_cards(player_hand));
}

////-------------------------------------------------
// Ask a player to take one card or open up cards
void game_take_card(void)
{
    while (1)
    {
        while (1)
        {
            while (getchar() != '\n') // clean the buffer
                ;

            printf("\n(T)ake a card or (O)pen up: ");
            choose = getchar();
            if ((choose == 't') || (choose == 'T') || (choose == 'o') || (choose == 'O'))
                break;
        }

        if ((choose == 't') || (choose == 'T'))
        {
            list_set_hand(&player_hand, list_pop_deck(&deck));
            puts("");
            game_show_cards_dealer_one();

            if (list_value_cards(player_hand) > 21) // overshoot
                break;
            
            if (list_value_cards(player_hand) == 21) // 21
                break;
        }
        else
            break;
    }
}

////-------------------------------------------------
// The dealer takes cards and checks who win
void game_dealer_take_cards(void)
{
    if (list_value_cards(player_hand) > 21) // overshoot for player
    {
        puts("\n\n----------End round----------\n");
        game_show_cards();
        puts("");
        printf("Dealer win the round!!!\n");
        player_score -= bet;
        dealer_score += bet;
        list_return_deck(&deck, &player_hand);
        list_return_deck(&deck, &dealer_hand);
    }
    else
    {
        while (1)
        {
            if (list_value_cards(dealer_hand) < list_value_cards(player_hand)) // the dealer takes a card
            {
                list_set_hand(&dealer_hand, list_pop_deck(&deck));
            }
            else if (list_value_cards(dealer_hand) > 21) // overshoot for dealer
            {
                puts("\n\n----------End round----------\n");
                game_show_cards();
                puts("");
                printf("You win the round!!!\n");
                player_score += bet;
                dealer_score -= bet;
                list_return_deck(&deck, &player_hand);
                list_return_deck(&deck, &dealer_hand);
                break;
            }
            else if (list_value_cards(dealer_hand) > list_value_cards(player_hand)) // dealer win
            {
                puts("\n\n----------End round----------\n");
                game_show_cards();
                puts("");
                printf("Dealer win the round!!!\n");
                player_score -= bet;
                dealer_score += bet;
                list_return_deck(&deck, &player_hand);
                list_return_deck(&deck, &dealer_hand);
                break;
            }
            else if (list_value_cards(dealer_hand) == list_value_cards(player_hand)) // draw
            {
                puts("\n\n----------End round----------\n");
                game_show_cards();
                puts("");
                printf("draw!!!\n");
                list_return_deck(&deck, &player_hand);
                list_return_deck(&deck, &dealer_hand);
                break;
            }
            else
            {
                // it's can't happen!
                printf("logeck error\n");
                list_free(&player_hand);
                list_free(&dealer_hand);
                list_free(&deck);
                exit(1);
            }
        }
    }
}
