#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Load an image
    SDL_Surface* imageSurface = IMG_Load("image.png");
    if (imageSurface == nullptr) {
        std::cerr << "Unable to load image! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create a texture from the loaded image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Free the surface as it's no longer needed
    if (texture == NULL) {
        std::cerr << "Unable to create texture! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Clear the screen
    SDL_RenderClear(renderer);

    // Render the texture
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for quit event or user input
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) { // Wait for any key press to quit
                quit = true;
            }
        }
    }

    // Destroy resources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
