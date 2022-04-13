#include "../include/game.h"


extern char game_end[];

Graphics::Graphics(const char* filename)
{
    file = filename;
    image.loadFromFile("./images/" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

Graphics::Graphics()
{

}

void Graphics::Create_Sprite(const char* filename)
{
    file = filename;
    image.loadFromFile("./images/" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

MyText::MyText(int x, int y)
{
	font.loadFromFile("Copperplate Bold.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);
	text.setPosition(x, y);
}

//--------------------------------------------------------------

RenderObject::RenderObject(BlackJack* object, RenderWindow* Window, int amount)
{
	player = object;
	window = Window;
	num_players = amount;
}

//--------------------------------------------------------------

void RenderObject::RenderingThread()
{
    window->setActive(true);

    Graphics table("table.jpg");
    Graphics deck ("deck.png"); 
	MyText t_deck(win_width/2 - card_height - 60, 60);
	MyText t_winnner(win_width/2 - 200, win_height/2);

	deck.sprite.setPosition(win_width/2, 10);

	Offset* offset = (Offset*) calloc (num_players, sizeof(Offset));

	int num_card = 0, deck_size = 0;

	char cap_deck[20] = "";

 	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

 		deck_size = 52;

		for(int i = 0; i < num_players; i++)
			deck_size -= player[i].GetSize();

		sprintf(cap_deck, "Deck sise: %d", deck_size);

		t_deck.text.setString	(cap_deck);
		t_winnner.text.setString(game_end);

    	window->clear();

		window->draw(table.sprite);
		window->draw(deck.sprite);
		window->draw(t_deck.text);
		window->draw(t_winnner.text);


		for(int j = 0; j < num_players; j++)
		{
			num_card = player[j].GetSize();

			offset[j].CalcOffset(j);

			for(int i = 0; i < 13; i++)
			{
				player[j].GetColor(Diamond)[i].PrintCard(window, &num_card, offset[j], j);
				player[j].GetColor(Spade)  [i].PrintCard(window, &num_card, offset[j], j);
				player[j].GetColor(Heart)  [i].PrintCard(window, &num_card, offset[j], j);
				player[j].GetColor(Club)   [i].PrintCard(window, &num_card, offset[j], j);
			}
		}

 		window->display();
	}

	free(offset);
}

//--------------------------------------------------------------

void CardColor::PrintCard(RenderWindow* window, int* size, Offset offset, int pos)
{
    if(status)
    {
		int pos_x = 0, pos_y = 0;

		MyText t_player(0,0);

		char player_name[20] = "";

		sprintf(player_name, "Player %d", pos + 1);

		if(pos < 4)
		{
			pos_x = (win_width - (*size)*card_width)/2 + offset.x;
			pos_y =  win_height + offset.y;
			t_player.text.setPosition(win_width/2 + offset.x - 70, pos_y - 50);
		}
		else
		{			
			pos_x = card_height + offset.x;
			pos_y = card_width  + offset.y + (*size)*card_width/3;
		
			if(pos < 6)
				t_player.text.setPosition(card_height + offset.x + 30, card_width  + offset.y + 40);
			else if(pos < 8)
				t_player.text.setPosition(offset.x - card_height + 10, card_width  + offset.y + 40);
		}

        graphic_card.sprite.setPosition(pos_x, pos_y);
		t_player.text.setString(player_name);

		window->draw(graphic_card.sprite);
		window->draw(t_player.text);

		(*size)--;
    }
}

//--------------------------------------------------------------

void Offset::CalcOffset(int pos)
{
	if(pos < 4) 
	{
		y = -80;
		x = pos*500 - 550;
	}
	else if(pos < 6)
	{
		x = 0;
		y = (pos - 4)*300;
	} 
	else if(pos < 8)
	{
		x = win_width;
		y = (pos - 6)*300;
	}
}