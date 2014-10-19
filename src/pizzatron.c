/*
 * pizzatron.c
 * This file is part of Pizzatron
 *
 * Copyright (C) 2013 - Félix Arreola Rodríguez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* ----------------
 * LEGAL NOTICE
 * ----------------
 *
 * This game is NOT related to Club Penguin in any way. Also,
 * this game is not intended to infringe copyrights, the graphics and
 * sounds used are Copyright of Disney.
 *
 * The new SDL code is written by Gatuno, and is released under
 * the term of the GNU General Public License.
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define FPS (1000/24)

#define SWAP(a, b, t) ((t) = (a), (a) = (b), (b) = (t))
#define RANDOM(x) ((int) (x ## .0 * rand () / (RAND_MAX + 1.0)))

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

/* Enumerar las imágenes */
enum {
	IMG_BACKGROUND,
	
	IMG_CONVEYORBELT,
	
	IMG_PIZZA_BASE_1,
	IMG_PIZZA_BASE_2,
	IMG_PIZZA_BASE_3,
	IMG_PIZZA_BASE_4,
	IMG_PIZZA_BASE_5,
	
	IMG_PIZZA_CHEESE,
	IMG_PIZZA_SPRINKLES,
	
	IMG_PIZZA_SHADOW,
	
	IMG_SPLAT_MASK,
	
	IMG_INGREDIENTS_BASE_SAUCE,
	
	IMG_INGREDIENTS_HOLDER_A_1,
	IMG_INGREDIENTS_HOLDER_A_2,
	IMG_INGREDIENTS_HOLDER_A_3,
	IMG_INGREDIENTS_HOLDER_B,
	
	IMG_SAUCE,
	IMG_HOT_SAUCE,
	IMG_CHOCOLATE,
	IMG_PINK_ICING,
	
	IMG_CHEESE_BOX,
	IMG_SPRINKLES_BOX,
	
	IMG_SPLAT_SAUCE_1,
	IMG_SPLAT_SAUCE_2,
	IMG_SPLAT_SAUCE_3,
	IMG_SPLAT_SAUCE_4,
	IMG_SPLAT_SAUCE_5,
	IMG_SPLAT_SAUCE_6,
	IMG_SPLAT_SAUCE_7,
	IMG_SPLAT_SAUCE_8,
	IMG_SPLAT_SAUCE_9,
	IMG_SPLAT_SAUCE_10,
	IMG_SPLAT_SAUCE_11,
	IMG_SPLAT_SAUCE_12,
	IMG_SPLAT_SAUCE_13,
	IMG_SPLAT_SAUCE_14,
	IMG_SPLAT_SAUCE_15,
	IMG_SPLAT_SAUCE_16,
	IMG_SPLAT_SAUCE_17,
	IMG_SPLAT_SAUCE_18,
	IMG_SPLAT_SAUCE_19,
	IMG_SPLAT_SAUCE_20,
	IMG_SPLAT_SAUCE_21,
	IMG_SPLAT_SAUCE_22,
	IMG_SPLAT_SAUCE_23,
	IMG_SPLAT_SAUCE_24,
	IMG_SPLAT_SAUCE_25,
	IMG_SPLAT_SAUCE_26,
	IMG_SPLAT_SAUCE_27,
	IMG_SPLAT_SAUCE_28,
	IMG_SPLAT_SAUCE_29,
	IMG_SPLAT_SAUCE_30,
	IMG_SPLAT_SAUCE_31,
	IMG_SPLAT_SAUCE_32,
	IMG_SPLAT_SAUCE_33,
	IMG_SPLAT_SAUCE_34,
	IMG_SPLAT_SAUCE_35,
	IMG_SPLAT_SAUCE_36,
	IMG_SPLAT_SAUCE_37,
	IMG_SPLAT_SAUCE_38,
	IMG_SPLAT_SAUCE_39,
	IMG_SPLAT_SAUCE_40,
	
	IMG_SPLAT_HOT_1,
	IMG_SPLAT_HOT_2,
	IMG_SPLAT_HOT_3,
	IMG_SPLAT_HOT_4,
	IMG_SPLAT_HOT_5,
	IMG_SPLAT_HOT_6,
	IMG_SPLAT_HOT_7,
	IMG_SPLAT_HOT_8,
	IMG_SPLAT_HOT_9,
	IMG_SPLAT_HOT_10,
	IMG_SPLAT_HOT_11,
	IMG_SPLAT_HOT_12,
	IMG_SPLAT_HOT_13,
	IMG_SPLAT_HOT_14,
	IMG_SPLAT_HOT_15,
	IMG_SPLAT_HOT_16,
	IMG_SPLAT_HOT_17,
	IMG_SPLAT_HOT_18,
	IMG_SPLAT_HOT_19,
	IMG_SPLAT_HOT_20,
	IMG_SPLAT_HOT_21,
	IMG_SPLAT_HOT_22,
	IMG_SPLAT_HOT_23,
	IMG_SPLAT_HOT_24,
	IMG_SPLAT_HOT_25,
	IMG_SPLAT_HOT_26,
	IMG_SPLAT_HOT_27,
	IMG_SPLAT_HOT_28,
	IMG_SPLAT_HOT_29,
	IMG_SPLAT_HOT_30,
	IMG_SPLAT_HOT_31,
	IMG_SPLAT_HOT_32,
	IMG_SPLAT_HOT_33,
	IMG_SPLAT_HOT_34,
	IMG_SPLAT_HOT_35,
	IMG_SPLAT_HOT_36,
	IMG_SPLAT_HOT_37,
	IMG_SPLAT_HOT_38,
	IMG_SPLAT_HOT_39,
	IMG_SPLAT_HOT_40,
	
	IMG_SPLAT_CHOCO_1,
	IMG_SPLAT_CHOCO_2,
	IMG_SPLAT_CHOCO_3,
	IMG_SPLAT_CHOCO_4,
	IMG_SPLAT_CHOCO_5,
	IMG_SPLAT_CHOCO_6,
	IMG_SPLAT_CHOCO_7,
	IMG_SPLAT_CHOCO_8,
	IMG_SPLAT_CHOCO_9,
	IMG_SPLAT_CHOCO_10,
	IMG_SPLAT_CHOCO_11,
	IMG_SPLAT_CHOCO_12,
	IMG_SPLAT_CHOCO_13,
	IMG_SPLAT_CHOCO_14,
	IMG_SPLAT_CHOCO_15,
	IMG_SPLAT_CHOCO_16,
	IMG_SPLAT_CHOCO_17,
	IMG_SPLAT_CHOCO_18,
	IMG_SPLAT_CHOCO_19,
	IMG_SPLAT_CHOCO_20,
	IMG_SPLAT_CHOCO_21,
	IMG_SPLAT_CHOCO_22,
	IMG_SPLAT_CHOCO_23,
	IMG_SPLAT_CHOCO_24,
	IMG_SPLAT_CHOCO_25,
	IMG_SPLAT_CHOCO_26,
	IMG_SPLAT_CHOCO_27,
	IMG_SPLAT_CHOCO_28,
	IMG_SPLAT_CHOCO_29,
	IMG_SPLAT_CHOCO_30,
	IMG_SPLAT_CHOCO_31,
	IMG_SPLAT_CHOCO_32,
	IMG_SPLAT_CHOCO_33,
	IMG_SPLAT_CHOCO_34,
	IMG_SPLAT_CHOCO_35,
	IMG_SPLAT_CHOCO_36,
	IMG_SPLAT_CHOCO_37,
	IMG_SPLAT_CHOCO_38,
	IMG_SPLAT_CHOCO_39,
	IMG_SPLAT_CHOCO_40,
	
	IMG_SPLAT_PINK_1,
	IMG_SPLAT_PINK_2,
	IMG_SPLAT_PINK_3,
	IMG_SPLAT_PINK_4,
	IMG_SPLAT_PINK_5,
	IMG_SPLAT_PINK_6,
	IMG_SPLAT_PINK_7,
	IMG_SPLAT_PINK_8,
	IMG_SPLAT_PINK_9,
	IMG_SPLAT_PINK_10,
	IMG_SPLAT_PINK_11,
	IMG_SPLAT_PINK_12,
	IMG_SPLAT_PINK_13,
	IMG_SPLAT_PINK_14,
	IMG_SPLAT_PINK_15,
	IMG_SPLAT_PINK_16,
	IMG_SPLAT_PINK_17,
	IMG_SPLAT_PINK_18,
	IMG_SPLAT_PINK_19,
	IMG_SPLAT_PINK_20,
	IMG_SPLAT_PINK_21,
	IMG_SPLAT_PINK_22,
	IMG_SPLAT_PINK_23,
	IMG_SPLAT_PINK_24,
	IMG_SPLAT_PINK_25,
	IMG_SPLAT_PINK_26,
	IMG_SPLAT_PINK_27,
	IMG_SPLAT_PINK_28,
	IMG_SPLAT_PINK_29,
	IMG_SPLAT_PINK_30,
	IMG_SPLAT_PINK_31,
	IMG_SPLAT_PINK_32,
	IMG_SPLAT_PINK_33,
	IMG_SPLAT_PINK_34,
	IMG_SPLAT_PINK_35,
	IMG_SPLAT_PINK_36,
	IMG_SPLAT_PINK_37,
	IMG_SPLAT_PINK_38,
	IMG_SPLAT_PINK_39,
	IMG_SPLAT_PINK_40,
	
	NUM_IMAGES
};

const char *images_names[NUM_IMAGES] = {
	GAMEDATA_DIR "images/background.png",
	GAMEDATA_DIR "images/conveyorbelt.png",
	
	GAMEDATA_DIR "images/pizza_base_1.png",
	GAMEDATA_DIR "images/pizza_base_2.png",
	GAMEDATA_DIR "images/pizza_base_3.png",
	GAMEDATA_DIR "images/pizza_base_4.png",
	GAMEDATA_DIR "images/pizza_base_5.png",
	
	GAMEDATA_DIR "images/pizza_cheese.png",
	GAMEDATA_DIR "images/pizza_sprinkles.png",
	GAMEDATA_DIR "images/pizza_shadow.png",
	
	GAMEDATA_DIR "images/splat_mask.png",
	
	GAMEDATA_DIR "images/base_sauces.png",
	GAMEDATA_DIR "images/holder_a_1.png",
	GAMEDATA_DIR "images/holder_a_2.png",
	GAMEDATA_DIR "images/holder_a_3.png",
	GAMEDATA_DIR "images/holder_b.png",
	GAMEDATA_DIR "images/sauce.png",
	GAMEDATA_DIR "images/hot_sauce.png",
	GAMEDATA_DIR "images/chocolate.png",
	GAMEDATA_DIR "images/pink_icing.png",
	
	GAMEDATA_DIR "images/cheese_box.png",
	GAMEDATA_DIR "images/sprinkle_box.png",
	
	GAMEDATA_DIR "images/splat_sauce_01.png",
	GAMEDATA_DIR "images/splat_sauce_02.png",
	GAMEDATA_DIR "images/splat_sauce_03.png",
	GAMEDATA_DIR "images/splat_sauce_04.png",
	GAMEDATA_DIR "images/splat_sauce_05.png",
	GAMEDATA_DIR "images/splat_sauce_06.png",
	GAMEDATA_DIR "images/splat_sauce_07.png",
	GAMEDATA_DIR "images/splat_sauce_08.png",
	GAMEDATA_DIR "images/splat_sauce_09.png",
	GAMEDATA_DIR "images/splat_sauce_10.png",
	GAMEDATA_DIR "images/splat_sauce_11.png",
	GAMEDATA_DIR "images/splat_sauce_12.png",
	GAMEDATA_DIR "images/splat_sauce_13.png",
	GAMEDATA_DIR "images/splat_sauce_14.png",
	GAMEDATA_DIR "images/splat_sauce_15.png",
	GAMEDATA_DIR "images/splat_sauce_16.png",
	GAMEDATA_DIR "images/splat_sauce_17.png",
	GAMEDATA_DIR "images/splat_sauce_18.png",
	GAMEDATA_DIR "images/splat_sauce_19.png",
	GAMEDATA_DIR "images/splat_sauce_20.png",
	GAMEDATA_DIR "images/splat_sauce_21.png",
	GAMEDATA_DIR "images/splat_sauce_22.png",
	GAMEDATA_DIR "images/splat_sauce_23.png",
	GAMEDATA_DIR "images/splat_sauce_24.png",
	GAMEDATA_DIR "images/splat_sauce_25.png",
	GAMEDATA_DIR "images/splat_sauce_26.png",
	GAMEDATA_DIR "images/splat_sauce_27.png",
	GAMEDATA_DIR "images/splat_sauce_28.png",
	GAMEDATA_DIR "images/splat_sauce_29.png",
	GAMEDATA_DIR "images/splat_sauce_30.png",
	GAMEDATA_DIR "images/splat_sauce_31.png",
	GAMEDATA_DIR "images/splat_sauce_32.png",
	GAMEDATA_DIR "images/splat_sauce_33.png",
	GAMEDATA_DIR "images/splat_sauce_34.png",
	GAMEDATA_DIR "images/splat_sauce_35.png",
	GAMEDATA_DIR "images/splat_sauce_36.png",
	GAMEDATA_DIR "images/splat_sauce_37.png",
	GAMEDATA_DIR "images/splat_sauce_38.png",
	GAMEDATA_DIR "images/splat_sauce_39.png",
	GAMEDATA_DIR "images/splat_sauce_40.png",
	
	GAMEDATA_DIR "images/splat_hot_01.png",
	GAMEDATA_DIR "images/splat_hot_02.png",
	GAMEDATA_DIR "images/splat_hot_03.png",
	GAMEDATA_DIR "images/splat_hot_04.png",
	GAMEDATA_DIR "images/splat_hot_05.png",
	GAMEDATA_DIR "images/splat_hot_06.png",
	GAMEDATA_DIR "images/splat_hot_07.png",
	GAMEDATA_DIR "images/splat_hot_08.png",
	GAMEDATA_DIR "images/splat_hot_09.png",
	GAMEDATA_DIR "images/splat_hot_10.png",
	GAMEDATA_DIR "images/splat_hot_11.png",
	GAMEDATA_DIR "images/splat_hot_12.png",
	GAMEDATA_DIR "images/splat_hot_13.png",
	GAMEDATA_DIR "images/splat_hot_14.png",
	GAMEDATA_DIR "images/splat_hot_15.png",
	GAMEDATA_DIR "images/splat_hot_16.png",
	GAMEDATA_DIR "images/splat_hot_17.png",
	GAMEDATA_DIR "images/splat_hot_18.png",
	GAMEDATA_DIR "images/splat_hot_19.png",
	GAMEDATA_DIR "images/splat_hot_20.png",
	GAMEDATA_DIR "images/splat_hot_21.png",
	GAMEDATA_DIR "images/splat_hot_22.png",
	GAMEDATA_DIR "images/splat_hot_23.png",
	GAMEDATA_DIR "images/splat_hot_24.png",
	GAMEDATA_DIR "images/splat_hot_25.png",
	GAMEDATA_DIR "images/splat_hot_26.png",
	GAMEDATA_DIR "images/splat_hot_27.png",
	GAMEDATA_DIR "images/splat_hot_28.png",
	GAMEDATA_DIR "images/splat_hot_29.png",
	GAMEDATA_DIR "images/splat_hot_30.png",
	GAMEDATA_DIR "images/splat_hot_31.png",
	GAMEDATA_DIR "images/splat_hot_32.png",
	GAMEDATA_DIR "images/splat_hot_33.png",
	GAMEDATA_DIR "images/splat_hot_34.png",
	GAMEDATA_DIR "images/splat_hot_35.png",
	GAMEDATA_DIR "images/splat_hot_36.png",
	GAMEDATA_DIR "images/splat_hot_37.png",
	GAMEDATA_DIR "images/splat_hot_38.png",
	GAMEDATA_DIR "images/splat_hot_39.png",
	GAMEDATA_DIR "images/splat_hot_40.png",
	
	GAMEDATA_DIR "images/splat_choco_01.png",
	GAMEDATA_DIR "images/splat_choco_02.png",
	GAMEDATA_DIR "images/splat_choco_03.png",
	GAMEDATA_DIR "images/splat_choco_04.png",
	GAMEDATA_DIR "images/splat_choco_05.png",
	GAMEDATA_DIR "images/splat_choco_06.png",
	GAMEDATA_DIR "images/splat_choco_07.png",
	GAMEDATA_DIR "images/splat_choco_08.png",
	GAMEDATA_DIR "images/splat_choco_09.png",
	GAMEDATA_DIR "images/splat_choco_10.png",
	GAMEDATA_DIR "images/splat_choco_11.png",
	GAMEDATA_DIR "images/splat_choco_12.png",
	GAMEDATA_DIR "images/splat_choco_13.png",
	GAMEDATA_DIR "images/splat_choco_14.png",
	GAMEDATA_DIR "images/splat_choco_15.png",
	GAMEDATA_DIR "images/splat_choco_16.png",
	GAMEDATA_DIR "images/splat_choco_17.png",
	GAMEDATA_DIR "images/splat_choco_18.png",
	GAMEDATA_DIR "images/splat_choco_19.png",
	GAMEDATA_DIR "images/splat_choco_20.png",
	GAMEDATA_DIR "images/splat_choco_21.png",
	GAMEDATA_DIR "images/splat_choco_22.png",
	GAMEDATA_DIR "images/splat_choco_23.png",
	GAMEDATA_DIR "images/splat_choco_24.png",
	GAMEDATA_DIR "images/splat_choco_25.png",
	GAMEDATA_DIR "images/splat_choco_26.png",
	GAMEDATA_DIR "images/splat_choco_27.png",
	GAMEDATA_DIR "images/splat_choco_28.png",
	GAMEDATA_DIR "images/splat_choco_29.png",
	GAMEDATA_DIR "images/splat_choco_30.png",
	GAMEDATA_DIR "images/splat_choco_31.png",
	GAMEDATA_DIR "images/splat_choco_32.png",
	GAMEDATA_DIR "images/splat_choco_33.png",
	GAMEDATA_DIR "images/splat_choco_34.png",
	GAMEDATA_DIR "images/splat_choco_35.png",
	GAMEDATA_DIR "images/splat_choco_36.png",
	GAMEDATA_DIR "images/splat_choco_37.png",
	GAMEDATA_DIR "images/splat_choco_38.png",
	GAMEDATA_DIR "images/splat_choco_39.png",
	GAMEDATA_DIR "images/splat_choco_40.png",
	
	GAMEDATA_DIR "images/splat_pink_01.png",
	GAMEDATA_DIR "images/splat_pink_02.png",
	GAMEDATA_DIR "images/splat_pink_03.png",
	GAMEDATA_DIR "images/splat_pink_04.png",
	GAMEDATA_DIR "images/splat_pink_05.png",
	GAMEDATA_DIR "images/splat_pink_06.png",
	GAMEDATA_DIR "images/splat_pink_07.png",
	GAMEDATA_DIR "images/splat_pink_08.png",
	GAMEDATA_DIR "images/splat_pink_09.png",
	GAMEDATA_DIR "images/splat_pink_10.png",
	GAMEDATA_DIR "images/splat_pink_11.png",
	GAMEDATA_DIR "images/splat_pink_12.png",
	GAMEDATA_DIR "images/splat_pink_13.png",
	GAMEDATA_DIR "images/splat_pink_14.png",
	GAMEDATA_DIR "images/splat_pink_15.png",
	GAMEDATA_DIR "images/splat_pink_16.png",
	GAMEDATA_DIR "images/splat_pink_17.png",
	GAMEDATA_DIR "images/splat_pink_18.png",
	GAMEDATA_DIR "images/splat_pink_19.png",
	GAMEDATA_DIR "images/splat_pink_20.png",
	GAMEDATA_DIR "images/splat_pink_21.png",
	GAMEDATA_DIR "images/splat_pink_22.png",
	GAMEDATA_DIR "images/splat_pink_23.png",
	GAMEDATA_DIR "images/splat_pink_24.png",
	GAMEDATA_DIR "images/splat_pink_25.png",
	GAMEDATA_DIR "images/splat_pink_26.png",
	GAMEDATA_DIR "images/splat_pink_27.png",
	GAMEDATA_DIR "images/splat_pink_28.png",
	GAMEDATA_DIR "images/splat_pink_29.png",
	GAMEDATA_DIR "images/splat_pink_30.png",
	GAMEDATA_DIR "images/splat_pink_31.png",
	GAMEDATA_DIR "images/splat_pink_32.png",
	GAMEDATA_DIR "images/splat_pink_33.png",
	GAMEDATA_DIR "images/splat_pink_34.png",
	GAMEDATA_DIR "images/splat_pink_35.png",
	GAMEDATA_DIR "images/splat_pink_36.png",
	GAMEDATA_DIR "images/splat_pink_37.png",
	GAMEDATA_DIR "images/splat_pink_38.png",
	GAMEDATA_DIR "images/splat_pink_39.png",
	GAMEDATA_DIR "images/splat_pink_40.png"
};

/* Codigos de salida */
enum {
	GAME_NONE = 0, /* No usado */
	GAME_CONTINUE,
	GAME_QUIT
};

/* Listar los ingredientes */
enum {
	NONE = 0,
	SAUCE_NORMAL,
	SAUCE_HOT,
	SAUCE_CHOCOLATE,
	SAUCE_PINK,
	
	CHEESE,
	SPRINKLES
};

/* Estructuras */
typedef struct {
	int x, y;
	int sauce_placed;
	int cheese_placed;
	int topping[4];
} Pizza;

typedef struct {
	int x, y;
	int frame;
	int rand;
	int type;
} Splat;

/* Prototipos de función */
int game_loop (int candy_mode);
void setup (void);
SDL_Surface * set_video_mode(unsigned);
void place_pizza_and_order (Pizza *p);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * images [NUM_IMAGES];

int main (int argc, char *argv[]) {
	int r;
	
	r = 0;
	if (argc > 1) r = 1;
	
	setup ();
	
	do {
		if (game_loop (r) == GAME_QUIT) break;
	} while (1 == 0);
	
	SDL_Quit ();
	return EXIT_SUCCESS;
}

int game_loop (int candy_mode) {
	int done = 0;
	SDL_Event event;
	SDLKey key;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	
	int handposx2, handposx1, handposx, handposy2, handposy1, handposy; /* Para calcular los desplazamientos del mouse */
	int mousedown;
	
	Pizza pizza;
	Splat splats[300];
	int splat_queue_start = 0, splat_queue_end = 0;
	int g, h, i;
	int pizzaspeed, speedboost, handicap = 0, conveyorbelt = 0;
	int image, splat_image;
	int sauce_state, sauce_timer;
	int hand;
	Uint8 alpha, rgb_r, rgb_g, rgb_b;
	Uint32 *pixel;
	int midleft, left, midright, right, top, bottom;
	
	SDL_Surface *splat_surface, *splat_surface2, *temp_surface;
	
	sauce_state = NONE;
	
	splat_surface = SDL_AllocSurface (SDL_SWSURFACE, images[IMG_PIZZA_BASE_1]->w, images[IMG_PIZZA_BASE_1]->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	splat_surface2 = SDL_AllocSurface (SDL_SWSURFACE, images[IMG_PIZZA_BASE_1]->w, images[IMG_PIZZA_BASE_1]->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_SetAlpha (images[IMG_SPLAT_MASK], 0, 0);
	
	SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
	
	SDL_GetMouseState (&handposx, &handposy);
	
	handposx2 = handposx1 = handposx;
	handposy2 = handposy1 = handposy;
	
	mousedown = FALSE;
	
	place_pizza_and_order (&pizza);
	speedboost = 0;
	
	do {
		last_time = SDL_GetTicks ();
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (event.button.x >= 40 && event.button.x < 100 && event.button.y >= 144 && event.button.y < 267) {
							hand = (candy_mode ? SAUCE_CHOCOLATE : SAUCE_NORMAL);
							mousedown = TRUE;
							sauce_state = SAUCE_NORMAL;
							sauce_timer = 0;
						} else if (event.button.x >= 101 && event.button.x < 161 && event.button.y >= 144 && event.button.y < 267) {
							hand = (candy_mode ? SAUCE_PINK : SAUCE_HOT);
							mousedown = TRUE;
							sauce_state = SAUCE_HOT;
							sauce_timer = 0;
						} else if (event.button.x >= 184 && event.button.x < 348 && event.button.y >= 214 && event.button.y < 274) {
							hand = (candy_mode ? SPRINKLES : CHEESE);
							mousedown = TRUE;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						mousedown = FALSE;
						
						if ((hand == SPRINKLES || hand == CHEESE) && (handposy >= pizza.y && handposy < pizza.y + images[IMG_PIZZA_BASE_1]->h && handposx >= pizza.x && handposx < pizza.x + images[IMG_PIZZA_BASE_1]->w)) {
							pizza.cheese_placed = hand;
						}
					}
					break;
				case SDL_KEYDOWN:
					
					break;
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
			}
		}
		
		handposy2 = handposy1;
		handposy1 = handposy;
		
		handposx2 = handposx1;
		handposx1 = handposx;
		
		SDL_GetMouseState (&handposx, &handposy);
		
		//pizzaspeed++;
		
		SDL_BlitSurface (images[IMG_BACKGROUND], NULL, screen, NULL);
		
		/* Dibujar las salsas */
		rect.x = 11;
		rect.y = 225;
		rect.w = images[IMG_INGREDIENTS_BASE_SAUCE]->w;
		rect.h = images[IMG_INGREDIENTS_BASE_SAUCE]->h;
		
		SDL_BlitSurface (images[IMG_INGREDIENTS_BASE_SAUCE], NULL, screen, &rect);
		
		if (sauce_state == NONE || sauce_state == SAUCE_HOT) {
			rect.x = 15;
			rect.y = 179;
			rect.w = images[IMG_INGREDIENTS_HOLDER_A_1]->w;
			rect.h = images[IMG_INGREDIENTS_HOLDER_A_1]->h;
			
			SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_1], NULL, screen, &rect);
			
			rect.x = 54;
			if (candy_mode) {
				rect.y = 143;
				rect.w = images[IMG_CHOCOLATE]->w;
				rect.h = images[IMG_CHOCOLATE]->h;
			
				SDL_BlitSurface (images[IMG_CHOCOLATE], NULL, screen, &rect);
			} else {
				rect.y = 140;
				rect.w = images[IMG_SAUCE]->w;
				rect.h = images[IMG_SAUCE]->h;
			
				SDL_BlitSurface (images[IMG_SAUCE], NULL, screen, &rect);
			}
			
			rect.x = 53;
			rect.y = 183;
			rect.w = images[IMG_INGREDIENTS_HOLDER_A_2]->w;
			rect.h = images[IMG_INGREDIENTS_HOLDER_A_2]->h;
			
			SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_2], NULL, screen, &rect);
		} else {
			/* Ejecutar la animación que hace que la salsa aparezca */
			switch (sauce_timer) {
				case 0:
					rect.x = 15;
					rect.y = 179;
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_1]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_1]->h;
			
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_1], NULL, screen, &rect);
					
					rect.x = 53;
					rect.y = 183;
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_2]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_2]->h;
			
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_2], NULL, screen, &rect);
					break;
				case 1:
					rect.x = 19;
					rect.y = 162;
					
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_3]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_3]->h;
					
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_3], NULL, screen, &rect);
					break;
				case 2:
					rect.x = 19;
					rect.y = 190;
					
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_3]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_3]->h;
					
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_3], NULL, screen, &rect);
					break;
				case 3:
					rect.x = 19;
					rect.y = 211;
					
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_3]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_3]->h;
					
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_3], NULL, screen, &rect);
					break;
				case 7:
					rect.x = 15;
					rect.y = 243;
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_1]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_1]->h;
			
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_1], NULL, screen, &rect);
			
					rect.x = 54;
					if (candy_mode) {
						rect.y = 210;
						rect.w = images[IMG_CHOCOLATE]->w;
						rect.h = images[IMG_CHOCOLATE]->h;
			
						SDL_BlitSurface (images[IMG_CHOCOLATE], NULL, screen, &rect);
					} else {
						rect.y = 207;
						rect.w = images[IMG_SAUCE]->w;
						rect.h = images[IMG_SAUCE]->h;
			
						SDL_BlitSurface (images[IMG_SAUCE], NULL, screen, &rect);
					}
			
					rect.x = 53;
					rect.y = 250;
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_2]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_2]->h;
			
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_2], NULL, screen, &rect);
					break;
				case 8:
					rect.x = 15;
					rect.y = 175;
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_1]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_1]->h;
		
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_1], NULL, screen, &rect);
		
					rect.x = 54;
					if (candy_mode) {
						rect.y = 139;
						rect.w = images[IMG_CHOCOLATE]->w;
						rect.h = images[IMG_CHOCOLATE]->h;
		
						SDL_BlitSurface (images[IMG_CHOCOLATE], NULL, screen, &rect);
					} else {
						rect.y = 136;
						rect.w = images[IMG_SAUCE]->w;
						rect.h = images[IMG_SAUCE]->h;
		
						SDL_BlitSurface (images[IMG_SAUCE], NULL, screen, &rect);
					}
		
					rect.x = 53;
					rect.y = 179;
					rect.w = images[IMG_INGREDIENTS_HOLDER_A_2]->w;
					rect.h = images[IMG_INGREDIENTS_HOLDER_A_2]->h;
		
					SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_A_2], NULL, screen, &rect);
					break;
			}
			
			sauce_timer++;
			if (sauce_timer == 9) sauce_state = NONE;
		}
		
		if (sauce_state == NONE || sauce_state == SAUCE_NORMAL) {
			rect.x = 147;
			rect.y = 151;
			rect.w = images[IMG_INGREDIENTS_HOLDER_B]->w;
			rect.h = images[IMG_INGREDIENTS_HOLDER_B]->h;
			
			SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_B], NULL, screen, &rect);
			
			if (candy_mode) {
				rect.x = 117;
				rect.y = 114;
				
				rect.w = images[IMG_PINK_ICING]->w;
				rect.h = images[IMG_PINK_ICING]->h;
			
				SDL_BlitSurface (images[IMG_PINK_ICING], NULL, screen, &rect);
			} else {
				rect.x = 104;
				rect.y = 139;
				rect.w = images[IMG_HOT_SAUCE]->w;
				rect.h = images[IMG_HOT_SAUCE]->h;
			
				SDL_BlitSurface (images[IMG_HOT_SAUCE], NULL, screen, &rect);
			}
		} else {
			/* Ejecutar la animación que hace que la salsa aparezca */
			rect.w = images[IMG_INGREDIENTS_HOLDER_B]->w;
			rect.h = images[IMG_INGREDIENTS_HOLDER_B]->h;
			rect.x = 147;
			
			switch (sauce_timer) {
				case 0:
					rect.y = 151;
					break;
				case 1:
					rect.y = 147;
					break;
				case 2:
					rect.y = 180;
					break;
				case 3:
					rect.y = 248;
					break;
				case 6:
					rect.y = 260;
					break;
				case 7:
					rect.y = 203;
					break;
				case 8:
					rect.y = 147;
					break;
			}
			
			if (sauce_timer != 4 && sauce_timer != 5) {
				SDL_BlitSurface (images[IMG_INGREDIENTS_HOLDER_B], NULL, screen, &rect);
			}
			
			if (sauce_timer > 5 && sauce_timer < 9) {
				if (candy_mode) {
					rect.x -= 30;
					rect.y -= 37;
					
					rect.w = images[IMG_PINK_ICING]->w;
					rect.h = images[IMG_PINK_ICING]->h;
					SDL_BlitSurface (images[IMG_PINK_ICING], NULL, screen, &rect);
				} else {
					rect.x -= 43;
					rect.y -= 12;
					
					rect.w = images[IMG_HOT_SAUCE]->w;
					rect.h = images[IMG_HOT_SAUCE]->h;
					SDL_BlitSurface (images[IMG_HOT_SAUCE], NULL, screen, &rect);
				}
			}
			sauce_timer++;
			if (sauce_timer == 9) sauce_state = NONE;
		}
		
		/* Dibujar la caja de queso o sprinkles */
		rect.x = 188;
		rect.y = 187;
		rect.w = images[IMG_CHEESE_BOX]->w;
		rect.h = images[IMG_CHEESE_BOX]->h;
		
		if (candy_mode) {
			SDL_BlitSurface (images[IMG_SPRINKLES_BOX], NULL, screen, &rect);
		} else {
			SDL_BlitSurface (images[IMG_CHEESE_BOX], NULL, screen, &rect);
		}
		
		if (splat_queue_end < splat_queue_start) {
			image = splat_queue_end + 300 - splat_queue_start;
		} else {
			image = splat_queue_end - splat_queue_start;
		}
		
		if (image > 190) {
			pizzaspeed++;
		} else if (handicap <= -2) {
			if (candy_mode) {
				pizzaspeed = 2;
			} else {
				pizzaspeed = 1;
			}
		} else if (handicap <= -1) {
			if (candy_mode) {
				pizzaspeed = 3;
			} else {
				pizzaspeed = 2;
			}
		} else if (handicap <= 4) {
			if (candy_mode) {
				pizzaspeed = 4;
			} else {
				pizzaspeed = 3;
			}
		} else if (handicap <= 8) {
			if (candy_mode) {
				pizzaspeed = 5;
			} else {
				pizzaspeed = 4;
			}
		} else if (handicap <= 13) {
			if (candy_mode) {
				pizzaspeed = 6;
			} else {
				pizzaspeed = 5;
			}
		} else if (handicap <= 19) {
			if (candy_mode) {
				pizzaspeed = 7;
			} else {
				pizzaspeed = 6;
			}
		} else if (handicap <= 26) {
			if (candy_mode) {
				pizzaspeed = 8;
			} else {
				pizzaspeed = 7;
			}
		} else if (handicap <= 34) {
			if (candy_mode) {
				pizzaspeed = 9;
			} else {
				pizzaspeed = 8;
			}
		}
		
		/* Dibujar la cinta de pizzas que se mueve */
		rect.w = images[IMG_CONVEYORBELT]->w;
		rect.h = images[IMG_CONVEYORBELT]->h;
		rect.y = 293;
		conveyorbelt = conveyorbelt + pizzaspeed + speedboost;
		if (conveyorbelt >= 100) {
			conveyorbelt = 0;
		}
		
		for (g = 750; g > -250; g = g - 100) {
			rect.x = g + conveyorbelt;
			
			SDL_BlitSurface (images[IMG_CONVEYORBELT], NULL, screen, &rect);
		}
		
		if (pizza.x < 900) {
			/* Pizza en escena, recoger ingredientes y dibujar */
			pizza.x += pizzaspeed + speedboost;
			rect.x = pizza.x;
			rect.y = pizza.y;
			image = IMG_PIZZA_BASE_1 + (pizza.sauce_placed - NONE);
			rect.w = images[image]->w;
			rect.h = images[image]->h;
			SDL_BlitSurface (images[image], NULL, screen, &rect);
		
			if (hand >= SAUCE_NORMAL && hand <= SAUCE_PINK && mousedown && (handposy >= pizza.y && handposy < pizza.y + images[IMG_PIZZA_BASE_1]->h && handposx >= pizza.x && handposx < pizza.x + images[IMG_PIZZA_BASE_1]->w)) {
				if (pizza.sauce_placed != hand) {
					if (splat_queue_start != splat_queue_end) {
						/* Revisar si el splat que hay es de otra salsa */
						if (splats[splat_queue_start].type != hand) {
							splat_queue_start = splat_queue_end = 0;
							pizza.sauce_placed = NONE;
						}
					}
					
					/* Si está lleno, eliminar el primer splat */
					if (splat_queue_start == (splat_queue_end + 1) % 300) {
						splat_queue_start = (splat_queue_start + 1) % 300;
					}
					
					temp_surface = images[IMG_SPLAT_SAUCE_1 + (hand - SAUCE_NORMAL) * 40];
					splats[splat_queue_end].x = handposx - (temp_surface->w / 2) - pizza.x;
					splats[splat_queue_end].y = handposy - (temp_surface->h / 2) - pizza.y;
					splats[splat_queue_end].frame = 0;
					splats[splat_queue_end].rand = RANDOM (4);
					
					splats[splat_queue_end].type = hand;
					
					splat_queue_end = (splat_queue_end + 1) % 300;
				}
			}
			
			/* Dibujar los splats */
			if (splat_queue_end != splat_queue_start) {
				image = IMG_SPLAT_SAUCE_1 + (splats[splat_queue_start].type - SAUCE_NORMAL) * 40;
				SDL_BlitSurface (images[IMG_SPLAT_MASK], NULL, splat_surface, NULL);
				SDL_BlitSurface (images[IMG_PIZZA_BASE_1 + pizza.sauce_placed], NULL, splat_surface, NULL);
				
				SDL_FillRect (splat_surface2, NULL, SDL_MapRGBA (splat_surface2->format, 0, 0, 0, SDL_ALPHA_OPAQUE));
				
				rect.w = images[image]->w;
				rect.h = images[image]->h;
				for (g = splat_queue_start; g != splat_queue_end; g = (g + 1) % 300) {
					splat_image = image + (splats[g].rand * 10) + splats[g].frame;
					h = rect.x = splats[g].x;
					i = rect.y = splats[g].y;
					
					SDL_BlitSurface (images[splat_image], NULL, splat_surface, &rect);
					rect.x = h;
					rect.y = i;
					SDL_BlitSurface (images[splat_image], NULL, splat_surface2, &rect);
					
					if (splats[g].frame < 9) {
						splats[g].frame++;
					}
					
				}
				
				rect.x = pizza.x;
				rect.y = pizza.y;
				rect.w = splat_surface->w;
				rect.h = splat_surface->h;
				SDL_BlitSurface (splat_surface, NULL, screen, &rect);
				
				/* Revisar si la salsa está cubierta completamente */
				/* Left Part */
				pixel = splat_surface2->pixels + (81 * splat_surface2->pitch) + (34 * splat_surface2->format->BytesPerPixel);
				
				SDL_GetRGBA (*pixel, splat_surface2->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
				//printf ("left, Colores del pixel: %i, %i, %i\n", rgb_r, rgb_g, rgb_b);
				if (rgb_r == rgb_g && rgb_g == rgb_b && rgb_b == 0) {
					/* Si sigue negro, no ha sido cubierta la parte de la pizza */
					left = FALSE;
				} else {
					left = TRUE;
				}
				
				/* Mid Left Part */
				pixel = splat_surface2->pixels + (81 * splat_surface2->pitch) + (104 * splat_surface2->format->BytesPerPixel);
				
				SDL_GetRGBA (*pixel, splat_surface2->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
				//printf ("midleft, Colores del pixel: %i, %i, %i\n", rgb_r, rgb_g, rgb_b);
				if (rgb_r == rgb_g && rgb_g == rgb_b && rgb_b == 0) {
					/* Si sigue negro, no ha sido cubierta la parte de la pizza */
					midleft = FALSE;
				} else {
					midleft = TRUE;
				}
				
				/* Mid Right Part */
				pixel = splat_surface2->pixels + (81 * splat_surface2->pitch) + (144 * splat_surface2->format->BytesPerPixel);
				
				SDL_GetRGBA (*pixel, splat_surface2->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
				//printf ("midright, Colores del pixel: %i, %i, %i\n", rgb_r, rgb_g, rgb_b);
				if (rgb_r == rgb_g && rgb_g == rgb_b && rgb_b == 0) {
					/* Si sigue negro, no ha sido cubierta la parte de la pizza */
					midright = FALSE;
				} else {
					midright = TRUE;
				}
				
				/* Right Part */
				pixel = splat_surface2->pixels + (81 * splat_surface2->pitch) + (214 * splat_surface2->format->BytesPerPixel);
				
				SDL_GetRGBA (*pixel, splat_surface2->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
				//printf ("right, Colores del pixel: %i, %i, %i\n", rgb_r, rgb_g, rgb_b);
				if (rgb_r == rgb_g && rgb_g == rgb_b && rgb_b == 0) {
					/* Si sigue negro, no ha sido cubierta la parte de la pizza */
					right = FALSE;
				} else {
					right = TRUE;
				}
				
				/* Top Part */
				pixel = splat_surface2->pixels + (31 * splat_surface2->pitch) + (124 * splat_surface2->format->BytesPerPixel);
				
				SDL_GetRGBA (*pixel, splat_surface2->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
				//printf ("top, Colores del pixel: %i, %i, %i\n", rgb_r, rgb_g, rgb_b);
				if (rgb_r == rgb_g && rgb_g == rgb_b && rgb_b == 0) {
					/* Si sigue negro, no ha sido cubierta la parte de la pizza */
					top = FALSE;
				} else {
					top = TRUE;
				}
				
				/* Bottom Part */
				pixel = splat_surface2->pixels + (131 * splat_surface2->pitch) + (124 * splat_surface2->format->BytesPerPixel);
				
				SDL_GetRGBA (*pixel, splat_surface2->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
				//printf ("bottom, Colores del pixel: %i, %i, %i\n", rgb_r, rgb_g, rgb_b);
				if (rgb_r == rgb_g && rgb_g == rgb_b && rgb_b == 0) {
					/* Si sigue negro, no ha sido cubierta la parte de la pizza */
					bottom = FALSE;
				} else {
					bottom = TRUE;
				}
				
				if (left && midleft && midright && right && bottom && top) {
					pizza.sauce_placed = splats[splat_queue_start].type;
				}
			}
			
			rect.x = pizza.x;
			rect.y = pizza.y;
			
			rect.w = images[IMG_PIZZA_SHADOW]->w;
			rect.h = images[IMG_PIZZA_SHADOW]->h;
			SDL_BlitSurface (images[IMG_PIZZA_SHADOW], NULL, screen, &rect);
			
			if (pizza.cheese_placed != NONE) {
				rect.x = pizza.x;
				rect.y = pizza.y;
				rect.w = images[IMG_PIZZA_CHEESE]->w;
				rect.h = images[IMG_PIZZA_CHEESE]->h;
				
				if (pizza.cheese_placed == CHEESE) {
					SDL_BlitSurface (images[IMG_PIZZA_CHEESE], NULL, screen, &rect);
				} else {
					SDL_BlitSurface (images[IMG_PIZZA_SPRINKLES], NULL, screen, &rect);
				}
			}
		} else {
			/* En caso contrario, acomodar una nueva pizza y una nueva orden */
			place_pizza_and_order (&pizza);
			splat_queue_start = splat_queue_end = 0;
			speedboost = 0;
		}
		
		SDL_Flip (screen);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
	} while (!done);
	
	SDL_FreeSurface (splat_surface);
	SDL_FreeSurface (splat_surface2);
	
	return done;
}

/* Set video mode: */
/* Mattias Engdegard <f91-men@nada.kth.se> */
SDL_Surface * set_video_mode (unsigned flags) {
	/* Prefer 16bpp, but also prefer native modes to emulated 16bpp. */

	int depth;

	depth = SDL_VideoModeOK (760, 480, 16, flags);
	return depth ? SDL_SetVideoMode (760, 480, depth, flags) : NULL;
}

void setup (void) {
	SDL_Surface * image;
	int g;
	
	/* Inicializar el Video SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			"Error: Can't initialize the video subsystem\n"
			"The error returned by SDL is:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	/* Crear la pantalla de dibujado */
	screen = set_video_mode (0);
	
	if (screen == NULL) {
		fprintf (stderr,
			"Error: Can't setup 760x480 video mode.\n"
			"The error returned by SDL is:\n"
			"%s\n", SDL_GetError());
		exit (1);
	}
	
	for (g = 0; g < NUM_IMAGES; g++) {
		image = IMG_Load (images_names[g]);
		
		if (image == NULL) {
			fprintf (stderr,
				"Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n", images_names[g], SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		images[g] = image;
		/* TODO: Mostrar la carga de porcentaje */
	}
	
	srand (SDL_GetTicks ());
}

void place_pizza_and_order (Pizza *p) {
	p->y = 293;
	p->x = -366;
	p->sauce_placed = p->cheese_placed = NONE;
	
	p->topping[0] = p->topping[1] = p->topping[2] = p->topping[3] = 0;
}

