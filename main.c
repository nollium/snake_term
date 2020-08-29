#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include "linked_lists/linked_lists.h"
#include <sys/ioctl.h>

#define BG_COLOR    ' '


double  my_sin(double x)
{
    static double   my_table[]=
{0.000000,0.006283,0.012566,0.018848,0.025130,0.031411,0.037690,0.043968,0.050244,0.056519,0.062791,0.069060,0.075327,0.081591,0.087851,0.094108,0.100362,0.106611,0.112856,0.119097,0.125333,0.131564,0.137790,0.144011,0.150226,0.156434,0.162637,0.168833,0.175023,0.181206,0.187381,0.193549,0.199710,0.205863,0.212007,0.218143,0.224271,0.230389,0.236499,0.242599,0.248690,0.254771,0.260842,0.266902,0.272952,0.278991,0.285019,0.291036,0.297042,0.303035,0.309017,0.314987,0.320944,0.326888,0.332820,0.338738,0.344643,0.350534,0.356412,0.362275,0.368125,0.373959,0.379779,0.385584,0.391374,0.397148,0.402906,0.408649,0.414376,0.420086,0.425779,0.431456,0.437116,0.442758,0.448383,0.453990,0.459580,0.465151,0.470704,0.476238,0.481754,0.487250,0.492727,0.498185,0.503623,0.509041,0.514440,0.519817,0.525175,0.530511,0.535827,0.541121,0.546394,0.551646,0.556876,0.562083,0.567269,0.572432,0.577573,0.582690,0.587785,0.592857,0.597905,0.602930,0.607930,0.612907,0.617860,0.622788,0.627691,0.632570,0.637424,0.642253,0.647056,0.651834,0.656586,0.661312,0.666012,0.670686,0.675333,0.679953,0.684547,0.689114,0.693653,0.698165,0.702650,0.707107,0.711536,0.715936,0.720309,0.724653,0.728969,0.733255,0.737513,0.741742,0.745941,0.750111,0.754251,0.758362,0.762443,0.766493,0.770513,0.774503,0.778462,0.782391,0.786288,0.790155,0.793990,0.797794,0.801567,0.805308,0.809017,0.812694,0.816339,0.819952,0.823533,0.827081,0.830596,0.834078,0.837528,0.840945,0.844328,0.847678,0.850994,0.854277,0.857527,0.860742,0.863923,0.867071,0.870184,0.873262,0.876307,0.879316,0.882291,0.885231,0.888136,0.891007,0.893841,0.896641,0.899405,0.902134,0.904827,0.907484,0.910106,0.912692,0.915241,0.917755,0.920232,0.922673,0.925077,0.927445,0.929776,0.932071,0.934329,0.936550,0.938734,0.940881,0.942991,0.945063,0.947098,0.949096,0.951057,0.952979,0.954865,0.956712,0.958522,0.960294,0.962028,0.963724,0.965382,0.967001,0.968583,0.970127,0.971632,0.973099,0.974527,0.975917,0.977268,0.978581,0.979855,0.981091,0.982287,0.983445,0.984564,0.985645,0.986686,0.987688,0.988652,0.989576,0.990461,0.991308,0.992115,0.992883,0.993611,0.994301,0.994951,0.995562,0.996134,0.996666,0.997159,0.997613,0.998027,0.998402,0.998737,0.999033,0.999289,0.999507,0.999684,0.999822,0.999921,0.999980,1.000000,0.999980,0.999921,0.999822,0.999684,0.999507,0.999289,0.999033,0.998737,0.998402,0.998027,0.997613,0.997159,0.996666,0.996134,0.995562,0.994951,0.994301,0.993611,0.992883,0.992115,0.991308,0.990461,0.989576,0.988652,0.987688,0.986686,0.985645,0.984564,0.983445,0.982287,0.981091,0.979855,0.978581,0.977268,0.975917,0.974527,0.973099,0.971632,0.970127,0.968583,0.967001,0.965382,0.963724,0.962028,0.960294,0.958522,0.956712,0.954865,0.952979,0.951057,0.949096,0.947098,0.945063,0.942991,0.940881,0.938734,0.936550,0.934329,0.932071,0.929776,0.927445,0.925077,0.922673,0.920232,0.917755,0.915241,0.912692,0.910106,0.907484,0.904827,0.902134,0.899405,0.896641,0.893841,0.891007,0.888136,0.885231,0.882291,0.879316,0.876307,0.873262,0.870184,0.867071,0.863923,0.860742,0.857527,0.854277,0.850994,0.847678,0.844328,0.840945,0.837528,0.834078,0.830596,0.827081,0.823533,0.819952,0.816339,0.812694,0.809017,0.805308,0.801567,0.797794,0.793990,0.790155,0.786288,0.782391,0.778462,0.774503,0.770513,0.766493,0.762443,0.758362,0.754251,0.750111,0.745941,0.741742,0.737513,0.733255,0.728969,0.724653,0.720309,0.715936,0.711536,0.707107,0.702650,0.698165,0.693653,0.689114,0.684547,0.679953,0.675333,0.670686,0.666012,0.661312,0.656586,0.651834,0.647056,0.642253,0.637424,0.632570,0.627691,0.622788,0.617860,0.612907,0.607930,0.602930,0.597905,0.592857,0.587785,0.582690,0.577573,0.572432,0.567269,0.562083,0.556876,0.551646,0.546394,0.541121,0.535827,0.530511,0.525175,0.519817,0.514440,0.509041,0.503623,0.498185,0.492727,0.487250,0.481754,0.476238,0.470704,0.465151,0.459580,0.453990,0.448383,0.442758,0.437116,0.431456,0.425779,0.420086,0.414376,0.408649,0.402906,0.397148,0.391374,0.385584,0.379779,0.373959,0.368125,0.362275,0.356412,0.350534,0.344643,0.338738,0.332820,0.326888,0.320944,0.314987,0.309017,0.303035,0.297042,0.291036,0.285019,0.278991,0.272952,0.266902,0.260842,0.254771,0.248690,0.242599,0.236499,0.230389,0.224271,0.218143,0.212007,0.205863,0.199710,0.193549,0.187381,0.181206,0.175023,0.168833,0.162637,0.156434,0.150226,0.144011,0.137790,0.131564,0.125333,0.119097,0.112856,0.106611,0.100362,0.094108,0.087851,0.081591,0.075327,0.069060,0.062791,0.056519,0.050244,0.043968,0.037690,0.031411,0.025130,0.018848,0.012566,0.006283,-0.000000,-0.006283,-0.012566,-0.018848,-0.025130,-0.031411,-0.037690,-0.043968,-0.050244,-0.056519,-0.062791,-0.069060,-0.075327,-0.081591,-0.087851,-0.094108,-0.100362,-0.106611,-0.112856,-0.119097,-0.125333,-0.131564,-0.137790,-0.144011,-0.150226,-0.156434,-0.162637,-0.168833,-0.175023,-0.181206,-0.187381,-0.193549,-0.199710,-0.205863,-0.212007,-0.218143,-0.224271,-0.230389,-0.236499,-0.242599,-0.248690,-0.254771,-0.260842,-0.266902,-0.272952,-0.278991,-0.285019,-0.291036,-0.297042,-0.303035,-0.309017,-0.314987,-0.320944,-0.326888,-0.332820,-0.338738,-0.344643,-0.350534,-0.356412,-0.362275,-0.368125,-0.373959,-0.379779,-0.385584,-0.391374,-0.397148,-0.402906,-0.408649,-0.414376,-0.420086,-0.425779,-0.431456,-0.437116,-0.442758,-0.448383,-0.453990,-0.459580,-0.465151,-0.470704,-0.476238,-0.481754,-0.487250,-0.492727,-0.498185,-0.503623,-0.509041,-0.514440,-0.519817,-0.525175,-0.530511,-0.535827,-0.541121,-0.546394,-0.551646,-0.556876,-0.562083,-0.567269,-0.572432,-0.577573,-0.582690,-0.587785,-0.592857,-0.597905,-0.602930,-0.607930,-0.612907,-0.617860,-0.622788,-0.627691,-0.632570,-0.637424,-0.642253,-0.647056,-0.651834,-0.656586,-0.661312,-0.666012,-0.670686,-0.675333,-0.679953,-0.684547,-0.689114,-0.693653,-0.698165,-0.702650,-0.707107,-0.711536,-0.715936,-0.720309,-0.724653,-0.728969,-0.733255,-0.737513,-0.741742,-0.745941,-0.750111,-0.754251,-0.758362,-0.762443,-0.766493,-0.770513,-0.774503,-0.778462,-0.782391,-0.786288,-0.790155,-0.793990,-0.797794,-0.801567,-0.805308,-0.809017,-0.812694,-0.816339,-0.819952,-0.823533,-0.827081,-0.830596,-0.834078,-0.837528,-0.840945,-0.844328,-0.847678,-0.850994,-0.854277,-0.857527,-0.860742,-0.863923,-0.867071,-0.870184,-0.873262,-0.876307,-0.879316,-0.882291,-0.885231,-0.888136,-0.891007,-0.893841,-0.896641,-0.899405,-0.902134,-0.904827,-0.907484,-0.910106,-0.912692,-0.915241,-0.917755,-0.920232,-0.922673,-0.925077,-0.927445,-0.929776,-0.932071,-0.934329,-0.936550,-0.938734,-0.940881,-0.942991,-0.945063,-0.947098,-0.949096,-0.951057,-0.952979,-0.954865,-0.956712,-0.958522,-0.960294,-0.962028,-0.963724,-0.965382,-0.967001,-0.968583,-0.970127,-0.971632,-0.973099,-0.974527,-0.975917,-0.977268,-0.978581,-0.979855,-0.981091,-0.982287,-0.983445,-0.984564,-0.985645,-0.986686,-0.987688,-0.988652,-0.989576,-0.990461,-0.991308,-0.992115,-0.992883,-0.993611,-0.994301,-0.994951,-0.995562,-0.996134,-0.996666,-0.997159,-0.997613,-0.998027,-0.998402,-0.998737,-0.999033,-0.999289,-0.999507,-0.999684,-0.999822,-0.999921,-0.999980,-1.000000,-0.999980,-0.999921,-0.999822,-0.999684,-0.999507,-0.999289,-0.999033,-0.998737,-0.998402,-0.998027,-0.997613,-0.997159,-0.996666,-0.996134,-0.995562,-0.994951,-0.994301,-0.993611,-0.992883,-0.992115,-0.991308,-0.990461,-0.989576,-0.988652,-0.987688,-0.986686,-0.985645,-0.984564,-0.983445,-0.982287,-0.981091,-0.979855,-0.978581,-0.977268,-0.975917,-0.974527,-0.973099,-0.971632,-0.970127,-0.968583,-0.967001,-0.965382,-0.963724,-0.962028,-0.960294,-0.958522,-0.956712,-0.954865,-0.952979,-0.951057,-0.949096,-0.947098,-0.945063,-0.942991,-0.940881,-0.938734,-0.936550,-0.934329,-0.932071,-0.929776,-0.927445,-0.925077,-0.922673,-0.920232,-0.917755,-0.915241,-0.912692,-0.910106,-0.907484,-0.904827,-0.902134,-0.899405,-0.896641,-0.893841,-0.891007,-0.888136,-0.885231,-0.882291,-0.879316,-0.876307,-0.873262,-0.870184,-0.867071,-0.863923,-0.860742,-0.857527,-0.854277,-0.850994,-0.847678,-0.844328,-0.840945,-0.837528,-0.834078,-0.830596,-0.827081,-0.823533,-0.819952,-0.816339,-0.812694,-0.809017,-0.805308,-0.801567,-0.797794,-0.793990,-0.790155,-0.786288,-0.782391,-0.778462,-0.774503,-0.770513,-0.766493,-0.762443,-0.758362,-0.754251,-0.750111,-0.745941,-0.741742,-0.737513,-0.733255,-0.728969,-0.724653,-0.720309,-0.715936,-0.711536,-0.707107,-0.702650,-0.698165,-0.693653,-0.689114,-0.684547,-0.679953,-0.675333,-0.670686,-0.666012,-0.661312,-0.656586,-0.651834,-0.647056,-0.642253,-0.637424,-0.632570,-0.627691,-0.622788,-0.617860,-0.612907,-0.607930,-0.602930,-0.597905,-0.592857,-0.587785,-0.582690,-0.577573,-0.572432,-0.567269,-0.562083,-0.556876,-0.551646,-0.546394,-0.541121,-0.535827,-0.530511,-0.525175,-0.519817,-0.514440,-0.509041,-0.503623,-0.498185,-0.492727,-0.487250,-0.481754,-0.476238,-0.470704,-0.465151,-0.459580,-0.453990,-0.448383,-0.442758,-0.437116,-0.431456,-0.425779,-0.420086,-0.414376,-0.408649,-0.402906,-0.397148,-0.391374,-0.385584,-0.379779,-0.373959,-0.368125,-0.362275,-0.356412,-0.350534,-0.344643,-0.338738,-0.332820,-0.326888,-0.320944,-0.314987,-0.309017,-0.303035,-0.297042,-0.291036,-0.285019,-0.278991,-0.272952,-0.266902,-0.260842,-0.254771,-0.248690,-0.242599,-0.236499,-0.230389,-0.224271,-0.218143,-0.212007,-0.205863,-0.199710,-0.193549,-0.187381,-0.181206,-0.175023,-0.168833,-0.162637,-0.156434,-0.150226,-0.144011,-0.137790,-0.131564,-0.125333,-0.119097,-0.112856,-0.106611,-0.100362,-0.094108,-0.087851,-0.081591,-0.075327,-0.069060,-0.062791,-0.056519,-0.050244,-0.043968,-0.037690,-0.031411,-0.025130,-0.018848,-0.012566,-0.006283,-0.000000,};

    int             size;
    double          inc;
    int             index;

    if (x < 0)
        return (-sin(-x));
    size = sizeof(my_table) / sizeof(double);
    inc = (2 * M_PI) / size;
    index = (x / inc);
    index = index % size;
    return (my_table[index]);
}

double  my_cos(double x)
{
    return (my_sin(M_PI / 2 - x));
}

#define MAX_WIDTH 300
#define MAX_HEIGHT 300
#define BUFFER_SIZE MAX_WIDTH * MAX_HEIGHT

typedef struct s_img
{
    int     width;
    int     height;
    char    buffer[BUFFER_SIZE];
}               t_img;

void    init_img(t_img *img, int width, int height, char bg_c)
{
    img->width = width;
    img->height = height;
    memset(img->buffer, bg_c, BUFFER_SIZE);
}

void    pxl_put(t_img *img, int x, int y, char pxl)
{ 
    if (x < 0 || x > MAX_WIDTH || x > img->width || y < 0 || y > MAX_WIDTH || y > img->width)
        return ;
    (img->buffer)[y * img->width + x] = pxl;
}

void clearScreen()
{
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
	//system("clear");
}

void    flush_buffer(t_img *img)
{
    int y;

    y = -1;
    clearScreen();
    while (++y < img->height)
    {
        write(1, img->buffer + y * img->width, img->width);
        write(1, "\r\n", 2);
    }
}

void    draw_circle(t_img *img, int x, int y, double radius, char pxl)
{
    int pxl_x;
    int pxl_y;
    double  angle;

    angle = 0;
    while (angle < 2 * M_PI)
    {
        pxl_put(img, x + sin(angle) * radius * 2, y + cos(angle) * radius, pxl);
        angle += 0.01;
    }
}

double  my_square(double x)
{
    return (x * x);
}

double my_dist(double x0, double y0, double x1, double y1)
{
    return (sqrt( my_square(x0 - x1) + my_square(y0 - y1) ));
}

int     my_round(double x)
{
    if (x - (int)x >= 0.5)
        return ((int)x + 1);
    else
        return ((int)x);
}

void    draw_circle_fill(t_img *img, int x, int y, double radius, char pxl)
{
    int pxl_x;
    int pxl_y;
    double  angle;
    double  i;
    double  line_inc;

    angle = 0;
    line_inc = 1;
    while (angle < 2 * M_PI)
    {
        i = 0;
        while (i < radius)
        {
            pxl_x = my_round(x + sin(angle) * i);
            pxl_y = my_round(y + cos(angle) * i);
            pxl_put(img, pxl_x, pxl_y, pxl);
            if (my_dist(x, y, pxl_x, pxl_y) > radius)
                fprintf(stderr, "ERR\n");
            i += line_inc;
        }
        angle += 0.01;
    }
}

void    *get_input(void *input)
{
    ssize_t  n;

    while (1)
        *(char *)input = getchar();
    return (NULL);
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:53:41 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/06 20:59:56 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FRAME_CAP           15

#  define ESC_KEY			27

#  define ARROW_UP_KEY		122
#  define ARROW_DOWN_KEY	115
#  define ARROW_LEFT_KEY	113
#  define ARROW_RIGHT_KEY	100

#define BORDER_CHAR '*'

typedef struct  s_cell
{
	int			x;
	int			y;
	int			color;
}				t_cell;

typedef struct  s_snake
{
	t_list		*cells_list;
	int			x;
	int			y;
	int			dir_x;
	int			dir_y;
	int			size;
	int			food_x;
	int			food_y;
	int			food_color;
}               t_snake;

typedef struct	s_game
{
	t_img  	    screen[1];
	t_snake		snake;
    char        key[1];
	int			frame_ready;
}	            t_game;

char    get_letter()
{
    static char letter = 'Z';
    letter = (++letter > 'Z') ? 'A' : letter;
    return (letter);
}

t_cell	*new_cell(int x, int y, int color)
{
	t_cell	*cell;

	cell = malloc(sizeof(t_cell));
	*cell = (t_cell){.x = x, .y = y, .color = color};
	return (cell);
}

void    init_snake(t_snake *snake, t_img *screen)
{
	snake->x = screen->width / 2;
	snake->y = screen->height / 2;
	snake->dir_x = 2;
	snake->dir_y = 0;
	snake->cells_list = ft_lstnew(new_cell(snake->x, snake->y, get_letter()));
	//snake->cells_list->next = ft_lstnew(new_cell(snake->x - snake->dir_x, snake->y - snake->dir_y, 0xFF));
	snake->size = ft_lstsize(snake->cells_list);
}

void	clean_all(t_game *game)
{
    (void)game;
    return  ;
}

int		leave(t_game *game)
{
	clean_all(game);
	exit(0);
}

int	get_random_int()
{
	srand(clock());
	return ((rand() ^ (rand() << 15) ^ ((long long int) rand() << 30)));
}

/*
** YOU SHOULD ALWAYS SWITCH BETWEEN TWO IMAGE BUFFERS TO PREVENT TEARING
** (DOUBLE BUFFERING) 
*/

void	*refresh(t_game *game)
{
	static clock_t	t0 = 0;

	if (game->frame_ready && (!FRAME_CAP
	|| (double)(clock() - t0) > ((double)CLOCKS_PER_SEC / (double)FRAME_CAP)))
	{
        flush_buffer(game->screen);
		t0 = clock();
		game->frame_ready = 0;
	}
	return (NULL);
}

t_cell	*find_cell(t_list *cell_list, int x, int y)
{
	t_cell	*cell;

	while (cell_list)
	{
		cell = cell_list->content;
		if (cell->x == x && cell->y == y)
			return (cell);
		cell_list = cell_list->next;
	}
	return (NULL);
}

int		get_pxl_color(t_img *data, int x, int y)
{
	char    *dst;

	if (x <= 0 || x >= data->width || y <= 0 || y >= data->height)
		return 0;
	dst = data->buffer + (y * data->width + x);
	return (*dst);
}

void	update_cells(t_snake *snake, t_img *screen)
{
	t_list	*node;
	t_list	*last;
	int		new_color;

	if (snake->x == snake->food_x && snake->y == snake->food_y)
	{
		snake->size++;
		new_color = snake->food_color;
		pxl_put(screen, snake->x, snake->y, new_color);
		ft_lstadd_front(&snake->cells_list, ft_lstnew(new_cell(snake->x,snake->y, new_color)));
		snake->food_x = 1 + abs(get_random_int()) % (screen->width - 2);
		snake->food_y = 1 + abs(get_random_int()) % (screen->height - 2);
		while ((snake->food_x - snake->x) % 2 || get_pxl_color(screen, snake->food_x, snake->food_y) != BG_COLOR)
		{
			snake->food_x = 1 + abs(get_random_int()) % (screen->width - 2);
			snake->food_y = 1 + abs(get_random_int()) % (screen->height - 2);
		}	
		pxl_put(screen, snake->food_x, snake->food_y, snake->food_color = get_letter());
		//printf("x%d y%d c 0x%x\n", snake->food_x, snake->food_y, snake->food_color);
		//return ;
	}
	else if ((snake->x + snake->dir_x < 0 || snake->x + snake->dir_x >= screen->width
		|| snake->y + snake->dir_y < 0 || snake->y + snake->dir_y >= screen->height) ||
		(get_pxl_color(screen, snake->x + snake->dir_x, snake->y + snake->dir_y) != BG_COLOR
		&& (snake->x + snake->dir_x != snake->food_x && snake->y + snake->dir_y != snake->food_y)))
		exit(0);
	node = snake->cells_list;
	while (node && node->next)
	{
		if (!(node->next->next))
		{
			last = node->next;
			node->next = NULL;
			last->next = snake->cells_list;
			snake->cells_list = last;
			return ;
		}
		node = node->next;
	}
}

void	update_snake(t_snake *snake, t_img *screen)
{
	t_cell	*cell;

	update_cells(snake, screen);
	cell = snake->cells_list->content;
	pxl_put(screen, cell->x, cell->y, BG_COLOR);
	snake->x += snake->dir_x;
	snake->y += snake->dir_y;
	cell->x = snake->x;
	cell->y = snake->y;
	pxl_put(screen, cell->x, cell->y, cell->color);
	//printf("x%d y%d dx %d dy %d\n",cell->x, cell->y, snake->dir_x, snake->dir_y);
}

void	inputs_handler(t_game *game, char key)
{
	t_snake	*snake;

	snake = &(game->snake);
	if (key == ESC_KEY)
		leave(game);
	if (!(snake->dir_y))
	{
		if (key == ARROW_UP_KEY)
		{
			snake->dir_y = -1;
			snake->dir_x = 0;
		}
		if (key == ARROW_DOWN_KEY)
		{
			snake->dir_y = 1;
			snake->dir_x = 0;
		}
	}
	else if (!(snake->dir_x))
	{
		if (key == ARROW_LEFT_KEY)
		{
			snake->dir_y = 0;
			snake->dir_x = -2;
		}
		if (key == ARROW_RIGHT_KEY)
		{
			snake->dir_y = 0;
			snake->dir_x = 2;
		}
	}
}

int		loop_handler(t_game *game)
{
	if (!game->frame_ready)
	{
		inputs_handler(game, *game->key);
		update_snake(&(game->snake), game->screen);
		game->frame_ready = 1;
	}
	refresh(game);
	return (0);
}

int main(void)
{
    int     y = -1;
    pthread_t   id;
    t_game game;
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    //printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col)

    init_img(game.screen, w.ws_col, w.ws_row - 1, BG_COLOR);
    //draw_circle_fill(img, img->width / 2, img->height / 2, 20, '+');
    //flush_buffer(img);
    memset(game.screen->buffer, BORDER_CHAR, game.screen->width);
    memset(game.screen->buffer + (game.screen->height - 1) * game.screen->width, BORDER_CHAR, game.screen->width);
	while (++y < game.screen->height)
	{
		pxl_put(game.screen, 0,y, BORDER_CHAR);
		pxl_put(game.screen, game.screen->width - 1, y, BORDER_CHAR);
	}
    game.key[0] = 0;
    system("stty raw");
    pthread_create(&id, NULL, get_input, game.key);

    init_snake(&game.snake, game.screen);
	game.snake.food_x = 1 + abs(get_random_int()) % (game.screen->width - 2);
	game.snake.food_y = 1 + abs(get_random_int()) % (game.screen->height - 2);
	while ((game.snake.food_x - game.snake.x) % 2 || get_pxl_color(game.screen, game.snake.food_x, game.snake.food_y) != BG_COLOR)
	{
		game.snake.food_x = 1 + abs(get_random_int()) % (game.screen->width - 2);
		game.snake.food_y = 1 + abs(get_random_int()) % (game.screen->height - 2);
	}	
    game.snake.food_color = get_letter();
    pxl_put(game.screen, game.snake.food_x, game.snake.food_y, game.snake.food_color);
    while (1)
    {
        
       // if (game.key[0] == ARROW_DOWN_KEY)
       //     exit(0);
        loop_handler(&game);
    }
    return (0);
}

void after_main() __attribute__((destructor));

void after_main()
{
    system("stty cooked");
}