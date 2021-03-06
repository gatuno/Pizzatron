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
#include <unistd.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <locale.h>
#include "gettext.h"
#define _(string) gettext (string)

#include "cp-button.h"

#include "cpstamp.h"
#include "rotar.h"
#include "draw-text.h"

#include "path.h"

#define FPS (1000/24)

#define SWAP(a, b, t) ((t) = (a), (a) = (b), (b) = (t))
#define RANDOM(x) ((int) (x ## .0 * rand () / (RAND_MAX + 1.0)))

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#else
#define RMASK 0x000000ff
#define GMASK 0x0000ff00
#define BMASK 0x00ff0000
#define AMASK 0xff000000
#endif

/* Enumerar las imágenes */
enum {
	IMG_BACKGROUND,
	
	IMG_CONVEYORBELT,
	
	IMG_PIZZA_BASE_CLEAR,
	IMG_PIZZA_BASE,
	
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
	
	IMG_PIZZA_OVERFLOW_SAUCE,
	IMG_PIZZA_OVERFLOW_HOT,
	IMG_PIZZA_OVERFLOW_CHOCO,
	IMG_PIZZA_OVERFLOW_PINK,
	
	IMG_ORDER_PIZZA,
	
	IMG_ORDER_TOPPING,
	IMG_ORDER_TOPPING_CANDY,
	
	IMG_CHECKED,
	IMG_DONE,
	
	IMG_CHEESE_DROPPED,
	IMG_SPRINKLES_DROPPED,
	
	IMG_TOPPING_1_1_DROPPED,
	IMG_TOPPING_1_2_DROPPED,
	IMG_TOPPING_1_3_DROPPED,
	IMG_TOPPING_2_1_DROPPED,
	IMG_TOPPING_2_2_DROPPED,
	IMG_TOPPING_2_3_DROPPED,
	IMG_TOPPING_3_1_DROPPED,
	IMG_TOPPING_3_2_DROPPED,
	IMG_TOPPING_3_3_DROPPED,
	IMG_TOPPING_4_1_DROPPED,
	IMG_TOPPING_4_2_DROPPED,
	IMG_TOPPING_4_3_DROPPED,
	IMG_TOPPING_5_1_DROPPED,
	IMG_TOPPING_5_2_DROPPED,
	IMG_TOPPING_5_3_DROPPED,
	IMG_TOPPING_6_1_DROPPED,
	IMG_TOPPING_6_2_DROPPED,
	IMG_TOPPING_6_3_DROPPED,
	IMG_TOPPING_7_1_DROPPED,
	IMG_TOPPING_7_2_DROPPED,
	IMG_TOPPING_7_3_DROPPED,
	IMG_TOPPING_8_1_DROPPED,
	IMG_TOPPING_8_2_DROPPED,
	IMG_TOPPING_8_3_DROPPED,
	
	IMG_BUTTON_CLOSE_UP,
	IMG_BUTTON_CLOSE_OVER,
	IMG_BUTTON_CLOSE_DOWN,
	
	IMG_BUTTON_1_UP,
	IMG_BUTTON_1_OVER,
	IMG_BUTTON_1_DOWN,
	
	IMG_BUTTON_2_UP,
	IMG_BUTTON_2_OVER,
	IMG_BUTTON_2_DOWN,
	
	IMG_BUTTON_3_UP,
	IMG_BUTTON_3_OVER,
	IMG_BUTTON_3_DOWN,
	
	IMG_ENDING_1,
	IMG_ENDING_2,
	IMG_ENDING_3,
	IMG_ENDING_4,
	
	NUM_IMAGES
};

const char *images_names[NUM_IMAGES] = {
	"images/background.png",
	"images/conveyorbelt.png",
	
	"images/pizza_base_clear.png",
	"images/pizza_base.png",
	
	"images/pizza_cheese.png",
	"images/pizza_sprinkles.png",
	"images/pizza_shadow.png",
	
	"images/splat_mask.png",
	
	"images/base_sauces.png",
	"images/holder_a_1.png",
	"images/holder_a_2.png",
	"images/holder_a_3.png",
	"images/holder_b.png",
	"images/sauce.png",
	"images/hot_sauce.png",
	"images/chocolate.png",
	"images/pink_icing.png",
	
	"images/cheese_box.png",
	"images/sprinkle_box.png",
	"images/topping_1_box.png",
	"images/topping_2_box.png",
	"images/topping_3_box.png",
	"images/topping_4_box.png",
	"images/topping_5_box.png",
	"images/topping_6_box.png",
	"images/topping_7_box.png",
	"images/topping_8_box.png",
	
	"images/splat_sauce.png",
	"images/splat_hot.png",
	"images/splat_choco.png",
	"images/splat_pink.png",
	
	"images/sauce_squash_01.png",
	"images/sauce_squash_02.png",
	"images/sauce_squash_03.png",
	"images/sauce_squash_04.png",
	"images/sauce_squash_05.png",
	"images/sauce_squash_06.png",
	"images/hot_sauce_squash_01.png",
	"images/hot_sauce_squash_02.png",
	"images/hot_sauce_squash_03.png",
	"images/hot_sauce_squash_04.png",
	"images/hot_sauce_squash_05.png",
	"images/hot_sauce_squash_06.png",
	"images/hot_sauce_squash_07.png",
	"images/hot_sauce_squash_08.png",
	"images/chocolate_squash_01.png",
	"images/chocolate_squash_02.png",
	"images/chocolate_squash_03.png",
	"images/chocolate_squash_04.png",
	"images/chocolate_squash_05.png",
	"images/chocolate_squash_06.png",
	"images/pink_icing_squash_01.png",
	"images/pink_icing_squash_02.png",
	"images/pink_icing_squash_03.png",
	"images/pink_icing_squash_04.png",
	"images/pink_icing_squash_05.png",
	"images/pink_icing_squash_06.png",
	
	"images/cheese_hand.png",
	"images/sprinkles_hand.png",
	
	"images/hand_topping_1_1.png",
	"images/hand_topping_1_2.png",
	"images/hand_topping_1_3.png",
	"images/hand_topping_2_1.png",
	"images/hand_topping_2_2.png",
	"images/hand_topping_2_3.png",
	"images/hand_topping_3_1.png",
	"images/hand_topping_3_2.png",
	"images/hand_topping_3_3.png",
	"images/hand_topping_4_1.png",
	"images/hand_topping_4_2.png",
	"images/hand_topping_4_3.png",
	"images/hand_topping_5_1.png",
	"images/hand_topping_5_2.png",
	"images/hand_topping_5_3.png",
	"images/hand_topping_6_1.png",
	"images/hand_topping_6_2.png",
	"images/hand_topping_6_3.png",
	"images/hand_topping_7_1.png",
	"images/hand_topping_7_2.png",
	"images/hand_topping_7_3.png",
	"images/hand_topping_8_1.png",
	"images/hand_topping_8_2.png",
	"images/hand_topping_8_3.png",
	"images/topping_1_1.png",
	"images/topping_1_2.png",
	"images/topping_1_3.png",
	"images/topping_2_1.png",
	"images/topping_2_2.png",
	"images/topping_2_3.png",
	"images/topping_3_1.png",
	"images/topping_3_2.png",
	"images/topping_3_3.png",
	"images/topping_4_1.png",
	"images/topping_4_2.png",
	"images/topping_4_3.png",
	"images/topping_5_1.png",
	"images/topping_5_2.png",
	"images/topping_5_3.png",
	"images/topping_6_1.png",
	"images/topping_6_2.png",
	"images/topping_6_3.png",
	"images/topping_7_1.png",
	"images/topping_7_2.png",
	"images/topping_7_3.png",
	"images/topping_8_1.png",
	"images/topping_8_2.png",
	"images/topping_8_3.png",
	
	"images/overflow_sauce.png",
	"images/overflow_hot.png",
	"images/overflow_chocolate.png",
	"images/overflow_pink.png",
	
	"images/order_pizza.png",
	
	"images/topping_order.png",
	"images/candy_topping_order.png",
	
	"images/checked.png",
	"images/done.png",
	
	"images/cheese_drop.png",
	"images/sprinkles_drop.png",
	
	"images/topping_1_1_dropped.png",
	"images/topping_1_2_dropped.png",
	"images/topping_1_3_dropped.png",
	"images/topping_2_1_dropped.png",
	"images/topping_2_2_dropped.png",
	"images/topping_2_3_dropped.png",
	"images/topping_3_1_dropped.png",
	"images/topping_3_2_dropped.png",
	"images/topping_3_3_dropped.png",
	"images/topping_4_1_dropped.png",
	"images/topping_4_2_dropped.png",
	"images/topping_4_3_dropped.png",
	"images/topping_5_1_dropped.png",
	"images/topping_5_2_dropped.png",
	"images/topping_5_3_dropped.png",
	"images/topping_6_1_dropped.png",
	"images/topping_6_2_dropped.png",
	"images/topping_6_3_dropped.png",
	"images/topping_7_1_dropped.png",
	"images/topping_7_2_dropped.png",
	"images/topping_7_3_dropped.png",
	"images/topping_8_1_dropped.png",
	"images/topping_8_2_dropped.png",
	"images/topping_8_3_dropped.png",
	
	"images/close_up.png",
	"images/close_over.png",
	"images/close_press.png",
	
	"images/boton_1_up.png",
	"images/boton_1_over.png",
	"images/boton_1_over.png",
	
	"images/boton_2_up.png",
	"images/boton_2_over.png",
	"images/boton_2_over.png",
	
	"images/boton_3_up.png",
	"images/boton_3_over.png",
	"images/boton_3_over.png",
	
	"images/ending_1.png",
	"images/ending_2.png",
	"images/ending_3.png",
	"images/ending_4.png"
};

enum {
	IMG_INTRO_NEW_BACKGROUND,
	IMG_INTRO_NEW_PENGUIN,
	IMG_INTRO_NEW_TOP,
	IMG_INTRO_NEW_CANDY,
	
	IMG_INTRO_NEW_EXPLAIN,
	
	NUM_INTRO_NEW_IMAGES
};

const char *images_intro_new_names [NUM_INTRO_NEW_IMAGES] = {
	"images/intro_new_background.png",
	"images/intro_new_penguin.png",
	"images/intro_new_top.png",
	"images/intro_new_candy_lever.png",
	
	"images/intro_new_explain.png"
};

enum {
	IMG_INTRO_OLD_BACKGROUND,
	IMG_INTRO_OLD_CANDY,
	
	NUM_INTRO_OLD_IMAGES
};

const char *images_intro_old_names [NUM_INTRO_OLD_IMAGES] = {
	"images/intro_old_background.png",
	"images/intro_old_candy_lever.png",
};

enum {
	SND_CACHING,
	SND_SAUCE,
	SND_HOTSAUCE,
	SND_TOPPING,
	SND_OVERFLOW,
	SND_THROW,
	
	SND_SAUCE_1,
	SND_SAUCE_2,
	
	NUM_SOUNDS
};

const char *sound_names[NUM_SOUNDS] = {
	"sounds/caching.wav",
	"sounds/sauce.wav",
	"sounds/hotsauce.wav",
	"sounds/topping.wav",
	"sounds/overflow.wav",
	"sounds/throw.wav",
	
	"sounds/sauce1.wav",
	"sounds/sauce2.wav",
};

#define MUS_106 "music/music_106.ogg"
#define MUS_270 "music/music_270.ogg"
#define MUS_344 "music/music_344.ogg"
#define MUS_385 "music/music_385.ogg"

/* Codigos de salida */
enum {
	GAME_NONE = 0, /* No usado */
	GAME_CONTINUE,
	GAME_QUIT
};

/* Tipos de final */
enum {
	END_LAME = 0,
	END_LOSE,
	END_WIN,
	END_PERFECT,
	
	NUM_ENDINGS
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

const SDL_Color penguin_colors[18] = {
	{0, 51, 102},
	{51, 51, 51},
	{206, 0, 0},
	{255, 204, 0},
	{0, 153, 0},
	{153, 102, 0},
	{255, 49, 156},
	{99, 0, 156},
	{0, 156, 204},
	{255, 102, 0},
	{0, 102, 0},
	{255, 99, 99},
	{139, 227, 3},
	{28, 150, 163},
	{240, 240, 216},
	{174, 159, 200},
	{128, 33, 75},
	{46, 71, 170}
};

/* Los textos */
enum {
	TEXT_PIZZAS_MADE,
	TEXT_PIZZAS_LEFT,
	TEXT_MISTAKES,
	
	TEXT_PIZZA_ORDER_1,
	TEXT_PIZZA_ORDER_2,
	TEXT_PIZZA_ORDER_3,
	TEXT_PIZZA_ORDER_4,
	TEXT_PIZZA_ORDER_5,
	TEXT_PIZZA_ORDER_6,
	TEXT_PIZZA_ORDER_7,
	TEXT_PIZZA_ORDER_8,
	TEXT_PIZZA_ORDER_9,
	TEXT_PIZZA_ORDER_10,
	TEXT_PIZZA_ORDER_11,
	TEXT_PIZZA_ORDER_12,
	TEXT_PIZZA_ORDER_13,
	TEXT_PIZZA_ORDER_14,
	TEXT_PIZZA_ORDER_15,
	TEXT_PIZZA_ORDER_16,
	TEXT_PIZZA_ORDER_17,
	TEXT_PIZZA_ORDER_18,
	TEXT_PIZZA_ORDER_19,
	TEXT_PIZZA_ORDER_20,
	TEXT_PIZZA_ORDER_21,
	TEXT_PIZZA_ORDER_22,
	TEXT_PIZZA_ORDER_23,
	TEXT_PIZZA_ORDER_24,
	
	TEXT_CHEESE_SPRINKLES,
	TEXT_SAUCE_1,
	TEXT_SAUCE_2,
	
	TEXT_5_TOPPING_1,
	TEXT_5_TOPPING_2,
	TEXT_5_TOPPING_3,
	TEXT_5_TOPPING_4,
	
	TEXT_2_TOPPING_1,
	TEXT_2_TOPPING_2,
	TEXT_2_TOPPING_3,
	TEXT_2_TOPPING_4,
	
	TEXT_1_TOPPING_1,
	TEXT_1_TOPPING_2,
	TEXT_1_TOPPING_3,
	TEXT_1_TOPPING_4,
	
	TEXT_DONE_LABEL,
	
	TEXT_5_COINS,
	TEXT_10_COINS,
	TEXT_TIP_10,
	TEXT_TIP_15,
	TEXT_TIP_20,
	TEXT_TIP_25,
	TEXT_TIP_30,
	TEXT_TIP_35,
	
	TEXT_COINS,
	
	NUM_TEXTS
};

/* Las posibles pantallas para el done screen */
enum {
	ORDER_SCREEN_NONE,
	ORDER_SCREEN_DONE,
	ORDER_SCREEN_TIP_10,
	ORDER_SCREEN_TIP_15,
	ORDER_SCREEN_TIP_20,
	ORDER_SCREEN_TIP_25,
	ORDER_SCREEN_TIP_30,
	ORDER_SCREEN_TIP_35
};

enum {
	BUTTON_NONE = 0,
	BUTTON_CLOSE,
	
	BUTTON_UI_INTRO_PLAY,
	BUTTON_UI_INTRO_HOW,
	
	BUTTON_UI_INTRO_HOW_PLAY,
	
	BUTTON_END_DONE,
	
	NUM_BUTTONS
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

typedef struct {
	int x, y;
	double speed_x, speed_y;
	int type;
	int frame;
	int rotable;
	int angulo;
} DroppedTopping;

/* Prototipos de función */
int game_loop (int *);
int game_intro_old (void);
int game_intro_new (void);
int game_intro_new_explain (SDL_Surface *play_text);
int game_end (int);
void setup (void);
void setup_texts (void);
void setup_ending (int fin);
void setup_locale_images (void);
SDL_Surface * set_video_mode(unsigned);
void place_pizza_and_order (Pizza *, int, int *, int *);
void dibujar_comanda (Pizza *, int, int, int, int, int, int);
int map_button_in_opening_old (int x, int y);
int map_button_in_opening_new (int x, int y);
int map_button_in_opening_new_how (int x, int y);
int map_button_in_game (int x, int y);
int map_button_in_finish (int x, int y);

/* Variables globales */
SDL_Surface * screen;
SDL_Surface * images [NUM_IMAGES];
SDL_Surface * images_intro_new [NUM_INTRO_NEW_IMAGES];
SDL_Surface * images_intro_old [NUM_INTRO_OLD_IMAGES];
SDL_Surface * image_background_ending;
SDL_Surface * texts [NUM_TEXTS];

int use_sound;
Mix_Chunk * sounds[NUM_SOUNDS];
Mix_Music * music;

int candy_mode;
int intro; /* Cuál de los 2 intros se va a dibujar */
int order_screen_timer;
int order_screen_done;
int pizzas_hechas = 0, score = 0, tips = 0;

SDL_RWops *ttf_burbank_bgbk, *ttf_burbank_sb, *ttf_acme;

/* La 10 y 12 se usan para renderizar los nombres de las pizzas */
/* La 12 se utiliza en la pantalla de ending */
TTF_Font *ttf10_burbank_bold, *ttf12_burbank_bold;
/* La 9 y 13 se usan para la comanda */
TTF_Font *ttf9_burbank_bold, *ttf13_burbank_bold;

/* Las acme para el intro viejo */
TTF_Font *ttf20_acme;

/* La 3 tipografias se usan para el intro nuevo */
TTF_Font *ttf18_burbank_bold, *ttf28_burbank_bold, *ttf14_burbank_small;

CPStampCategory *c;
CPStampHandle *stamp_handle;

int main (int argc, char *argv[]) {
	int fin;
	
	initSystemPaths (argv[0]);
	
	/* Inicializar l18n */
	setlocale (LC_ALL, "");
	bindtextdomain (PACKAGE, get_l10n_path ());
	
	textdomain (PACKAGE);
	
	setup ();
	stamp_handle = CPStamp_Init (argc, argv);
	
	if (use_sound) CPStamp_WithSound (stamp_handle, TRUE);
	
	/* Registrar botones */
	cp_registrar_botones (NUM_BUTTONS);
	
	cp_registrar_boton (BUTTON_CLOSE, IMG_BUTTON_CLOSE_UP);
	cp_registrar_boton (BUTTON_UI_INTRO_PLAY, IMG_BUTTON_1_UP);
	cp_registrar_boton (BUTTON_UI_INTRO_HOW, IMG_BUTTON_1_UP);
	cp_registrar_boton (BUTTON_UI_INTRO_HOW_PLAY, IMG_BUTTON_2_UP);
	cp_registrar_boton (BUTTON_END_DONE, IMG_BUTTON_3_UP);
	cp_button_start ();
	
	/* Registrar las estampas */
	c = CPStamp_Open (stamp_handle, STAMP_TYPE_GAME, gettext_noop ("Pizzatron"), "pizzatron");
	
	CPStamp_SetLocale (c, PACKAGE, get_l10n_path ());
	char buffer_file[8192];
	sprintf (buffer_file, "%simages/stamps", get_systemdata_path ());
	CPStamp_SetResourceDir (c, buffer_file);
	
	if (c == NULL) {
		printf (_("Failed to init the substamp system\n"));
	}
	
	if (!CPStamp_IsRegistered (c, 392)) {
		CPStamp_Register (c, 392, gettext_noop ("Food Fiasco"), gettext_noop ("Make a mess of the kitchen with 3 wrong pizzas"), "images/stamps/392.png", STAMP_TYPE_GAME, STAMP_EASY);
	}
	if (!CPStamp_IsRegistered (c, 394)) {
		CPStamp_Register (c, 394, gettext_noop ("Just Dessert"), gettext_noop ("Play Pizzatron in Candy Mode"), "images/stamps/394.png", STAMP_TYPE_GAME, STAMP_EASY);
	}
	if (!CPStamp_IsRegistered (c, 396)) {
		CPStamp_Register (c, 396, gettext_noop ("Chef's Hat"), gettext_noop ("Make 20 pizzas without any mistakes"), "images/stamps/396.png", STAMP_TYPE_GAME, STAMP_NORMAL);
	}
	if (!CPStamp_IsRegistered (c, 398)) {
		CPStamp_Register (c, 398, gettext_noop ("Spice Sea"), gettext_noop ("Make 3 hot sauce and shrimp pizzas to order"), "images/stamps/398.png", STAMP_TYPE_GAME, STAMP_NORMAL);
	}
	if (!CPStamp_IsRegistered (c, 400)) {
		CPStamp_Register (c, 400, gettext_noop ("Cocoa Beans"), gettext_noop ("Make 3 jellybean and chocolate pizzas to order"), "images/stamps/400.png", STAMP_TYPE_GAME, STAMP_NORMAL);
	}
	if (!CPStamp_IsRegistered (c, 402)) {
		CPStamp_Register (c, 402, gettext_noop ("Fiery Squids"), gettext_noop ("Make 3 hot sauce and squid pizzas to order"), "images/stamps/402.png", STAMP_TYPE_GAME, STAMP_HARD);
	}
	if (!CPStamp_IsRegistered (c, 404)) {
		CPStamp_Register (c, 404, gettext_noop ("Candy Land"), gettext_noop ("Make 3 pink sauce and marshmallow pizzas to order"), "images/stamps/404.png", STAMP_TYPE_GAME, STAMP_HARD);
	}
	if (!CPStamp_IsRegistered (c, 406)) {
		CPStamp_Register (c, 406, gettext_noop ("Pizza Chef"), gettext_noop ("Make 30 pizzas without any mistakes"), "images/stamps/406.png", STAMP_TYPE_GAME, STAMP_HARD);
	}
	if (!CPStamp_IsRegistered (c, 408)) {
		CPStamp_Register (c, 408, gettext_noop ("Pizza Master"), gettext_noop ("Make 40 pizzas without any mistakes"), "images/stamps/408.png", STAMP_TYPE_GAME, STAMP_EXTREME);
	}
	if (!CPStamp_IsRegistered (c, 410)) {
		CPStamp_Register (c, 410, gettext_noop ("Dessert Chef"), gettext_noop ("Make 40 candy pizzas without any mistakes"), "images/stamps/410.png", STAMP_TYPE_GAME, STAMP_EXTREME);
	}
	
	candy_mode = 0;
	fin = 0;
	do {
		/* Iniciar la música */
		if (use_sound) {
			Mix_PlayMusic (music, -1);
		}
		if (intro == 1) {
			if (game_intro_new () == GAME_QUIT) break;
		} else {
			if (game_intro_old () == GAME_QUIT) break;
		}
		setup_texts ();
		if (game_loop (&fin) == GAME_QUIT) break;
		setup_ending (fin);
		if (game_end (fin) == GAME_QUIT) break;
	} while (1 == 0);
	
	CPStamp_Close (c);
	
	SDL_Quit ();
	return EXIT_SUCCESS;
}

int game_intro_old (void) {
	int done = 0;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	SDL_Rect update_rects[6];
	int num_rects;
	int map;
	SDL_Surface *play_button_text;
	SDL_Color blanco;
	SDLKey key;
	
	blanco.r = blanco.g = blanco.b = 0xff;
	
	/* Renderizar el texto de Start */
	play_button_text = TTF_RenderUTF8_Blended (ttf20_acme, _("START"), blanco);
	
	SDL_BlitSurface (images_intro_old [IMG_INTRO_OLD_BACKGROUND], NULL, screen, NULL);
	
	TTF_CloseFont (ttf20_acme);
	SDL_RWclose (ttf_acme);
	
	/* Dibujar el boton de cierre */
	rect.x = 721; rect.y = 9;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	
	SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
	
	/* Dibujar el boton de jugar */
	rect.x = 49; rect.y = 425;
	rect.w = images [IMG_BUTTON_3_UP]->w;
	rect.h = images [IMG_BUTTON_3_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_3_UP], NULL, screen, &rect);
	
	/* Su texto */
	rect.x = 49 + 4 + (images[IMG_BUTTON_3_UP]->w - play_button_text->w) / 2;
	rect.y = 436;
	rect.w = play_button_text->w;
	rect.h = play_button_text->h;
	
	SDL_BlitSurface (play_button_text, NULL, screen, &rect);
	
	SDL_Flip (screen);
	
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEMOTION:
					map = map_button_in_opening_old (event.motion.x, event.motion.y);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button != SDL_BUTTON_LEFT) break;
					map = map_button_in_opening_old (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
						case BUTTON_UI_INTRO_PLAY:
							done = GAME_CONTINUE;
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Motor de botones primero */
					if (event.button.button != SDL_BUTTON_LEFT) break;
					
					map = map_button_in_opening_old (event.button.x, event.button.y);
					cp_button_down (map);
					
					if (candy_mode == 0 && event.button.x > 412 && event.button.x < 433 &&
					    event.button.y > 423 && event.button.y < 441) {
						candy_mode = 1;
						
						rect.x = 413;
						rect.y = 408;
						rect.w = images_intro_old [IMG_INTRO_OLD_CANDY]->w;
						rect.h = images_intro_old [IMG_INTRO_OLD_CANDY]->h;
			
						SDL_BlitSurface (images_intro_old [IMG_INTRO_OLD_CANDY], NULL, screen, &rect);
						update_rects[num_rects++] = rect;
					} else if (candy_mode == 1 && event.button.x > 528 && event.button.x < 548 &&
					    event.button.y > 429 && event.button.y < 447) {
						candy_mode = 0;
						
						rect.x = 413;
						rect.y = 408;
						rect.w = images_intro_old [IMG_INTRO_OLD_CANDY]->w;
						rect.h = images_intro_old [IMG_INTRO_OLD_CANDY]->h;
			
						SDL_BlitSurface (images_intro_old [IMG_INTRO_OLD_BACKGROUND], &rect, screen, &rect);
						update_rects[num_rects++] = rect;
					}
					break;
				case SDL_KEYDOWN:
					/* Tengo una tecla presionada */
					key = event.key.keysym.sym;
					
					if (key == SDLK_F11 || (key == SDLK_RETURN && (event.key.keysym.mod & KMOD_ALT))) {
						SDL_WM_ToggleFullScreen (screen);
					}
					if (key == SDLK_ESCAPE) {
						done = GAME_QUIT;
					}
					break;
			}
		}
		
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 721; rect.y = 9;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (images_intro_old [IMG_INTRO_OLD_BACKGROUND], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		SDL_UpdateRects (screen, num_rects, update_rects);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
	} while (!done);
	
	SDL_FreeSurface (play_button_text);
	
	return done;
}

int game_intro_new_explain (SDL_Surface *play_text) {
	int done = 0;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect, rect2, update_rects[6];
	int num_rects;
	int map;
	SDL_Surface *text;
	SDL_Color cafe, blanco, negro, azul;
	SDLKey key;
	
	negro.r = negro.b = negro.g = 0x00;
	cafe.r = 0x7b; cafe.g = 0x3f; cafe.b = 0x29;
	blanco.r = blanco.g = blanco.b = 0xFF;
	azul.r = 0x01; azul.g = 0x45; azul.b = 0x87;
	
	/* Renderizar los textos */
	text = TTF_RenderUTF8_Blended (ttf28_burbank_bold, _("ORDERS"), cafe);
	rect.x = 26;
	rect.y = 25;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf28_burbank_bold, _("ORDERS"), blanco);
	rect.x = 24;
	rect.y = 23;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf28_burbank_bold, _("SAUCES"), cafe);
	rect.x = 668 - text->w;
	rect.y = 33;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf28_burbank_bold, _("SAUCES"), blanco);
	rect.x = 666 - text->w;
	rect.y = 31;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf28_burbank_bold, _("TOPPINGS"), cafe);
	rect.x = 507 - text->w;
	rect.y = 242;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf28_burbank_bold, _("TOPPINGS"), blanco);
	rect.x = 504 - text->w;
	rect.y = 239;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	/* Texto debajo de las ordenes */
	text = draw_text (ttf14_burbank_small, _("Make pizza to\nmatch the orders\non the screen."), negro, ALIGN_LEFT, 0);
	rect.x = 24;
	rect.y = 80;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	/* Texto debajo de las salsas */
	text = draw_text (ttf14_burbank_small, _("Pick your sauce\nand spread it over\nthe entire pizza."), negro, ALIGN_LEFT, 0);
	rect.x = 560;
	rect.y = 147;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	/* Texto de los ingredientes */
	text = draw_text (ttf14_burbank_small, _("Drag toppings onto your\npizza to match the order."), negro, ALIGN_LEFT, 0);
	rect.x = 516;
	rect.y = 239;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	/* Texto de la comanda */
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("CHEESE PIZZA"), azul);
	rect.x = 163;
	rect.y = 60;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("CHEESE"), azul);
	rect.x = 260;
	rect.y = 86;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("PIZZA SAUCE"), azul);
	rect.x = 260;
	rect.y = 102;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 SHRIMP"), azul);
	rect.x = 260;
	rect.y = 132;
	rect.w = text->w;
	rect.h = text->h;
	
	SDL_BlitSurface (text, NULL, images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect);
	SDL_FreeSurface (text);
	
	/* Predibujar todo */
	SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_BACKGROUND], NULL, screen, NULL);
	
	/* Dibujar las instrucciones */
	rect.x = 16; rect.y = 16;
	rect.w = images_intro_new[IMG_INTRO_NEW_EXPLAIN]->w; rect.h = images_intro_new[IMG_INTRO_NEW_EXPLAIN]->h;
	
	SDL_BlitSurface (images_intro_new[IMG_INTRO_NEW_EXPLAIN], NULL, screen, &rect);
	
	/* Dibujar el boton de cierre */
	rect.x = 721; rect.y = 9;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_CLOSE_UP], NULL, screen, &rect);
	
	/* Dibujar el boton de "Jugar" */
	rect.x = 582; rect.y = 396;
	rect.w = images[IMG_BUTTON_2_UP]->w; rect.h = images[IMG_BUTTON_2_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_2_UP], NULL, screen, &rect);
	
	rect.x = 582 + (rect.w - play_text->w) / 2;
	rect.y = 396 + (rect.h - play_text->h) / 2;
	
	rect.w = play_text->w; rect.h = play_text->h;
	
	SDL_BlitSurface (play_text, NULL, screen, &rect);
	
	SDL_Flip (screen);
	
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEMOTION:
					map = map_button_in_opening_new_how (event.motion.x, event.motion.y);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button != SDL_BUTTON_LEFT) break;
					map = map_button_in_opening_new_how (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
						case BUTTON_UI_INTRO_HOW_PLAY:
							done = GAME_CONTINUE;
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Motor de botones primero */
					if (event.button.button != SDL_BUTTON_LEFT) break;
					
					map = map_button_in_opening_new_how (event.button.x, event.button.y);
					cp_button_down (map);
					break;
				case SDL_KEYDOWN:
					/* Tengo una tecla presionada */
					key = event.key.keysym.sym;
					
					if (key == SDLK_F11 || (key == SDLK_RETURN && (event.key.keysym.mod & KMOD_ALT))) {
						SDL_WM_ToggleFullScreen (screen);
					}
					if (key == SDLK_ESCAPE) {
						done = GAME_QUIT;
					}
					break;
			}
		}
		
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 721; rect.y = 9;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			/* Necesito doble borrado */
			/* Primero fondo */
			SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_BACKGROUND], &rect, screen, &rect);
			
			/* Luego con las instrucciones */
			rect2.x = 721 - 16;
			rect2.y = 0;
			rect2.w = images_intro_new[IMG_INTRO_NEW_EXPLAIN]->w - rect2.x;
			rect2.h = rect.w - 16 + 9;
			rect.w = rect2.w; rect.h = rect2.h;
			rect.y = 16; rect.x = 721;
			
			SDL_BlitSurface (images_intro_new[IMG_INTRO_NEW_EXPLAIN], &rect2, screen, &rect);
			
			rect.x = 721; rect.y = 9;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		if (cp_button_refresh[BUTTON_UI_INTRO_HOW_PLAY]) {
			rect.x = 582; rect.y = 396;
			rect.w = images[IMG_BUTTON_2_UP]->w; rect.h = images[IMG_BUTTON_2_UP]->h;
			
			rect2.x = 582 - 16;
			rect2.y = 396 - 16;
			rect2.w = rect.w; rect2.h = rect.h;
			SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_EXPLAIN], &rect2, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames [BUTTON_UI_INTRO_HOW_PLAY]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			
			rect.x = 582 + (rect.w - play_text->w) / 2;
			rect.y = 396 + (rect.h - play_text->h) / 2;
			
			rect.w = play_text->w; rect.h = play_text->h;
			
			SDL_BlitSurface (play_text, NULL, screen, &rect);
			cp_button_refresh[BUTTON_UI_INTRO_HOW_PLAY] = 0;
		}
		
		SDL_UpdateRects (screen, num_rects, update_rects);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
	} while (!done);
	
	return done;
}

int game_intro_new (void) {
	int done = 0;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	SDL_Rect update_rects[6];
	int num_rects;
	int map;
	SDL_Surface *play_text, *how_text;
	SDL_Color cafe;
	cafe.r = 0x54; cafe.g = 0x32; cafe.b = 0x01;
	SDLKey key;
	
	/* Renderizar el texto de los botones */
	play_text = TTF_RenderUTF8_Blended (ttf18_burbank_bold, _("PLAY"), cafe);
	how_text = TTF_RenderUTF8_Blended (ttf18_burbank_bold, _("INSTRUCTIONS"), cafe);
	
	SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_BACKGROUND], NULL, screen, NULL);
	
	/* Dibujar el boton de cierre */
	rect.x = 721; rect.y = 9;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_CLOSE_UP], NULL, screen, &rect);
	
	/* Dibujar el boton de "Jugar" */
	rect.x = 16; rect.y = 365;
	rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_1_UP], NULL, screen, &rect);
	
	rect.x = 16 + (rect.w - play_text->w) / 2;
	rect.y = 365 + (rect.h - play_text->h) / 2;
	
	rect.w = play_text->w; rect.h = play_text->h;
	
	SDL_BlitSurface (play_text, NULL, screen, &rect);
	
	/* Dibujar el botón de instrucciones */
	rect.x = 16; rect.y = 420;
	rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
	
	SDL_BlitSurface (images[IMG_BUTTON_1_UP], NULL, screen, &rect);
	
	rect.x = 16 + (rect.w - how_text->w) / 2;
	rect.y = 420 + (rect.h - how_text->h) / 2;
	
	rect.w = how_text->w; rect.h = how_text->h;
	
	SDL_BlitSurface (how_text, NULL, screen, &rect);
	
	SDL_Flip (screen);
	
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
				case SDL_MOUSEMOTION:
					map = map_button_in_opening_new (event.motion.x, event.motion.y);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button != SDL_BUTTON_LEFT) break;
					map = map_button_in_opening_new (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
						case BUTTON_UI_INTRO_PLAY:
							done = GAME_CONTINUE;
							break;
						case BUTTON_UI_INTRO_HOW:
							cp_button_motion (BUTTON_NONE);
							cp_button_refresh[BUTTON_UI_INTRO_HOW] = 0; /* Para evitar que se redibuje */
							done = game_intro_new_explain (play_text);
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Motor de botones primero */
					if (event.button.button != SDL_BUTTON_LEFT) break;
					
					map = map_button_in_opening_new (event.button.x, event.button.y);
					cp_button_down (map);
					
					if (candy_mode == 0 && event.button.x > 15 && event.button.x < 45 &&
					    event.button.y > 284 && event.button.y < 304) {
						candy_mode = 1;
						
						rect.x = 15;
						rect.y = 264;
						rect.w = images_intro_new [IMG_INTRO_NEW_CANDY]->w;
						rect.h = images_intro_new [IMG_INTRO_NEW_CANDY]->h;
			
						SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_CANDY], NULL, screen, &rect);
						update_rects[num_rects++] = rect;
					} else if (candy_mode == 1 && event.button.x > 40 && event.button.x < 57 &&
					    event.button.y > 263 && event.button.y < 294) {
						candy_mode = 0;
						
						rect.x = 15;
						rect.y = 264;
						rect.w = images_intro_new [IMG_INTRO_NEW_CANDY]->w;
						rect.h = images_intro_new [IMG_INTRO_NEW_CANDY]->h;
			
						SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_BACKGROUND], &rect, screen, &rect);
						update_rects[num_rects++] = rect;
					}
					break;
				case SDL_KEYDOWN:
					/* Tengo una tecla presionada */
					key = event.key.keysym.sym;
					
					if (key == SDLK_F11 || (key == SDLK_RETURN && (event.key.keysym.mod & KMOD_ALT))) {
						SDL_WM_ToggleFullScreen (screen);
					}
					if (key == SDLK_ESCAPE) {
						done = GAME_QUIT;
					}
					break;
			}
		}
		
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 721; rect.y = 9;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_BACKGROUND], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		if (cp_button_refresh[BUTTON_UI_INTRO_PLAY]) {
			rect.x = 16; rect.y = 365;
			rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
			
			SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_BACKGROUND], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames [BUTTON_UI_INTRO_PLAY]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			
			rect.x = 16 + (rect.w - play_text->w) / 2;
			rect.y = 365 + (rect.h - play_text->h) / 2;
	
			rect.w = play_text->w; rect.h = play_text->h;
	
			SDL_BlitSurface (play_text, NULL, screen, &rect);
			cp_button_refresh[BUTTON_UI_INTRO_PLAY] = 0;
		}
		
		if (cp_button_refresh[BUTTON_UI_INTRO_HOW]) {
			rect.x = 16; rect.y = 420;
			rect.w = images[IMG_BUTTON_1_UP]->w; rect.h = images[IMG_BUTTON_1_UP]->h;
			
			SDL_BlitSurface (images_intro_new [IMG_INTRO_NEW_BACKGROUND], &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames [BUTTON_UI_INTRO_HOW]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			
			rect.x = 16 + (rect.w - how_text->w) / 2;
			rect.y = 420 + (rect.h - how_text->h) / 2;
	
			rect.w = how_text->w; rect.h = how_text->h;
	
			SDL_BlitSurface (how_text, NULL, screen, &rect);
			cp_button_refresh[BUTTON_UI_INTRO_HOW] = 0;
		}
		
		SDL_UpdateRects (screen, num_rects, update_rects);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
	} while (!done);
	
	SDL_FreeSurface (play_text);
	SDL_FreeSurface (how_text);
	
	TTF_CloseFont (ttf18_burbank_bold);
	TTF_CloseFont (ttf28_burbank_bold);
	TTF_CloseFont (ttf14_burbank_small);
	
	return done;
}

int game_loop (int *fin) {
	int done = 0;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect, rect2;
	int map;
	SDLKey key;
	
	int handposx2, handposx1, handposx, handposy2, handposy1, handposy; /* Para calcular los desplazamientos del mouse */
	int strengthY, strengthX;
	int mousedown;
	
	Pizza pizza;
	Splat splats[300];
	Topping toppings[20];
	int topping_count = 0;
	int splat_queue_start = 0, splat_queue_end = 0;
	int g, i;
	int pizzaspeed, speedboost, handicap = 0, conveyorbelt = 0;
	int image;
	int sauce_state, sauce_timer;
	int hand = NONE;
	Uint8 alpha, rgb_r, rgb_g, rgb_b;
	Uint32 *pixel;
	int midleft, left, midright, right, top, bottom;
	int hand_frame, pizza_overflow = -1, perfect_pizza;
	int orden, pizzas_consecutivas, failures = 0, ordenes_hechas = 0;
	SDL_Surface *splat_surface, *splat_surface2, *rotated;
	
	DroppedTopping dropped_tops[20];
	int dropt_queue_start = 0, dropt_queue_end = 0;
	int lanzados[TOPPING_8 + 1];
	int no_marshmallow_pizzas = 0, no_jelly_pizzas = 0, no_squid_pizzas = 0, no_shrimp_pizzas = 0;
	
	memset (lanzados, 0, sizeof (lanzados));
	
	sauce_state = NONE;
	
	splat_surface = SDL_AllocSurface (SDL_SWSURFACE, images[IMG_PIZZA_BASE_CLEAR]->w, images[IMG_PIZZA_BASE_CLEAR]->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	splat_surface2 = SDL_AllocSurface (SDL_SWSURFACE, images[IMG_PIZZA_BASE_CLEAR]->w, images[IMG_PIZZA_BASE_CLEAR]->h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_SetAlpha (images[IMG_SPLAT_MASK], 0, 0);
	
	//SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
	
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
	
	if (candy_mode) CPStamp_Earn (stamp_handle, c, 394);
	
	do {
		last_time = SDL_GetTicks ();
		
		handposy2 = handposy1;
		handposy1 = handposy;
		
		handposx2 = handposx1;
		handposx1 = handposx;
		
		strengthY = (handposy2 - handposy + 60) / 3;
		if (strengthY > 40) {
			strengthY = 40;
		} else if (strengthY < -20) {
			strengthY = -20;
		}
		strengthX = (handposx2 - handposx) / 3;
		if (strengthX > 30) {
			strengthX = 30;
		} else if (strengthX < -30) {
			strengthX = -30;
		}
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_MOUSEMOTION:
					map = map_button_in_game (event.motion.x, event.motion.y);
					
					handposx = event.motion.x;
					handposy = event.motion.y;
					
					strengthY = (handposy2 - handposy + 60) / 3;
					if (strengthY > 40) {
						strengthY = 40;
					} else if (strengthY < -20) {
						strengthY = -20;
					}
					strengthX = (handposx2 - handposx) / 3;
					if (strengthX > 30) {
						strengthX = 30;
					} else if (strengthX < -30) {
						strengthX = -30;
					}
					
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button != SDL_BUTTON_LEFT) break;
					
					/* Primero motor de botones */
					map = map_button_in_game (event.button.x, event.button.y);
					cp_button_down (map);
					/*if (map == BUTTON_START) {
						if (use_sound) Mix_PlayChannel (-1, sounds[SND_BUTTON], 0);
					}*/
					if (map != BUTTON_NONE) break;
					
					if (event.button.x >= 40 && event.button.x < 100 && event.button.y >= 144 && event.button.y < 267) {
						hand = (candy_mode ? SAUCE_CHOCOLATE : SAUCE_NORMAL);
						mousedown = TRUE;
						sauce_state = SAUCE_NORMAL;
						sauce_timer = hand_frame = 0;
						if (use_sound) Mix_PlayChannel (0, sounds[SND_SAUCE], -1);
					} else if (event.button.x >= 101 && event.button.x < 161 && event.button.y >= 144 && event.button.y < 267) {
						hand = (candy_mode ? SAUCE_PINK : SAUCE_HOT);
						mousedown = TRUE;
						sauce_state = SAUCE_HOT;
						sauce_timer = hand_frame = 0;
						if (use_sound && hand == SAUCE_PINK) Mix_PlayChannel (0, sounds[SND_SAUCE], -1);
						if (use_sound && hand == SAUCE_HOT) Mix_PlayChannel (0, sounds[SND_HOTSAUCE], -1);
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
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button != SDL_BUTTON_LEFT) break;
					
					/* Primero el motor de botones */
					map = map_button_in_game (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					if (map == BUTTON_CLOSE) {
						done = GAME_QUIT;
						break;
					}
					
					mousedown = FALSE;
					
					if ((hand == SPRINKLES || hand == CHEESE) && (event.button.y >= pizza.y && event.button.y < pizza.y + images[IMG_PIZZA_BASE_CLEAR]->h && event.button.x >= pizza.x && event.button.x < pizza.x + images[IMG_PIZZA_BASE_CLEAR]->w)) {
						pixel = images[IMG_PIZZA_BASE_CLEAR]->pixels + ((event.button.y - pizza.y) * images[IMG_PIZZA_BASE_CLEAR]->pitch) + ((event.button.x - pizza.x) * images[IMG_PIZZA_BASE_CLEAR]->format->BytesPerPixel);
						
						SDL_GetRGBA (*pixel, images[IMG_PIZZA_BASE_CLEAR]->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
						if (alpha != 0) {
							pizza.cheese_placed = hand;
						}
						if (use_sound) Mix_PlayChannel (2, sounds[SND_TOPPING], 0);
					} else if ((hand >= TOPPING_1 && hand <= TOPPING_8) && (event.button.y >= pizza.y && event.button.y < pizza.y + images[IMG_PIZZA_BASE_CLEAR]->h && event.button.x >= pizza.x && event.button.x < pizza.x + images[IMG_PIZZA_BASE_CLEAR]->w)) {
						toppings[topping_count].type = hand - TOPPING_1;
						toppings[topping_count].frame = hand_frame;
						image = IMG_TOPPING_1_1 + (hand - TOPPING_1) * 3 + hand_frame;
						toppings[topping_count].x = event.button.x - (images[image]->w / 2) - pizza.x;
						toppings[topping_count].y = event.button.y - (images[image]->h / 2) - pizza.y;
						
						pixel = images[IMG_PIZZA_BASE_CLEAR]->pixels + ((event.button.y - pizza.y) * images[IMG_PIZZA_BASE_CLEAR]->pitch) + ((event.button.x - pizza.x) * images[IMG_PIZZA_BASE_CLEAR]->format->BytesPerPixel);
						
						SDL_GetRGBA (*pixel, images[IMG_PIZZA_BASE_CLEAR]->format, &rgb_r, &rgb_g, &rgb_b, &alpha);
						if (alpha != 0) {
							topping_count++;
							pizza.topping[(hand - TOPPING_1) % 4]++;
						}
						if (use_sound) Mix_PlayChannel (2, sounds[SND_TOPPING], 0);
					} else if (hand != NONE) {
						/* Soltó un ingrediente */
						/* Si está lleno, eliminar el primer ingrediente volando */
						if (dropt_queue_start == (dropt_queue_end + 1) % 20) {
							dropt_queue_start = (dropt_queue_start + 1) % 20;
						}
						dropped_tops[dropt_queue_end].type = hand;
						dropped_tops[dropt_queue_end].frame = hand_frame;
						dropped_tops[dropt_queue_end].x = event.button.x;
						dropped_tops[dropt_queue_end].y = event.button.y;
						dropped_tops[dropt_queue_end].rotable = (hand != SPRINKLES && hand != CHEESE);
						dropped_tops[dropt_queue_end].angulo = 0;
						dropped_tops[dropt_queue_end].speed_x = 0 - strengthX;
						dropped_tops[dropt_queue_end].speed_y = 20 - strengthY;
						
						if (strengthX >= 30 || strengthX <= -30) {
							if (use_sound) Mix_PlayChannel (2, sounds[SND_THROW], 0);
						}
						lanzados[hand] = 1;
						dropt_queue_end = (dropt_queue_end + 1) % 20;
						
						/* Estampa "Mess of the kitchen" */
						image = 0;
						for (g = 0; g <= TOPPING_8; g++) {
							image += lanzados[g];
						}
						
						if (image == 7 && failures == 3) {
							CPStamp_Earn (stamp_handle, c, 392);
						}
					}
					Mix_HaltChannel (0); // El canal de las salsas
					hand = NONE;
					break;
				case SDL_KEYDOWN:
					/* Tengo una tecla presionada */
					key = event.key.keysym.sym;
					
					if (key == SDLK_F11 || (key == SDLK_RETURN && (event.key.keysym.mod & KMOD_ALT))) {
						SDL_WM_ToggleFullScreen (screen);
					}
					if (key == SDLK_ESCAPE) {
						done = GAME_QUIT;
					}
					break;
				case SDL_QUIT:
					/* Vamos a cerrar la aplicación */
					done = GAME_QUIT;
					break;
			}
		}
		
		/* Considerar la pizza perfecta hasta que se compruebe lo contrario */
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
		
		/* Si no han puesto el queso, o la salsa correcta, no es perfecta */
		if (pizza.cheese_placed == NONE || pizza.sauce_requested != pizza.sauce_placed) {
			perfect_pizza = FALSE;
		}
		
		/* Si ya es perfecta, quitarla de la banda */
		if (perfect_pizza) {
			speedboost++;
		}
		
		/* Borrar todo */
		SDL_BlitSurface (images[IMG_BACKGROUND], NULL, screen, NULL);
		
		dibujar_comanda (&pizza, orden, candy_mode, pizzas_hechas, 40 - ordenes_hechas, failures, score + tips);
		
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
					if (use_sound) Mix_PlayChannel (4, sounds[SND_SAUCE_1], 0);
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
					if (use_sound) Mix_PlayChannel (4, sounds[SND_SAUCE_2], 0);
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
		
		i = (candy_mode ? IMG_SPRINKLES_BOX : IMG_CHEESE_BOX);
		/* Dibujar la caja de queso o sprinkles */
		rect.x = 188;
		rect.y = 187;
		rect.w = images[i]->w;
		rect.h = images[i]->h;
		
		SDL_BlitSurface (images[i], NULL, screen, &rect);
		
		/* Dibujar las cajas de ingredientes */
		i = (candy_mode ? IMG_TOPPING_5_BOX : IMG_TOPPING_1_BOX);
		for (g = 0; g < 4; g++) {
			rect.x = 349 + (g * 102);
			rect.y = 273 - images[i]->h;
			rect.w = images[i]->w;
			rect.h = images[i]->h;
			
			SDL_BlitSurface (images[i], NULL, screen, &rect);
			i++;
		}
		
		if (hand >= SAUCE_NORMAL && hand <= SAUCE_PINK && mousedown && (handposy + 100 >= pizza.y && handposy + 100 < pizza.y + images[IMG_PIZZA_BASE_CLEAR]->h && handposx >= pizza.x && handposx < pizza.x + images[IMG_PIZZA_BASE_CLEAR]->w)) {
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
		} else {
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
			rect.w = images[IMG_PIZZA_BASE_CLEAR]->w;
			rect.h = images[IMG_PIZZA_BASE_CLEAR]->h;
			rect2.w = rect.w;
			rect2.h = rect.h;
			rect2.y = 0;
			if (pizza.sauce_placed == NONE) {
				SDL_BlitSurface (images[IMG_PIZZA_BASE_CLEAR], NULL, screen, &rect);
				image = IMG_PIZZA_BASE_CLEAR;
				rect2.x = 0;
			} else {
				rect2.x = rect.w * (pizza.sauce_placed - NONE - 1);
				
				SDL_BlitSurface (images[IMG_PIZZA_BASE], &rect2, screen, &rect);
				image = IMG_PIZZA_BASE;
			}
		
			/* Dibujar los splats */
			if (pizza.sauce_placed == NONE && splat_queue_end != splat_queue_start) {
				SDL_BlitSurface (images[IMG_SPLAT_MASK], NULL, splat_surface, NULL);
				SDL_BlitSurface (images[image], &rect2, splat_surface, NULL);
				
				SDL_FillRect (splat_surface2, NULL, SDL_MapRGBA (splat_surface2->format, 0, 0, 0, SDL_ALPHA_OPAQUE));
				
				image = IMG_SPLAT_SAUCE + (splats[splat_queue_start].type - SAUCE_NORMAL);
				
				rect.w = images[image]->w;
				rect.h = images[image]->h;
				for (g = splat_queue_start; g != splat_queue_end; g = (g + 1) % 300) {
					rect2.h = images[image]->h / 4;
					rect2.w = images[image]->w / 10;
					rect2.x = splats[g].frame * rect2.w;
					rect2.y = splats[g].rand * rect2.h;
					
					rect.x = splats[g].x;
					rect.y = splats[g].y;
					
					SDL_BlitSurface (images[image], &rect2, splat_surface, &rect);
					rect.x = splats[g].x;
					rect.y = splats[g].y;
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
					i = (candy_mode ? IMG_PIZZA_SPRINKLES : IMG_PIZZA_CHEESE);
					rect.x = pizza.x;
					rect.y = pizza.y;
					rect.w = images[i]->w;
					rect.h = images[i]->h;
				
					SDL_BlitSurface (images[i], NULL, screen, &rect);
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
				if (use_sound && pizza_overflow == 0) Mix_PlayChannel (1, sounds[SND_OVERFLOW], 0);
				image = IMG_PIZZA_OVERFLOW_SAUCE + (pizza.sauce_placed - SAUCE_NORMAL);
				rect.x = pizza.x - 40;
				rect.y = pizza.y - 15;
				rect.w = images[image]->w / 7;
				rect.h = images[image]->h;
				
				rect2.x = pizza_overflow * rect.w;
				rect2.y = 0;
				rect2.w = rect.w;
				rect2.h = rect.h;
				
				SDL_BlitSurface (images[image], &rect2, screen, &rect);
				
				if (pizza_overflow < 6) {
					pizza_overflow++;
				}
			}
		} else {
			if (perfect_pizza) {
				/* En caso contrario, acomodar una nueva pizza y una nueva orden */
				if (orden == 5 && candy_mode == 0) {
					no_shrimp_pizzas++;
					if (no_shrimp_pizzas == 3) {
						CPStamp_Earn (stamp_handle, c, 398);
					}
				}
				
				if (orden == 7 && candy_mode == 0) {
					no_squid_pizzas++;
					if (no_squid_pizzas == 3) {
						CPStamp_Earn (stamp_handle, c, 402);
					}
				}
				
				if (orden == 8 && candy_mode == 1) {
					no_jelly_pizzas++;
					if (no_jelly_pizzas == 3) {
						CPStamp_Earn (stamp_handle, c, 400);
					}
				}
				
				if (orden == 7 && candy_mode == 1) {
					no_marshmallow_pizzas++;
					if (no_marshmallow_pizzas == 3) {
						CPStamp_Earn (stamp_handle, c, 404);
					}
				}
				place_pizza_and_order (&pizza, candy_mode, &pizzas_hechas, &orden);
				pizzas_hechas++;
				pizzas_consecutivas++;
				handicap++;
				
				if (pizzas_consecutivas == 20) {
					CPStamp_Earn (stamp_handle, c, 396);
				} else if (pizzas_consecutivas == 30) {
					CPStamp_Earn (stamp_handle, c, 406);
				} else if (candy_mode && pizzas_consecutivas == 40) {
					CPStamp_Earn (stamp_handle, c, 408);
					CPStamp_Earn (stamp_handle, c, 410);
				} else if (pizzas_consecutivas == 40) {
					CPStamp_Earn (stamp_handle, c, 408);
				}
				
				/* Activar el mensaje de "hecho" */
				order_screen_timer = 0;
				order_screen_done = ORDER_SCREEN_DONE;
				if (use_sound) Mix_PlayChannel (3, sounds[SND_CACHING], 0);
				if (pizzas_consecutivas >= 30) {
					order_screen_done = ORDER_SCREEN_TIP_35;
					tips = tips + 35;
				} else if (pizzas_consecutivas >= 25) {
					order_screen_done = ORDER_SCREEN_TIP_30;
					tips = tips + 30;
				} else if (pizzas_consecutivas >= 20) {
					order_screen_done = ORDER_SCREEN_TIP_25;
					tips = tips + 25;
				} else if (pizzas_consecutivas >= 15) {
					order_screen_done = ORDER_SCREEN_TIP_20;
					tips = tips + 20;
				} else if (pizzas_consecutivas >= 10) {
					order_screen_done = ORDER_SCREEN_TIP_15;
					tips = tips + 15;
				} else if (pizzas_consecutivas >= 5) {
					order_screen_done = ORDER_SCREEN_TIP_10;
					tips = tips + 10;
				}
				
				score = score + 5;
				if (candy_mode) score = score + 5;
				
			} else {
				pizzas_consecutivas = 0;
				failures++;
				handicap--;
				
				/* Estampa "Mess of the kitchen" */
				image = 0;
				for (g = 0; g <= TOPPING_8; g++) {
					image += lanzados[g];
				}
				
				if (image == 7 && failures == 3) {
					CPStamp_Earn (stamp_handle, c, 392);
				}
			}
			ordenes_hechas++;
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
						rect.x += 1;
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
		
		/* Dibujar aquí los ingredientes que caen */
		for (g = dropt_queue_start; g != dropt_queue_end; g = (g + 1) % 20) {
			if (dropped_tops[g].y >= 1000 && g == dropt_queue_start) {
				dropt_queue_start = (dropt_queue_start + 1) % 20;
				continue;
			}
			
			//printf ("Recorriend el dropped: %i\n", g);
			if (dropped_tops[g].type >= SAUCE_NORMAL && dropped_tops[g].type <= SAUCE_PINK) {
				if (dropped_tops[g].type == SAUCE_HOT) {
					rect.x = dropped_tops[g].x - 24;
					rect.y = dropped_tops[g].y - 58;
					image = IMG_HOT_SAUCE;
				} else {
					rect.x = dropped_tops[g].x - 21;
					if (dropped_tops[g].type == SAUCE_NORMAL) {
						rect.y = dropped_tops[g].y - 50;
						image = IMG_SAUCE;
					} else if (dropped_tops[g].type == SAUCE_CHOCOLATE) {
						rect.y = dropped_tops[g].y - 38;
						image = IMG_CHOCOLATE;
					} else {
						rect.y = dropped_tops[g].y - 106;
						image = IMG_PINK_ICING;
					}
				}
				/* Dibujar en la coordenada indicada */
			} else if (dropped_tops[g].type == CHEESE) {
				rect.x = dropped_tops[g].x - 60;
				rect.y = dropped_tops[g].y - 39;
				
				image = IMG_CHEESE_DROPPED;
			} else if (dropped_tops[g].type == SPRINKLES) {
				rect.x = dropped_tops[g].x - 50;
				rect.y = dropped_tops[g].y - 42;
				
				image = IMG_SPRINKLES_DROPPED;
			} else if (dropped_tops[g].type == TOPPING_1) {
				rect.x = dropped_tops[g].x - 44;
				rect.y = dropped_tops[g].y - 37;
				
				image = IMG_TOPPING_1_1_DROPPED + dropped_tops[g].frame;
			} else if (dropped_tops[g].type == TOPPING_2) {
				rect.x = dropped_tops[g].x - 66;
				rect.y = dropped_tops[g].y - 59;
				
				image = IMG_TOPPING_2_1_DROPPED + dropped_tops[g].frame;
			} else if (dropped_tops[g].type == TOPPING_3) {
				rect.x = dropped_tops[g].x - 84;
				rect.y = dropped_tops[g].y - 54;
				
				image = IMG_TOPPING_3_1_DROPPED + dropped_tops[g].frame;
			} else if (dropped_tops[g].type == TOPPING_4) {
				rect.x = dropped_tops[g].x - 71;
				rect.y = dropped_tops[g].y - 52;
				
				image = IMG_TOPPING_4_1_DROPPED + dropped_tops[g].frame;
			} else if (dropped_tops[g].type == TOPPING_5) {
				rect.x = dropped_tops[g].x - 41;
				rect.y = dropped_tops[g].y - 62;
				
				image = IMG_TOPPING_5_1_DROPPED + dropped_tops[g].frame;
			} else if (dropped_tops[g].type == TOPPING_6) {
				rect.x = dropped_tops[g].x - 26;
				rect.y = dropped_tops[g].y - 29;
				
				image = IMG_TOPPING_6_1_DROPPED + dropped_tops[g].frame;
			} else if (dropped_tops[g].type == TOPPING_7) {
				rect.x = dropped_tops[g].x - 31;
				rect.y = dropped_tops[g].y - 35;
				
				image = IMG_TOPPING_7_1_DROPPED + dropped_tops[g].frame;
			} else if (dropped_tops[g].type == TOPPING_8) {
				rect.x = dropped_tops[g].x - 32;
				rect.y = dropped_tops[g].y - 20;
				
				image = IMG_TOPPING_8_1_DROPPED + dropped_tops[g].frame;
			}
			
			rect.w = images[image]->w;
			rect.h = images[image]->h;
			
			if (dropped_tops[g].rotable) {
				int r_x, r_y;
				coordenadas_centro (-1 * (rect.x - dropped_tops[g].x), -1 * (rect.y - dropped_tops[g].y), images[image]->w, images[image]->h, dropped_tops[g].angulo, &r_x, &r_y);
				
				rotated = rotozoomSurface (images[image], dropped_tops[g].angulo, 1);
				
				rect.x += r_x;
				rect.y += r_y;
				dropped_tops[g].angulo -= dropped_tops[g].speed_x;
				if (dropped_tops[g].angulo < 0) dropped_tops[g].angulo += 360;
			} else {
				rotated = images[image];
			}
			SDL_BlitSurface (rotated, NULL, screen, &rect);
			
			if (dropped_tops[g].rotable) {
				SDL_FreeSurface (rotated);
			}
			
			if (dropped_tops[g].speed_y > 20.0) {
				dropped_tops[g].speed_y = dropped_tops[g].speed_y - 1.0;
			} else if (dropped_tops[g].speed_y < 20.0) {
				dropped_tops[g].speed_y = dropped_tops[g].speed_y + 1.0;
			}
			
			dropped_tops[g].y = dropped_tops[g].y + dropped_tops[g].speed_y;
			
			if (dropped_tops[g].speed_x > 0.0) {
				dropped_tops[g].speed_x = dropped_tops[g].speed_x - 0.5;
			} else if (dropped_tops[g].speed_x < 0.0) {
				dropped_tops[g].speed_x = dropped_tops[g].speed_x + 0.5;
			}
			dropped_tops[g].x = dropped_tops[g].x + dropped_tops[g].speed_x;
		}
		
		if (failures >= 5) {
			done = GAME_CONTINUE;
			if (pizzas_hechas <= 1) {
				*fin = END_LAME;
			} else {
				*fin = END_LOSE;
			}
		}
		
		if (ordenes_hechas >= 40) {
			done = GAME_CONTINUE;
			if (pizzas_hechas >= 40) {
				*fin = END_PERFECT;
			} else {
				*fin = END_WIN;
			}
		}
		
		/* Dibujar el boton de cierre */
		rect.x = 721; rect.y = 9;
		rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
		SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
		
		if (CPStamp_IsActive (stamp_handle)) {
			CPStamp_Draw (stamp_handle, screen, FALSE);
		}
		
		SDL_Flip (screen);
		
		now_time = SDL_GetTicks ();
		if (now_time < last_time + FPS) SDL_Delay(last_time + FPS - now_time);
	} while (!done);
	
	SDL_FreeSurface (splat_surface);
	SDL_FreeSurface (splat_surface2);
	
	TTF_CloseFont (ttf9_burbank_bold);
	TTF_CloseFont (ttf13_burbank_bold);
	Mix_HaltChannel (-1);
	return done;
}

int game_end (int fin) {
	int done = 0;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDL_Rect rect;
	SDL_Rect update_rects[6];
	int num_rects;
	int map;
	SDLKey key;
	
	/* Predibujar todo y renderizar */
	SDL_BlitSurface (image_background_ending, NULL, screen, NULL);
	
	/* Dibujar el boton de cierre */
	rect.x = 721; rect.y = 9;
	rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
	SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
	
	/* Dibujar el boton de done */
	rect.x = 49; rect.y = 428;
	rect.w = images[IMG_BUTTON_3_UP]->w; rect.h = images[IMG_BUTTON_3_UP]->h;
	SDL_BlitSurface (images[cp_button_frames[BUTTON_END_DONE]], NULL, screen, &rect);
	
	SDL_Flip (screen);
	
	do {
		last_time = SDL_GetTicks ();
		
		num_rects = 0;
		
		CPStamp_Restore (stamp_handle, screen);
		
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_MOUSEMOTION:
					map = map_button_in_finish (event.motion.x, event.motion.y);
					cp_button_motion (map);
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button != SDL_BUTTON_LEFT) break;
					map = map_button_in_finish (event.button.x, event.button.y);
					map = cp_button_up (map);
					
					switch (map) {
						case BUTTON_CLOSE:
							done = GAME_QUIT;
							break;
						case BUTTON_END_DONE:
							done = GAME_QUIT;
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					/* Motor de botones primero */
					if (event.button.button != SDL_BUTTON_LEFT) break;
					
					map = map_button_in_finish (event.button.x, event.button.y);
					cp_button_down (map);
					break;
				case SDL_QUIT:
					done = GAME_QUIT;
					break;
				case SDL_KEYDOWN:
					/* Tengo una tecla presionada */
					key = event.key.keysym.sym;
					
					if (key == SDLK_F11 || (key == SDLK_RETURN && (event.key.keysym.mod & KMOD_ALT))) {
						SDL_WM_ToggleFullScreen (screen);
					}
					if (key == SDLK_ESCAPE) {
						done = GAME_QUIT;
					}
					break;
			}
		}
		
		if (cp_button_refresh[BUTTON_CLOSE]) {
			rect.x = 721; rect.y = 9;
			rect.w = images[IMG_BUTTON_CLOSE_UP]->w; rect.h = images[IMG_BUTTON_CLOSE_UP]->h;
			
			SDL_BlitSurface (image_background_ending, &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_CLOSE]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_CLOSE] = 0;
		}
		
		if (cp_button_refresh[BUTTON_END_DONE]) {
			rect.x = 49; rect.y = 428;
			rect.w = images[IMG_BUTTON_3_UP]->w; rect.h = images[IMG_BUTTON_3_UP]->h;
			
			SDL_BlitSurface (image_background_ending, &rect, screen, &rect);
			
			SDL_BlitSurface (images[cp_button_frames[BUTTON_END_DONE]], NULL, screen, &rect);
			update_rects[num_rects++] = rect;
			cp_button_refresh[BUTTON_END_DONE] = 0;
		}
		
		if (CPStamp_IsActive (stamp_handle)) {
			CPStamp_Draw (stamp_handle, screen, TRUE);
			update_rects[num_rects++] = CPStamp_GetUpdateRect (stamp_handle);
		}
		
		SDL_UpdateRects (screen, num_rects, update_rects);
		
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
	SDL_Surface *image, *color, *image2;
	SDL_Rect rect;
	int g;
	TTF_Font *temp1, *temp2, *temp3;
	SDL_Color negro;
	char buffer_file[8192];
	char *systemdata_path = get_systemdata_path ();
	
	/* Inicializar el Video SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf (stderr,
			_("Error: Can't initialize the video subsystem\n"
			"The error returned by SDL is:\n"
			"%s\n"), SDL_GetError());
		exit (1);
	}
	
	sprintf (buffer_file, "%simages/icon.png", systemdata_path);
	image = IMG_Load (buffer_file);
	if (image) {
		SDL_WM_SetIcon (image, NULL);
		SDL_FreeSurface (image);
	}
	SDL_WM_SetCaption ("Pizzatron", "Pizzatron");
	
	/* Crear la pantalla de dibujado */
	screen = set_video_mode (0);
	
	if (screen == NULL) {
		fprintf (stderr,
			_("Error: Can't setup 760x480 video mode.\n"
			"The error returned by SDL is:\n"
			"%s\n"), SDL_GetError());
		exit (1);
	}
	
	use_sound = 1;
	if (SDL_InitSubSystem (SDL_INIT_AUDIO) < 0) {
		fprintf (stdout,
			_("Warning: Can't initialize the audio subsystem\n"
			"Continuing...\n"));
		use_sound = 0;
	}
	if (use_sound) {
		/* Inicializar el sonido */
		Mix_Init (MIX_INIT_OGG);
		
		if (Mix_OpenAudio (22050, AUDIO_S16, 2, 4096) < 0) {
			fprintf (stdout,
				_("Warning: Can't initialize the SDL Mixer library\n"));
			use_sound = 0;
		} else {
			Mix_AllocateChannels (5);
		}
	}

	for (g = 0; g < NUM_IMAGES; g++) {
		sprintf (buffer_file, "%s%s", systemdata_path, images_names[g]);
		image = IMG_Load (buffer_file);
		
		if (image == NULL) {
			fprintf (stderr,
				_("Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n"), buffer_file, SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		images[g] = image;
		/* TODO: Mostrar la carga de porcentaje */
	}
	
	setup_locale_images ();
	
	srand ((unsigned int) getpid ());
	
	intro = RANDOM(10);
	intro = intro % 2;
	
	if (intro == 0) {
		/* Cargar el viejo intro */
		/* La carga es muy simple, 2 imágenes */
		for (g = 0; g < NUM_INTRO_OLD_IMAGES; g++) {
			sprintf (buffer_file, "%s%s", systemdata_path, images_intro_old_names[g]);
			image = IMG_Load (buffer_file);
		
			if (image == NULL) {
				fprintf (stderr,
					_("Failed to load data file:\n"
					"%s\n"
					"The error returned by SDL is:\n"
					"%s\n"), buffer_file, SDL_GetError());
				SDL_Quit ();
				exit (1);
			}
		
			images_intro_old[g] = image;
			/* TODO: Mostrar la carga de porcentaje */
		}
	} else {
		/* Cargar el nuevo intro */
		sprintf (buffer_file, "%s%s", systemdata_path, images_intro_new_names [IMG_INTRO_NEW_PENGUIN]);
		image2 = IMG_Load (buffer_file);
		
		if (image2 == NULL) {
			fprintf (stderr,
				_("Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n"), buffer_file, SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		/* Pintar de un color aleatorio el pingüino */
		g = RANDOM (18);
		
		color = SDL_CreateRGBSurface (SDL_SWSURFACE, image2->w, image2->h, 32, RMASK, GMASK, BMASK, AMASK);
		SDL_FillRect (color, NULL, SDL_MapRGB (color->format, penguin_colors[g].r, penguin_colors[g].g, penguin_colors[g].b));
		
		/* Copiar el color sobre el pinguino */
		SDL_BlitSurface (color, NULL, image2, NULL);
		
		SDL_FreeSurface (color);
		
		sprintf (buffer_file, "%s%s", systemdata_path, images_intro_new_names [IMG_INTRO_NEW_BACKGROUND]);
		image = IMG_Load (buffer_file);
		if (image == NULL) {
			fprintf (stderr,
				_("Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n"), buffer_file, SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		/* Copiar el penguino al fondo */
		rect.x = 417;
		rect.y = 85;
		rect.w = image2->w;
		rect.h = image2->h;
		
		SDL_BlitSurface (image2, NULL, image, &rect);
		
		SDL_FreeSurface (image2);
		
		sprintf (buffer_file, "%s%s", systemdata_path, images_intro_new_names [IMG_INTRO_NEW_TOP]);
		image2 = IMG_Load (buffer_file);
		if (image2 == NULL) {
			fprintf (stderr,
				_("Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n"), buffer_file, SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		/* Copiar el top al fondo */
		SDL_BlitSurface (image2, NULL, image, NULL);
		
		SDL_FreeSurface (image2);
		
		images_intro_new [IMG_INTRO_NEW_BACKGROUND] = image;
		
		sprintf (buffer_file, "%s%s", systemdata_path, images_intro_new_names [IMG_INTRO_NEW_CANDY]);
		image = IMG_Load (buffer_file);
		if (image == NULL) {
			fprintf (stderr,
				_("Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n"), buffer_file, SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		images_intro_new [IMG_INTRO_NEW_CANDY] = image;
		
		sprintf (buffer_file, "%s%s", systemdata_path, images_intro_new_names [IMG_INTRO_NEW_EXPLAIN]);
		image = IMG_Load (buffer_file);
		if (image == NULL) {
			fprintf (stderr,
				_("Failed to load data file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n"), buffer_file, SDL_GetError());
			SDL_Quit ();
			exit (1);
		}
		
		images_intro_new [IMG_INTRO_NEW_EXPLAIN] = image;
	}
	
	if (use_sound) {
		for (g = 0; g < NUM_SOUNDS; g++) {
			sprintf (buffer_file, "%s%s", systemdata_path, sound_names[g]);
			sounds[g] = Mix_LoadWAV (buffer_file);
			
			if (sounds[g] == NULL) {
				fprintf (stderr,
					_("Failed to load data file:\n"
					"%s\n"
					"The error returned by SDL is:\n"
					"%s\n"), buffer_file, SDL_GetError ());
				SDL_Quit ();
				exit (1);
			}
			Mix_VolumeChunk (sounds[g], MIX_MAX_VOLUME / 2);
		}
		
		g = RANDOM (12);
		
		if (g >= 0 && g <= 3) {
			sprintf (buffer_file, "%s%s", systemdata_path, MUS_106);
		} else if (g >= 4 && g <= 7) {
			sprintf (buffer_file, "%s%s", systemdata_path, MUS_270);
		} else if (g >= 8 && g <= 10) {
			sprintf (buffer_file, "%s%s", systemdata_path, MUS_344);
		} else {
			sprintf (buffer_file, "%s%s", systemdata_path, MUS_385);
		}
		music = Mix_LoadMUS (buffer_file);
		
		if (music == NULL) {
			fprintf (stderr,
				_("Failed to load a music file:\n"
				"%s\n"
				"The error returned by SDL is:\n"
				"%s\n"), buffer_file, SDL_GetError ());
			SDL_Quit ();
			exit (1);
		}
	}

	if (TTF_Init () < 0) {
		fprintf (stderr,
			_("Error: Can't initialize the SDL TTF library\n"
			"%s\n"), TTF_GetError ());
		SDL_Quit ();
		exit (1);
	}
	/* Abrir los archivos TTF como SDL_RWOPS */
	
	/* La 10 y 12 son para los nombres de las pizzas */
	sprintf (buffer_file, "%s%s", systemdata_path, "burbanksb.ttf");
	ttf_burbank_sb = SDL_RWFromFile(buffer_file, "rb");
	
	if (ttf_burbank_sb == NULL) {
		fprintf (stderr,
			_("Failed to load font file 'Burbank Small Bold'\n"
			"The error returned by SDL is:\n"
			"%s\n"), SDL_GetError ());
		SDL_Quit ();
		exit (1);
	}
	
	sprintf (buffer_file, "%s%s", systemdata_path, "burbankbgbk.ttf");
	ttf_burbank_bgbk = SDL_RWFromFile(buffer_file, "rb");
	
	if (ttf_burbank_bgbk == NULL) {
		fprintf (stderr,
			_("Failed to load font file 'Burbank Big Regular'\n"
			"The error returned by SDL is:\n"
			"%s\n"), SDL_GetError ());
		SDL_Quit ();
		exit (1);
	}
	
	/* Ahora, cargar todas las tipografías */
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	ttf10_burbank_bold = TTF_OpenFontRW (ttf_burbank_sb, 0, 10);
	
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	ttf12_burbank_bold = TTF_OpenFontRW (ttf_burbank_sb, 0, 12);
	
	if (!ttf10_burbank_bold || !ttf12_burbank_bold) {
		SDL_Quit ();
		exit (1);
	}
	
	/* ttf10 y ttf12 se cierran cuando se renderizan los nombres */
	
	if (intro == 0) {
		sprintf (buffer_file, "%s%s", systemdata_path, "acmeexplosive.ttf");
		ttf_acme = SDL_RWFromFile(buffer_file, "rb");
		if (ttf_acme == NULL) {
			fprintf (stderr,
				_("Failed to load font file 'Acme Explosive'\n"
				"The error returned by SDL is:\n"
				"%s\n"), SDL_GetError ());
			SDL_Quit ();
			exit (1);
		}
		
		/* Tipografia exclusiva para el intro viejo */
		SDL_RWseek (ttf_acme, 0, RW_SEEK_SET);
		ttf20_acme = TTF_OpenFontRW (ttf_acme, 0, 20);
		
		if (!ttf20_acme) {
			SDL_Quit ();
			exit (1);
		}
	} else {
		/* Tipografias exclusiva para el intro nuevo */
		SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
		ttf18_burbank_bold = TTF_OpenFontRW (ttf_burbank_sb, 0, 18);
	
		SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
		ttf28_burbank_bold = TTF_OpenFontRW (ttf_burbank_sb, 0, 28);
		
		sprintf (buffer_file, "%s%s", systemdata_path, "burbanks.ttf");
		ttf14_burbank_small = TTF_OpenFont (buffer_file, 14);
		
		if (ttf14_burbank_small == NULL) {
			fprintf (stderr,
				_("Failed to load font file 'Burbank Small'\n"
				"The error returned by SDL is:\n"
				"%s\n"), SDL_GetError ());
			SDL_Quit ();
			exit (1);
		}
		
		if (!ttf18_burbank_bold || !ttf28_burbank_bold) {
			SDL_Quit ();
			exit (1);
		}
		
		/* Las 3 tipografías se cierran en el intro nuevo */
	}
	
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	ttf9_burbank_bold = TTF_OpenFontRW (ttf_burbank_sb, 0, 9);
	
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	ttf13_burbank_bold = TTF_OpenFontRW (ttf_burbank_sb, 0, 13);
	
	if (!ttf13_burbank_bold || !ttf9_burbank_bold) {
		SDL_Quit ();
		exit (1);
	}
	/* La ttf9 y ttf13 no se cierran, se usan para la comanda */
	
	SDL_RWseek (ttf_burbank_bgbk, 0, RW_SEEK_SET);
	temp1 = TTF_OpenFontRW (ttf_burbank_bgbk, 0, 38);
	
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	temp2 = TTF_OpenFontRW (ttf_burbank_sb, 0, 20);
	
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	temp3 = TTF_OpenFontRW (ttf_burbank_sb, 0, 16);
	
	if (!temp1 || !temp2 || !temp3) {
		SDL_Quit ();
		exit (1);
	}
	
	/* Renderizar todos los textos */
	bind_textdomain_codeset (PACKAGE, "UTF-8");
	
	negro.r = negro.g = negro.b = 0;
	
	texts[TEXT_PIZZAS_MADE] = TTF_RenderUTF8_Blended (ttf9_burbank_bold, _("PIZZAS MADE"), negro);
	texts[TEXT_PIZZAS_LEFT] = TTF_RenderUTF8_Blended (ttf9_burbank_bold, _("PIZZAS LEFT"), negro);
	texts[TEXT_MISTAKES] = TTF_RenderUTF8_Blended (ttf9_burbank_bold, _("MISTAKES"), negro);
	
	texts[TEXT_COINS] = TTF_RenderUTF8_Blended (ttf13_burbank_bold, _("COINS"), negro);
	
	texts[TEXT_DONE_LABEL] = TTF_RenderUTF8_Blended (temp1, _("DONE!"), negro);
	
	texts[TEXT_5_COINS] = TTF_RenderUTF8_Blended (temp2, _("+5 COINS"), negro);
	texts[TEXT_10_COINS] = TTF_RenderUTF8_Blended (temp2, _("+10 COINS"), negro);
	
	texts[TEXT_TIP_10] = TTF_RenderUTF8_Blended (temp3, _("+10 TIP!"), negro);
	texts[TEXT_TIP_15] = TTF_RenderUTF8_Blended (temp3, _("+15 TIP!"), negro);
	texts[TEXT_TIP_20] = TTF_RenderUTF8_Blended (temp3, _("+20 TIP!"), negro);
	texts[TEXT_TIP_25] = TTF_RenderUTF8_Blended (temp3, _("+25 TIP!"), negro);
	texts[TEXT_TIP_30] = TTF_RenderUTF8_Blended (temp3, _("+30 TIP!"), negro);
	texts[TEXT_TIP_35] = TTF_RenderUTF8_Blended (temp3, _("+35 TIP!"), negro);
	
	TTF_CloseFont (temp1);
	TTF_CloseFont (temp2);
	TTF_CloseFont (temp3);
}

void setup_texts (void) {
	/* Renderizar todos los textos */
	SDL_Color azul, negro;
	int g;
	
	azul.r = 0x01;
	azul.g = 0x45;
	azul.b = 0x87;
	
	negro.r = negro.g = negro.b = 0;
	
	if (candy_mode) {
		texts[TEXT_PIZZA_ORDER_1] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("CHOCOLATE SPRINKLE PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_2] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK ICING SPRINKLE"), azul);
		texts[TEXT_PIZZA_ORDER_3] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("LIQUORICE PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_4] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK LIQUORICE PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_5] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("CHOCOLATE PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_6] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK CHOCOLATE PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_7] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("MARSHMALLOW PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_8] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK MARSHMALLOW PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_9] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("JELLY BEAN PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_10] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK JELLY BEAN PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_11] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("LIQUORICE-CHIP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_12] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK LIQUORICE-CHIP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_13] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("MARSHMALLOW JELLY PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_14] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK MARSHMALLOW JELLY PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_15] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("LIQUORICE MARSHMALLOW PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_16] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK LIQUORICE MARSHMALLOW PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_17] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("JELLY CHIP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_18] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK JELLY CHIP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_19] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("LIQUORICE JELLY PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_20] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK LIQUORICE JELLY PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_21] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("MARSHMALLOW CHIP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_22] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK MARSHMALLOW CHIP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_23] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("CHOCOLATE SUGAR PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_24] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PINK SUGAR PIZZA"), azul);
		
		texts[TEXT_CHEESE_SPRINKLES] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("SPRINKLES"), azul);
		
		texts[TEXT_SAUCE_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("CHOCOLATE SAUCE"), azul);
		texts[TEXT_SAUCE_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("PINK ICING"), azul);
		
		texts[TEXT_5_TOPPING_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 LIQUORICE"), azul);
		texts[TEXT_5_TOPPING_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 CHOCOLATE CHIPS"), azul);
		texts[TEXT_5_TOPPING_3] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 MARSHMALLOWS"), azul);
		texts[TEXT_5_TOPPING_4] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 JELLY BEANS"), azul);
		
		texts[TEXT_2_TOPPING_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 LIQUORICE"), azul);
		texts[TEXT_2_TOPPING_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 CHOCOLATE CHIPS"), azul);
		texts[TEXT_2_TOPPING_3] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 MARSHMALLOWS"), azul);
		texts[TEXT_2_TOPPING_4] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 JELLY BEANS"), azul);
		
		texts[TEXT_1_TOPPING_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 LIQUORICE"), azul);
		texts[TEXT_1_TOPPING_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 CHOCOLATE CHIP"), azul);
		texts[TEXT_1_TOPPING_3] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 MARSHMALLOW"), azul);
		texts[TEXT_1_TOPPING_4] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 JELLY BEAN"), azul);
	} else {
		texts[TEXT_PIZZA_ORDER_1] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("CHEESE PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_2] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT CHEESE PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_3] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SEAWEED PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_4] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SPICY SEAWEED PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_5] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SHRIMP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_6] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT SHRIMP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_7] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SQUID PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_8] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SPICY SQUID PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_9] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("FISH PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_10] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("FLAMETHROWER FISH PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_11] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SEAWEED-SHRIMP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_12] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT SEAWEED-SHRIMP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_13] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("FISH DISH PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_14] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT FISH DISH PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_15] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SEAWEED-SQUID PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_16] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT SEAWEED-SQUID PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_17] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("FISH SHRIMP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_18] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT FISH SHRIMP PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_19] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SEAWEED FISH PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_20] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT SEAWEED FISH PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_21] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SHRIMP SQUID PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_22] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("HOT SHRIMP SQUID PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_23] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SUPREME PIZZA"), azul);
		texts[TEXT_PIZZA_ORDER_24] = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SUPREME SIZZLE PIZZA"), azul);
		
		texts[TEXT_CHEESE_SPRINKLES] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("CHEESE"), azul);
		
		texts[TEXT_SAUCE_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("PIZZA SAUCE"), azul);
		texts[TEXT_SAUCE_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("HOT SAUCE"), azul);
		
		texts[TEXT_5_TOPPING_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 SEAWEED"), azul);
		texts[TEXT_5_TOPPING_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 SHRIMP"), azul);
		texts[TEXT_5_TOPPING_3] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 SQUID"), azul);
		texts[TEXT_5_TOPPING_4] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("5 FISH"), azul);
		
		texts[TEXT_2_TOPPING_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 SEAWEED"), azul);
		texts[TEXT_2_TOPPING_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 SHRIMP"), azul);
		texts[TEXT_2_TOPPING_3] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 SQUID"), azul);
		texts[TEXT_2_TOPPING_4] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("2 FISH"), azul);
		
		texts[TEXT_1_TOPPING_1] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 SEAWEED"), azul);
		texts[TEXT_1_TOPPING_2] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 SHRIMP"), azul);
		texts[TEXT_1_TOPPING_3] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 SQUID"), azul);
		texts[TEXT_1_TOPPING_4] = TTF_RenderUTF8_Blended (ttf10_burbank_bold, _("1 FISH"), azul);
	}
	
	/* La 10 y la 12 ya no son necesarias */
	TTF_CloseFont (ttf10_burbank_bold);
	/* La ttf12_burbank se utiliza otra vez en el ending, por lo tanto, no se cierra */
	
	/* Cerrar las imágenes que no son necesarias */
	if (candy_mode) {
		SDL_FreeSurface (images[IMG_PIZZA_CHEESE]);
		SDL_FreeSurface (images[IMG_CHEESE_BOX]);
		SDL_FreeSurface (images[IMG_CHEESE_HAND]);
		
		images[IMG_PIZZA_CHEESE] = images[IMG_CHEESE_BOX] = images[IMG_CHEESE_HAND] = NULL;
		
		SDL_FreeSurface (images[IMG_SAUCE]);
		SDL_FreeSurface (images[IMG_SPLAT_SAUCE]);
		SDL_FreeSurface (images[IMG_HOT_SAUCE]);
		SDL_FreeSurface (images[IMG_SPLAT_HOT]);
		
		images[IMG_SAUCE] = images[IMG_SPLAT_SAUCE] = images[IMG_HOT_SAUCE] = images[IMG_SPLAT_HOT] = NULL;
		
		for (g = IMG_TOPPING_1_BOX; g <= IMG_TOPPING_4_BOX; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_SAUCE_SQUASH_1; g <= IMG_SAUCE_SQUASH_6; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_HOT_SQUASH_1; g <= IMG_HOT_SQUASH_8; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_HAND_TOPPING_1_1; g <= IMG_HAND_TOPPING_4_3; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_TOPPING_1_1; g <= IMG_TOPPING_4_3; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		SDL_FreeSurface (images[IMG_PIZZA_OVERFLOW_SAUCE]);
		SDL_FreeSurface (images[IMG_PIZZA_OVERFLOW_HOT]);
		
		images[IMG_PIZZA_OVERFLOW_SAUCE] = images[IMG_PIZZA_OVERFLOW_HOT] = NULL;
		
		SDL_FreeSurface (images[IMG_ORDER_TOPPING]);
		SDL_FreeSurface (images[IMG_CHEESE_DROPPED]);
		
		images[IMG_ORDER_TOPPING] = images[IMG_CHEESE_DROPPED] = NULL;
		
		for (g = IMG_TOPPING_1_1_DROPPED; g <= IMG_TOPPING_4_3_DROPPED; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
	} else {
		SDL_FreeSurface (images[IMG_PIZZA_SPRINKLES]);
		SDL_FreeSurface (images[IMG_SPRINKLES_BOX]);
		SDL_FreeSurface (images[IMG_SPRINKLES_HAND]);
		
		images[IMG_PIZZA_SPRINKLES] = images[IMG_SPRINKLES_BOX] = images[IMG_SPRINKLES_HAND] = NULL;
		
		SDL_FreeSurface (images[IMG_CHOCOLATE]);
		SDL_FreeSurface (images[IMG_SPLAT_CHOCO]);
		SDL_FreeSurface (images[IMG_PINK_ICING]);
		SDL_FreeSurface (images[IMG_SPLAT_PINK]);
		
		images[IMG_CHOCOLATE] = images[IMG_SPLAT_CHOCO] = images[IMG_PINK_ICING] = images[IMG_SPLAT_PINK] = NULL;
		for (g = IMG_TOPPING_5_BOX; g <= IMG_TOPPING_8_BOX; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_CHOCO_SQUASH_1; g <= IMG_CHOCO_SQUASH_6; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_PINK_SQUASH_1; g <= IMG_PINK_SQUASH_6; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_HAND_TOPPING_5_1; g <= IMG_HAND_TOPPING_8_3; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		for (g = IMG_TOPPING_5_1; g <= IMG_TOPPING_8_3; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
		
		SDL_FreeSurface (images[IMG_PIZZA_OVERFLOW_CHOCO]);
		SDL_FreeSurface (images[IMG_PIZZA_OVERFLOW_PINK]);
		
		images[IMG_PIZZA_OVERFLOW_CHOCO] = images[IMG_PIZZA_OVERFLOW_PINK] = NULL;
		
		SDL_FreeSurface (images[IMG_ORDER_TOPPING_CANDY]);
		SDL_FreeSurface (images[IMG_SPRINKLES_DROPPED]);
		
		images[IMG_ORDER_TOPPING_CANDY] = images[IMG_SPRINKLES_DROPPED] = NULL;
		
		for (g = IMG_TOPPING_5_1_DROPPED; g <= IMG_TOPPING_8_3_DROPPED; g++) {
			SDL_FreeSurface (images[g]);
			images[g] = NULL;
		}
	}
}

void setup_ending (int fin) {
	SDL_Surface *image, *text;
	TTF_Font *temp;
	SDL_Color blanco, negro;
	SDL_Rect rect;
	char buffer[10];
	
	blanco.r = blanco.g = blanco.b = 0xFF;
	negro.r = negro.g = negro.b = 0;
	
	image = images[IMG_ENDING_1 + fin];
	
	SDL_RWseek (ttf_burbank_bgbk, 0, RW_SEEK_SET);
	temp = TTF_OpenFontRW (ttf_burbank_bgbk, 0, 30);
	
	if (!temp) {
		SDL_Quit ();
		exit (1);
	}
	
	TTF_SetFontOutline (temp, 3);
	const char *score_txt;
	if (fin == END_PERFECT) {
		score_txt = _("PERFECT SCORE");
	} else {
		score_txt = _("SCORE");
	}
	
	text = TTF_RenderUTF8_Blended (temp, score_txt, negro);
	rect.x = 22;
	rect.y = 15;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	TTF_SetFontOutline (temp, 0);
	rect.x = 25;
	rect.y = 18;
	rect.w = text->w;
	rect.h = text->h;
	text = TTF_RenderUTF8_Blended (temp, score_txt, blanco);
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	TTF_CloseFont (temp);
	
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("PIZZAS SOLD"), negro);
	rect.x = 22;
	rect.y = 70;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	sprintf (buffer, "%i", pizzas_hechas);
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, buffer, negro);
	rect.x = 160 - text->w;
	rect.y = 70;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	/* Texto de score */
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("SALES"), negro);
	rect.x = 22;
	rect.y = 88;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	sprintf (buffer, "%i", score);
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, buffer, negro);
	rect.x = 160 - text->w;
	rect.y = 88;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("COINS"), negro);
	rect.x = 162;
	rect.y = 88;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	
	rect.x = 162;
	rect.y = 106;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	/* Texto de las propinas */
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, _("TIPS"), negro);
	rect.x = 22;
	rect.y = 106;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	sprintf (buffer, "%i", tips);
	text = TTF_RenderUTF8_Blended (ttf12_burbank_bold, buffer, negro);
	rect.x = 160 - text->w;
	rect.y = 106;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	temp = TTF_OpenFontRW (ttf_burbank_sb, 0, 16);
	
	if (!temp) {
		SDL_Quit ();
		exit (1);
	}
	
	/* Texto "Total de monedas" */
	text = TTF_RenderUTF8_Blended (temp, _("TOTAL"), negro);
	rect.x = 22;
	rect.y = 134;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	sprintf (buffer, "%i", score + tips);
	text = TTF_RenderUTF8_Blended (temp, buffer, negro);
	rect.x = 160 - text->w;
	rect.y = 134;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	text = TTF_RenderUTF8_Blended (temp, _("COINS"), negro);
	rect.x = 162;
	rect.y = 134;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, image, &rect);
	SDL_FreeSurface (text);
	
	TTF_CloseFont (temp);
	
	SDL_RWseek (ttf_burbank_sb, 0, RW_SEEK_SET);
	temp = TTF_OpenFontRW (ttf_burbank_sb, 0, 20);
	
	if (!temp) {
		SDL_Quit ();
		exit (1);
	}
	
	TTF_SetFontOutline (temp, 2);
	
	text = TTF_RenderUTF8_Blended (temp, _("DONE"), negro);
	rect.x = 4 + (images[IMG_BUTTON_3_UP]->w - text->w) / 2;
	rect.y = 11;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, images[IMG_BUTTON_3_UP], &rect);
	SDL_BlitSurface (text, NULL, images[IMG_BUTTON_3_OVER], &rect);
	SDL_BlitSurface (text, NULL, images[IMG_BUTTON_3_DOWN], &rect);
	SDL_FreeSurface (text);
	
	TTF_SetFontOutline (temp, 0);
	
	text = TTF_RenderUTF8_Blended (temp, _("DONE"), blanco);
	rect.x = 4 + (images[IMG_BUTTON_3_UP]->w - text->w) / 2;
	rect.y = 13;
	rect.w = text->w;
	rect.h = text->h;
	SDL_BlitSurface (text, NULL, images[IMG_BUTTON_3_UP], &rect);
	SDL_BlitSurface (text, NULL, images[IMG_BUTTON_3_OVER], &rect);
	SDL_BlitSurface (text, NULL, images[IMG_BUTTON_3_DOWN], &rect);
	SDL_FreeSurface (text);
	
	TTF_CloseFont (temp);
	
	TTF_CloseFont (ttf12_burbank_bold);
	SDL_RWclose (ttf_burbank_sb);
	SDL_RWclose (ttf_burbank_bgbk);
	
	image_background_ending = image;
}

void setup_locale_images (void) {
	SDL_Surface *local_images[9], *image;
	char buffer_file[8192];
	char *full_locale;
	char locale_country[128];
	char locale_lang[128];
	int g, h;
	int loaded;
	char *systemdata_path = get_systemdata_path ();
	
	int choc_images[] = {IMG_CHOCOLATE, IMG_CHOCO_SQUASH_1, IMG_CHOCO_SQUASH_2, IMG_CHOCO_SQUASH_3, IMG_CHOCO_SQUASH_4, IMG_CHOCO_SQUASH_5, IMG_CHOCO_SQUASH_6};
	int hot_images[] = {IMG_HOT_SAUCE,IMG_HOT_SQUASH_1, IMG_HOT_SQUASH_2, IMG_HOT_SQUASH_3, IMG_HOT_SQUASH_4, IMG_HOT_SQUASH_5, IMG_HOT_SQUASH_6, IMG_HOT_SQUASH_7, IMG_HOT_SQUASH_8};
	
	char *choc_names[] = {
		"chocolate.png",
		"chocolate_squash_01.png",
		"chocolate_squash_02.png",
		"chocolate_squash_03.png",
		"chocolate_squash_04.png",
		"chocolate_squash_05.png",
		"chocolate_squash_06.png",
	};
	
	char *hot_names[] = {
		"hot_sauce.png",
		"hot_sauce_squash_01.png",
		"hot_sauce_squash_02.png",
		"hot_sauce_squash_03.png",
		"hot_sauce_squash_04.png",
		"hot_sauce_squash_05.png",
		"hot_sauce_squash_06.png",
		"hot_sauce_squash_07.png",
		"hot_sauce_squash_08.png"
	};
	
	/* Generar la cadena de texto de la locale */
	full_locale = setlocale (LC_ALL, "");
	
	if (full_locale == NULL) return;
	
	g = 0;
	h = 0;
	while (full_locale[g] != 0 && full_locale[g] != '.' && full_locale[g] != '@') {
		locale_country[h] = full_locale[g];
		g++;
		h++;
	}
	locale_country[h] = 0;
	
	g = h = 0;
	while (full_locale[g] != 0 && full_locale[g] != '.' && full_locale[g] != '@' && full_locale[g] != '_') {
		locale_lang[h] = full_locale[g];
		g++;
		h++;
	}
	locale_lang[h] = 0;
	
	/* Intentar cargar la imagen correspondiente en el locale para las botellas de chocolate */
	h = 1;
	for (g = 0; g < 7; g++) {
		sprintf (buffer_file, "%simages/%s/%s", systemdata_path, locale_country, choc_names[g]);
		image = IMG_Load (buffer_file);
		
		if (image == NULL) {
			h = 0;
			
			/* Revertir las imágenes posiblemente cargadas */
			while (g > 0) {
				SDL_FreeSurface (local_images[g - 1]);
				g--;
			}
			
			break;
		}
		
		local_images[g] = image;
	}
	
	if (h == 0) {
		h = 1;
		/* Intentar cargar las imágenes con solo el lenguaje */
		for (g = 0; g < 7; g++) {
			sprintf (buffer_file, "%simages/%s/%s", systemdata_path, locale_lang, choc_names[g]);
			image = IMG_Load (buffer_file);
		
			if (image == NULL) {
				h = 0;
			
				/* Revertir las imágenes posiblemente cargadas */
				while (g > 0) {
					SDL_FreeSurface (local_images[g - 1]);
					g--;
				}
			
				break;
			}
		
			local_images[g] = image;
		}
	}
	
	/* Si todas las imágenes fueron cargadas, sustituir las imágenes en el arreglo global */
	if (h == 1) {
		for (g = 0; g < 7; g++) {
			SDL_FreeSurface (images[choc_images[g]]);
			
			images[choc_images[g]] = local_images[g];
		}
	}
	
	/* Intentar lo mismo con la botella de salsa picante */
	h = 1;
	for (g = 0; g < 9; g++) {
		sprintf (buffer_file, "%simages/%s/%s", systemdata_path, locale_country, hot_names[g]);
		image = IMG_Load (buffer_file);
		
		if (image == NULL) {
			h = 0;
			
			/* Revertir las imágenes posiblemente cargadas */
			while (g > 0) {
				SDL_FreeSurface (local_images[g - 1]);
				g--;
			}
			
			break;
		}
		
		local_images[g] = image;
	}
	
	if (h == 0) {
		h = 1;
		/* Intentar cargar las imágenes con solo el lenguaje */
		for (g = 0; g < 9; g++) {
			sprintf (buffer_file, "%simages/%s/%s", systemdata_path, locale_lang, hot_names[g]);
			image = IMG_Load (buffer_file);
		
			if (image == NULL) {
				h = 0;
			
				/* Revertir las imágenes posiblemente cargadas */
				while (g > 0) {
					SDL_FreeSurface (local_images[g - 1]);
					g--;
				}
			
				break;
			}
		
			local_images[g] = image;
		}
	}
	
	/* Si todas las imágenes fueron cargadas, sustituir las imágenes en el arreglo global */
	if (h == 1) {
		for (g = 0; g < 9; g++) {
			SDL_FreeSurface (images[hot_images[g]]);
			
			images[hot_images[g]] = local_images[g];
		}
	}
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
	
	*orden = ((int) (((float) posibles) * rand () / (RAND_MAX + 1.0)));
	
	p->sauce_requested = candy_mode ? SAUCE_CHOCOLATE : SAUCE_NORMAL;
	
	if (*orden % 2 == 1) {
		p->sauce_requested = candy_mode ? SAUCE_PINK : SAUCE_HOT;
	}
	
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
}

void dibujar_comanda (Pizza *pizza, int orden, int candy_mode, int pizzas_hechas, int pizzas_left, int fallos, int coins) {
	SDL_Rect rect, rect2;
	int g;
	SDL_Surface *temp;
	char buffer[32];
	SDL_Color negro;
	
	negro.r = negro.g = negro.b = 0;
	
	/* Dibujar la cantidad de pizzas hechas y faltantes */
	rect.x = 613;
	rect.y = 17;
	rect.w = texts[TEXT_PIZZAS_MADE]->w;
	rect.h = texts[TEXT_PIZZAS_MADE]->h;
	SDL_BlitSurface (texts[TEXT_PIZZAS_MADE], NULL, screen, &rect);
	
	rect.x = 613;
	rect.y = 33;
	rect.w = texts[TEXT_PIZZAS_LEFT]->w;
	rect.h = texts[TEXT_PIZZAS_LEFT]->h;
	SDL_BlitSurface (texts[TEXT_PIZZAS_LEFT], NULL, screen, &rect);
	
	rect.x = 613;
	rect.y = 50;
	rect.w = texts[TEXT_MISTAKES]->w;
	rect.h = texts[TEXT_MISTAKES]->h;
	SDL_BlitSurface (texts[TEXT_MISTAKES], NULL, screen, &rect);
	
	rect.x = 650 - texts[TEXT_COINS]->w;
	rect.y = 153;
	rect.w = texts[TEXT_COINS]->w;
	rect.h = texts[TEXT_COINS]->h;
	SDL_BlitSurface (texts[TEXT_COINS], NULL, screen, &rect);
	
	sprintf (buffer, "%i", pizzas_hechas);
	temp = TTF_RenderUTF8_Blended (ttf9_burbank_bold, buffer, negro);
	rect.x = 690 - temp->w;
	rect.y = 17;
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_BlitSurface (temp, NULL, screen, &rect);
	SDL_FreeSurface (temp);
	
	sprintf (buffer, "%i", pizzas_left);
	temp = TTF_RenderUTF8_Blended (ttf9_burbank_bold, buffer, negro);
	rect.x = 690 - temp->w;
	rect.y = 33;
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_BlitSurface (temp, NULL, screen, &rect);
	SDL_FreeSurface (temp);
	
	sprintf (buffer, "%i", fallos);
	temp = TTF_RenderUTF8_Blended (ttf9_burbank_bold, buffer, negro);
	rect.x = 690 - temp->w;
	rect.y = 50;
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_BlitSurface (temp, NULL, screen, &rect);
	SDL_FreeSurface (temp);
	
	sprintf (buffer, "%i", coins);
	temp = TTF_RenderUTF8_Blended (ttf13_burbank_bold, buffer, negro);
	rect.x = 688 - temp->w;
	rect.y = 153;
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_BlitSurface (temp, NULL, screen, &rect);
	SDL_FreeSurface (temp);
	
	if (order_screen_done != ORDER_SCREEN_NONE) {
		rect.x = 401;
		rect.y = 20;
		rect.w = texts[TEXT_DONE_LABEL]->w;
		rect.h = texts[TEXT_DONE_LABEL]->h;
		
		SDL_BlitSurface (texts[TEXT_DONE_LABEL], NULL, screen, &rect);
		
		rect.x = 401;
		rect.y = 75;
		if (candy_mode) {
			temp = texts[TEXT_10_COINS];
		} else {
			temp = texts[TEXT_5_COINS];
		}
		rect.w = temp->w;
		rect.h = temp->h;
		
		SDL_BlitSurface (temp, NULL, screen, &rect);
		
		if (order_screen_done != ORDER_SCREEN_DONE) {
			temp = texts[TEXT_TIP_10 + order_screen_done - ORDER_SCREEN_TIP_10];
			
			rect.x = 401;
			rect.y = 100;
			rect.w = temp->w;
			rect.h = temp->h;
			
			SDL_BlitSurface (temp, NULL, screen, &rect);
		}
		
		rect.x = 500;
		rect.y = 97;
		rect.w = images[IMG_DONE]->w;
		rect.h = images[IMG_DONE]->h;
		
		SDL_BlitSurface (images[IMG_DONE], NULL, screen, &rect);
		
		order_screen_timer++;
		if (order_screen_timer >= 16) order_screen_done = ORDER_SCREEN_NONE;
		return; /* No dibujar lo demás */
	}
	
	/* Dibujar la pizza correcta en la comanda */
	rect.x = 401;
	rect.y = 51;
	rect.w = images[IMG_ORDER_PIZZA]->w / 4;
	rect.h = images[IMG_ORDER_PIZZA]->h;
	
	rect2.x = rect.w * (pizza->sauce_requested - SAUCE_NORMAL);
	rect2.y = 0;
	rect2.w = rect.w;
	rect2.h = rect.h;
	SDL_BlitSurface (images[IMG_ORDER_PIZZA], &rect2, screen, &rect);
	
	/* Dibujar el nombre de la pizza */
	rect.x = 398;
	rect.y = 18;
	temp = texts[TEXT_PIZZA_ORDER_1 + orden];
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_BlitSurface (temp, NULL, screen, &rect);
	
	/* Dibujar los ingredientes abajo, en la comanda */
	if (orden > 1) {
		g = IMG_ORDER_TOPPING;
		if (candy_mode) g = IMG_ORDER_TOPPING_CANDY;
		
		rect.x = 391;
		rect.y = 106;
		rect.w = images[g]->w / 11;
		rect.h = images[g]->h;
		
		rect2.x = rect.w * ((orden / 2) - 1);
		rect2.y = 0;
		rect2.w = rect.w;
		rect2.h = rect.h;
		
		SDL_BlitSurface (images[g], &rect2, screen, &rect);
	}
	
	/* Dibujar las palomitas */
	if (pizza->cheese_placed != NONE) {
		rect.x = 524;
		rect.y = 50;
		rect.w = images[IMG_CHECKED]->w;
		rect.h = images[IMG_CHECKED]->h;
		
		SDL_BlitSurface (images[IMG_CHECKED], NULL, screen, &rect);
	}
	
	/* Dibujar el texto */
	rect.x = 544;
	rect.y = 53;
	rect.w = texts[TEXT_CHEESE_SPRINKLES]->w;
	rect.h = texts[TEXT_CHEESE_SPRINKLES]->h;
	
	SDL_BlitSurface (texts[TEXT_CHEESE_SPRINKLES], NULL, screen, &rect);
	
	/* Palomita para la salsa */
	if (pizza->sauce_placed == pizza->sauce_requested) {
		rect.x = 524;
		rect.y = 72;
		rect.w = images[IMG_CHECKED]->w;
		rect.h = images[IMG_CHECKED]->h;
		
		SDL_BlitSurface (images[IMG_CHECKED], NULL, screen, &rect);
	}
	
	/* Dibujar el texto de la salsa */
	rect.x = 544;
	rect.y = 75;
	if (candy_mode) {
		temp = texts[TEXT_SAUCE_1 + pizza->sauce_requested - SAUCE_CHOCOLATE];
	} else {
		temp = texts[TEXT_SAUCE_1 + pizza->sauce_requested - SAUCE_NORMAL];
	}
	rect.w = temp->w;
	rect.h = temp->h;
	
	SDL_BlitSurface (temp, NULL, screen, &rect);
	
	/* Palomitas para los ingredientes */
	if (orden > 1 && orden < 22) {
		/* Ordenes con uno o dos ingredientes */
		rect.y = 119;
		rect.x = 524;
		rect.w = images[IMG_CHECKED]->w;
		rect.h = images[IMG_CHECKED]->h;
		rect2.y = 121;
		rect2.x = 544;
		for (g = 0; g < 4; g++) {
			if (pizza->topping_requested[g] != 0 && pizza->topping[g] >= pizza->topping_requested[g]) {
				SDL_BlitSurface (images[IMG_CHECKED], NULL, screen, &rect);
				
				rect.y = 139;
			}
			
			if (pizza->topping_requested[g] != 0) {
				/* Dibujar el texto */
				if (pizza->topping_requested[g] == 5) {
					temp = texts[TEXT_5_TOPPING_1 + g];
				} else {
					temp = texts[TEXT_2_TOPPING_1 + g];
				}
				
				rect2.w = temp->w;
				rect2.h = temp->h;
			
				SDL_BlitSurface (temp, NULL, screen, &rect2);
				rect2.y = 142;
			}
		}
	} else if (orden >= 22) {
		/* Ordenes con 4 ingredientes */
		rect.x = 524;
		rect.w = images[IMG_CHECKED]->w;
		rect.h = images[IMG_CHECKED]->h;
		
		rect2.x = 544;
		for (g = 0; g < 4; g++) {
			
			rect2.y = 95 + (g * 18);
			
			temp = texts[TEXT_1_TOPPING_1 + g];
			
			rect2.w = temp->w;
			rect2.h = temp->h;
			
			SDL_BlitSurface (temp, NULL, screen, &rect2);
			if (pizza->topping_requested[g] != 0 && pizza->topping[g] >= pizza->topping_requested[g]) {
				rect.y = 92 + (g * 18);
				
				SDL_BlitSurface (images[IMG_CHECKED], NULL, screen, &rect);
			}
			
		}
	}
}

int map_button_in_opening_old (int x, int y) {
	if (x >= 721 && x < 749 && y >= 9 && y < 37) return BUTTON_CLOSE;
	if (x >= 49 && x < 176 && y >= 425 && y < 476) return BUTTON_UI_INTRO_PLAY;
	return BUTTON_NONE;
}

int map_button_in_opening_new (int x, int y) {
	if (x >= 721 && x < 749 && y >= 9 && y < 37) return BUTTON_CLOSE;
	if (x >= 16 && x < 211 && y >= 365 && y < 408) return BUTTON_UI_INTRO_PLAY;
	if (x >= 16 && x < 211 && y >= 420 && y < 463) return BUTTON_UI_INTRO_HOW;
	return BUTTON_NONE;
}

int map_button_in_opening_new_how (int x, int y) {
	if (x >= 721 && x < 749 && y >= 9 && y < 37) return BUTTON_CLOSE;
	if (x >= 582 && x < 710 && y >= 396 && y < 438) return BUTTON_UI_INTRO_HOW_PLAY;
	return BUTTON_NONE;
}

int map_button_in_game (int x, int y) {
	if (x >= 721 && x < 749 && y >= 9 && y < 37) return BUTTON_CLOSE;
	return BUTTON_NONE;
}

int map_button_in_finish (int x, int y) {
	if (x >= 721 && x < 749 && y >= 9 && y < 37) return BUTTON_CLOSE;
	if (x >= 49 && x < 176 && y >= 428 && y < 476) return BUTTON_END_DONE;
	
	return BUTTON_NONE;
}

