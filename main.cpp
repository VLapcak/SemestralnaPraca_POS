#include <iostream>
#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {

    SDL_Window* window;

    window = SDL_CreateWindow("Clovece nehnevaj sa", 0, 0, 800, 600, SDL_WINDOWEVENT_SHOWN);


    SDL_Delay(3000);

    SDL_DestroyWindow(window);

    return 0;

}
