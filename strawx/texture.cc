#include "texture.h"

#include "SDL2/SDL_image.h"
#include "unordered_map"

using namespace strawx;

namespace {

    SDL_Renderer* mRenderer;

    struct TextureDetails {
        SDL_Texture* ptr_to_texture;
        SDL_Rect source_rect;
        SDL_FRect destin_rect;

        TextureDetails() : ptr_to_texture{ nullptr } {
            SDL_Log("Default Constructed Texture");
        }

        ~TextureDetails()
        {
            SDL_DestroyTexture(ptr_to_texture);
            SDL_Log("Destroyed Texture [%s]", SDL_GetError());
        }
    };

    std::unordered_map<std::string, TextureDetails> mTextures;
}

void TextureHandlers::Load(std::string filename, SDL_Rect source, std::string name)
{
    static SDL_Texture* temp_texture = nullptr;
    
    temp_texture = IMG_LoadTexture(mRenderer, filename.c_str());

    if (!temp_texture) {
        SDL_Log("%s", IMG_GetError());
        return;
    }

    mTextures[name].ptr_to_texture = temp_texture;
    mTextures[name].source_rect = source;

    SDL_Log("Loaded %s", name.c_str());
}

void TextureHandlers::Draw(std::string name, SDL_FRect destination)
{
    SDL_RenderCopyF(
        mRenderer,
        mTextures[name].ptr_to_texture,
        &mTextures[name].source_rect,
        &destination
    );
}

// PRIVATE METHODS ()
void TextureHandlers::non_interface::Init(void* renderer)
{
    static uint8_t use = SDL_TRUE;
    if (use) mRenderer = (SDL_Renderer*)renderer;
    use = SDL_FALSE;
}

void TextureHandlers::non_interface::Clear()
{
    SDL_Log("Clearing Textures...");
    mRenderer = nullptr;
    mTextures.clear();
}
