#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string.h"
#include "../include/game.h"

char game_end[128] = "";

int ScanPlayer(char* inputdata);
void WinnersStr(int* winners, int num_players);

//--------------------------------------------------------------

int main (int argc, char* argv[])
{
	int num_players = ScanPlayer(argv[1]);

	BlackJack deck(1);

	BlackJack* player = new BlackJack[num_players];

 	RenderWindow window(sf::VideoMode(1920, 1080), "Black Jack");

	window.setActive(false);

 	RenderObject object(player, &window, num_players);

	Thread render(&RenderObject::RenderingThread, &object);
    render.launch();

	srand(time(NULL));

	for(int i = 0; i < num_players; i++)
		deck.NewCard(player + i, i + 1);

	int winners[9] = {};

	deck.Game(player, num_players, winners);

	WinnersStr(winners, num_players);

	Clock clock;
	while(clock.getElapsedTime().asSeconds() < 1.5);
	render.terminate();

 	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
	}

	delete[] player;

	return 0;
}

//--------------------------------------------------------------

int ScanPlayer(char* inputdata)
{
	int num_players = 0;

	if(inputdata == nullptr)
	{
		printf("Type number of players:\n");
		scanf("%d", &num_players);
	}
	else num_players = atoi(inputdata);

	if(num_players > 8)
	{
		printf("Table is full. Maximum of 8 players\n");
		num_players = 8;
	} else if(num_players < 1) num_players = 1;

	return num_players;
}

//--------------------------------------------------------------

void WinnersStr(int* winners, int num_players)
{
	int win_count = 0;

	for(int i = 0; i < num_players; i++)
		if(winners[i])	win_count++;

	if(win_count == 1)
	{
		sprintf(game_end, "\n\tPlayer ");

		for(int i = 0; i < num_players; i++)
			if(winners[i]) sprintf(game_end + strlen(game_end), "%d, ", i + 1);

		sprintf(game_end + strlen(game_end) - 2, " won. He scored %d points."
					"\n\t\t\t\tCongratulations!!!\n", winners[8]);
	} 
	else 
	{
		sprintf(game_end, "\n\tPlayers ");

		for(int i = 0; i < num_players; i++)
			if(winners[i]) sprintf(game_end + strlen(game_end), "%d, ", i + 1);

		sprintf(game_end + strlen(game_end) - 2, " won. They scored %d points."
					"\n\t\t Congratulations!!!\n", winners[8]);
	}
}

//--------------------------------------------------------------