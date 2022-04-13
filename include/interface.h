#include <SFML/Graphics.hpp>

class BlackJack;

using namespace sf;

class Graphics
{
    public:

    String  file;
   	Image   image;
    Texture texture;
    Sprite  sprite;

    Graphics(const char* filename);
    Graphics();
    void Create_Sprite(const char* filename);
};

class MyText
{
	Font font;

    public:
       	Text text;
        MyText(int x, int y);
};

struct Offset
{
	int x = 0;
	int y = 0;

	void CalcOffset(int pos);
};

class RenderObject
{
	BlackJack* player;
	RenderWindow* window;
	int num_players = 0;

	public:

		RenderObject(BlackJack* object, RenderWindow* Window, int amount);
		void RenderingThread();
};
