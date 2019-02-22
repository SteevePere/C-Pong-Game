#ifndef GAME_H
#define	GAME_H

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<SDL2/SDL.h>
#include	<SDL2/SDL_image.h>
#include	<SDL2/SDL_main.h>
#include	<SDL2/SDL_thread.h>
#include 	<unistd.h>
#include 	<sys/socket.h>
#include 	<sys/types.h>
#include 	<netinet/in.h>
#include 	<netdb.h>
#include 	<arpa/inet.h>
#include 	<pthread.h>
#include 	<sys/ioctl.h>
#include 	<sys/time.h>
#include 	<errno.h>

typedef struct	s_client {
	char 	*addr;
	int  	port;
	int	my_socket;
	int 	flagConnection;
}t_client;

typedef struct 		s_game {
	SDL_Point	screenSize;
	SDL_Window	*pWindows;
	SDL_Renderer	*pRender, *pRenderPlayer;
	SDL_Texture	*pTexPlayer;
	SDL_Texture	*pScore;
	SDL_Texture	*pCountdown1;
	SDL_Texture     *pCountdown2;
	SDL_Texture     *pCountdown3;
	SDL_Texture	*pYou_win;
	SDL_Texture	*pMenu;
	SDL_Texture	*pFirstServeMsg;
	SDL_Rect	gamecover;
	SDL_Rect	gamecover2;
	SDL_Texture 	*pTexBallon;
	SDL_Texture	*pTexNet;
	SDL_Texture     *pPause;
	SDL_Texture     *pPauseMenu;
	SDL_Texture	*pQuitMsg;
	SDL_Rect	playerPosition;
	SDL_Texture	*pTexPlayer2;
	SDL_Rect	playerPosition2;
	t_client 	*pclient;

	int		draw_counter;
	int 		client;
	int 		socket;
	int             state;
	int 		score[];
}t_game;

typedef struct		s_ball {
	int 		x; //position x
	int 		y; //position y
	int 		w; //width
	int 		h; //height
	int 		dir_x; //movement x
	int 		dir_y; //movement y
}t_ball;

typedef struct		s_cover {
        int 		x;
        int 		y;
        int 		w;
        int 		h;
}t_cover;

typedef struct 		s_player {
	SDL_Texture	*pTexPlayer;
	SDL_Rect	playerPosition;

}t_player;

t_game	*game_init(t_game *game);
t_ball 	*ball_init(t_game *game);
t_cover	*cover_init(t_game *game);
t_cover *cover2_init(t_game *game);
void	game_destroy(t_game *game);
void	game_draw(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2);
int	game_event(t_game *game);
void	game_movePlayer(t_game *game, SDL_Keycode direction);
void    reset_ball(t_ball *ball);
void	moveBall(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2);
int	connection_client(char *addr, int port);
void	*Server(t_game *game);
void	*connection_client_thread();
void	*game_thread(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2);
char	*my_strcpy(char *dest, char *src);
char	*my_strcpy(char *dest, char *src);
char    *my_strdup(char *str);
void    menu_draw(t_game *game);
void    pause_draw(t_game *game);
void    confirmation_draw(t_game *game);
void    resetGame(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2);

#endif
