#ifndef STRAWX_TEXTURE_HANDLERS_H
#define STRAWX_TEXTURE_HANDLERS_H

#include "SDL2/SDL_rect.h"
#include <string>

namespace strawx::TextureHandlers {

    void Load(std::string filename, SDL_Rect source, std::string name);

    void Draw(std::string name, SDL_FRect destination);

    namespace non_interface { // called internally
        void Init(void*);
        void Clear();
    }

}

#endif