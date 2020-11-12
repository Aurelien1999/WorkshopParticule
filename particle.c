#include<SFML/Graphics.h>
#include<SFML/Window.h>
#include<SFML/Audio.h>
#include<SFML/System.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#define PI 3.141529
#include <SFML/Graphics.h>

int nbr_part = 900;

struct framebuffer {
    unsigned int width;
    unsigned int height;
    sfUint8 *pixels;
};
typedef struct framebuffer framebuffer_t;

// struct particuleben {
    
// };
// typedef struct particuleben particuleben_t;

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *framebuffer = malloc(sizeof(framebuffer_t));
    framebuffer->pixels = malloc(sizeof(sfUint8) * 4 * width * height);
    framebuffer->width = width;
    framebuffer->height = height;

    return (framebuffer);
}

void framebuffer_destroy(framebuffer_t *framebuffer)
{
    free(framebuffer);
}
void my_put_pixel(framebuffer_t *framebuffer, float x, float y, sfColor color)
{
    int i = ((framebuffer->width * y + x) * 4);
    framebuffer->pixels[i + 0] = color.r;
    framebuffer->pixels[i + 1] = color.g;
    framebuffer->pixels[i + 2] = color.b;
    framebuffer->pixels[i + 3] = color.a;
}

int setDone(int done, sfRenderWindow *window)
{
     if (sfKeyboard_isKeyPressed(sfKeyNum0))
        done = 0;
    if (sfKeyboard_isKeyPressed(sfKeyNum1))
        done = 1;
    if (sfKeyboard_isKeyPressed(sfKeyNum2))
        done = 2;
    if (sfKeyboard_isKeyPressed(sfKeyNum3))
        done = 3;
    sfRenderWindow_display(window);
    sfRenderWindow_setFramerateLimit(window, 60);
    return (done);
}

void destroyFramebufferandWindow(int nbr_part, framebuffer_t **framebuffer, sfRenderWindow *window) 
{
    for (int i = 0; i < nbr_part; i++)
        framebuffer_destroy(framebuffer[i]);
    sfRenderWindow_destroy(window);
}
int main()
{
    int done = 0;
    sfVideoMode mode = {1600, 900, 32};
    sfRenderWindow *window;
    // array de framebuffer sprite et texture pour en avoir plusieurs
    framebuffer_t **framebuffer = malloc(sizeof(framebuffer_t *) * nbr_part + 1);
    sfTexture **text = malloc(sizeof(sfTexture *) * nbr_part+1);
    sfSprite **sprite = malloc(sizeof(sfSprite *) * nbr_part+1);
    // déclaration des pos
    sfVector2i position;
    sfVector2i pos= {1,1};
    sfVector2f pos3 = {800, 500};
    sfVector2f *pos5 = malloc(sizeof(sfVector2f) * nbr_part + 1);
    int a = 2, b = 2, c = 0;

    // creation de l'objet window
    window = sfRenderWindow_create(mode, "PARTICLE", sfFullscreen, NULL);
    
    // creation textures et sprites et framebuffer
    for (int i = 0; i < nbr_part; i++) {
        framebuffer[i] = framebuffer_create(3, 3);
        text[i] = sfTexture_create(3, 3);
        sprite[i] = sfSprite_create();
    }
    // rendre le curseur invisible
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);

    // boucle infinie des évenements
    while (sfRenderWindow_isOpen(window)){
        // get la position de la souris
        position = sfMouse_getPositionRenderWindow(window);
        // clear la derniere frame de l'écran
        sfRenderWindow_clear(window, sfBlack);
        // update les textures avec les particules
        for (int i = 0; i < nbr_part; i++) {
            my_put_pixel(framebuffer[i], pos.x, pos.y, (sfColor){255,255,255,255});
            sfTexture_updateFromPixels(text[i], framebuffer[i]->pixels, 3, 3, 0, 0);
            sfSprite_setTexture(sprite[i], text[i], sfTrue);
        }
        //appuyer sur échap pour fermer la window
        if (sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(window);
        // afficher les particules à l'écran
        for (int i = 0; i < nbr_part; i++)
            sfRenderWindow_drawSprite(window, sprite[i], NULL);
        // première manipulation des positions des particules pour faire notre premier algo -> éléctricité
        if (done == 1) {
            for (int i = 0; i < nbr_part; i++) {
                if (pos3.x > rand()%1599)
                    a = -1;
                else a = 1;
                if (pos3.y > rand()%899)
                    b = -1;
                else b = 1;
                pos3.x -= a;
                pos3.y -= b;
                sfSprite_setPosition(sprite[i], pos3);
            }
            pos3.x = position.x;
            pos3.y = position.y;
        }
        if (done == 2) {
            // écris ton algo ici 
            // 1 utilise les pos5[i].x et .y pour définir la position de tes particules
            // 2 for (int i = 0; i < nbr_part; i++) { quasi obligatoire pour parcourir tes pos5[i] et set au sprite
            // 3 sfSprite_setPosition(sprite[i], pos5[i]);
            // 4 soit imaginatif 
        }
        //change de scene avec NUM 0, 1 , 2 etc... + display + setframelimit
        done = setDone(done, window);
    }
    //destroyer
    destroyFramebufferandWindow(nbr_part, framebuffer, window);
}