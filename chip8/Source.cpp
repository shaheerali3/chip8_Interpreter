#include <iostream>
#include <SDL.h>

#define global_variable static

const int WIN_WIDTH = 640;
const int WIN_HEIGHT = 320;

int count = 0;

global_variable uint8_t memory[4096]; // load rom after 0x200
global_variable uint8_t display[64 * 32] = {};

global_variable uint8_t registers[16];
global_variable uint16_t indexreg;
global_variable uint16_t programcounter; //stores the location to be fetched
global_variable uint16_t opcode;
global_variable uint8_t chip8_fontset[80] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void initdisplay() {
    for (int i = 0; i < 2048; i++) 
    {
        if (i % 2 == 0) 
        {
            display[i] = 1;
        
        }
        else
        {
            display[i] == 0;
        }
    }

}

void initmemory()
{
    for (int i = 0; i < 80; i++) {
        memory[i] = chip8_fontset[i];
    }

}

void initreg(uint8_t* reg)
{
    for (int i = 0; i < 16; i++)
    {
        reg[i] = 0;

    }
}

void Fetch_Decode_Execute()
{

    opcode = memory[programcounter] << 8 | memory[programcounter + 1];
    //left bits                   //right bits
    //8 bits                       //8 bits


    switch (opcode & 0xf000)
    {
    case 0x00:
    {
        switch (opcode & 0x000f)
        {
        case 0x000: //  000E
        {

            //clear display
            for (int i = 0; i < 2048; i++)
            {
                
                    display[i] = 0;
            }

        }
        case 0x000E: // 00E0
        {


        }

        }


    }
    case 0x1000:
    {
        programcounter = (opcode & 0xFFF);

        break;
    }
    case 0x2000:
    {
        programcounter = (opcode & 0xFFF);

        break;
    }

    case 0x3000:
    {

        break;
    }

    case 0x4000:
    {
        break;
    }

    case 0x5000:
    {
        break;
    }

    case 0x6000:
    {
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t nn = opcode & 0x00FF;
        registers[x] = nn;

        break;
    }

    case 0x7000:
    {
        uint16_t x = (opcode & 0x0F00) >> 8;
        uint16_t nn = opcode & 0x00FF;
        registers[x] = registers[x] + nn;

        break;
    }

    case 0x8000:
    {
        switch (opcode & 0x000F)
        {
        case 0x0000:
        {

        }
        case 0x0001:
        {

            break;
        }
        case 0x0002:
        {


            break;
        }

        case 0x0003:
        {


            break;
        }

        case 0x0004:
        {


            break;
        }

        case 0x0005:
        {


            break;
        }
        case 0x0006:
        {

            break;
        }

        case 0x0007:
        {

            break;

        }
        case 0x000E:
        {

            break;
        }

        }

    }
    //case
    case 0x9000:
    {


        break;
    }
    case 0xA000:
    {
        indexreg = opcode & 0x0FFF;


        break;
    }
    case 0xB000:
    {

        break;
    }
    case 0xC000:
    {

        break;
    }

    case 0xD000: //DXYN
    {
        uint8_t vx = (opcode & 0x0F00 >> 8);
        uint8_t vy = (opcode & 0x00F0 >> 4);
        uint8_t n = (opcode & 0x000F);

        uint8_t x = registers[vx] % 64;
        uint8_t y = registers[vy] % 32;

        for (int i = 0; i < n; i++) {
            uint8_t spritepixel = memory[indexreg+i];
            for (int j = 0; j < 8; j++) {
                if ((spritepixel & (1 << i)) !=0) 
                {
                    if (display[x + j + (y + i) * 64] !=0  ) {
                        registers[0xF] = 1;
                    }
                    display[x + j + (y + i) * 64] ^= 1;

                }
            
            }


        }



        break;
    }

    case 0xE000:
    {

        switch (opcode & 0x000F)
        {

        case 0x000E:
        {

            break;
        }
        case 0x0001:
        {

            break;
        }

        }



        break;
    }
    case 0xF000:
    {
        switch (opcode & 0x00FF)
        {
        case 0x0007:
        {

            break;
        }

        case 0x000A:
        {

            break;
        }

        case 0x0015:
        {
            break;
        }

        case 0x0018:
        {
            break;
        }

        case 0x001E:
        {

            break;
        }

        case 0x0029:
        {

            break;
        }

        case 0x0033:
        {

            break;
        }
        case 0x0055:
        {

            break;
        }
        case 0x0065:
        {

            break;
        }


        }


    }


    }

    //case()











}







void initsound()
{






}





int main(int argv, char** args)
{
    //FILE* Fin;
    //File* Fout;
   // fopen_s(&Fin, "IBM Logo.ch8", "rb");




    bool game_is_still_running = true;
    //The window we'll be rendering to
    SDL_Window* win = NULL;
    SDL_Renderer* renderer = NULL;
    //The surface contained by the window

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }


    win = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    initdisplay();


    while (game_is_still_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // poll until all events are handled!
        // decide what to do with this event.



        }
        // update game state, draw the current frame
        // update game state, draw the current frame
        SDL_RenderClear(renderer);
        // Set our color for the draw functions
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        // Now we can draw our point
        count = 0;
        for (int i = 0; i < 32; i++) 
        {
           
            for(int j=0; j<64; j++)
            {
                if (display[count]==1) {
                    printf("%d /n", count);
                    SDL_Rect rect;
                    rect.x = j*10;
                    rect.y = i*10;
                    rect.w = 10;
                    rect.h = 10;
                 
                  SDL_RenderDrawRect(renderer, &rect);
                  SDL_RenderFillRect(renderer, &rect);   
                }
                
            }
            count++;
        }
        
        // Set the color to what was before

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        // .. you could do some other drawing here
        // And now we present everything we draw after the clear.
        SDL_RenderPresent(renderer);


    }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);


    return 0;
}