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
	
	IMG_TOPPING_1_BOX,
	IMG_TOPPING_2_BOX,
	IMG_TOPPING_3_BOX,
	IMG_TOPPING_4_BOX,
	IMG_TOPPING_5_BOX,
	IMG_TOPPING_6_BOX,
	IMG_TOPPING_7_BOX,
	IMG_TOPPING_8_BOX,
	
	
	IMG_SPLAT_SAUCE,
	IMG_SPLAT_HOT,
	IMG_SPLAT_CHOCO,
	IMG_SPLAT_PINK,
	
	IMG_SAUCE_SQUASH_1,
	IMG_SAUCE_SQUASH_2,
	IMG_SAUCE_SQUASH_3,
	IMG_SAUCE_SQUASH_4,
	IMG_SAUCE_SQUASH_5,
	IMG_SAUCE_SQUASH_6,
	
	IMG_HOT_SQUASH_1,
	IMG_HOT_SQUASH_2,
	IMG_HOT_SQUASH_3,
	IMG_HOT_SQUASH_4,
	IMG_HOT_SQUASH_5,
	IMG_HOT_SQUASH_6,
	IMG_HOT_SQUASH_7,
	IMG_HOT_SQUASH_8,
	
	IMG_CHOCO_SQUASH_1,
	IMG_CHOCO_SQUASH_2,
	IMG_CHOCO_SQUASH_3,
	IMG_CHOCO_SQUASH_4,
	IMG_CHOCO_SQUASH_5,
	IMG_CHOCO_SQUASH_6,
	
	IMG_PINK_SQUASH_1,
	IMG_PINK_SQUASH_2,
	IMG_PINK_SQUASH_3,
	IMG_PINK_SQUASH_4,
	IMG_PINK_SQUASH_5,
	IMG_PINK_SQUASH_6,
	
	IMG_CHEESE_HAND,
	IMG_SPRINKLES_HAND,
	
	IMG_HAND_TOPPING_1_1,
	IMG_HAND_TOPPING_1_2,
	IMG_HAND_TOPPING_1_3,
	IMG_HAND_TOPPING_2_1,
	IMG_HAND_TOPPING_2_2,
	IMG_HAND_TOPPING_2_3,
	IMG_HAND_TOPPING_3_1,
	IMG_HAND_TOPPING_3_2,
	IMG_HAND_TOPPING_3_3,
	IMG_HAND_TOPPING_4_1,
	IMG_HAND_TOPPING_4_2,
	IMG_HAND_TOPPING_4_3,
	IMG_HAND_TOPPING_5_1,
	IMG_HAND_TOPPING_5_2,
	IMG_HAND_TOPPING_5_3,
	IMG_HAND_TOPPING_6_1,
	IMG_HAND_TOPPING_6_2,
	IMG_HAND_TOPPING_6_3,
	IMG_HAND_TOPPING_7_1,
	IMG_HAND_TOPPING_7_2,
	IMG_HAND_TOPPING_7_3,
	IMG_HAND_TOPPING_8_1,
	IMG_HAND_TOPPING_8_2,
	IMG_HAND_TOPPING_8_3,
	
	IMG_TOPPING_1_1,
	IMG_TOPPING_1_2,
	IMG_TOPPING_1_3,
	IMG_TOPPING_2_1,
	IMG_TOPPING_2_2,
	IMG_TOPPING_2_3,
	IMG_TOPPING_3_1,
	IMG_TOPPING_3_2,
	IMG_TOPPING_3_3,
	IMG_TOPPING_4_1,
	IMG_TOPPING_4_2,
	IMG_TOPPING_4_3,
	IMG_TOPPING_5_1,
	IMG_TOPPING_5_2,
	IMG_TOPPING_5_3,
	IMG_TOPPING_6_1,
	IMG_TOPPING_6_2,
	IMG_TOPPING_6_3,
	IMG_TOPPING_7_1,
	IMG_TOPPING_7_2,
	IMG_TOPPING_7_3,
	IMG_TOPPING_8_1,
	IMG_TOPPING_8_2,
	IMG_TOPPING_8_3,
	
	IMG_PIZZA_OVERFLOW_SAUCE_1,
	IMG_PIZZA_OVERFLOW_SAUCE_2,
	IMG_PIZZA_OVERFLOW_SAUCE_3,
	IMG_PIZZA_OVERFLOW_SAUCE_4,
	IMG_PIZZA_OVERFLOW_SAUCE_5,
	IMG_PIZZA_OVERFLOW_SAUCE_6,
	IMG_PIZZA_OVERFLOW_SAUCE_7,
	
	IMG_PIZZA_OVERFLOW_HOT_1,
	IMG_PIZZA_OVERFLOW_HOT_2,
	IMG_PIZZA_OVERFLOW_HOT_3,
	IMG_PIZZA_OVERFLOW_HOT_4,
	IMG_PIZZA_OVERFLOW_HOT_5,
	IMG_PIZZA_OVERFLOW_HOT_6,
	IMG_PIZZA_OVERFLOW_HOT_7,
	
	IMG_PIZZA_OVERFLOW_CHOCO_1,
	IMG_PIZZA_OVERFLOW_CHOCO_2,
	IMG_PIZZA_OVERFLOW_CHOCO_3,
	IMG_PIZZA_OVERFLOW_CHOCO_4,
	IMG_PIZZA_OVERFLOW_CHOCO_5,
	IMG_PIZZA_OVERFLOW_CHOCO_6,
	IMG_PIZZA_OVERFLOW_CHOCO_7,
	
	IMG_PIZZA_OVERFLOW_PINK_1,
	IMG_PIZZA_OVERFLOW_PINK_2,
	IMG_PIZZA_OVERFLOW_PINK_3,
	IMG_PIZZA_OVERFLOW_PINK_4,
	IMG_PIZZA_OVERFLOW_PINK_5,
	IMG_PIZZA_OVERFLOW_PINK_6,
	IMG_PIZZA_OVERFLOW_PINK_7,
	
	IMG_ORDER_PIZZA_CHEESE,
	IMG_ORDER_PIZZA_HOT,
	IMG_ORDER_PIZZA_CHOCO,
	IMG_ORDER_PIZZA_PINK,
	
	IMG_ORDER_TOPPING_1,
	IMG_ORDER_TOPPING_2,
	IMG_ORDER_TOPPING_3,
	IMG_ORDER_TOPPING_4,
	IMG_ORDER_TOPPING_5,
	IMG_ORDER_TOPPING_6,
	IMG_ORDER_TOPPING_7,
	IMG_ORDER_TOPPING_8,
	IMG_ORDER_TOPPING_9,
	IMG_ORDER_TOPPING_10,
	IMG_ORDER_TOPPING_11,
	
	IMG_ORDER_CANDY_TOPPING_1,
	IMG_ORDER_CANDY_TOPPING_2,
	IMG_ORDER_CANDY_TOPPING_3,
	IMG_ORDER_CANDY_TOPPING_4,
	IMG_ORDER_CANDY_TOPPING_5,
	IMG_ORDER_CANDY_TOPPING_6,
	IMG_ORDER_CANDY_TOPPING_7,
	IMG_ORDER_CANDY_TOPPING_8,
	IMG_ORDER_CANDY_TOPPING_9,
	IMG_ORDER_CANDY_TOPPING_10,
	IMG_ORDER_CANDY_TOPPING_11,
	
	IMG_CHECKED,
	
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
	GAMEDATA_DIR "images/topping_1_box.png",
	GAMEDATA_DIR "images/topping_2_box.png",
	GAMEDATA_DIR "images/topping_3_box.png",
	GAMEDATA_DIR "images/topping_4_box.png",
	GAMEDATA_DIR "images/topping_5_box.png",
	GAMEDATA_DIR "images/topping_6_box.png",
	GAMEDATA_DIR "images/topping_7_box.png",
	GAMEDATA_DIR "images/topping_8_box.png",
	
	GAMEDATA_DIR "images/splat_sauce.png",
	GAMEDATA_DIR "images/splat_hot.png",
	GAMEDATA_DIR "images/splat_choco.png",
	GAMEDATA_DIR "images/splat_pink.png",
	
	GAMEDATA_DIR "images/sauce_squash_01.png",
	GAMEDATA_DIR "images/sauce_squash_02.png",
	GAMEDATA_DIR "images/sauce_squash_03.png",
	GAMEDATA_DIR "images/sauce_squash_04.png",
	GAMEDATA_DIR "images/sauce_squash_05.png",
	GAMEDATA_DIR "images/sauce_squash_06.png",
	GAMEDATA_DIR "images/hot_sauce_squash_01.png",
	GAMEDATA_DIR "images/hot_sauce_squash_02.png",
	GAMEDATA_DIR "images/hot_sauce_squash_03.png",
	GAMEDATA_DIR "images/hot_sauce_squash_04.png",
	GAMEDATA_DIR "images/hot_sauce_squash_05.png",
	GAMEDATA_DIR "images/hot_sauce_squash_06.png",
	GAMEDATA_DIR "images/hot_sauce_squash_07.png",
	GAMEDATA_DIR "images/hot_sauce_squash_08.png",
	GAMEDATA_DIR "images/chocolate_squash_01.png",
	GAMEDATA_DIR "images/chocolate_squash_02.png",
	GAMEDATA_DIR "images/chocolate_squash_03.png",
	GAMEDATA_DIR "images/chocolate_squash_04.png",
	GAMEDATA_DIR "images/chocolate_squash_05.png",
	GAMEDATA_DIR "images/chocolate_squash_06.png",
	GAMEDATA_DIR "images/pink_icing_squash_01.png",
	GAMEDATA_DIR "images/pink_icing_squash_02.png",
	GAMEDATA_DIR "images/pink_icing_squash_03.png",
	GAMEDATA_DIR "images/pink_icing_squash_04.png",
	GAMEDATA_DIR "images/pink_icing_squash_05.png",
	GAMEDATA_DIR "images/pink_icing_squash_06.png",
	
	GAMEDATA_DIR "images/cheese_hand.png",
	GAMEDATA_DIR "images/sprinkles_hand.png",
	
	GAMEDATA_DIR "images/hand_topping_1_1.png",
	GAMEDATA_DIR "images/hand_topping_1_2.png",
	GAMEDATA_DIR "images/hand_topping_1_3.png",
	GAMEDATA_DIR "images/hand_topping_2_1.png",
	GAMEDATA_DIR "images/hand_topping_2_2.png",
	GAMEDATA_DIR "images/hand_topping_2_3.png",
	GAMEDATA_DIR "images/hand_topping_3_1.png",
	GAMEDATA_DIR "images/hand_topping_3_2.png",
	GAMEDATA_DIR "images/hand_topping_3_3.png",
	GAMEDATA_DIR "images/hand_topping_4_1.png",
	GAMEDATA_DIR "images/hand_topping_4_2.png",
	GAMEDATA_DIR "images/hand_topping_4_3.png",
	GAMEDATA_DIR "images/hand_topping_5_1.png",
	GAMEDATA_DIR "images/hand_topping_5_2.png",
	GAMEDATA_DIR "images/hand_topping_5_3.png",
	GAMEDATA_DIR "images/hand_topping_6_1.png",
	GAMEDATA_DIR "images/hand_topping_6_2.png",
	GAMEDATA_DIR "images/hand_topping_6_3.png",
	GAMEDATA_DIR "images/hand_topping_7_1.png",
	GAMEDATA_DIR "images/hand_topping_7_2.png",
	GAMEDATA_DIR "images/hand_topping_7_3.png",
	GAMEDATA_DIR "images/hand_topping_8_1.png",
	GAMEDATA_DIR "images/hand_topping_8_2.png",
	GAMEDATA_DIR "images/hand_topping_8_3.png",
	GAMEDATA_DIR "images/topping_1_1.png",
	GAMEDATA_DIR "images/topping_1_2.png",
	GAMEDATA_DIR "images/topping_1_3.png",
	GAMEDATA_DIR "images/topping_2_1.png",
	GAMEDATA_DIR "images/topping_2_2.png",
	GAMEDATA_DIR "images/topping_2_3.png",
	GAMEDATA_DIR "images/topping_3_1.png",
	GAMEDATA_DIR "images/topping_3_2.png",
	GAMEDATA_DIR "images/topping_3_3.png",
	GAMEDATA_DIR "images/topping_4_1.png",
	GAMEDATA_DIR "images/topping_4_2.png",
	GAMEDATA_DIR "images/topping_4_3.png",
	GAMEDATA_DIR "images/topping_5_1.png",
	GAMEDATA_DIR "images/topping_5_2.png",
	GAMEDATA_DIR "images/topping_5_3.png",
	GAMEDATA_DIR "images/topping_6_1.png",
	GAMEDATA_DIR "images/topping_6_2.png",
	GAMEDATA_DIR "images/topping_6_3.png",
	GAMEDATA_DIR "images/topping_7_1.png",
	GAMEDATA_DIR "images/topping_7_2.png",
	GAMEDATA_DIR "images/topping_7_3.png",
	GAMEDATA_DIR "images/topping_8_1.png",
	GAMEDATA_DIR "images/topping_8_2.png",
	GAMEDATA_DIR "images/topping_8_3.png",
	
	GAMEDATA_DIR "images/overflow_sauce_1.png",
	GAMEDATA_DIR "images/overflow_sauce_2.png",
	GAMEDATA_DIR "images/overflow_sauce_3.png",
	GAMEDATA_DIR "images/overflow_sauce_4.png",
	GAMEDATA_DIR "images/overflow_sauce_5.png",
	GAMEDATA_DIR "images/overflow_sauce_6.png",
	GAMEDATA_DIR "images/overflow_sauce_7.png",
	GAMEDATA_DIR "images/overflow_hot_1.png",
	GAMEDATA_DIR "images/overflow_hot_2.png",
	GAMEDATA_DIR "images/overflow_hot_3.png",
	GAMEDATA_DIR "images/overflow_hot_4.png",
	GAMEDATA_DIR "images/overflow_hot_5.png",
	GAMEDATA_DIR "images/overflow_hot_6.png",
	GAMEDATA_DIR "images/overflow_hot_7.png",
	GAMEDATA_DIR "images/overflow_chocolate_1.png",
	GAMEDATA_DIR "images/overflow_chocolate_2.png",
	GAMEDATA_DIR "images/overflow_chocolate_3.png",
	GAMEDATA_DIR "images/overflow_chocolate_4.png",
	GAMEDATA_DIR "images/overflow_chocolate_5.png",
	GAMEDATA_DIR "images/overflow_chocolate_6.png",
	GAMEDATA_DIR "images/overflow_chocolate_7.png",
	GAMEDATA_DIR "images/overflow_pink_1.png",
	GAMEDATA_DIR "images/overflow_pink_2.png",
	GAMEDATA_DIR "images/overflow_pink_3.png",
	GAMEDATA_DIR "images/overflow_pink_4.png",
	GAMEDATA_DIR "images/overflow_pink_5.png",
	GAMEDATA_DIR "images/overflow_pink_6.png",
	GAMEDATA_DIR "images/overflow_pink_7.png",
	
	GAMEDATA_DIR "images/order_pizza_cheese.png",
	GAMEDATA_DIR "images/order_pizza_hot.png",
	GAMEDATA_DIR "images/order_pizza_choco.png",
	GAMEDATA_DIR "images/order_pizza_pink.png",
	
	GAMEDATA_DIR "images/topping_1.png",
	GAMEDATA_DIR "images/topping_2.png",
	GAMEDATA_DIR "images/topping_3.png",
	GAMEDATA_DIR "images/topping_4.png",
	GAMEDATA_DIR "images/topping_5.png",
	GAMEDATA_DIR "images/topping_6.png",
	GAMEDATA_DIR "images/topping_7.png",
	GAMEDATA_DIR "images/topping_8.png",
	GAMEDATA_DIR "images/topping_9.png",
	GAMEDATA_DIR "images/topping_10.png",
	GAMEDATA_DIR "images/topping_11.png",
	
	GAMEDATA_DIR "images/candy_topping_1.png",
	GAMEDATA_DIR "images/candy_topping_2.png",
	GAMEDATA_DIR "images/candy_topping_3.png",
	GAMEDATA_DIR "images/candy_topping_4.png",
	GAMEDATA_DIR "images/candy_topping_5.png",
	GAMEDATA_DIR "images/candy_topping_6.png",
	GAMEDATA_DIR "images/candy_topping_7.png",
	GAMEDATA_DIR "images/candy_topping_8.png",
	GAMEDATA_DIR "images/candy_topping_9.png",
	GAMEDATA_DIR "images/candy_topping_10.png",
	GAMEDATA_DIR "images/candy_topping_11.png",
	
	GAMEDATA_DIR "images/checked.png"
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
	SPRINKLES,
	
	TOPPING_1,
	TOPPING_2,
	TOPPING_3,
	TOPPING_4,
	TOPPING_5,
	TOPPING_6,
	TOPPING_7,
	TOPPING_8
};

/* Estructuras */
typedef struct {
	int x, y;
	int sauce_placed;
	int cheese_placed;
	int topping[4];
	
	int sauce_requested;
	int topping_requested[4];
} Pizza;

typedef struct {
	int x, y;
	int frame;
	int rand;
	int type;
} Splat;

typedef struct {
	int x, y;
	int type;
	int frame;
} Topping;

/* Prototipos de función */
int game_loop (int candy_mode);
void setup (void);
SDL_Surface * set_video_mode(unsigned);
void place_pizza_and_order (Pizza *, int, int *, int *);

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
	SDL_Rect rect, rect2;
	
	int handposx2, handposx1, handposx, handposy2, handposy1, handposy; /* Para calcular los desplazamientos del mouse */
	int mousedown;
	
	Pizza pizza;
	Splat splats[300];
	Topping toppings[20];
	int topping_count = 0;
	int splat_queue_start = 0, splat_queue_end = 0;
	int g, h, i;
	int pizzaspeed, speedboost, handicap = 0, conveyorbelt = 0;
	int image;
	int sauce_state, sauce_timer;
	int hand;
	Uint8 alpha, rgb_r, rgb_g, rgb_b;
	Uint32 *pixel;
	int midleft, left, midright, right, top, bottom;
	int hand_frame, pizza_overflow = -1, perfect_pizza;
	int pizzas_hechas = 0, orden, pizzas_consecutivas;
	
	SDL_Surface *splat_surface, *splat_surface2;
	
	sauce_state = NONE;
	
	splat_surface = SDL_AllocSurface (SDL_SWSURFACE, images[IMG_PIZZA_BASE_1]->w, images[IMG_PIZZA_BASE_1]->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	splat_surface2 = SDL_AllocSurface (SDL_SWSURFACE, images[IMG_PIZZA_BASE_1]->w, images[IMG_PIZZA_BASE_1]->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_SetAlpha (images[IMG_SPLAT_MASK], 0, 0);
	
	SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
	
	SDL_GetMouseState (&handposx, &handposy);
	
	handposx2 = handposx1 = handposx;
	handposy2 = handposy1 = handposy;
	
	mousedown = FALSE;
	
	pizza.y = 293;
	pizza.x = -366;
	pizza.sauce_placed = pizza.cheese_placed = NONE;
	pizza.topping[0] = pizza.topping[1] = pizza.topping[2] = pizza.topping[3] = 0;
	place_pizza_and_order (&pizza, candy_mode, &pizzas_hechas, &orden);
	speedboost = 0;
	pizzas_consecutivas = 0;
	
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
							sauce_timer = hand_frame = 0;
						} else if (event.button.x >= 101 && event.button.x < 161 && event.button.y >= 144 && event.button.y < 267) {
							hand = (candy_mode ? SAUCE_PINK : SAUCE_HOT);
							mousedown = TRUE;
							sauce_state = SAUCE_HOT;
							sauce_timer = hand_frame = 0;
						} else if (event.button.x >= 184 && event.button.x < 348 && event.button.y >= 214 && event.button.y < 274) {
							hand = (candy_mode ? SPRINKLES : CHEESE);
							mousedown = TRUE;
						} else if (event.button.x >= 349 && event.button.x < 451 && event.button.y >= 207 && event.button.y < 274) {
							hand = (candy_mode ? TOPPING_5 : TOPPING_1);
							hand_frame = RANDOM(3);
							mousedown = TRUE;
						} else if (event.button.x >= 451 && event.button.x < 553 && event.button.y >= 207 && event.button.y < 274) {
							hand = (candy_mode ? TOPPING_6 : TOPPING_2);
							hand_frame = RANDOM(3);
							mousedown = TRUE;
						} else if (event.button.x >= 553 && event.button.x < 655 && event.button.y >= 207 && event.button.y < 274) {
							hand = (candy_mode ? TOPPING_7 : TOPPING_3);
							hand_frame = RANDOM(3);
							mousedown = TRUE;
						} else if (event.button.x >= 655 && event.button.x < 757 && event.button.y >= 207 && event.button.y < 274) {
							hand = (candy_mode ? TOPPING_8 : TOPPING_4);
							hand_frame = RANDOM(3);
							mousedown = TRUE;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						mousedown = FALSE;
						
						if ((hand == SPRINKLES || hand == CHEESE) && (handposy >= pizza.y && handposy < pizza.y + images[IMG_PIZZA_BASE_1]->h && handposx >= pizza.x && handposx < pizza.x + images[IMG_PIZZA_BASE_1]->w)) {
							pixel = images[IMG_PIZZA_BASE_1]->pixels + ((handposy - pizza.y) * images[IMG_PIZZA_BASE_1]->pitch) + ((handposx - pizza.x) * images[IMG_PIZZA_BASE_1]->format->BytesPerPixel);
							
							SDL_GetRGBA (*pixel, images[IMG_PIZZA_BASE_1]->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
							if (alpha != 0) {
								pizza.cheese_placed = hand;
							}
						} else if ((hand >= TOPPING_1 && hand <= TOPPING_8) && (handposy >= pizza.y && handposy < pizza.y + images[IMG_PIZZA_BASE_1]->h && handposx >= pizza.x && handposx < pizza.x + images[IMG_PIZZA_BASE_1]->w)) {
							toppings[topping_count].type = hand - TOPPING_1;
							toppings[topping_count].frame = hand_frame;
							image = IMG_TOPPING_1_1 + (hand - TOPPING_1) * 3 + hand_frame;
							toppings[topping_count].x = handposx - (images[image]->w / 2) - pizza.x;
							toppings[topping_count].y = handposy - (images[image]->h / 2) - pizza.y;
							
							pixel = images[IMG_PIZZA_BASE_1]->pixels + ((handposy - pizza.y) * images[IMG_PIZZA_BASE_1]->pitch) + ((handposx - pizza.x) * images[IMG_PIZZA_BASE_1]->format->BytesPerPixel);
							
							SDL_GetRGBA (*pixel, images[IMG_PIZZA_BASE_1]->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
							if (alpha != 0) {
								topping_count++;
								pizza.topping[(hand - TOPPING_1) % 4]++;
							}
							hand = NONE;
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
		
		perfect_pizza = TRUE;
		//printf ("Pizza = {%i, %i, %i, %i}, Requested = {%i, %i, %i, %i}\n", pizza.topping[0], pizza.topping[1], pizza.topping[2], pizza.topping[3], pizza.topping_requested[0], pizza.topping_requested[1], pizza.topping_requested[2], pizza.topping_requested[3]);
		for (g = 0; g < 4; g++) {
			if (pizza.topping_requested[g] == 0 && pizza.topping[g] > 0) {
				perfect_pizza = FALSE;
				speedboost++;
			} else if (pizza.topping_requested[g] > pizza.topping[g]) {
				perfect_pizza = FALSE;
			}
		}
		
		if (pizza.cheese_placed == NONE || pizza.sauce_requested != pizza.sauce_placed) {
			perfect_pizza = FALSE;
		}
		
		if (perfect_pizza) {
			speedboost++;
		}
		
		SDL_BlitSurface (images[IMG_BACKGROUND], NULL, screen, NULL);
		
		/* Borrar la vieja pizza de la comanda */
		rect.x = 401;
		rect.y = 51;
		rect.w = images[IMG_ORDER_PIZZA_CHEESE]->w;
		rect.h = images[IMG_ORDER_PIZZA_CHEESE]->h;
		
		image = pizza.sauce_requested - SAUCE_NORMAL + IMG_ORDER_PIZZA_CHEESE;
		SDL_BlitSurface (images[image], NULL, screen, &rect);
		
		rect.x = 391;
		rect.y = 106;
		rect.w = images[IMG_ORDER_TOPPING_1]->w;
		rect.h = images[IMG_ORDER_TOPPING_1]->h;
		
		image = IMG_ORDER_TOPPING_1 + (orden / 2) - 1;
		if (candy_mode) image += 11;
		
		if (orden > 1) {
			SDL_BlitSurface (images[image], NULL, screen, &rect);
		}
		
		/* Dibujar las palomitas */
		if (pizza.cheese_placed != NONE) {
			rect.x = 524;
			rect.y = 50;
			rect.w = images[IMG_CHECKED]->w;
			rect.h = images[IMG_CHECKED]->h;
			
			SDL_BlitSurface (images[IMG_CHECKED], NULL, screen, &rect);
		}
		
		if (pizza.sauce_placed == pizza.sauce_requested) {
			rect.x = 524;
			rect.y = 72;
			rect.w = images[IMG_CHECKED]->w;
			rect.h = images[IMG_CHECKED]->h;
			
			SDL_BlitSurface (images[IMG_CHECKED], NULL, screen, &rect);
		}
		
		/* Dibujar las salsas */
		rect.x = 11;
		rect.y = 225;
		rect.w = images[IMG_INGREDIENTS_BASE_SAUCE]->w;
		rect.h = images[IMG_INGREDIENTS_BASE_SAUCE]->h;
		
		SDL_BlitSurface (images[IMG_INGREDIENTS_BASE_SAUCE], NULL, screen, &rect);
		
		/* Dibujar las salsas, según su estado */
		rect.x = 12;
		rect.w = 158;
		rect.y = 0;
		rect.h = 272;
		SDL_SetClipRect (screen, &rect);
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
		
		SDL_SetClipRect (screen, NULL);
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
		
		/* Dibujar las cajas de ingredientes */
		if (candy_mode) {
			rect.x = 349;
			rect.y = 273 - images[IMG_TOPPING_5_BOX]->h;
			rect.w = images[IMG_TOPPING_5_BOX]->w;
			rect.h = images[IMG_TOPPING_5_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_5_BOX], NULL, screen, &rect);
			
			rect.x = 451;
			rect.y = 273 - images[IMG_TOPPING_6_BOX]->h;
			rect.w = images[IMG_TOPPING_6_BOX]->w;
			rect.h = images[IMG_TOPPING_6_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_6_BOX], NULL, screen, &rect);
			
			rect.x = 553;
			rect.y = 273 - images[IMG_TOPPING_7_BOX]->h;
			rect.w = images[IMG_TOPPING_7_BOX]->w;
			rect.h = images[IMG_TOPPING_7_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_7_BOX], NULL, screen, &rect);
			
			rect.x = 655;
			rect.y = 273 - images[IMG_TOPPING_8_BOX]->h;
			rect.w = images[IMG_TOPPING_8_BOX]->w;
			rect.h = images[IMG_TOPPING_8_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_8_BOX], NULL, screen, &rect);
		} else {
			rect.x = 349;
			rect.y = 273 - images[IMG_TOPPING_1_BOX]->h;
			rect.w = images[IMG_TOPPING_1_BOX]->w;
			rect.h = images[IMG_TOPPING_1_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_1_BOX], NULL, screen, &rect);
			
			rect.x = 451;
			rect.y = 273 - images[IMG_TOPPING_2_BOX]->h;
			rect.w = images[IMG_TOPPING_2_BOX]->w;
			rect.h = images[IMG_TOPPING_2_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_2_BOX], NULL, screen, &rect);
			
			rect.x = 553;
			rect.y = 273 - images[IMG_TOPPING_3_BOX]->h;
			rect.w = images[IMG_TOPPING_3_BOX]->w;
			rect.h = images[IMG_TOPPING_3_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_3_BOX], NULL, screen, &rect);
			
			rect.x = 655;
			rect.y = 273 - images[IMG_TOPPING_4_BOX]->h;
			rect.w = images[IMG_TOPPING_4_BOX]->w;
			rect.h = images[IMG_TOPPING_4_BOX]->h;
			
			SDL_BlitSurface (images[IMG_TOPPING_4_BOX], NULL, screen, &rect);
		}
		
		if (hand >= SAUCE_NORMAL && hand <= SAUCE_PINK && mousedown && (handposy + 100 >= pizza.y && handposy + 100 < pizza.y + images[IMG_PIZZA_BASE_1]->h && handposx >= pizza.x && handposx < pizza.x + images[IMG_PIZZA_BASE_1]->w)) {
			if (pizza.sauce_placed != hand) {
				if (splat_queue_start != splat_queue_end) {
					/* Revisar si el splat que hay es de otra salsa */
					if (splats[splat_queue_start].type != hand) {
						splat_queue_start = splat_queue_end = 0;
						pizza.sauce_placed = NONE;
					}
				}
			}
			/* Si está lleno, eliminar el primer splat */
			if (splat_queue_start == (splat_queue_end + 1) % 300) {
				splat_queue_start = (splat_queue_start + 1) % 300;
			}
			
			image = IMG_SPLAT_SAUCE + (hand - SAUCE_NORMAL);
			splats[splat_queue_end].x = handposx - (images[image]->w / 20) - pizza.x;
			splats[splat_queue_end].y = handposy + 100 - (images[image]->h / 8) - pizza.y;
			splats[splat_queue_end].frame = 0;
			splats[splat_queue_end].rand = RANDOM (4);
			
			splats[splat_queue_end].type = hand;
			
			splat_queue_end = (splat_queue_end + 1) % 300;
		}
		
		/* Calcular la cantidad de splats */
		if (splat_queue_end < splat_queue_start) {
			image = splat_queue_end + 300 - splat_queue_start;
		} else {
			image = splat_queue_end - splat_queue_start;
		}
		
		/* Si la cantidad de splats se desborda, acelerar la pizza */
		if (image > 190) {
			pizzaspeed++;
			if (pizza_overflow < 0) {
				pizza_overflow = 0;
			}
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
		
			/* Dibujar los splats */
			if (pizza.sauce_placed == NONE && splat_queue_end != splat_queue_start) {
				image = IMG_SPLAT_SAUCE + (splats[splat_queue_start].type - SAUCE_NORMAL);
				SDL_BlitSurface (images[IMG_SPLAT_MASK], NULL, splat_surface, NULL);
				SDL_BlitSurface (images[IMG_PIZZA_BASE_1 + pizza.sauce_placed], NULL, splat_surface, NULL);
				
				SDL_FillRect (splat_surface2, NULL, SDL_MapRGBA (splat_surface2->format, 0, 0, 0, SDL_ALPHA_OPAQUE));
				
				rect.w = images[image]->w;
				rect.h = images[image]->h;
				for (g = splat_queue_start; g != splat_queue_end; g = (g + 1) % 300) {
					rect2.h = images[image]->h / 4;
					rect2.w = images[image]->w / 10;
					rect2.x = splats[g].frame * rect2.w;
					rect2.y = splats[g].rand * rect2.h;
					
					h = rect.x = splats[g].x;
					i = rect.y = splats[g].y;
					
					SDL_BlitSurface (images[image], &rect2, splat_surface, &rect);
					rect.x = h;
					rect.y = i;
					SDL_BlitSurface (images[image], &rect2, splat_surface2, &rect);
					
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
			
			/* Si la pizza no ha explotado, dibujar sus ingredientes */
			if (pizza_overflow < 6) {
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
			
				for (g = 0; g < topping_count; g++) {
					image = IMG_TOPPING_1_1 + (toppings[g].type * 3) + toppings[g].frame;
					rect.x = pizza.x + toppings[g].x;
					rect.y = pizza.y + toppings[g].y;
					rect.w = images[image]->w;
					rect.h = images[image]->h;
				
					SDL_BlitSurface (images[image], NULL, screen, &rect);
				}
			}
			
			if (splat_queue_end < splat_queue_start) {
				image = splat_queue_end + 300 - splat_queue_start;
			} else {
				image = splat_queue_end - splat_queue_start;
			}
			
			if (image > 190 && pizza.sauce_placed != NONE) {
				rect.x = pizza.x - 40;
				rect.y = pizza.y - 15;
				rect.w = images[IMG_PIZZA_OVERFLOW_SAUCE_1]->w;
				rect.h = images[IMG_PIZZA_OVERFLOW_SAUCE_1]->h;
				
				image = IMG_PIZZA_OVERFLOW_SAUCE_1 + (pizza.sauce_placed - SAUCE_NORMAL) * 7 + pizza_overflow;
				SDL_BlitSurface (images[image], NULL, screen, &rect);
				
				if (pizza_overflow < 6) {
					pizza_overflow++;
				}
			}
		} else {
			if (perfect_pizza) {
				/* En caso contrario, acomodar una nueva pizza y una nueva orden */
				place_pizza_and_order (&pizza, candy_mode, &pizzas_hechas, &orden);
				pizzas_hechas++;
				pizzas_consecutivas++;
				handicap++;
			} else {
				pizzas_consecutivas = 0;
				handicap--;
			}
			pizza.y = 293;
			pizza.x = -366;
			pizza.sauce_placed = pizza.cheese_placed = NONE;
			pizza.topping[0] = pizza.topping[1] = pizza.topping[2] = pizza.topping[3] = 0;
			splat_queue_start = splat_queue_end = 0;
			speedboost = 0;
			topping_count = 0;
			pizza_overflow = -1;
		}
		
		if (mousedown) {
			if (hand >= SAUCE_NORMAL && hand <= SAUCE_PINK) {
				if (hand == SAUCE_HOT) {
					rect.x = handposx - 34;
					rect.y = handposy - 54;
					image = IMG_HOT_SQUASH_1;
				} else {
					rect.x = handposx - 45;
					if (hand == SAUCE_NORMAL) {
						rect.y = handposy - 50;
						image = IMG_SAUCE_SQUASH_1;
					} else if (hand == SAUCE_CHOCOLATE) {
						rect.y = handposy - 38;
						image = IMG_CHOCO_SQUASH_1;
					} else {
						rect.y = handposy - 126;
						image = IMG_PINK_SQUASH_1;
					}
				}
			
				//rect.y = handposy - images[image]->h + 100;
				rect.w = images[image]->w;
				rect.h = images[image]->h;
			
				SDL_BlitSurface (images[image + hand_frame], NULL, screen, &rect);
			
				hand_frame++;
				if (hand == SAUCE_HOT && hand_frame >= 8) {
					hand_frame = 0;
				} else if (hand_frame >= 6) {
					hand_frame = 0;
				}
			} else if (hand == CHEESE) {
				rect.x = handposx - 97;
				rect.y = handposy - 57;
				rect.w = images[IMG_CHEESE_HAND]->w;
				rect.h = images[IMG_CHEESE_HAND]->h;
			
				SDL_BlitSurface (images[IMG_CHEESE_HAND], NULL, screen, &rect);
			} else if (hand == SPRINKLES) {
				rect.x = handposx - 14;
				rect.y = handposy - 14;
				rect.w = images[IMG_SPRINKLES_HAND]->w;
				rect.h = images[IMG_SPRINKLES_HAND]->h;
			
				SDL_BlitSurface (images[IMG_SPRINKLES_HAND], NULL, screen, &rect);
			} else if (hand >= TOPPING_1 && hand <= TOPPING_8) {
				image = IMG_HAND_TOPPING_1_1 + ((hand - TOPPING_1) * 3) + hand_frame;
				rect.x = handposx - images[image]->w / 2;
				rect.y = handposy - images[image]->h / 2;
				rect.w = images[image]->w;
				rect.h = images[image]->h;
				
				SDL_BlitSurface (images[image], NULL, screen, &rect);
			}
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

void place_pizza_and_order (Pizza *p, int candy_mode, int *pizzas_hechas, int *orden) {
	int posibles;
	
	if (candy_mode) {
		posibles = 24;
	} else {
		posibles = *pizzas_hechas + 1;
		if (posibles > 24) posibles = 24;
	}
	
	p->topping_requested[0] = p->topping_requested[1] = p->topping_requested[2] = p->topping_requested[3] = 0;
	
	printf ("Posibles combinaciones: %i\n", posibles);
	*orden = ((int) (((float) posibles) * rand () / (RAND_MAX + 1.0)));
	printf ("Orden: %i\n", *orden);
	
	p->sauce_requested = candy_mode ? SAUCE_CHOCOLATE : SAUCE_NORMAL;
	
	if (*orden % 2 == 1) {
		p->sauce_requested = candy_mode ? SAUCE_PINK : SAUCE_HOT;
	}
	
	printf ("Salsa: %i, SAUCE_NORMAL = %i\n", p->sauce_requested, SAUCE_NORMAL);
	switch (*orden) {
		case 2:
		case 3:
			p->topping_requested[0] = 5;
			break;
		case 4:
		case 5:
			p->topping_requested[1] = 5;
			break;
		case 6:
		case 7:
			p->topping_requested[2] = 5;
			break;
		case 8:
		case 9:
			p->topping_requested[3] = 5;
			break;
		case 10:
		case 11:
			p->topping_requested[0] = p->topping_requested[1] = 2;
			break;
		case 12:
		case 13:
			p->topping_requested[2] = p->topping_requested[3] = 2;
			break;
		case 14:
		case 15:
			p->topping_requested[0] = p->topping_requested[2] = 2;
			break;
		case 16:
		case 17:
			p->topping_requested[1] = p->topping_requested[3] = 2;
			break;
		case 18:
		case 19:
			p->topping_requested[0] = p->topping_requested[3] = 2;
			break;
		case 20:
		case 21:
			p->topping_requested[1] = p->topping_requested[2] = 2;
			break;
		case 22:
		case 23:
			p->topping_requested[0] = p->topping_requested[1] = p->topping_requested[2] = p->topping_requested[3] = 1;
			break;
	}
	
	printf ("Toppings_requested[4] = {%i, %i, %i, %i};\n", p->topping_requested[0], p->topping_requested[1], p->topping_requested[2], p->topping_requested[3]);
}

