#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // usleep()

#include <SDL2/SDL.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   300

SDL_Window* window;

SDL_Renderer* renderer;

void init_display() {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized!: %s\n", SDL_GetError());
        return;
    }

    // Create window
    window = SDL_CreateWindow("Basic C SDL project",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void draw(int r, int g, int b) {
    // Declare rect of square
    SDL_Rect squareRect;

    // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
    squareRect.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
    squareRect.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;

    // Square position: In the middle of the screen
    squareRect.x = SCREEN_WIDTH / 2 - squareRect.w / 2;
    squareRect.y = SCREEN_HEIGHT / 2 - squareRect.h / 2;

    // Initialize renderer color white for the background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Clear screen
    SDL_RenderClear(renderer);

    // Actually draw the desired color
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    // Draw filled square
    SDL_RenderFillRect(renderer, &squareRect);

    // Update screen
    SDL_RenderPresent(renderer);
}

void destroy_window() {
    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();
}



int main() {
    init_display();
    if(!window) {
        printf("Window could not be created with error: %s\n", SDL_GetError());
        return 0;
    }
    if(!renderer) {
        printf("Renderer could not be created with error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Event event;

    int should_quit = 0;
    int red_iter = 0;
    int blue_iter = 255;
    while(!should_quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                should_quit = 1;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q) {
                    // If the 'q' button is pressed, quit the application
                    should_quit = 1;
                    break;
                }
            default:
                // Change the color from blue to red over time
                draw(red_iter, 0, blue_iter);
                red_iter++;
                blue_iter--;
                red_iter %= 255;
                if (blue_iter == 0) {
                    blue_iter = 255;
                }

                // Sleep for half a second
                usleep(0.5 * 100000);
        }
    }
    destroy_window();

    return 0;
}

