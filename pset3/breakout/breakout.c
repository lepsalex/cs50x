//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle dimensions and vectors
#define PWIDTH 64
#define PHEIGHT 4
#define PADX ((WIDTH / 2) - (PWIDTH/2))
#define PADY HEIGHT-60

// ball dimensions and vectors
#define BWIDTH 16
#define BHEIGHT 16
#define BALLX ((WIDTH / 2) - (BWIDTH/2))
#define BALLY ((HEIGHT / 2) - (BHEIGHT/2))

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // game paused state
    bool gamePaused = true;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {                
        // initial velocity variable (randomize x for fun)
        double xvelocity = drand48() * 1.5 + 1;
        
        // Randomize direction based on drand
        if (drand48() >= 0.5)
            xvelocity = -xvelocity;
        
        // inital y velocity
        double yvelocity = 2.0;
        
        // check for mouse click event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            // if the event was click
            if (getEventType(event) == MOUSE_CLICKED)
            {
                gamePaused = false;
                
                // RE-INIT Ball Location on start
                setLocation(ball, BALLX, BALLY);
            }
        }
        
        while (gamePaused == false)
        {
            // Tracks mouse movement and moves paddle to match (x-axis only)
            GEvent event = getNextEvent(MOUSE_EVENT);
            if (event != NULL)
            {
                if (getEventType(event) == MOUSE_MOVED)
                {
                    double x = getX(event) - getWidth(paddle) / 2;
                    // Eensures that the entire paddle remains on screen
                    if (x > 0 && x < WIDTH - PWIDTH)
                        setLocation(paddle, x, PADY);
                }
            }
            
            // move ball along x-axis
            move(ball, xvelocity, yvelocity);

            // bounce off right edge of window
            if (getX(ball) + BWIDTH >= getWidth(window))
            {
                xvelocity = -xvelocity;
            }

            // bounce off left edge of window
            else if (getX(ball) <= 0)
            {
                xvelocity = -xvelocity;
            }
            
            // bounce off top edge of window
            else if (getY(ball) <= 0)
            {
                yvelocity = -yvelocity;
            }
            
            // if bottom edge, pause game, incremenet score, reduce one life
            else if (getY(ball) + BHEIGHT >= getHeight(window))
            {
                gamePaused = true;
                lives--;
            }
            
            // Check for collisions
            GObject object = detectCollision(window, ball);
            
            // If collision with rectangle reverse y-vector
            if (object != NULL)
            {
                if (strcmp(getType(object), "GRect") == 0)
                {
                    yvelocity = -yvelocity;
                    
                    // If it's not the paddle, remove brick, increment score and points, decrement bricks, update score
                    if (object != paddle)
                    {
                        removeGWindow(window, object);
                        points++;
                        bricks--;
                        updateScoreboard(window, label, points);
                        
                        // If last brick is broken then pause (game will end here)
                        if (bricks == 0)
                            gamePaused = true;
                    }
                }
            }

            // linger before moving again
            pause(10);
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Colours Array
    string colours[] = {"BLUE", "CYAN", "MAGENTA", "ORANGE", "RED"};
    
    // Create grid of brick
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            // Sets grid with 2px spacing inside, 1px outside and 64px gap from top
            GRect brick = newGRect((38 * j + 2 * j + 1), (12 * i + 2 * i + 64), 36, 10);
            setColor(brick, colours[i]);
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // Instantiate paddle
    GOval ball = newGOval(BALLX, BALLY,BWIDTH, BHEIGHT);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    // Return paddle
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Instantiate paddle
    GRect paddle = newGRect(PADX, PADY, PWIDTH, PHEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    
    // Return paddle
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate label
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-48");
    setColor(label, "GRAY");
    add(window, label);
    
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
