#include "texture.h"

#include "SDL2/SDL_image.h"
#include "core/common.hh"

#include <unordered_map>

using namespace strawx;

struct TextureDetails {

    TextureDetails() : ptr_to_texture{ nullptr } { }

    ~TextureDetails() {
        SDL_DestroyTexture(ptr_to_texture);
        SDL_Log("Destroyed Texture [%s]", SDL_GetError());
    }

    SDL_Texture* ptr_to_texture;
    SDL_Rect source_rect;
    SDL_FRect destin_rect;
};

namespace {
    SDL_Renderer* mRenderer{ nullptr };
    std::unordered_map<std::string, TextureDetails> mTextures;
}

void TextureHandler::LoadTexture(std::string filename, SDL_Rect source, std::string name)
{
    static SDL_Texture* temp_texture = nullptr;
    
    temp_texture = IMG_LoadTexture(mRenderer, filename.c_str());

    if (!temp_texture) {
        SDL_Log("%s", IMG_GetError());
        return;
    }

    mTextures[name].ptr_to_texture = temp_texture;
    temp_texture = nullptr;

    mTextures[name].source_rect = source;
    mTextures[name].destin_rect.w = static_cast<float>(source.w);
    mTextures[name].destin_rect.h = static_cast<float>(source.h);

    SDL_Log("Loaded %s", name.c_str());
}

void TextureHandler::DrawTexture(const std::string name, const float x, const float y)
{
    mTextures[name].destin_rect.x = x;
    mTextures[name].destin_rect.y = y;

    SDL_RenderCopyF(
        mRenderer,
        mTextures[name].ptr_to_texture,
        &mTextures[name].source_rect,
        &mTextures[name].destin_rect
    );
}

void TextureHandler::SetTextureSize(const std::string name, const float size)
{
    mTextures.at(name).destin_rect.w *= size;
    mTextures.at(name).destin_rect.h *= size;
}


using namespace texture_impl;

void set_renderer(void* renderer)
{
    mRenderer = static_cast<SDL_Renderer*>(renderer);
}

void clear_textures()
{
    SDL_Log("Clearing Textures...");
    mRenderer = nullptr;
    mTextures.clear();
}
