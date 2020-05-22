#ifndef SDLLAYER_H
#define SDLLAYER_H

class SdlLayer
{
public:
    SdlLayer(char const *title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    ~SdlLayer();
    void Update(void const *buffer, int pitch);
    bool ProcessInput(unsigned char *keys);

private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    SDL_Texture *texture{};
};

#endif // SDLLAYER_H