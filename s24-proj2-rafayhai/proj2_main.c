/**
 * Starter code for Project 2. Good luck!
 *
 * We recommending copy/pasting your HAL folder from Project 1
 * into this project.
 */

#include <HAL/LcdDriver/Crystalfontz128x128_ST7735.h>
#include <proj2_app.h>
#include <HAL/HAL.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define OBSTACLE_DELAY  1000  // 1 second
#define MOVE_DELAY  30  // 30 millisecond
extern const Graphics_Image colors8BPP_UNCOMP;
extern const Graphics_Image sad8BPP_UNCOMP;
extern const Graphics_Image happy8BPP_UNCOMP;

// Non-blocking check. Whenever Launchpad S1 is pressed, LED1 turns on.
static void InitNonBlockingLED() {
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
}
//
//// Non-blocking check. Whenever Launchpad S1 is pressed, LED1 turns on.
static void PollNonBlockingLED() {
  GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
  if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == 0) {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
  }
}

int main(void) {
  WDT_A_holdTimer();
  InitSystemTiming();
  Crystalfontz128x128_Init();
   Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
  Graphics_Context g_sContext;
  Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
  Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
  Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
  Graphics_setFont(&g_sContext, &g_sFontCm12b);
  //Graphics_Context g_sContext;
  Graphics_clearDisplay(&g_sContext);

  HAL hal = HAL_construct();
  App_Proj2 app = App_Proj2_construct(&hal);

//  // Do not remove this line. This is your non-blocking check.
  InitNonBlockingLED();
    // Do not remove this line. This is your non-blocking check.
    //PollNonBlockingLED();
while (true) {
    PollNonBlockingLED();
    HAL_refresh(&hal);
    App_Proj2_loop(&app, &hal, &g_sContext);
  }

}
//when joystick is up x = 8741 y = 8741
//when joystick is right x = 16103 y = 16105
//when joystick is down x = 7282 y = 7281
//when joystick is left x = 19 y = 19

App_Proj2 App_Proj2_construct(HAL* hal_p)
{
    srand(time(NULL));
    static bool display = false;
    // The App_GuessTheColor object to initialize
    App_Proj2 app;
    int i;
    for (i = 0; i < 500; i++) {
        app.scoreValues[i] = 0;
    }


    app.randomNumberChoice = 0;
    for (i = 0; i < 500; i++) {
    strcpy(app.scores[i], "000000\0");
    }
    //strcpy(app.scores[1], "000000\0");
   // strcpy(app.scores[2], "000000\0");
    strcpy(app.Highscores[0], "000000\0");
    strcpy(app.Highscores[1], "000000\0");
    strcpy(app.Highscores[2], "000000\0");

    //all x values start out the screen from the right side
    //adding obstacles in array
    //bottom lane
    //rect that fills half the screen (top)
    app.obstacleArray[0][0].xMin = 122;
    app.obstacleArray[0][0].yMin = 81;
    app.obstacleArray[0][0].xMax = 132;
    app.obstacleArray[0][0].yMax = 93;
    //rect that fills the lane completely
    app.obstacleArray[1][0].xMin = 122;
    app.obstacleArray[1][0].yMin = 81;
    app.obstacleArray[1][0].xMax = 132;
    app.obstacleArray[1][0].yMax = 109;

    //half the screen (bottom)
    //{122, 97, 132, 109}
    app.obstacleArray[6][0].xMin = 122;
    app.obstacleArray[6][0].yMin = 97;
    app.obstacleArray[6][0].xMax = 132;
    app.obstacleArray[6][0].yMax = 109;
    app.instructionDisplay = false;

    //middle line
    //{100, 50, 110, 63};
    //rect that fills half the screen (top)
    app.obstacleArray[2][0].xMin = 122;
    app.obstacleArray[2][0].yMin = 51;
    app.obstacleArray[2][0].xMax = 132;
    app.obstacleArray[2][0].yMax = 63;

    //rect that fills the lane completely
    //{100, 50, 110, 80}
    app.obstacleArray[3][0].xMin = 122;
    app.obstacleArray[3][0].yMin = 51;
    app.obstacleArray[3][0].xMax = 132;
    app.obstacleArray[3][0].yMax = 79;

    //half the screen (bottom)
    //{122, 37, 132, 49}
    app.obstacleArray[7][0].xMin = 122;
    app.obstacleArray[7][0].yMin = 37;
    app.obstacleArray[7][0].xMax = 132;
    app.obstacleArray[7][0].yMax = 49;

    //top lane
    //{122, 21, 132, 33}
    //rect that fills half the screen (top)
    app.obstacleArray[4][0].xMin = 122;
    app.obstacleArray[4][0].yMin = 21;
    app.obstacleArray[4][0].xMax = 132;
    app.obstacleArray[4][0].yMax = 33;

    //rect that fills the lane completely
   // {100, 20, 110, 50}
    app.obstacleArray[5][0].xMin = 122;
    app.obstacleArray[5][0].yMin = 21;
    app.obstacleArray[5][0].xMax = 132;
    app.obstacleArray[5][0].yMax = 49;

    //half the screen (bottom)
    //{122, 37, 132, 49}
    app.obstacleArray[8][0].xMin = 122;
    app.obstacleArray[8][0].yMin = 37;
    app.obstacleArray[8][0].xMax = 132;
    app.obstacleArray[8][0].yMax = 49;
    app.gameScreenDisplay = false;
    app.removeLifeDisplay = false;
    app.gameOver = false;
    app.baudChoice = BAUD_115200;
    UART_SetBaud_Enable(&hal_p->uart, app.baudChoice);

    // Initialization of FSM variables
    app.clearDisplayInResult = false;
    app.displayState = false;
    if (!display) {
    GFX_clear(&hal_p->gfx);
    display = true;
    }
    app.state = TITLE_SCREEN;
    app.timer = SWTimer_construct(TITLE_SCREEN_WAIT);
    SWTimer_start(&app.timer);

    App_Proj2_initGameVariables(&app, hal_p);
    app.ObstacleEnd[0] = false;
    app.ObstacleEnd[1] = false;
    app.ObstacleEnd[2] = false;
    app.obstacleTimer = SWTimer_construct(OBSTACLE_DELAY);
    app.moveTimer = SWTimer_construct(MOVE_DELAY);
    app.cursor = CURSOR_0;
    app.scoreCount = 0;
    app.scoreCounter = 0;
    app.activeObstacles = 0;
    app.indexofScore = 0;
    app.lifeCount = 3;

    // Return the completed Application struct to the user
    return app;

}
unsigned colormix(unsigned r,unsigned g,unsigned b) {

    return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}


/**
 * The main super-loop function of the application. We place this inside of a
 * single infinite loop in main. In this way, we can model a polling system of
 * FSMs. Every cycle of this loop function, we poll each of the FSMs one time.
 */
void App_Proj2_loop(App_Proj2* app_p, HAL* hal_p, Graphics_Context* g_sContext)
{
    //unsigned int r, g, b;
    //r = 25; // red color is kept constant
    //g = hal_p->joystick.x/64;
    //b = hal_p->joystick.y/64;
   // Graphics_setForegroundColor(&hal_p->gfx.context, colormix(r,g,b));
    //Graphics_fillCircle(&hal_p->gfx.context, 64, 64, 20);
    switch (app_p->state)
    {
        case TITLE_SCREEN:
            App_Proj2_showTitleScreen(&hal_p->gfx, app_p);
            break;
        case MAIN_MENU:
            App_Proj2_showMainMenu(app_p,hal_p,&hal_p->gfx);
            break;

        case INSTRUCTIONS_SCREEN:
            App_Proj2_handleInstructionsScreen(app_p, hal_p, &hal_p->gfx);
            break;

        case GAME_SCREEN:
            App_Proj2_handleGameScreen(app_p, hal_p,&hal_p->gfx,  g_sContext);
            break;
        case HIGH_SCORES:
            App_Proj2_handleHighScores(app_p, hal_p, &hal_p->gfx);
            break;

        case RESULT_SCREEN:
            App_Proj2_handleResultScreen(app_p, hal_p, &hal_p->gfx, g_sContext);
            break;

        default:
            break;
    }
}
//displays game over screen
void App_Proj2_handleResultScreen(App_Proj2* app_p, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext) {
    if (!app_p->clearDisplayInResult) {
        app_p->clearDisplayInResult = true;
        Graphics_clearDisplay(g_sContext);

    }

    GFX_print(gfx_p, "GAME OVER", 4, 5);
    GFX_print(gfx_p, "Score:", 6, 6);
    GFX_print(gfx_p, app_p->scores[app_p->scoreCount], 7, 6);
    GFX_print(gfx_p, "(Press JSB to return", 9, 1);
    GFX_print(gfx_p, "to Main Menu)", 10, 2);
    int i;
    for (i = 0; i < 500; i++) {
        if (app_p->obstacles->active) {
            app_p->obstacles->active = false;

        }

    }
    if (Button_isTapped(&hal_p->boosterpackJS)) {
        if (app_p->scoreCount < 500) {
        app_p->scoreCount++;
        app_p->scoreCounter = 0;
        }
        app_p->obstacleTimerInitialized = false;
        app_p->clearDisplayInResult = false;
        app_p->gameScreenDisplay = false;
        app_p->removeLifeDisplay = false;
        app_p->displayState = true;
        app_p->gameOver = true;
        app_p->indexofScore += 1;
        app_p->lifeCount = 3;
        updateHighScores(app_p,  hal_p);
        app_p->state = MAIN_MENU; //change to main menu
        GFX_clear(gfx_p);

    }


}
//compares scores to arrange scores array in descending order
int compare_scores(const void* a, const void* b) {
    // Cast the pointers and dereference to get the values
    int val_a = *(const int*)a;
    int val_b = *(const int*)b;

    if (val_a < val_b) return 1;
    if (val_a > val_b) return -1;
    return 0;
}
void updateHighScores(App_Proj2* app_p, HAL* hal_p) {
    int N = 500;

     // Sort the scoreValues array in descending order
     qsort(app_p->scoreValues, N, sizeof(int), compare_scores);

     int i;
     for (i = 0; i < 3; i++) {

     char score[7] = {0};
     //static int scoreCounter = 0;

     // Convert the score count to a string
     if (app_p->scoreValues[i] == 0) {
         continue;

     }
     sprintf(score, "%d", app_p->scoreValues[i]);

     if (app_p->scoreValues[i] < 1000) {
         strcpy(app_p->Highscores[i], "000");
     } else if (app_p->scoreValues[i] < 10000) {
         strcpy(app_p->Highscores[i], "00");
     }
     else if (app_p->scoreValues[i] < 100000) {
         strcpy(app_p->Highscores[i], "0");
     }
     else {
         strcpy(app_p->Highscores[i], "");
     }

     // Concatenate the actual score to the zeros in app->scores[0]
     strcat(app_p->Highscores[i], score);
     }

}
//displays title screen
void App_Proj2_showTitleScreen(GFX* gfx_p, App_Proj2* app_p)
{
    static bool display = false;
    if (!display) {
    //Graphics_drawImage(&gfx_p->context, &colors8BPP_UNCOMP, 0, 0);

    GFX_print(gfx_p, "Spring 2024 Project", 0, 0);
    GFX_print(gfx_p, "ECE surfers", 1, 0);
    GFX_print(gfx_p, "Rafay Hai", 2, 0);
    display = true;
    }

    if (SWTimer_expired(&app_p->timer))
    {
        app_p->state = MAIN_MENU; //change to main menu
        GFX_clear(gfx_p);
        //App_Proj2_showMainMenu(gfx_p);

    }
}
//writes the high scores screen
void App_Proj2_handleHighScores(App_Proj2* app, HAL* hal_p, GFX* gfx_p) {
    static bool display = false;
    if (!display) {
    GFX_print(gfx_p, "View High Scores", 1, 3);
    GFX_print(gfx_p, "1:", 3, 9);
    GFX_print(gfx_p, app->Highscores[0], 4, 7);
    GFX_print(gfx_p, "2:", 5, 9);
    GFX_print(gfx_p, app->Highscores[1], 6, 7);
    GFX_print(gfx_p, "3:", 7, 9);
    GFX_print(gfx_p, app->Highscores[2], 8, 7);
    GFX_print(gfx_p, "Press JSB to return", 12, 2);
    GFX_print(gfx_p, "to main menu", 13, 2);
    }
    if (Button_isTapped(&hal_p->boosterpackJS)) {
        app->state = MAIN_MENU;
        GFX_clear(gfx_p);
        app->displayState = true;


    }

}
//displays main menu with the 3 options
void App_Proj2_showMainMenu(App_Proj2* app,HAL* hal_p,GFX* gfx_p) {
    static int row = 1;

    static int x = 6;
    static bool display = false;

    if  (app->displayState) {
        app->displayState = false;
        GFX_print(gfx_p, "Play ECE surfers", 6, 3);
        GFX_print(gfx_p, "Instructions", 7, 3);
        GFX_print(gfx_p, "View High Scores", 8, 3);
        GFX_print(gfx_p, ">", x, 1);

    }
    if (!display) {
      //GFX_print(gfx_p, "Main Menu  ", 0, 0);
      GFX_print(gfx_p, "Play ECE surfers", 6, 3);
      GFX_print(gfx_p, "Instructions", 7, 3);
      GFX_print(gfx_p, "View High Scores", 8, 3);
      GFX_print(gfx_p, ">", 6, 1);

      display = true;
    }
    if (row != 3) {
        if (Joystick_isTappedToDown(&hal_p->joystick)) {
            row++;
            GFX_print(gfx_p, " ", x, 1);
            x++;
            GFX_print(gfx_p, ">", x, 1);


        }
        if (row != 1) {
        if (Joystick_isTappedToUp(&hal_p->joystick)) {
            row--;
            GFX_print(gfx_p, " ", x, 1);
            x--;
            GFX_print(gfx_p, ">", x, 1);
        }


        }
    }
    else {
        if (Joystick_isTappedToUp(&hal_p->joystick)) {
            row--;
            GFX_print(gfx_p, " ", x, 1);
            x--;
            GFX_print(gfx_p, ">", x, 1);


        }

    }
    if (row == 1 && Button_isTapped(&hal_p->boosterpackJS)) {
        app->state = GAME_SCREEN;
        GFX_clear(gfx_p);


    }
    if (row == 2 && Button_isTapped(&hal_p->boosterpackJS)) {
        app->state = INSTRUCTIONS_SCREEN;
        app->instructionDisplay = false;
        GFX_clear(gfx_p);


    }
    if (row == 3 && Button_isTapped(&hal_p->boosterpackJS)) {
        app->state = HIGH_SCORES;
        GFX_clear(gfx_p);


    }


}
//displays instructions screen
void App_Proj2_handleInstructionsScreen(App_Proj2* app, HAL* hal_p, GFX* gfx_p) {
    if (!app->instructionDisplay) {
    GFX_print(gfx_p, "Instructions", 0, 0);
    GFX_print(gfx_p, "Avoid the obstacles!", 2, 2);
    GFX_print(gfx_p, "score points by", 3, 2);
    GFX_print(gfx_p, "surviving as long", 4, 2);
    GFX_print(gfx_p, "as possible.", 5, 2);
    GFX_print(gfx_p, "colliding with", 6, 2);
    GFX_print(gfx_p, "an obstacle", 7, 2);
    GFX_print(gfx_p, "will result in", 8, 2);
    GFX_print(gfx_p, "a loss of life.", 9, 2);
    GFX_print(gfx_p, "Press JSB to return", 12, 2);
    GFX_print(gfx_p, "to main menu", 13, 2);
    app->instructionDisplay = true;
    }
    if (Button_isTapped(&hal_p->boosterpackJS)) {
        app->state = MAIN_MENU;
        GFX_clear(gfx_p);
        app->displayState = true;


    }

}
//creates a new obstacle and stores it in obstacle array, and sets initial conditions
void createObstacle(App_Proj2* app) {
    int random_index;
    if (app->activeObstacles < 500) {
        random_index = rand() % 8;
        Obstacle* newObstacle = &app->obstacles[app->activeObstacles++];
        newObstacle->xMin = 122;  // Starting X position
        newObstacle->xMax = 132;  // Ending X position
        newObstacle->rect.xMin = newObstacle->xMin;
        newObstacle->rect.xMax = newObstacle->xMax;
        newObstacle->active = true;
        newObstacle->rect = app->obstacleArray[random_index][0];
        newObstacle->collisionCheck = false;
        newObstacle->lifeLoss = false;
        newObstacle->scoreCount = false;

    }
}
//checks for collision
bool checkCollision(Graphics_Rectangle a, Graphics_Rectangle* b) {
    // Check if one rectangle is to the left of the other
    if (a.xMax < b->xMin || b->xMax < a.xMin) {
       // a->lifeLoss = true;
        return false;
    }

    // Check if one rectangle is above the other
    if (a.yMax < b->yMin || b->yMax < a.yMin) {
       // a->lifeLoss = true;
        return false;
    }

    // If none of the above, then they are colliding
    return true;
}
//allows for collision with the same obstacle that you collided with before
bool afterCollision(App_Proj2* app, Graphics_Rectangle a, Graphics_Rectangle* b) {

    // Check if one rectangle is above the other
    if (a.yMax < b->yMin || b->yMax < a.yMin) {
       // a->lifeLoss = true;
        return false;
    }
    // Check if player is to the right of the obstacle
    if (a.xMin > b->xMax) {
        return true;
    }
    return false;


}
//generates the obstacles, moves them on the screen
void generateObstacles(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext) {

    if (!app->obstacleTimerInitialized) {
        app->activeObstacles = 0;
        //obstacleTimerTwo = SWTimer_construct(5000);
        SWTimer_start(&app->obstacleTimer);
        app->obstacleTimerInitialized = true;
        SWTimer_start(&app->moveTimer);
    }

    if (SWTimer_expired(&app->obstacleTimer)) {
        createObstacle(app); // Creates a new obstacle every second
        SWTimer_start(&app->obstacleTimer); // Restart the timer for the next obstacle
    }

    // Update and draw each obstacle
    if (SWTimer_expired(&app->moveTimer)) {
    int i;
    for (i = 0; i < app->activeObstacles; i++) {
        Obstacle* obs = &app->obstacles[i];
        if (obs->active && obs->xMax > -1) {
            Graphics_fillRectangle(g_sContext, &obs->rect);
            Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext, &obs->rect);
            obs->xMin -= 1;  // Move obstacle to the left
            obs->xMax -= 1;
            obs->rect.xMin = obs->xMin;
            obs->rect.xMax = obs->xMax;

            // Draw obstacle
            Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_fillRectangle(g_sContext, &obs->rect);
            if (afterCollision(app, app->player, &obs->rect)) {
                obs->lifeLoss = false;

            }
            if (checkCollision(app->player, &obs->rect)) {
                obs->collisionCheck = true;
                if (obs->collisionCheck && !obs->lifeLoss) {
                removeLife(app, hal_p,  gfx_p, g_sContext);
                }
                obs->lifeLoss = true;
            }


        }
        else {
            obs->active = false;
            if (!obs->scoreCount) {
            scoreUpdate(&app->scoreCount, app, gfx_p, hal_p);
            }
            obs->scoreCount = true;
           // Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
           // Graphics_fillRectangle(g_sContext, &obs->rect);

        }
        SWTimer_start(&app->moveTimer);
    }
    }
}
//updates the score in-game after the obstacles passes off the screen
//added bonus points for UART score and lives display
void scoreUpdate(int* scoreCount, App_Proj2* app, GFX* gfx_p, HAL* hal_p) {
    char score[7] = {0};
    //static int scoreCounter = 0;
    app->scoreCounter += 500;

    // Convert the score count to a string
    sprintf(score, "%d", app->scoreCounter);


    if (app->scoreCounter < 1000) {
        strcpy(app->scores[app->scoreCount], "000");
    } else if (app->scoreCounter < 10000) {
        strcpy(app->scores[app->scoreCount], "00");
    }
    else if (app->scoreCounter < 100000) {
        strcpy(app->scores[app->scoreCount], "0");
    }
    else {
        strcpy(app->scores[app->scoreCount], "");
    }


    strcat(app->scores[app->scoreCount], score);
    GFX_print(gfx_p, app->scores[app->scoreCount], 1, 10);
    if (UART_canSend(&hal_p->uart)) {
        char prompt[100] = {'\0'}; // Initialize all to null characters

        // Construct the prompt string with snprintf
        snprintf(prompt, sizeof(prompt), "S:%s L: %d", app->scores[app->scoreCount], app->lifeCount);

        // Send the prompt
        int t;
        for (t = 0; prompt[t] != '\0'; t++) {
            UART_sendChar(&hal_p->uart, prompt[t]);
        }
        // Send new line and move right
        UART_sendChar(&hal_p->uart, '\n');
        UART_sendChar(&hal_p->uart, '\r');
    }


    app->scoreValues[app->indexofScore] = app->scoreCounter;
}

//removes a life if player collides with obstacle
void removeLife(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext) {
    //static bool display = false;
    static int lifeCounter =  0;
    static float xMin = 0;
    static int yMin = 0;
    static float xMax = 0;
    static int yMax = 0;
    if (!app->removeLifeDisplay) {
    app->removeLifeDisplay = true;
    xMin = 100;
    yMin = 120;
    xMax = 104;
    yMax = 124;
    lifeCounter = 0;
    app->lifeCount = 3;
    Graphics_Rectangle life = {xMin, yMin, xMax, yMax};
    Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(g_sContext, &life);
    lifeCounter++;
    app->lifeCount--;
    return;
    }
    else {

    xMin -= 20;
    xMax -= 20;
    Graphics_Rectangle life = {xMin, yMin, xMax, yMax};
    Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_fillRectangle(g_sContext, &life);
    lifeCounter++;
    app->lifeCount--;
    if (lifeCounter == 3) {
        app->state = RESULT_SCREEN; //change to main menu
        GFX_clear(gfx_p);
       // Graphics_clearDisplay(g_sContext);
    }
    return;
    }



}


//prompts the game scree with the score, lanes, life and player, and allows for player movement
 void App_Proj2_handleGameScreen(App_Proj2* app, HAL* hal_p, GFX* gfx_p, Graphics_Context* g_sContext) {
    //static bool display = false;
    static float xMin = 11;
    static float yMin = 105;
    static float xMax = 15;
    static float yMax = 109;
    float scale = 100;
    static int row = 1;
    int xIncrement = 4;
    int yIncrement = 30;
    int maxRow = 3;
    int minRow = 1;
    int maxXval = 122;
    int minXval = 6;
    static bool goUp = false;
    static bool goDown = false;

    Graphics_Rectangle player = {xMin, yMin, xMax, yMax};

    if (!app->gameScreenDisplay) {
        SWTimer_start(&app->jumpTimer);
        app->gameScreenDisplay = true;
         xMin = 11;
         yMin = 105;
         xMax = 15;
         yMax = 109;
         row = 1;
         Graphics_Rectangle player = {xMin, yMin, xMax, yMax};
        GFX_print(gfx_p, "Score", 1, 3);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        GFX_print(gfx_p, app->scores[app->scoreCount], 1, 10);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineH(g_sContext, 1,140,20);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineH(g_sContext, 1,140,50);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineH(g_sContext, 1,140,80);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineH(g_sContext, 1,140,110);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        GFX_print(gfx_p, "LIVES", 15, 3);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_Rectangle myRect = {60, 120, 64, 124};
        Graphics_fillRectangle(g_sContext, &myRect);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_Rectangle myRect2 = {80, 120, 84, 124};
        Graphics_fillRectangle(g_sContext, &myRect2);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_Rectangle myRect3 = {100, 120, 104, 124};
        Graphics_fillRectangle(g_sContext, &myRect3);
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_fillRectangle(g_sContext, &player);



    }
    if (xMin <= maxXval || xMax <= maxXval) {
    if (Joystick_isPressedToRight(&hal_p->joystick)) {
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext, &player);
        xMin += xIncrement/scale;
        xMax += xIncrement/scale;
        Graphics_Rectangle player = {xMin, yMin, xMax, yMax};
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_fillRectangle(g_sContext, &player);
    }
    }
    if (xMin >= minXval || xMax >= minXval) {
        if (Joystick_isPressedToLeft(&hal_p->joystick)) {
            Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext, &player);
            xMin -= xIncrement/scale;
            xMax -= xIncrement/scale;
            Graphics_Rectangle player = {xMin, yMin, xMax, yMax};
            Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_fillRectangle(g_sContext, &player);
        }

    }
    if (row != maxRow) {
    if (Joystick_isTappedToUp(&hal_p->joystick)) {
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext, &player);
        yMin -= yIncrement;
        yMax -= yIncrement;
        Graphics_Rectangle player = {xMin, yMin, xMax, yMax};
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_fillRectangle(g_sContext, &player);
        row++;

    }
    }
    if (row != minRow) {
    if (Joystick_isTappedToDown(&hal_p->joystick)) {
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext, &player);
        yMin += yIncrement;
        yMax += yIncrement;
        Graphics_Rectangle player = {xMin, yMin, xMax, yMax};
        Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_fillRectangle(g_sContext, &player);
        row--;

    }
    }
    if (Button_isTapped(&hal_p->boosterpackS1) || goUp || goDown) {
        static bool once = false;
        static bool once2 = false;
        if (app->gameOver) {
            app->gameOver = false;
            goUp = false;
            goDown = false;
            once = false;
            once2 = false;
            return;

        }
        static int yMaximum;
        static float i;
        static int maxJump;
        if (!once) {
        yMaximum = yMax;
        once = true;
        goUp = true;
        i = yMaximum;
        maxJump = yMax - 20;
        }
        if (goUp) {
        if( i > maxJump) {
          //  if (SWTimer_expired(&app->jumpTimer)) {
                Graphics_Rectangle player = {xMin, yMin, xMax, yMax};
                Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
                Graphics_fillRectangle(g_sContext, &player);
                i -= 0.05;
                yMin -= 0.05;
                yMax -= 0.05;
                Graphics_Rectangle player2 = {xMin, yMin, xMax, yMax};
                Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
                Graphics_fillRectangle(g_sContext, &player2);
               // SWTimer_start(&app->jumpTimer);


         //   }
        }
        else {
            goUp = false;
            goDown = true;
        }
        }
        if (goDown) {
            if (!once2) {
                once2 = true;
            i = maxJump;
            }
        if (i <= yMaximum) {
        //    if (SWTimer_expired(&app->jumpTimer)) {
                i+= 0.05;
                Graphics_Rectangle player = {xMin, yMin, xMax, yMax};
                Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_BLACK);
                Graphics_fillRectangle(g_sContext, &player);
                yMin += 0.05;
                yMax += 0.05;
                Graphics_Rectangle player2 = {xMin, yMin, xMax, yMax};
                Graphics_setForegroundColor(g_sContext, GRAPHICS_COLOR_WHITE);
                Graphics_fillRectangle(g_sContext, &player2);
                SWTimer_start(&app->jumpTimer);


           // }
        }
        else {
            goDown = false;
            once = false;
            once2 = false;

        }
        }


    }
    app->player = player;
    generateObstacles(app, hal_p,  gfx_p, g_sContext);

}
void App_Proj2_initGameVariables(App_Proj2* app_p, HAL* hal_p)
{
    // Reset the cursor
    app_p->cursor = CURSOR_0;

    // Deselect each option
    app_p->redSelected = false;
    app_p->greenSelected = false;
    app_p->blueSelected = false;

    // Turn off all LEDs - they don't turn on until a random number is generated
    LED_turnOff(&hal_p->boosterpackRed);
    LED_turnOff(&hal_p->boosterpackGreen);
    LED_turnOff(&hal_p->boosterpackBlue);
}
