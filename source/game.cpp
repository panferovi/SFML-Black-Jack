#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"


//--------------------------------------------------------------

BlackJack::BlackJack(int stat)
{
	size = 52;

	int card_val = 0;

	for(int i = 0; i < 13; i++)
	{
		if(i < 8) 		 card_val = i + 2;
		else if(i < 12)	 card_val = 10;
		else if(i == 12) card_val = 11;

		diamond[i].card = card_val;		diamond[i].status = stat;
		spade  [i].card = card_val;		spade  [i].status = stat;
		heart  [i].card = card_val;		heart  [i].status = stat;
		club   [i].card = card_val;		club   [i].status = stat;
	}
}

//--------------------------------------------------------------

BlackJack::BlackJack()
{
	int card_val = 0;

	for(int i = 0; i < 13; i++)
	{
		if(i < 8) 		 card_val = i + 2;
		else if(i < 12)	 card_val = 10;
		else if(i == 12) card_val = 11;

		diamond[i].card = card_val;
		spade  [i].card = card_val;
		heart  [i].card = card_val;
		club   [i].card = card_val;
	}
}

//--------------------------------------------------------------

void BlackJack::Game(BlackJack* player, int num_players, int* winners)
{
	for(int i = 0; i < num_players; i++)
		Strategy(player + i, i + 1);

	int max_res = 0;

	for(int i = 0; i < num_players; i++)
	{
		if(max_res < player[i].sum && player[i].sum <= 21) 
			max_res = player[i].sum;
	}

	for(int i = 0; i < num_players; i++)
	{
		if(max_res == player[i].sum) winners[i] = 1;
	}	

	winners[8] = max_res;
}

//--------------------------------------------------------------

void BlackJack::Strategy(BlackJack* player, int player_number)									// стратегия игрока
{
	int action = 0;

	while (size < 52)
	{
		action = rand() % 8 + 1;

		if(player->sum < 12) 
			NewCard(player, player_number);
		else if(player->sum < 15 && action <= 4)					// шанс взятия карты игроком 0.5   (action <= 4)
			NewCard(player, player_number);
		else if(player->sum < 18 && action <= 2)					// шанс взятия карты игроком 0.25  (action <= 2)
			NewCard(player, player_number);
		else if(player->sum < 21 && action == 1)					// шанс взятия карты игроком 0.125 (action == 1)
			NewCard(player, player_number);
		else break;
	}
}

//--------------------------------------------------------------

void BlackJack::NewCard (BlackJack* player, int player_number)
{
	if(size == 0)
	{
		printf("Deck is out of card\n");
		return;
	}

	Clock clock;
	while(clock.getElapsedTime().asSeconds() < 1);

	int	color = 0, num_card = 0;

	while (true)
	{
		color = rand() % 4 + 1;
		num_card  = rand() % 13;

		if(color == 1 && diamond[num_card].status)
		{
			diamond[num_card].new_card(&(player->diamond[num_card]), num_card, "diamonds");
			player->sum += player->diamond[num_card].card;

			if(player_number > 4) 
				player->diamond[num_card].graphic_card.sprite.rotate(90);

			break;
		}
		if(color == 2 && spade[num_card].status)
		{
			spade[num_card].new_card(&(player->spade[num_card]), num_card, "spades");
			player->sum += player->spade[num_card].card;

			if(player_number > 4) 
				player->spade[num_card].graphic_card.sprite.rotate(90);

			break;
		}
		if(color == 3 && heart[num_card].status)
		{
			heart[num_card].new_card(&(player->heart[num_card]), num_card, "hearts");
			player->sum += player->heart[num_card].card;

			if(player_number > 4)
				player->heart[num_card].graphic_card.sprite.rotate(90);
			
			break;
		}
		if(color == 4 && club[num_card].status)
		{
			club[num_card].new_card(&(player->club[num_card]), num_card, "clubs");
			player->sum += player->club[num_card].card;

			if(player_number > 4) 
				player->club[num_card].graphic_card.sprite.rotate(90);

			break;
		}
	}

	(player->size)++;
	size--;
}

//--------------------------------------------------------------

void BlackJack::Print()
{
	printf("\tdiamond\t spade\theart\tclub\n");

	for(int i = 0; i < 13; i++)
	{
		printf("card[%d] ", i);

		if(diamond[i].status) 	printf("%d", diamond[i].card);
								printf("\t ");
		if(spade  [i].status) 	printf("%d", spade[i].card);
								printf("\t");
		if(heart  [i].status) 	printf("%d", heart[i].card);
								printf("\t");
		if(club   [i].status)	printf("%d", club[i].card);
								printf("\n");
	}
}

//--------------------------------------------------------------

void CardColor::new_card(CardColor* color, int filename, const char* card_color)
{
	status = 0;
	color->status = 1;

	char imagename[256] = "";

	sprintf(imagename, "%s/%d.png", card_color, filename);

	color->graphic_card.Create_Sprite(imagename);
}

//--------------------------------------------------------------

int BlackJack::GetSize()
{
	return size;
}

//--------------------------------------------------------------

CardColor* BlackJack::GetColor(int color)
{
	switch (color)
	{
	case (Diamond):	return diamond;
	case (Spade):	return spade;
	case (Heart):	return heart;
	case (Club):	return club;

	default:
		printf("Wrong color\n");
		break;
	}

	return nullptr;
}

//--------------------------------------------------------------