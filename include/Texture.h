#ifndef _TEXTURE_
#define _TEXTURE_

#include<glad/glad.h>
#include<iostream>
#include <string>
#include "stb_image.h"

class Texture {
	
	unsigned int ID;
	
public:
	Texture(const char* path);

    inline unsigned int getID()const
    {
        return ID;
    }
};


#endif