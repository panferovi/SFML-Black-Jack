#include "../include/interface.h"


const int win_width  = 1720;
const int win_height = 910;
const int card_height = 175;
const int card_width = 127;


enum Colors 
{
	Diamond = 0,
	Spade,
	Heart, 
	Club
};


struct Offset;

struct CardColor
{
	int card   = 0;
	int status = 0;
	Graphics graphic_card;

	void new_card(CardColor* color, int filename, const char* card_color);
	void PrintCard(RenderWindow* window, int* size, Offset offset, int pos);
};


class BlackJack
{
	CardColor diamond[13];
	CardColor spade	 [13];
	CardColor heart	 [13];
	CardColor club	 [13];
	int size = 0;
	int sum  = 0;

	public:

		BlackJack ();
		BlackJack (int stat);

		int  GetSize  ();
		void Print	  ();
		void Game 	  (BlackJack* player, int num_players, int* winners);
		void NewCard  (BlackJack* player, int player_number);
		void Strategy (BlackJack* player, int player_number);
		void PrintPlayer (RenderWindow& window);
		CardColor* GetColor (int color);
};

