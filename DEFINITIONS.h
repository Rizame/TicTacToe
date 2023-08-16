#pragma once

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 1000
#define SPLASH_STATE_SHOW_TIME 3
#define BEFORE_GAME_OVER_TIME 2

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/SplashBg.jpg"
#define MAIN_MENU_BG_FILEPATH "Resources/res/MainMenuBg.jpg"
#define GAME_BG_FILEPATH "Resources/res/GameMenuBg.jpg"
#define PAUSE_BG_FILEPATH "Resources/res/GameMenuBg.jpg"

#define MAIN_MENU_PLAY_BUTTON "Resources/res/PlayButton.png"
#define MENU_HOME_BUTTON "Resources/res/HomeButton.png"
#define MENU_RESUME_BUTTON "Resources/res/ResumeButton.png"
#define PAUSE_BUTTON "Resources/res/PauseButton.png"
#define RETRY_BUTTON "Resources/res/RetryButton.png"

#define X_SPRITE_FILEPATH "Resources/res/XPiece.png"
#define O_SPRITE_FILEPATH "Resources/res/OPiece.png"
#define X_WIN_SPRITE_FILEPATH "Resources/res/XWinPiece.png"
#define O_WIN_SPRITE_FILEPATH "Resources/res/OWinPiece.png"

#define GRID_SPRITE_FILEPATH "Resources/res/Grid.png"

#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1
#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE

#define STATE_PLAYING 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOST 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92