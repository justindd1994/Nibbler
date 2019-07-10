#include <SDL2/SDL.h>
#include <iostream>

int main(int ac, char **av) {

    (void)ac;
    (void)av;

if (SDL_Init(SDL_INIT_VIDEO) < 0) {
     printf("-------");
     return -1;
     //   throw SnakeSDLException("SDL could not initialize!");
    }
    SDL_Window *window = NULL;                    // Declare a pointer


    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        0,           // initial x position
        0,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL          // flags - see below
    );

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!render) {
        std::cout << "jeez" << std::endl;
    }

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderPresent(render);

    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent( & event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }
    }

    // while(1) {}
    //SDL_Delay(8000);  // Pause execution for 3000 milliseconds, for example
    // printf("Could not create window:");÷
    
    // Close and destroy the window
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
