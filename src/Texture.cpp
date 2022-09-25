#include "Texture.h"

Texture::Texture(const char* path) {

        std::string p = path;
        int width, height, nrChannels;

        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        //filter and wrap options are set
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load and generate the texture
        if (data)
        {
            //Finding the extension of the texture file. OpenGL throws error if jpg and png channels are not defined correctly
            if (p.substr((p.find_last_of(".") + 1)) == "png"){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA/*For png*/, GL_UNSIGNED_BYTE, data);//GL_RGBA for png and GL_RGB for jpg
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB/*For jpg*/, GL_UNSIGNED_BYTE, data);//GL_RGBA for png and GL_RGB for jpg
            }

            glGenerateMipmap(GL_TEXTURE_2D);
            std::cout << "Texture '"<<path<<"' loaded properly and mipmap generated" << std::endl;
        }
        else
        {
            std::cout << "Textures could not load properly. Check the texture path provided." << std::endl;
        }

        stbi_image_free(data);//Since the texture and it's mipmaps are generated the data could be freed;
        glBindTexture(GL_TEXTURE_2D, 0);//unbind current texture
    
}