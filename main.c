
#include "game.h"

int		connection_client(char *addr, int port) {
	int	s_socket;
	struct	hostent *server;
	struct	sockaddr_in addrin;
	struct	in_addr adrin;

	s_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (s_socket == -1) {
        	printf("La connection à la socket a echoué \n");
        	return -1;
	}

	bzero(&addrin, sizeof(addrin));
	addrin.sin_family = AF_INET;
	addrin.sin_port = htons(port);

	if (inet_pton(AF_INET,addr,&addrin.sin_addr) <= 0) {
        	return -1;
		printf("Echec");
	}

	if (connect(s_socket,(struct sockaddr*)&addrin, sizeof(addrin)) >= 0)
		printf("Connection serveur réussie \n");
    	else {
		fprintf(stderr,"Echec de la connection \n");
       		return -1;
	}

	return s_socket;
}

int	socket_s;

void		*connection_client_thread() {

	char	*ip = "127.0.0.1";
	int 	port = 12345;

	socket_s = connection_client(ip,port);
}

void		*game_thread(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2){

	int	quit, flagConnection;
	SDL_Event e;
	SDL_Event o;
	SDL_Event a;

	quit, flagConnection = 0;
	game = game_init(game);
	ball = ball_init(game);
	cover = cover_init(game);
	cover2 = cover2_init(game);

	flagConnection = 1;
	game->state = 0;

	while (game->state == 0 || game->state == 6) {

		menu_draw(game);

		if (SDL_PollEvent(&e)) {
   	        	if (e.type == SDL_KEYDOWN) {
                        	switch(e.key.keysym.sym) {
                                case SDLK_1 :
					resetGame(game, ball, cover, cover2);
                                        break;
				case SDLK_2 :
                        	game->state = 2;
							resetGame(game, ball, cover, cover2);
							break;
				case SDLK_3 :
							game->state = 3;
							resetGame(game, ball, cover, cover2);
							break;
				case SDLK_ESCAPE :
							quit = -1;
							break;
                        	}
                	}
        	}

		while ((game->state == 1 || game->state == 6) && (quit != -1)) {

			game_draw(game,ball,cover,cover2);
			quit = game_event(game);
			moveBall(game,ball,cover,cover2);

			if (game_event(game) == 4) {
                        	game->state = 0;
            		}

			if (game->state == 5 || game->state == 6) {
				while (game->state == 5 || game->state == 6) {
					pause_draw(game);
					if (SDL_PollEvent(&o)) {
                        			if (o.type == SDL_KEYDOWN) {
                                			switch (o.key.keysym.sym) {
                                				case SDLK_p :
                                        				game->state = 1;
									break;
								case SDLK_m :
									game->state = 0;
									break;
								case SDLK_ESCAPE :
									game->state = 1;
									quit = -1;
									break;
							}
						}
					}
				}
			}
		}

		while (game->state == 2 && quit != -1) {


			if (game_event(game) == 4) {
                        	game->state = 0;
            }
		}
		while (game->state == 3 && quit != -1) {
			game_draw(game,ball,cover,cover2);
			quit = game_event(game);
			moveBall(game,ball,cover,cover2);

			if (game_event(game) == 4) {
                        	game->state = 0;
            }
		}

		while (quit == -1) {

			confirmation_draw(game);

			if (SDL_PollEvent(&o) && game->state != 0) {
               			if (o.type == SDL_KEYDOWN) {
                       			switch (o.key.keysym.sym) {
                               			case SDLK_y :
                                       			game_destroy(game);
                                        		break;
						case SDLK_n :
							quit = 0;
							game->state = 6;
							break;
					}
				}
			}

			while (game->state == 0 && quit == -1) {
				if (SDL_PollEvent(&a)) {
                                	if (a.type == SDL_KEYDOWN) {
                                        	switch (a.key.keysym.sym) {
                                                	case SDLK_y :
                                                        	game_destroy(game);
                                                        	break;
                                                	case SDLK_n :
                                                        	quit = 0;
                                                        	break;
                                        	}
                                	}
                        	}
			}

		}
	}
}

int	main(void) {

	pthread_t t_server;
	pthread_t th_client;
	pthread_t th_game;
	t_game *game;

	game = malloc(sizeof(t_game));

	if (game == NULL)
		return -1;

	if (pthread_create(&t_server, 0, Server, (t_game *)&game)) {
		perror("pthread_create");
		return -1;
	}

	sleep(2);

	if (pthread_create(&th_client, NULL, connection_client_thread, NULL)) {
		perror("pthread_create");
		return -1;
	}

	if (pthread_join(th_client, NULL)) {
		perror("pthread_join");
		return -1;
	}

	sleep(2);

	if (pthread_create(&th_game, NULL, game_thread, (t_game *)&game)) {
		perror("pthread_create");
		return -1;
    	}

	puts("Client connecté");

	if (pthread_join(th_game, NULL)) {
		perror("pthread_join");
		return -1;
	}

	return 0;
}
