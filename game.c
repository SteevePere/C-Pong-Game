#include "game.h"

/////JEU/////

//Destruction du jeu
void	game_destroy(t_game *game) {

	if (game) {
		if (game->pTexPlayer2) {
			SDL_DestroyTexture(game->pTexPlayer2);
		} if (game->pTexBallon) {
			SDL_DestroyTexture(game->pTexBallon);
		} if (game->pTexPlayer) {
			SDL_DestroyTexture(game->pTexPlayer);
		} if (game->pRender) {
			SDL_DestroyRenderer(game->pRender);
		} if (game->pWindows) {
			SDL_DestroyWindow(game->pWindows);
		} if (game->pScore) {
                        SDL_DestroyTexture(game->pScore);
                } if (game->pCountdown1) {
                        SDL_DestroyTexture(game->pCountdown1);
                } if (game->pCountdown2) {
                        SDL_DestroyTexture(game->pCountdown2);
                } if (game->pCountdown3) {
                        SDL_DestroyTexture(game->pCountdown3);
                } if (game->pYou_win) {
                        SDL_DestroyTexture(game->pYou_win);
                } if (game->pMenu) {
                        SDL_DestroyTexture(game->pMenu);
                }

		SDL_Quit();
		free(game);
	}
}

//Affichage du jeu
void	game_draw(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2) {

	SDL_Event event;
	int quit;

	quit = 0;

	//baballe
	SDL_Rect game_ball;
	game_ball.x = ball->x;
	game_ball.y = ball->y;
	game_ball.w = ball->w;
	game_ball.h = ball->h;

	//compte à rebours
	SDL_Rect countdown;
        countdown.x = 384;
        countdown.y = 384;
        countdown.w = 32;
        countdown.h = 32;

	//you win gauche
	SDL_Rect victory1;
        victory1.x = 136;
        victory1.y = 384;
        victory1.w = 128;
        victory1.h = 32;

	//you win droite
	SDL_Rect victory2;
        victory2.x = 536;
        victory2.y = 384;
        victory2.w = 128;
        victory2.h = 32;

	//filet
	SDL_Rect net;
	net.x = game->screenSize.x /2;
	net.y = 0;
	net.w = 2;
	net.h = 800;

	//bande de chiffres de gauche
	SDL_Rect game_score_player1;
	game_score_player1.x = game->gamecover.x;
	game_score_player1.y = 765;
	game_score_player1.w = 320;
	game_score_player1.h = 32;

	//bande de chiffres de droite
	SDL_Rect game_score_player2;
        game_score_player2.x = game->gamecover2.x;
        game_score_player2.y = 765;
        game_score_player2.w = 320;
        game_score_player2.h = 32;

	//couverture de la bande de chiffres de gauche (partie droite)
	SDL_Rect game_score_cover;
        game_score_cover.x = cover->x;
        game_score_cover.y = cover->y;
        game_score_cover.w = cover->w;
        game_score_cover.h = cover->h;

	//couverture de la bande de chiffres de droite (partie droite)
	SDL_Rect game_score_cover2;
        game_score_cover2.x = cover2->x;
        game_score_cover2.y = cover2->y;
        game_score_cover2.w = cover2->w;
        game_score_cover2.h = cover2->h;

	//couverture de la bande de chiffres de gauche (partie gauche)
	SDL_Rect game_score_cover_left;
	game_score_cover_left.x = 0;
	game_score_cover_left.y = 765;
	game_score_cover_left.w = 184;
	game_score_cover_left.h = 32;

	//couverture de la bande de chiffres de droite (partie gauche)
	SDL_Rect game_score_cover_right;
        game_score_cover_right.x = 402;
        game_score_cover_right.y = 765;
        game_score_cover_right.w = 190;
        game_score_cover_right.h = 32;

	//message de premier service
	SDL_Rect first_serve_message;
        first_serve_message.x = 25;
        first_serve_message.y = 300;
        first_serve_message.w = 750;
        first_serve_message.h = 200;

	SDL_SetRenderDrawColor(game->pRender,0,0,0,255);
        SDL_RenderClear(game->pRender);
        SDL_RenderCopy(game->pRender,game->pTexPlayer,NULL,&game->playerPosition);
	SDL_RenderCopy(game->pRender,game->pTexPlayer2,NULL,&game->playerPosition2);
	SDL_RenderCopy(game->pRender,game->pScore,NULL,&game_score_player1);
	SDL_RenderCopy(game->pRender,game->pScore,NULL,&game_score_player2);
	SDL_RenderFillRect(game->pRender, &game_score_cover2);
	SDL_RenderFillRect(game->pRender, &game_score_cover);
	SDL_RenderCopy(game->pRender,game->pTexBallon,NULL,&game_ball);
	SDL_RenderCopy(game->pRender,game->pTexNet,NULL,&net);
	SDL_RenderFillRect(game->pRender, &game_score_cover_left);
	SDL_RenderFillRect(game->pRender, &game_score_cover_right);

	//attente du lancement de la balle
	while (game->draw_counter == 0) {

		SDL_RenderCopy(game->pRender,game->pFirstServeMsg,NULL,&first_serve_message);
		SDL_RenderPresent(game->pRender);

		if (SDL_PollEvent(&event)) {
                        if (event.type == SDL_KEYDOWN) {
                                switch(event.key.keysym.sym) {
                                case SDLK_SPACE :
                                        game->draw_counter = 1;
                                        break;
				case SDLK_ESCAPE :
					quit = -1;
					break;
				case SDLK_m :
					game->draw_counter = 12; //sortie de boucle
					game->state = 0;
					break;
                                }
                        }
                }
	}

	//compte à rebours
	if (game->draw_counter == 2) {
                SDL_RenderCopy(game->pRender,game->pCountdown3,NULL,&countdown);
		sleep(1);
	}

	if (game->draw_counter == 3) {
                SDL_RenderCopy(game->pRender,game->pCountdown2,NULL,&countdown);
                sleep(1);
        }

	if (game->draw_counter == 4) {
                SDL_RenderCopy(game->pRender,game->pCountdown1,NULL,&countdown);
		sleep(1);
        }

	//affichage post-victoire
	//joueur 1 (gauche)
	if (game->draw_counter == 10 && game->score[0] == 10) {
                SDL_RenderCopy(game->pRender,game->pYou_win,NULL,&victory1);
		SDL_RenderFillRect(game->pRender, &game_score_player2); //cache le score non terminé
		SDL_RenderCopy(game->pRender,game->pTexNet,NULL,&net); //assure que le filet reste entièrement visible
        }

	//joueur 2 (droite)
	if (game->draw_counter == 11 && game->score[1] == 10) {
                SDL_RenderCopy(game->pRender,game->pYou_win,NULL,&victory2);
		SDL_RenderFillRect(game->pRender, &game_score_player1); //cache le score non terminé
		SDL_RenderCopy(game->pRender,game->pTexNet,NULL,&net); //assure que le filet reste entièrement visible
        }

	//affichage des éléments
	SDL_RenderPresent(game->pRender);

	SDL_Event e;
	SDL_PollEvent(&e);

	SDL_Delay(50);
	game->draw_counter += 1; //compteur de frames

}

//Affichage du menu
void    menu_draw(t_game *game) {

	SDL_Rect menu;
        menu.x = 100;
        menu.y = 250;
        menu.w = 600;
        menu.h = 300;

	SDL_SetRenderDrawColor(game->pRender,0,0,0,255);
        SDL_RenderClear(game->pRender);
        SDL_RenderCopy(game->pRender,game->pMenu,NULL,&menu);
	SDL_RenderPresent(game->pRender);
}

//Affichage du message de pause
void    pause_draw(t_game *game) {

        SDL_Rect pause_menu;
        pause_menu.x = 100;
        pause_menu.y = 250;
        pause_menu.w = 600;
        pause_menu.h = 300;

 	SDL_Rect pause;
        pause.x = 20;
        pause.y = 10;
        pause.w = 77;
        pause.h = 32;

        SDL_RenderCopy(game->pRender,game->pPause,NULL,&pause);
        SDL_RenderCopy(game->pRender,game->pPauseMenu,NULL,&pause_menu);
        SDL_RenderPresent(game->pRender);
}

//Affichage du message de confirmation
void    confirmation_draw(t_game *game) {

        SDL_Rect quit_msg;
        quit_msg.x = 25;
        quit_msg.y = 300;
        quit_msg.w = 750;
        quit_msg.h = 200;

	SDL_RenderClear(game->pRender);
        SDL_RenderCopy(game->pRender,game->pQuitMsg,NULL,&quit_msg);
        SDL_RenderPresent(game->pRender);
}

//Gestion des inputs
int		game_event(t_game *game) {

	int	result;

	result = 0;
	SDL_Event e;

	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			result = -1;
		} else if (e.type == SDL_KEYDOWN) {
			switch(e.key.keysym.sym) {
				case SDLK_ESCAPE :
					result = -1;
					break;
				case SDLK_UP :
					game_movePlayer(game, e.key.keysym.sym);
					break;
				case SDLK_DOWN :
					game_movePlayer(game, e.key.keysym.sym);
					break;
				case SDLK_m:
					result = 4;
					break;
				case SDLK_z:
                                        game_movePlayer(game, e.key.keysym.sym);
                                        break;
				case SDLK_s:
					game_movePlayer(game, e.key.keysym.sym);
					break;
				case SDLK_p:
					game->state = 5;
				default:
					fprintf(stderr,"Touche %d \n", e.key.keysym.sym);
					break;
			}
		}
	}
	return result;
}

//Mouvement joueur
void	game_movePlayer(t_game *game, SDL_Keycode direction) {

	if ((direction == SDLK_UP) && (game->playerPosition.y > 40)) {
		game->playerPosition.y -= 40;
		write(game->socket,"up",2);
	} else if (direction == SDLK_DOWN) {
		if ((game->playerPosition.y < game->screenSize.y - game->playerPosition.h) &&
		((game->playerPosition.y < 720))) {
			game->playerPosition.y += 40;
			write(game->socket,"down",4);
		}
	} else if (direction == SDLK_s) {
                if ((game->playerPosition2.y < game->screenSize.y - game->playerPosition2.h) &&
                ((game->playerPosition2.y < 720))) {
                        game->playerPosition2.y += 40;
                        write(game->socket,"down",4);
                }
	} else if ((direction == SDLK_z) && (game->playerPosition2.y > 40)) {
                game->playerPosition2.y -= 40;
                write(game->socket,"up",2);
        }
}

//Initialisation balle
t_ball		*ball_init(t_game *game) {

	t_ball	*ball;
	time_t	t;

	ball = malloc(sizeof(t_ball));
	srand((unsigned) time(&t));

	if (ball == NULL)
		return NULL;

	ball->x = 395;
	ball->y = 395;
	ball->w = 10;
	ball->h = 10;
	ball->dir_y = rand() % 5 + 2;
	ball->dir_x = rand() % 5 + 2;

	return ball;
}

//Ré-initialisation de la balle
void 	reset_ball(t_ball *ball) {

	ball->x = 395;
	ball->y = 395;
	//sleep(1);
}

//Initialisation couverture du score de gauche
t_cover          *cover_init(t_game *game) {

        t_cover  *cover;

        cover = malloc(sizeof(t_cover));

        if (cover == NULL)
                return NULL;

        cover->x = 216;
        cover->y = 765;
        cover->w = 184;
        cover->h = 32;

        return cover;
}

//Initialisation couverture du score de droite
t_cover          *cover2_init(t_game *game) {

        t_cover  *cover2;

        cover2 = malloc(sizeof(t_cover));

        if (cover2 == NULL)
                return NULL;

        cover2->x = 616;
        cover2->y = 765;
        cover2->w = 328;
        cover2->h = 32;

        return cover2;
}

//Initialisation du jeu
t_game	*game_init(t_game *game) {

	game->screenSize.x = 800;
	game->screenSize.y = 800;
	game->pWindows = NULL;
	game->pTexPlayer = NULL;
	game->pRender = NULL;
	game->pTexBallon = NULL;
	game->playerPosition.x = 720;
	game->playerPosition.y = 720;
	game->playerPosition.w = 40;
	game->playerPosition.h = 40;
	game->score[0] = 0;
	game->score[1] = 0;
	game->client = 0;
	game->draw_counter = 0;
	game->gamecover.x = 184;
	game->gamecover2.x = 584;

	if (game == NULL)
		return NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr,"Impossible d'initialiser la SDL: %s\n", SDL_GetError());
		game_destroy(game);
		return NULL;
	}

	game->pWindows = SDL_CreateWindow("Pong",SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, game->screenSize.x, game->screenSize.y, SDL_WINDOW_SHOWN);

	if (game->pWindows) {
		game->pRender = SDL_CreateRenderer(game->pWindows, -1, SDL_RENDERER_ACCELERATED);

		if (!game->pRender) {
			fprintf(stderr,"Impossible d'initialiser le renderer SDL : %s\n", SDL_GetError());
			game_destroy(game);
			return NULL;
		}
	}
	else {
		fprintf(stderr,"Impossible de créer la fenêtre SDL : %s\n", SDL_GetError());
		game_destroy(game);
		return NULL;
	}

	SDL_Surface *surfacePonge = IMG_Load("./joueur.png");

	if (!surfacePonge) {
		fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
		game_destroy(game);
		return NULL;
	}
	else {
		game->pTexPlayer = SDL_CreateTextureFromSurface(game->pRender,surfacePonge);

		if (!game->pTexPlayer) {
			fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
			game_destroy(game);
			return NULL;
		}
		SDL_FreeSurface(surfacePonge);
	}

	SDL_Surface *creatBal = IMG_Load("./ball.jpg");

	if (!creatBal) {
		fprintf(stderr,"Impossible de charger l'image de la balle: %s\n", IMG_GetError());
		game_destroy(game);
		return NULL;
	}
	else {
		game->pTexBallon = SDL_CreateTextureFromSurface(game->pRender,creatBal);

		if (!game->pTexBallon) {
			fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
			game_destroy(game);
			return NULL;
		}
		SDL_FreeSurface(creatBal);
	}

	game->pTexPlayer2 = NULL;
	game->playerPosition2.x = 40;
	game->playerPosition2.y = 40;
	game->playerPosition2.w = 40;
	game->playerPosition2.h = 40;

	SDL_Surface *surfacePlayer = IMG_Load("./joueur.png");

	if (!surfacePlayer) {
		fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
		game_destroy(game);
		return NULL;
	}
	else {
		game->pTexPlayer2 = SDL_CreateTextureFromSurface(game->pRender,surfacePlayer);

		if (!game->pTexPlayer2) {
			fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
			game_destroy(game);
			return NULL;
		}
		SDL_FreeSurface(surfacePlayer);
	}

	game->pScore = NULL;

	SDL_Surface *score = IMG_Load("./score.bmp");

        if (!score) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pScore = SDL_CreateTextureFromSurface(game->pRender,score);

                if (!game->pScore) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(score);
        }

	game->pCountdown1 = NULL;

        SDL_Surface *Countdown1 = IMG_Load("./1.bmp");

        if (!Countdown1) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pCountdown1 = SDL_CreateTextureFromSurface(game->pRender,Countdown1);

                if (!game->pCountdown1) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(Countdown1);
        }

	game->pCountdown2 = NULL;

        SDL_Surface *Countdown2 = IMG_Load("./2.bmp");

        if (!Countdown2) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pCountdown2 = SDL_CreateTextureFromSurface(game->pRender,Countdown2);

                if (!game->pCountdown2) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(Countdown2);
        }

	game->pCountdown3 = NULL;

        SDL_Surface *Countdown3 = IMG_Load("./3.bmp");

        if (!Countdown3) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pCountdown3 = SDL_CreateTextureFromSurface(game->pRender,Countdown3);

                if (!game->pCountdown3) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(Countdown3);
        }

	game->pYou_win = NULL;

        SDL_Surface *Youwin = IMG_Load("./win.bmp");

        if (!Youwin) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pYou_win = SDL_CreateTextureFromSurface(game->pRender,Youwin);

                if (!game->pYou_win) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(Youwin);
        }

	game->pMenu = NULL;

        SDL_Surface *Menu = IMG_Load("./menu.bmp");

        if (!Menu) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pMenu = SDL_CreateTextureFromSurface(game->pRender,Menu);

                if (!game->pMenu) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(Menu);
        }

	game->pFirstServeMsg = NULL;

        SDL_Surface *FirstServeMsg = IMG_Load("./servemsg.bmp");

        if (!FirstServeMsg) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pFirstServeMsg = SDL_CreateTextureFromSurface(game->pRender,FirstServeMsg);

                if (!game->pFirstServeMsg) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(FirstServeMsg);
        }

	game->pTexNet = NULL;

        SDL_Surface *Net = IMG_Load("./net.jpg");

        if (!Net) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pTexNet = SDL_CreateTextureFromSurface(game->pRender,Net);

                if (!game->pTexNet) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(Net);
        }

	SDL_Surface *Pause = IMG_Load("./pause.bmp");

        if (!Pause) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pPause = SDL_CreateTextureFromSurface(game->pRender,Pause);

                if (!game->pPause) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(Pause);
        }

	SDL_Surface *PauseMenu = IMG_Load("./pauseMenu.bmp");

        if (!PauseMenu) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pPauseMenu = SDL_CreateTextureFromSurface(game->pRender,PauseMenu);

                if (!game->pPauseMenu) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(PauseMenu);
        }

	SDL_Surface *QuitMsg = IMG_Load("./quitmsg.bmp");

        if (!QuitMsg) {
                fprintf(stderr,"Impossible de charger l'image: %s\n", IMG_GetError());
                game_destroy(game);
                return NULL;
        }
        else {
                game->pQuitMsg = SDL_CreateTextureFromSurface(game->pRender,QuitMsg);

                if (!game->pQuitMsg) {
                        fprintf(stderr,"Impossible de créer la texture : %s\n", IMG_GetError());
                        game_destroy(game);
                        return NULL;
                }
                SDL_FreeSurface(QuitMsg);
        }

return game;
}

//ré-initialisation du jeu, au cas où plusieurs parties
void	resetGame(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2) {

	ball->x = 390;
      	ball->y = 390;
        ball->w = 10;
        ball->h = 10;
        ball->dir_y = rand() % 5 + 2;
        ball->dir_x = rand() % 5 + 2;
        cover->x = 216;
        cover->y = 765;
        cover->w = 184;
        cover->h = 32;
        cover2->x = 616;
        cover2->y = 765;
        cover2->w = 328;
        cover2->h = 32;
        game->playerPosition.x = 720;
        game->playerPosition.y = 720;
        game->playerPosition.w = 40;
        game->playerPosition.h = 40;
        game->playerPosition2.x = 40;
        game->playerPosition2.y = 40;
        game->playerPosition2.w = 40;
        game->playerPosition2.h = 40;
        game->score[0] = 0;
        game->score[1] = 0;
        game->client = 0;
        game->draw_counter = 0;
        game->gamecover.x = 184;
        game->gamecover2.x = 584;
        game->state = 1;
}

//Mouvements de la balle
void	moveBall(t_game *game, t_ball *ball, t_cover *cover, t_cover *cover2) {

	time_t t;

	srand((unsigned) time(&t));

	//premier service de la partie, jeu dessiné une fois
	if (game->draw_counter == 5) {
		sleep(1);
	}

	//service après point, game->draw_counter a été mis à 5 (+ 1 pour nouveau draw)
	if (game->draw_counter == 6 && ball->x == 395 && ball->y == 395) {
		SDL_Delay(800);
	}

	//fin de partie, un des joueurs est à 10
	if ((game->score[0] == 10) || (game->score[1] == 10)) {
                sleep(3);
                game->state = 0; //retour au menu
        }

	//lancement d'une nouvelle balle
	ball->x = ball->x + ball->dir_x;
	ball->y = ball->y + ball->dir_y;

	//contact avec joueur de droite
	if (ball->x >= game->playerPosition.x && ball->y >= game->playerPosition.y - 20 && ball->y <= game->playerPosition.y + 60) {
		ball->dir_y = -rand() % 10 + 3;
		ball->dir_x = -10;
	}

	//contact avec joueur de gauche
        if (ball->x <= game->playerPosition2.x + 40 && ball->y >= game->playerPosition2.y - 20 && ball->y <= game->playerPosition2.y + 20) {
                ball->dir_y = rand() % 10 + 3;
                ball->dir_x = 10;
        }

	//contact avec mur droite
	if (ball->x >= 790) {
		game->score[0] += 1;
		printf("SCORE : %d",game->score[0]);
		printf(" - %d\n",game->score[1]);
		ball->dir_y = ball->dir_y + 3; //accélération de la balle
		ball->dir_x = -ball->dir_x; //changement de direction (balle au vainqueur du point)
		game->gamecover.x -= 32; //score révélé
		reset_ball(ball); //balle au centre
		SDL_Delay(800); //pause pour montrer contact
		game->draw_counter = 5; //indique qu'un délai doit être appliqué avant le service

		if (game->score[0] == 10) {
                        printf("Le Joueur 1 a gagné la partie ! \n");
                        game->draw_counter = 10;
			ball->w = 0; //cache la balle
			ball->h = 0; //cache la balle
                }
	}

	//contact avec mur gauche
	if ((ball->x <= 0) && (ball->y != 0)) {
                game->score[1] += 1;
		printf("SCORE : %d",game->score[0]);
                printf(" - %d\n",game->score[1]);
                ball->dir_y = ball->dir_y + 3; //accélération de la balle
                ball->dir_x = -ball->dir_x; //changement de direction (balle au vainqueur du point)
		game->gamecover2.x -= 32; //score révélé
		reset_ball(ball); //balle au centre
		SDL_Delay(800); //pause pour montrer contact
		game->draw_counter = 5; //indique qu'un délai doit être appliqué avant le service

        	if (game->score[1] == 10) {
                	printf("Le Joueur 2 a gagné la partie ! \n");
                	game->draw_counter = 11;
			ball->w = 0; //cache la balle
                        ball->h = 0; //cache la balle
        	}
        }

	//contact avec murs horizontaux
	if ((ball->y <= 0) || (ball->y >= 760)) {
                ball->dir_y = -ball->dir_y; //changement de direction
                ball->dir_x = ball->dir_x + 2;
        }
}

/////SERVEUR/////

char		*checkReception(char *str){

	char	*reception;
	int 	cpt;

	if (str == NULL){
		reception = NULL;
	}
	else {
		while(str[cpt]) {
			reception[cpt] = str[cpt];
			cpt++;
		}
	}

	return reception;
}

void		*Server(t_game *game) {

	struct  timeval    timeout;
    	struct 	sockaddr_in addr;
    	struct 	sockaddr_in client_addr;

    	int     sockfd, sockfd2 ,value;
    	fd_set  readfds;
    	int     t[FD_SETSIZE];
    	int     taille=0;
    	char    buf[255];
    	socklen_t sin_size = sizeof(struct sockaddr_in);
    	memset(buf,'\0',255);
    	int 	sockmax=0;
    	int 	j, i, var_tmp;

    	t_client *client;

	client = malloc(sizeof(t_client));

	if (client == NULL)
        	return 0;

	game->playerPosition2.y = 0;
	game->playerPosition2.x = 0;
	game->socket = 0;
	client->my_socket = 0;
	client->flagConnection = 0;
    	client->addr = my_strdup("127.0.0.1");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(12345);
    	addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if (bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) != 0) {
      		perror("bind");
      		exit(1);
    	}

    	var_tmp = listen(sockfd, 1);

	if (var_tmp < 0) {
      		perror("listen() échec");
      		close(sockfd);
      		exit(-1);
    	}

	printf("En attente d'un joueur...\n");

    	t[0]=sockfd;
    	taille++;

	char *dest;

    	do {

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        timeout.tv_sec  = 1 * 60;
		timeout.tv_usec = 0;

        for (j=0;j<taille;j++) {
            if (t[j] != 0) {
                FD_SET(t[j],&readfds);
            } if(sockmax < t[j]) {
                sockmax = t[j];
            }
        }

        var_tmp = select(sockmax+1,&readfds,NULL,NULL,NULL);

	if (var_tmp == -1) {
            perror("select() échec");
            break;
        }

        if (FD_ISSET(sockfd,&readfds)) {

		if ((sockfd2 = accept(sockfd,(struct sockaddr*)&client_addr,&sin_size)) == -1) {
                	perror("Erreur lors de l'accept -> ");
                	exit(-1);
            	}

		game->client = game->client + 1;

		write (sockfd2,"toto",4);
		client->my_socket = sockfd2;
		game->socket = sockfd2;
            	taille++;
            	t[taille-1] = sockfd2;
        }
		memset(buf,'\0',255);

	for (i=1;i<taille;i++) {

            if (FD_ISSET(t[i],&readfds)) {

                if (recv(t[i],&buf,255,0) == -1) {
                    perror("Le client est déconnecté -> ");
                    exit(-1);
                }

		if (read(t[i],buf,sizeof(buf)) == -1) {
                	perror("error");
			exit(-1);
                }

		else if (read(t[i],buf,sizeof(buf)) == 0){
			perror("Echec de la connection");
			exit(-1);
		}

		else {
			printf("Action client %s",buf);

			if (strcmp(buf,"down")==0) {
				printf("Je suis ok pour down");
				game->playerPosition2.y = game->playerPosition2.y += 40;
				SDL_Log("Position: x= %i y=%i",
				game->playerPosition2.x, game->playerPosition2.y);
			}

			else if (strcmp(buf,"up") == 0) {
				printf("Je suis ok pour up");
				game->playerPosition2.y = game->playerPosition2.y -= 40;
			}
		}

            	memset(buf,'\0',255);
            }
        }
    } while (1);
}
