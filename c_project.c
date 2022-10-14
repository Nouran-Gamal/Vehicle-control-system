
/* ===========================================================================
                         VEHICLE CONTROL PORJECTT
 =========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1

//////////////////////***VEHICLE STRUCT DEFINITION***/////////////////////////
typedef struct
{
	int engine_state;
	int speed;
	int AC_state;
	float room_temp;
	int Controller_state;
	float engine_temp;
} Vehicle;
int controlller_condition= WITH_ENGINE_TEMP_CONTROLLER;

///////////////////////***FUNCTIONS PROTOTYPES***/////////////////////////////
void main_menu(void);
void sensors_menu(Vehicle *v);
void print_struct(Vehicle *v);
void delay(int no_secs);
void set_traffic_light(Vehicle *v);
void set_ac_state(Vehicle *v);
void set_room_temp(Vehicle *v);
void set_engine_controller_state(Vehicle *v);
void set_engine_temp(Vehicle *v);


////////////////////////***MAIN FUNCTION***/////////////////////////////////////
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	main_menu();

	return 0;
}

////////////////////////***FUNCTIONS DEFINITION***//////////////////////////////
void main_menu(void)
{
	Vehicle v;
	v. engine_state = 0;
	v.speed = 0;
	v.AC_state = 0.0;
	v.room_temp = 0;
	v.Controller_state = 0;
	v.engine_temp = 0.0;
	char choice = ' ';
	do
	{
		printf("What do you want ?\n");                //Displaying main menu options to the user
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");

		scanf(" %c", &choice);                         //Scanning choice from user

		switch(choice)
		{
		case 'a':                                     //turn on vehicle engine
			printf("Vehicle engine is ON\n");         //Display engine state
			sensors_menu (&v);                     //call turn on vehicle function
			break;
		case 'b':
			printf("Vehicle engine turned off.\n\n");
			break;
		case 'c':
			printf("Quitting the system..\n");
			delay(1.5);
			printf("System is shut down\n");
			//exit(0);
			return;
		default:
			break;
		}
	}while(1);
}
void sensors_menu(Vehicle *v)
{
	v->engine_state=1;
	char choice = ' ';
	do{
		printf("a. Turn off the engine.\n");
		printf("b. Set the traffic light color.\n");
		printf("c. Set the room temperature (Temperature Sensor).\n");
		if (controlller_condition == 1){
			printf("d. Set the engine temperature (Engine Temperature Sensor)\n\n");
		}

		scanf(" %c", &choice);
		switch(choice)
		{
		case 'a':

			v->engine_state=0;
			printf("Turning off the engine\n");
			//main_menu();
			return;
		case 'b':
			v->engine_state=1;
			set_traffic_light(v);
			break;
		case 'c':
			v->engine_state=1;
			set_room_temp(v);
			print_struct(v);
			break;
		case 'd':
			v->engine_state=1;
			if(controlller_condition==1)        //check WITH_ENGINE_TEMP_CONTROLLER condition
			{
				set_engine_temp(v);
			}
			break;
		default:
			break;
		}
	}while(1);
}
void print_struct(Vehicle *v)        //to print the states of the vehicle
{
	if((v->engine_state)==1){           //engine state (on or off) based on its value(0 or 1)
		printf("The engine is ON\n");
	}
	else{
		printf("The engine is OFF\n");

	}

	if((v->AC_state)==1){               //AC state (on or off) based on its value(0 or 1)
		printf("The AC is ON\n");
	}
	else{
		printf("The AC is OFF\n");

	}
	printf("Vehicle speed is %d Km/Hr\n",v->speed);

	printf("Room Temperature: %.2f C\n",v->room_temp);

	if(controlller_condition==1){                  //Check the value of WITH_ENGINE_TEMP_CONTROLLER to display any controller data
		if((v->Controller_state)==1){
			printf("Engine Temp Conroller is ON\n");
		}
		else{
			printf("Engine Temp Conroller is OFF\n");

		}
		printf("Engine temperature: %.2f C\n",v->engine_temp);
	}
	printf("\n\n");
}
void delay(int no_secs){             //used at quitting the system
	int milli_seconds = 1000 * no_secs;
	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);
}
void set_traffic_light(Vehicle *v)
{
	char traffic_color = ' ';
	do{                                            //do while loop to make sure that the input is from the list
		printf("Enter the color (G or O or R)\n");
		scanf(" %c", &traffic_color);
	}while ( (traffic_color!='G') && (traffic_color!='O') && (traffic_color!='R') );

	switch(traffic_color)
	{
	case 'G':
		v->speed = 100;
		break;
	case 'O':
		v->speed = 30;
		set_ac_state(v);
		if(controlller_condition==1)             //check WITH_ENGINE_TEMP_CONTROLLER condition
		{
			set_engine_controller_state(v);
		}
		break;
	default:
		v-> speed = 0;
		break;
	}
	print_struct(v);
}
void set_ac_state(Vehicle *v)
{
	v->AC_state=1;
	v->room_temp=(v->room_temp)*5/4+1;
}
void set_room_temp(Vehicle *v)                 //used to set room temp at choosing it from sensors menu
{
	printf("Enter the current room temperature\n");
	scanf("%f" ,&v->room_temp);
	if (( (v->room_temp)<10 ) || ( (v->room_temp)>30 ) ){
		v->AC_state=1;
		v->room_temp=20.0;
	}
	else{
		v->AC_state=0;
	}
}
void set_engine_controller_state(Vehicle *v)     //used when choosing O traffic light color
{
	v->Controller_state=1;
	v->engine_temp=(v->engine_temp)*5/4+1;
}
void set_engine_temp(Vehicle *v)               //used to set engine temp at choosing it from sensors menu
{
	printf("Enter the current engine temperature\n");
	scanf ("%f",&v->engine_temp);

	if (( (v->engine_temp)<100 ) || ( (v->engine_temp)>150 ) ){
		v->Controller_state =1;
		v->engine_temp=125.0;
	}
	else{
		v->Controller_state=0;
	}
	print_struct(v);
}
