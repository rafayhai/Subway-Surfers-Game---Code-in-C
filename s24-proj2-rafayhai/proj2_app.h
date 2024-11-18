/*
 * App_Proj2.h
 *
 *  Created on: Dec 29, 2019
 *      Author: Matthew Zhong
 */

#ifndef Proj2_APP_H_
#define Proj2_APP_H_

#include <HAL/HAL.h>
#include <HAL/Graphics.h>
#include <HAL/Timer.h>
#include "HAL/LcdDriver/Crystalfontz128x128_ST7735.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>

#define TITLE_SCREEN_WAIT   3000  //3 seconds
#define RESULT_SCREEN_WAIT  3000  // 3 seconds

#define NUM_TEST_OPTIONS    4
#define NUM_RANDOM_NUMBERS  5

typedef struct {
    Graphics_Rectangle rect;
    float xMin;
    float xMax;
    bool active;
    bool collisionCheck;
    bool lifeLoss;
    bool scoreCount;
} Obstacle;


enum _GameState
{
    TITLE_SCREEN, MAIN_MENU, INSTRUCTIONS_SCREEN, GAME_SCREEN, RESULT_SCREEN, HIGH_SCORES
};
typedef enum _GameState GameState;

enum _Cursor
{
    CURSOR_0 = 0, CURSOR_1 = 1, CURSOR_2 = 2, CURSOR_3 = 3
};
typedef enum _Cursor Cursor;

/**
 * The top-level Application object, initialized in the main() entry point and
 * passed around to basically every other function. Holds state variables
 * which YOU define as part of your application's state.
 */
struct _App_Proj2
{
    UART_Baudrate baudChoice;
    GameState state;  // Determines which screen is currently shown
    SWTimer timer;    // General-purpose timer for when screens must disappear

    // Booleans to determine which colors the user has picked
    bool redSelected;
    bool greenSelected;
    bool blueSelected;
    char scores[500][9];
    char Highscores[3][9];
    int scoreValues[500];
    int indexofScore;
    bool ObstacleEnd[3];
    Graphics_Rectangle obstacleArray[9][4];
    Graphics_Rectangle player;
    bool instructionDisplay;

    Obstacle obstacles[500];
    int activeObstacles;
    SWTimer obstacleTimer;
    SWTimer moveTimer;
    SWTimer jumpTimer;
    bool obstacleTimerInitialized;
    int scoreCount; //keeps track of score index
    int scoreCounter; //represents game score
    int lifeCount; //keeps track of lives
    bool gameOver; //determines if game is over

    // Cursor tracker variable
    Cursor cursor;
   // Graphics_Context* g_sContextOne;

    // List of predetermined random numbers
    int randomNumbers[NUM_RANDOM_NUMBERS];
    int randomNumberChoice;
    bool displayState;
    bool clearDisplayInResult;
    bool gameScreenDisplay;
    bool removeLifeDisplay;
};
typedef struct _App_Proj2 App_Proj2;

// Boilerplate constructor function for the Application
void updateHighScores(App_Proj2* app_p, HAL* hal_p);
App_Proj2 App_Proj2_construct(HAL* hal_p);
void App_Proj2_loop(App_Proj2* app_p, HAL* hal_p, Graphics_Context* g_sContext);
void App_Proj2_showMainMenu(App_Proj2* app, HAL* hal_p, GFX* gfx_p);
void obstaclePlayerTwo(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext, bool* obstacleTwoSent, bool* SecondTimer);
void obstaclePlayerThree(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext, bool* obstacleThreeSent, bool* thirdTimer);

// Handle callback functions used for each state of the App_Proj2_loop()
// function. State transitions are embedded inside of each of these functions.
//void App_Proj2_handleTitleScreen(App_Proj2* app, HAL* hal);
void App_Proj2_handleInstructionsScreen(App_Proj2* app, HAL* hal_p, GFX* gfx_p);
void App_Proj2_handleGameScreen(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext);
//void App_Proj2_handleResultScreen(App_Proj2* app, HAL* hal_p, GFX* gfx_p);
void App_Proj2_handleHighScores(App_Proj2* app, HAL* hal_p, GFX* gfx_p);
//function that generates obstacles
void generateObstacles(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext);


// Helper functions which clear the screen and draw the text for each state
void App_Proj2_showTitleScreen(GFX* gfx_p, App_Proj2* app_p);
void App_Proj2_showInstructionsScreen(App_Proj2* app_p, GFX* gfx_p);
void App_Proj2_showGameScreen(App_Proj2* app_p, GFX* gfx_p);
void App_Proj2_handleResultScreen(App_Proj2* app_p, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext);
void scoreUpdate(int* scoreCount, App_Proj2* app, GFX* gfx_p, HAL* hal_p);
void setScoreCount(int score, App_Proj2* app);

void removeLife(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext);

// Helper function which reduces the number of redraws required when moving the
// cursor.
void App_Proj2_updateGameScreen(App_Proj2* app_p, GFX* gfx_p);

// Used to reset the internal game variables
void App_Proj2_initGameVariables(App_Proj2* app_p, HAL* hal_p);

#endif /* Proj2_APP_H_ */
