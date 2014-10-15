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
	
	IMG_PIZZA_CANDY,
	IMG_PIZZA_CHEESE,
	
	IMG_PIZZA_SHADOW,
	
	IMG_SPLAT_MASK,
	
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
	
	GAMEDATA_DIR "images/pizza_candy.png",
	GAMEDATA_DIR "images/pizza_cheese.png",
	GAMEDATA_DIR "images/pizza_shadow.png",
	
	GAMEDATA_DIR "images/splat_mask.png",
	
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
	GAMEDATA_DIR "images/splat_choco_40.png"
};

/* TODO: Listar aquí los automátas */

/* Codigos de salida */
enum {
	GAME_NONE = 0, /* No usado */
	GAME_CONTINUE,
	GAME_QUIT
};

/* Listar las salas */
enum {
	SAUCE_NONE = 0,
	SAUCE_NORMAL,
	SAUCE_HOT,
	SAUCE_CHOCOLATE,
	SAUCE_PINK
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
int game_loop (void);
void setup (void);
SDL_Surface * set_video_mode(unsigned);
void place_pizza_and_order (Pizza *p);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * images [NUM_IMAGES];

int main (int argc, char *argv[]) {
	
	setup ();
	
	do {
		if (game_loop () == GAME_QUIT) break;
	} while (1 == 0);
	
	SDL_Quit ();
	return EXIT_SUCCESS;
}

int game_loop (void) {
	int done = 0;
	SDL_Event event;
	SDLKey key;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	
	int handposx2, handposx1, handposx, handposy2, handposy1, handposy; /* Para calcular los desplazamientos del mouse */
	int mousedown;
	
	Pizza pizza;
	Splat splats[300];
	int num_splats = 0;
	int g;
	int pizzaspeed = 1, conveyorbelt = 0;
	int image, splat_image;
	
	SDL_Surface *splat_surface;
	
	splat_surface = SDL_AllocSurface (SDL_SWSURFACE, images[IMG_PIZZA_BASE_1]->w, images[IMG_PIZZA_BASE_1]->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_SetAlpha (images[IMG_SPLAT_MASK], 0, 0);
	SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
	
	SDL_GetMouseState (&handposx, &handposy);
	
	handposx2 = handposx1 = handposx;
	handposy2 = handposy1 = handposy;
	
	mousedown = FALSE;
	
	place_pizza_and_order (&pizza);
	
	do {
		last_time = SDL_GetTicks ();
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) mousedown = TRUE;
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) mousedown = FALSE;
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
		
		/* Dibujar la cinta de pizzas que se mueve */
		rect.w = images[IMG_CONVEYORBELT]->w;
		rect.h = images[IMG_CONVEYORBELT]->h;
		rect.y = 293;
		conveyorbelt = conveyorbelt + pizzaspeed;
		if (conveyorbelt >= 100) {
			conveyorbelt = 0;
		}
		
		for (g = 750; g > -250; g = g - 100) {
			rect.x = g + conveyorbelt;
			
			SDL_BlitSurface (images[IMG_CONVEYORBELT], NULL, screen, &rect);
		}
		
		if (pizza.x < 900) {
			/* Pizza en escena, recoger ingredientes y dibujar */
			pizza.x += pizzaspeed;
			rect.x = pizza.x;
			rect.y = pizza.y;
			rect.w = images[IMG_PIZZA_BASE_1]->w;
			rect.h = images[IMG_PIZZA_BASE_1]->h;
			SDL_BlitSurface (images[IMG_PIZZA_BASE_1], NULL, screen, &rect);
		
			if (mousedown && (handposy >= pizza.y && handposy < pizza.y + images[IMG_PIZZA_BASE_1]->h && handposx >= pizza.x && handposx < pizza.x + images[IMG_PIZZA_BASE_1]->w)) {
				/* if (!not sauce placed) { */
				/* FIXME: Eliminar la otra salsa */
				splats[num_splats].x = handposx - 31 - pizza.x;
				splats[num_splats].y = handposy - 36 - pizza.y;
				splats[num_splats].frame = 0;
				splats[num_splats].rand = RANDOM (4);
				splats[num_splats].type = SAUCE_CHOCOLATE;
			
				num_splats++;
			}
		
			if (num_splats > 0) {
				if (splats[0].type == SAUCE_CHOCOLATE) {
					image = IMG_SPLAT_CHOCO_1;
				}
				SDL_BlitSurface (images[IMG_SPLAT_MASK], NULL, splat_surface, NULL);
				SDL_BlitSurface (images[IMG_PIZZA_BASE_1], NULL, splat_surface, NULL);
			
				rect.w = images[image]->w;
				rect.h = images[image]->h;
				for (g = 0; g < num_splats; g++) {
					splat_image = image + (splats[g].rand * 10) + splats[g].frame;
					rect.x = splats[g].x;
					rect.y = splats[g].y;
				
					SDL_BlitSurface (images[splat_image], NULL, splat_surface, &rect);
				
					if (splats[g].frame < 9) {
						splats[g].frame++;
					}
				}
			
				rect.x = pizza.x;
				rect.y = pizza.y;
				rect.w = splat_surface->w;
				rect.h = splat_surface->h;
				SDL_BlitSurface (splat_surface, NULL, screen, &rect);
			}
		
			rect.x = pizza.x;
			rect.y = pizza.y;
			rect.w = images[IMG_PIZZA_SHADOW]->w;
			rect.h = images[IMG_PIZZA_SHADOW]->h;
			SDL_BlitSurface (images[IMG_PIZZA_SHADOW], NULL, screen, &rect);
		} else {
			/* En caso contrario, acomodar una nueva pizza y una nueva orden */
			place_pizza_and_order (&pizza);
		}
		
		SDL_Flip (screen);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
		
	} while (!done);
	
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
	p->sauce_placed = p->cheese_placed = FALSE;
	
	p->topping[0] = p->topping[1] = p->topping[2] = p->topping[3] = 0;
}

