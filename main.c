

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery_sdram.h"
#include "RTE_Components.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
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

//Size of the blocks used
const int BLOCK_SIZE = 15;

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
 *      Thread 1 'taskGLCD':   
 *--------------------------------------------------*/
void taskGLCD (void const *argument) {
}

/*--------------------------------------------------
 *      Thread 2 'taskGameLogic':   
 *--------------------------------------------------*/
void taskBall (void const *argument) {
}

/*--------------------------------------------------
 *      Thread 3 'taskInput':   
 *--------------------------------------------------*/
void taskADC (void const *argument) {
}

/*********************************************************************
*
*       Main
*/
int main (void) {
	GameState state = GameInit;
  int score;
	int initXpos;																/* initial screen touch x pos*/
	int initTime = 0;																/* initial time on touch */
  CPU_CACHE_Enable();                       /* Enable the CPU Cache          */
  HAL_Init();                               				 /* Initialize the HAL Library     		*/
  BSP_SDRAM_Init();                        	 /* Initialize BSP SDRAM           	*/
  SystemClock_Config();                      /* Configure the System Clock  */

	//Set up touchscreen hardware
  Touch_Initialize();
	//Set up GLCD hardware
	GLCD_Initialize ();
 // GLCD_ClearScreen ();

	//gfxInit must be called after setting up hardware above
	gfxInit();																	/* Initialise uGFX library */

	 gdispClear(White);											/* Use given colour to clear screen (set background) */
	//gdispFillArea(20, 20, 200, 200, Blue);		/* Draw a rectangle filled with specified colour */
	 while (state == GameInit) {
       // printf("Initialisation\n");
        //Will show start menu here, allow user to select singleplayer or multiplayer
        //Set up new game variables
        initialiseNewGame(11, 17);

        state = GameRunning;

    }

    //Main game loop
    while (state == GameRunning) {
			
			// Clear the previous display
			eraseBlock();
			
			//Apply changes to the block
			Touch_GetState (&tsc_state); /* Get touch state */
			if(tsc_state.pressed == true && stillPressed == false){
				stillPressed = true;
				initXpos = tsc_state.x; // gets the  x pos when pressed
				initTime = HAL_GetTick(); //gets the  time when pressed
			}
			
			//rotate if the press lasted for half sec
			if(tsc_state.pressed ==false){
				if((HAL_GetTick()-initTime)<5000&&initTime!=0){
						//attemptMove('R');
						attemptMove('D');
			    	//rotateBlock();
					  initTime = 0;
				}
			}
			
			//move block right if swipped right
			if(stillPressed == true){
				if((tsc_state.x-initXpos)>50){
					currentPiece->x +=1;
					initXpos = tsc_state.x;
				}
				//move block left if swipped left
				if((tsc_state.x-initXpos)<-50){
					currentPiece->x -=1;
					initXpos = tsc_state.x;
				}
				
				
				
			}
			//moves block down
			//attemptMove('D');
			
			// Is the touch screen still being pressed from the previous loop? (prevent rotating multiple times from one touch)
			if(tsc_state.pressed == false){
				stillPressed = false;
			}
			
			updateBlock();
			
			// Print the game screen
			printTetrisBucket();
			
			
			wait_delay(1000); //Sleep for a short duration
			
			if(checkForFullRows() == 1){
					gdispClear(White);
			} //checks for full rows

				}
}
