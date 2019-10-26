/*
 * 		Challenge Name: Infotainment with scheduler
 *
 *      Author: Mostafa Khalil
 *      		Mahmoud Khalid
 *      		(Sprints Wave4)
 */

/*******************************************************
 * 						Includes
 *******************************************************/
#include "LCD.h"
#include "OS.h"
#include "keypad.h"

/*******************************************************
 * 						  Macros
 *******************************************************/

#define NOT_INIT_YET 0
#define INIT_DONE 1

#define FIRST_ANS_KEY 1
#define SECOND_ANS_KEY 2
#define THIRD_ANS_KEY 4
#define FOURTH_ANS_KEY 5
#define NEXT_KEY 9

#define CORRECT_ANS 10
#define WRONG_ANS 11
#define WRONG_INPUT 6
#define SKIP_QUES 3

#define WELCOME_SCREEN 12
#define QUESTION_DISPLAY 13
#define DISP_RESULT 14
#define DISP_SCORE 15


/*******************************************************
 * 			   Shared Resources between Tasks
 *******************************************************/

static volatile uint8 g_initFlag = NOT_INIT_YET;
static volatile uint8 g_LCD_dispCharRequest_Flag = 0;
static volatile uint8 g_LCD_dispStringRequest_Flag = 0;
static volatile uint8 g_LCD_clearRequest_Flag = 0;
static volatile uint8 g_LCD_dispData;
static volatile uint8*g_LCD_dispString;
static volatile uint8 g_keyPadPressedKey = NO_KEY_PRESSED;
static volatile uint8 g_LED_Flash1Request = 0;
static volatile uint8 g_LED_Flash2Request = 0;
static volatile uint8 g_LED_Flash3Request = 0;
static volatile uint8 g_LED_Flash4Request = 0;

/*******************************************************
 * 			   		Quiz Questions,
 * 			   		Answer Sheet,
 * 			   		Display Statements
 *******************************************************/

uint8 entryStatement[33]= "     Ready!     Press 9 to START";

uint8 Question_array[5][33] =
{{"3>8>15>24>35>?  *42 *36 *48 *46"},		/*increase 5,7,9,,11,13 = 48*/
		{"  ?>19>23>29>31 *12 *15 *16 *17"},	/*prime numbers*/
		{"Largest City In EUR? *L *I *F *R"},	/*London Istanbul(correct) France Rome*/
		{"Caspian sea is  Russian   *T *F"},	/*True*/
		{"Nicaragua city  in Asia?  *T *F"}};	/*False*/

uint8 AnswerSheet[5] =
{THIRD_ANS_KEY,\
		FOURTH_ANS_KEY,\
		SECOND_ANS_KEY,\
		FIRST_ANS_KEY,\
		SECOND_ANS_KEY};

uint8 result_array[4][33] =
{{"   Wrong Input"},\
		{"      SKIP"},\
		{"   Correct Ans"},\
		{"   Wrong Ans"}};

uint8 scoreStatement[6][33] =
{{"     ZEROO          HAHAHAHA"},\
		{"     LOSER            :)-"},\
		{"   2 Ma3leSH"},\
		{"3 Mesh BattaaL"},\
		{"4 Gada3 ya Hamada"},\
		{"5 Enta Gamed Zo7le2a"}};

/*******************************************************
 * 	Task Name: 			quizHandler
 * 	Task Periodicity   	100ms
 * 	Task Priority		NA
 * 	Task Desc		   	It handles the state machine of
 * 						the quiz
 *******************************************************/

void TASK_quizHandler(void)
{
	static volatile uint8 quizState = WELCOME_SCREEN;
	static volatile uint8 firstEntry_Flag = 0;
	static volatile uint8 questionNumber=0;
	static volatile uint8 result=0;
	static volatile uint8 LOC_delayTime = 0;
	static volatile uint8 score=0;

	/**************************************************************
	 * 	Blocking the task until all the initializations finish
	 **************************************************************/
	if(g_initFlag == INIT_DONE)
	{
		/**************************************************************
		 * 	In case there is any task delay request, the if condition
		 * 	will skip the code and decrement a counter till it becomes
		 * 	zero again to get back to the function
		 **************************************************************/
		if(LOC_delayTime == 0)
		{

			/**************************************************************
			 * 	 				Switching between the states
			 **************************************************************/
			switch(quizState)
			{

			/**************************************************************
			 * 							Entry Screen
			 **************************************************************/
			case WELCOME_SCREEN:
				/********************************************
				 * Guard to print the statement only one time
				 ********************************************/
				if(firstEntry_Flag == 0)
				{
					firstEntry_Flag=1;
					g_LCD_dispStringRequest_Flag = 1;
					g_LCD_dispString = entryStatement;
				}

				/********************************************
				 * Wait until the user press the next key
				 ********************************************/
				if(g_keyPadPressedKey == NEXT_KEY)
				{
					/***********************************
					 * Change the state to 1st Question
					 ***********************************/
					quizState = QUESTION_DISPLAY;
					firstEntry_Flag =0;
					g_keyPadPressedKey = NO_KEY_PRESSED;
				}
				break;

			/**************************************************************
			 * 					Displaying Questions Case
			 **************************************************************/
			case QUESTION_DISPLAY:
				/********************************************
				 * Guard to request clear command only one time
				 ********************************************/
				if(firstEntry_Flag == 0)
				{
					/******************************
					 * Request to clear the screen
					 ******************************/
					firstEntry_Flag=1;
					g_LCD_clearRequest_Flag = 1;
				}
				/********************************************
				 * Guard to wait until the clear is done to
				 * display the question
				 ********************************************/
				if(g_LCD_clearRequest_Flag ==0)
				{
					g_LCD_clearRequest_Flag =3;
					g_LCD_dispStringRequest_Flag = 1;
					g_LCD_dispString = Question_array[questionNumber];

				}

				/***********************************************
				 * Wait until the user press any key
				 * and check the upcoming state based on the key
				 ***********************************************/
				if(g_keyPadPressedKey == NEXT_KEY)
				{
					result = SKIP_QUES;
					quizState = DISP_RESULT;
					firstEntry_Flag =0;
					g_keyPadPressedKey = NO_KEY_PRESSED;
				}
				else if((g_keyPadPressedKey == FIRST_ANS_KEY)\
						||(g_keyPadPressedKey == SECOND_ANS_KEY)\
						||(g_keyPadPressedKey ==THIRD_ANS_KEY)\
						||(g_keyPadPressedKey ==FOURTH_ANS_KEY))
				{
					if(g_keyPadPressedKey == AnswerSheet[questionNumber])
						result = CORRECT_ANS;
					else
						result = WRONG_ANS;

					quizState = DISP_RESULT;
					firstEntry_Flag =0;
					g_keyPadPressedKey = NO_KEY_PRESSED;
				}
				else if(g_keyPadPressedKey != NO_KEY_PRESSED)
				{
					result = WRONG_INPUT;
					quizState = DISP_RESULT;
					firstEntry_Flag =0;
					g_keyPadPressedKey = NO_KEY_PRESSED;
				}


				break;

			/**************************************************************
			 * 					Displaying The result Case
			 **************************************************************/
			case DISP_RESULT:

				/********************************************
				 * Guard to request clear command only one time
				 ********************************************/
				if(firstEntry_Flag == 0)
				{
					firstEntry_Flag=1;
					g_LCD_clearRequest_Flag = 1;
				}


				switch(result)
				{
				case WRONG_INPUT:

					if(g_LCD_clearRequest_Flag ==0)
					{
						g_LCD_clearRequest_Flag =3;
						g_LCD_dispStringRequest_Flag = 1;
						g_LCD_dispString = result_array[0];
						firstEntry_Flag=0;
						LOC_delayTime = 10;
						quizState = QUESTION_DISPLAY;
					}

					break;
				case SKIP_QUES:

					if(g_LCD_clearRequest_Flag ==0)
					{
						g_LCD_clearRequest_Flag =3;
						g_LCD_dispStringRequest_Flag = 1;
						g_LCD_dispString = result_array[1];
						g_LED_Flash3Request =1;
						firstEntry_Flag=0;
						LOC_delayTime = 10;
						questionNumber++;
						if(questionNumber > 4)
						{
							quizState = DISP_SCORE;
						}
						else
						{
							quizState = QUESTION_DISPLAY;
						}
					}

					break;
				case CORRECT_ANS:

					if(g_LCD_clearRequest_Flag ==0)
					{
						g_LCD_clearRequest_Flag =3;
						score++;
						g_LCD_dispStringRequest_Flag = 1;
						g_LCD_dispString = result_array[2];
						g_LED_Flash2Request =1;
						firstEntry_Flag=0;
						LOC_delayTime = 10;
						questionNumber++;
						if(questionNumber > 4)
						{
							quizState = DISP_SCORE;
						}
						else
						{
							quizState = QUESTION_DISPLAY;
						}
					}

					break;
				case WRONG_ANS:

					if(g_LCD_clearRequest_Flag ==0)
					{
						g_LCD_clearRequest_Flag =3;
						g_LCD_dispStringRequest_Flag = 1;
						g_LCD_dispString = result_array[3];
						g_LED_Flash1Request=1;
						firstEntry_Flag=0;
						LOC_delayTime = 10;
						questionNumber++;
						if(questionNumber > 4)
						{
							quizState = DISP_SCORE;
						}
						else
						{
							quizState = QUESTION_DISPLAY;
						}
					}

					break;

				}

				break;

				/**************************************************************
				 * 					Displaying The Score Case
				 **************************************************************/
				case DISP_SCORE:
					if(firstEntry_Flag == 0)
					{
						firstEntry_Flag=1;
						g_LCD_clearRequest_Flag = 1;
					}

					if(g_LCD_clearRequest_Flag ==0)
					{
						g_LCD_clearRequest_Flag=3;
						g_LCD_dispString = scoreStatement[score];
						g_LCD_dispStringRequest_Flag = 1;
					}

					break;
			}
		}

		else
		{
			LOC_delayTime--;
		}
	}
}

void TASK_initSystem(void)
{
	static uint8 DIO_init_status = NOT_INIT_YET;
	static uint8 LCD_init_status = NOT_INIT_YET;


	/**************************************************************
	 * 	Blocking the task after all the initializations finish
	 **************************************************************/

	if(g_initFlag == NOT_INIT_YET)
	{
		if(DIO_init_status != INIT_DONE)
		{
			DIO_init();
			DIO_init_status = INIT_DONE;
		}

		if(LCD_init_status != INIT_DONE)
		{
			LCD_init_status = LCD_init(LCD_ptrConfig);
			if(LCD_init_status == LCD_DONE)
			{
				LCD_init_status = INIT_DONE;
				g_initFlag = INIT_DONE;
			}
		}

	}
}

void TASK_LCD_dispChar (void)
{
	uint8 LCD_dispFuncStatus;

	/**************************************************************
	 * 	Blocking the task until all the initializations finish
	 **************************************************************/

	if(g_initFlag == INIT_DONE)
	{
		if(g_LCD_dispCharRequest_Flag ==1)
		{
			LCD_dispFuncStatus = LCD_displayChar(g_LCD_dispData);
			if(LCD_dispFuncStatus == LCD_DONE)
			{
				g_LCD_dispCharRequest_Flag = 0;
			}
		}
	}
}

void TASK_KeyPad_Check(void)
{
	uint8 LOC_pressedKey;
	uint8 keyPad_Status;
	static uint8 prevKey = NO_KEY_PRESSED;

	/**************************************************************
	 * 	Blocking the task until all the initializations finish
	 **************************************************************/
	if(g_initFlag == INIT_DONE)
	{
		keyPad_Status = KeyPad_getPressedKey(&LOC_pressedKey);
		if(keyPad_Status == KEYPAD_DONE)
		{
			if(prevKey != LOC_pressedKey)
			{
				prevKey = LOC_pressedKey;
				g_keyPadPressedKey = LOC_pressedKey;
			}


		}
		else if(keyPad_Status == NO_KEY_PRESSED)
		{
			prevKey = NO_KEY_PRESSED;
		}
	}
}

void TASK_LCD_dispStr (void)
{
	uint8 LCD_dispFuncStatus = 0;
	uint8 LCD_clearFuncStatus = 0;

	/**************************************************************
	 * 	Blocking the task until all the initializations finish
	 **************************************************************/

	if(g_initFlag == INIT_DONE)
	{
		if(g_LCD_clearRequest_Flag == 1)
		{
			LCD_clearFuncStatus = LCD_clear();
			if(LCD_clearFuncStatus == LCD_DONE)
			{
				g_LCD_clearRequest_Flag = 0;
			}
		}

		if(g_LCD_dispStringRequest_Flag ==1)
		{
			LCD_dispFuncStatus = LCD_displayString(g_LCD_dispString);
			if(LCD_dispFuncStatus == LCD_STR_COMPELET)
			{
				g_LCD_dispStringRequest_Flag = 0;
			}
		}
	}
}

void TASK_LED_Flash1(void)
{
	static volatile uint8 flash1Value = 0xFF;
	static volatile uint8 flash1Counter = 20;
	static volatile uint8 flash2Value = 0xFF;
	static volatile uint8 flash2Counter = 20;
	static volatile uint8 flash3Value = 0xFF;
	static volatile uint8 flash3Counter = 20;

	/**************************************************************
	 * 	Blocking the task until all the initializations finish
	 **************************************************************/

	if(g_initFlag == INIT_DONE)
	{
		if(g_LED_Flash1Request == 1)
		{
			flash1Value ^=0xFF;
			flash1Counter--;
			if(flash1Counter == 0)
			{
				flash1Counter = 20;
				g_LED_Flash1Request = 0;
				flash1Value=0;
			}
			DIO_write_port_value(PORT_B,flash1Value);
		}
		if(g_LED_Flash2Request == 1)
		{
			flash2Value <<= 1;
			if(flash2Value == 0)
				flash2Value = 0xFF;
			flash2Counter--;
			if(flash2Counter == 0)
			{
				flash2Counter = 20;
				g_LED_Flash2Request = 0;
				flash2Value=0;
			}
			DIO_write_port_value(PORT_B,flash2Value);
		}
		if(g_LED_Flash3Request == 1)
		{
			flash3Counter--;
			if(flash3Value ==0)
				flash3Value = 0xFF;

			if(flash3Counter == 0)
			{
				flash3Counter = 20;
				g_LED_Flash3Request = 0;
				flash3Value=0;
			}
			DIO_write_port_value(PORT_B,flash3Value);
		}
	}
}

void main(void)
{
	REG_DDRB = 0xFF;
	REG_DDRD = 0xFF;
	OS_Init(&OS_Config_STR_t);
	sei();

	Create_Task(1,TASK_initSystem,0);
	Create_Task(1,TASK_LCD_dispStr,0);
	Create_Task(30,TASK_KeyPad_Check,0);
	Create_Task(100,TASK_quizHandler,0);
	Create_Task(80,TASK_LED_Flash1,0);

	SOS_Run();

}

