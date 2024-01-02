#ifndef STRAWX_TEXTURE_HANDLERS_H
#define STRAWX_TEXTURE_HANDLERS_H

#include "SDL2/SDL_rect.h"
#include <string>

namespace strawx::TextureHandler {

    void LoadTexture(const std::string filename, const SDL_Rect source, const std::string name);

    void DrawTexture(const std::string name, const float x, const float y);

    void SetTextureSize(const std::string name, const float size);
}

#endif