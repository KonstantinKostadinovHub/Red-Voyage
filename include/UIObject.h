#ifndef UIOBJECT_H
#define UIOBJECT_H


#include <SDL.h>
#include <string>


#include "defines.h"
/// \brief A class used to initialize and draw the little representations of ores and food so we can keep track of their quantity. 
class UIObject
{
    public:
        UIObject(); ///< The class constructor
        virtual ~UIObject(); ///< The class destructor

        int m_distance; ///< A variable used to save the distance between two separate UIObjects
        int m_startPos; ///< Coordinates of the starting point where the set of UIObjects is begining to draw
        int m_pos; ///< The position of a sertain UIObject in the sequence
        string m_img; ///< The image used to create a UIObject
        string count; ///< Used to save the visual representation of the number we have got from a said Ore or Food

        coordinates coor; ///< Coordinates of the visual representation of the number we have got from a said Ore or Food

        SDL_Texture* m_objectTexture; ///< Texture of the UIObject

        SDL_Rect m_objectRect; ///< Used to define the placement of the UIObject

        void load(string config); ///\fn Used to initialize a UIObject
        void update(); ///\fn Used to update a UIObject
        void draw(); ///\fn Used to draw a UIObject

    protected:

    private:
};

#endif // UIOBJECT_H
