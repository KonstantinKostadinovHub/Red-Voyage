#include <SDL.h>

#include <fstream>

using namespace std;

/** 
* \brief text input field use by the user to gie information in text form
* in order to use it create a config file and enter the 
* parameters of the rect (coor, width and height)
* the background texture (it muse be put in the ui folder)
*/

class TextInputField 
{
public:
	TextInputField();
	virtual ~TextInputField();

	string getContaier();
	void update();
	void init(string configFile);
protected:
	bool m_clickedTheField;
	string m_container;
	SDL_Rect m_objectRect;
	SDL_Texture* m_backgroundTexture;
};