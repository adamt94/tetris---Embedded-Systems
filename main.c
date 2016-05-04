

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery_sdram.h"
#include "RTE_Components.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#include "Board_Buttons.h"
#include "main.h"
#include "stdlib.h"
#include "globals.h"
#include "gameLoop.h"
#include "output.h"
#include "setup.h"
#include "block.h"
#include <time.h>

#include "gfx.h" //uGFX library header


#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void) {
  return os_time;
}
#endif

//The game area
Bucket bucket;

//Tetris pieces
Block *currentPiece;
Block *nextPiece;
color_t tetrisShapeColors[9] = {White, Yellow, Red, Blue, Magenta, SkyBlue, Orange,Lime,Black}; 
//Size of the blocks used
const int BLOCK_SIZE = 15;
int Score = 0;
int totaltime = 0;
//Touch screen status
TOUCH_STATE  tsc_state;
bool stillPressed = false;

/**
  * System Clock Configuration
  *   System Clock source            = PLL (HSE)
  *   SYSCLK(Hz)                     = 200000000
  *   HCLK(Hz)                       = 200000000
  *   AHB Prescaler                  = 1
  *   APB1 Prescaler                 = 4
  *   APB2 Prescaler                 = 2
  *   HSE Frequency(Hz)              = 25000000
  *   PLL_M                          = 25
  *   PLL_N                          = 400
  *   PLL_P                          = 2
  *   PLL_Q                          = 8
  *   VDD(V)                         = 3.3
  *   Main regulator output voltage  = Scale1 mode
  *   Flash Latency(WS)              = 6
  */
static void SystemClock_Config (void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the OverDrive to reach the 200 MHz Frequency */
  HAL_PWREx_EnableOverDrive();

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
}

/**
  * CPU L1-Cache enable
  */
static void CPU_CACHE_Enable (void) {

  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

/*--------------------------------------------------
 *      Thread 1 'taskGLCD':   for drawing the main gameplay screen
 *--------------------------------------------------*/
void taskGLCD (void const *argument) {
	for(;;){
		osMutexWait(mut_GLCD, osWaitForever);		//Attempt to acquire GLCD mutex
		//Erase the block's last position
		eraseBlock();
		//Print the tetris bucket
		printTetrisBucket();
		//print score
		printScoreWindow();
		//print next block
		printNextBrickWindow();
		//Clear bucket if there is a full row
		if(checkForFullRows() == 1){
					gdispClear(tetrisShapeColors[0]);
			}
		osMutexRelease(mut_GLCD);	//Release control of GLCD
		//Wait
		osDelay(1000);
	}
	
}

/*--------------------------------------------------
 *      Thread 2 'taskGameLogic':   
 *--------------------------------------------------*/
void taskGameLogic (void const *argument) {
	int delay =10000;
	for(;;){
		//Make the block fall one position
		attemptMove('D');
		//speed up game as score goes up
		if(delay >5000){
		delay = 10000 - (Score*50);
		}
		//THRESHOLD
		if(delay <5000)
		{
			delay = 5000 - (Score *10);
		}
		if(delay<500)
		{
			delay = 500;
		}
		
		//Wait for one second
		osDelay(delay);
	}
}

/*--------------------------------------------------
 *      Thread 3 'taskInput':   
 *--------------------------------------------------*/
void taskInput (void const *argument) {
	int initXpos;			/* initial screen touch x pos*/
	int initYpos;			/* initial screen touch y pos*/
	int initTime = 0;																/* initial time on touch */
	uint8_t but;
	uint8_t buf;
	int delaymove = 0;
	bool canmove = true;
	for(;;){
		//Apply changes to the block
		Touch_GetState (&tsc_state); /* Get touch state */
		if(tsc_state.pressed == true && stillPressed == false){
				stillPressed = true;
				initXpos = tsc_state.x; // gets the  x pos when pressed
			  initYpos = tsc_state.y; // gets the  y pos when pressed
				initTime = HAL_GetTick(); //gets the  time when pressed
			}
			
			//On board button rotate block
		   but = (uint8_t)(Buttons_GetState ());
			if (but ^ buf) {
      buf = but;
				if(delaymove>40){
				rotateBlock('R');
					delaymove = 0;
				}
		
			}
			
			//counts to 20 to create delay when moving
			delaymove +=1;
			//check if not a touch and hold
			if(initTime!=0 && delaymove > 20){
				//check is press was in the tetris area 
				if(tsc_state.x > bucket.x && tsc_state.x < bucket.x+200 & tsc_state.pressed == true){
					attemptMove('D');
					delaymove= 0;
				}else{
				
				//check where on screen it was pressed and move block accordinly 
				if(((bucket.x + (currentPiece->x * BLOCK_SIZE)) > tsc_state.x) && tsc_state.pressed == true ){
					attemptMove('L');
					delaymove = 0;
				}
				if(((bucket.x + (currentPiece->x * BLOCK_SIZE)) <tsc_state.x) &&tsc_state.pressed == true ){
					attemptMove('R');
					delaymove = 0;
					}
				}
		}
			
			// Is the touch screen still being pressed from the previous loop? (prevent rotating multiple times from one touch)
			if(tsc_state.pressed == false){
				stillPressed = false;
			}
			
			osDelay(100);
	} // End for
}

// A utility function to swap to integers
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
 // A function to generate a random permutation of arr[]
void randomize ( int arr[], int n )
{
	int i =0;
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( HAL_GetTick() );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}

/*********************************************************************
*
*       Main
*/
int main (void) {
	//Set the game state to 'Initialisation'
	GameState state = GameInit;
	//Set up variables
  font_t          font16 = gdispOpenFont("DejaVuSans16");
	color_t colorrange[21] = {White, Yellow, Red, Blue, Magenta, SkyBlue, Orange,Lime,Black,Gray,Grey,Fuchsia,Green,Aqua,Maroon,Navy,Olive,Purple,Silver,Teal,Pink}; 
	int rand[21] = {0,1,2,3,4,5,6,7,8,10,11,12,13,14,15,16,17,18,19,20,21};
	int i =0;
		
	//Set up hardware
  CPU_CACHE_Enable();                       /* Enable the CPU Cache          */
  HAL_Init();                               				 /* Initialize the HAL Library     		*/
  BSP_SDRAM_Init();                        	 /* Initialize BSP SDRAM           	*/
  SystemClock_Config();                      /* Configure the System Clock  */
	Buttons_Initialize();                 				 /* Buttons Initialization             */

	//Set up touchscreen hardware
  Touch_Initialize();
	//Set up GLCD hardware
	GLCD_Initialize ();

	//gfxInit must be called after setting up hardware above
	gfxInit();																	/* Initialise uGFX library */
 
	gdispClear(tetrisShapeColors[0] );											/* Use given colour to clear screen (set background) */
		
	//While game is initialising
	while (state == GameInit) {
		 //Draw menu screen
				menuScreen();
		
		//While the user is on the main menu
		for(;;){
				//Get the user's touch position
				Touch_GetState (&tsc_state);
			
				//
				// If user pressed the top region of the screen (and therefore the 'Start Menu' button)
				//
				if(tsc_state.pressed == true && tsc_state.y <100){
						//Time taken to press start game is used to initialise the random seed, giving truly random numbers
						 totaltime = HAL_GetTick();
						 //Set up new game variables
							initialiseNewGame(11, 17);
						//Set the game state to 'Running'
						 state = GameRunning;
						//Clear the screen (Uses the tetris colours array instead of explicit colour, as could be using a different colour scheme)
						gdispClear(tetrisShapeColors[0]);
					
						//Break out of the for loop
						break;
					
				} //End if
				
				// 
				// If user pressed the centre region of the screen (and therefore the 'Dark Mode' button)
				//
				if(tsc_state.pressed == true && tsc_state.y >100 && tsc_state.y<150){
					
					//Set the colour array to the dark colour scheme
					tetrisShapeColors[0] = Black;
					tetrisShapeColors[8] = White;
					
					//Clear the screen with the new colours
					gdispClear(tetrisShapeColors[0]);
					
					//Redisplay the menu
					menuScreen();
				}
		
				// 
				// If user pressed the bottom region of the screen (and therefore the 'Random Mode' button)
				//
				if(tsc_state.pressed == true && tsc_state.y >150){
					
					// Shuffle the colour array to give a random colour scheme
					randomize (rand, 21);					
					for( i =0; i<9; i++){
						tetrisShapeColors[i] = colorrange[rand[i]];
					}
					
					//Clear the screen to use the new colours
					gdispClear(tetrisShapeColors[0]);
					
					//Redisplay the menu
					menuScreen();
				}
		} //End for
	} //End while
	
      
 //Create thread instances
	tid_taskGLCD = osThreadCreate(osThread(taskGLCD), NULL);
	tid_taskInput = osThreadCreate(osThread(taskInput), NULL);
	tid_taskGameLogic = osThreadCreate(osThread(taskGameLogic), NULL);
	
	osDelay(osWaitForever);
	while(1);
}
