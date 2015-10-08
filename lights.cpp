/**
* Demonstration code from CSC 340
* Note: I did not write this code.  Prof Sosnick at SFSU wrote this for demonstration 
* and comparing purposes.
*/
#include <iostream>
using namespace std;


//  Bitmasks for each device that is being controlled (see header comments)

/** Bitmask with garage bit on */
const unsigned char MASK_GARAGE_ON = 0X01;	

/** Inverse bitmask with garage bit off */
const unsigned char MASK_GARAGE_OFF = 0XFE;	

/** Bitmask with entry hall bit on */
const unsigned char MASK_ENTRY_ON = 0x02;	

/** Inverse bitmask with entry hall bit off */
const unsigned char MASK_ENTRY_OFF = 0xFD;	

/** Bitmask with living room bit on */
const unsigned char MASK_LIVING_ON = 0x04;	

/** Inverse bitmask with living room bit off */
const unsigned char MASK_LIVING_OFF = 0xFB;	

/** Bitmask with kitchen bit on */
const unsigned char MASK_KITCHEN_ON = 0x08;	

/** Inverse bitmask with kitchen bit off */
const unsigned char MASK_KITCHEN_OFF = 0xF7;	

/** Bitmask with bedroom bit on */
const unsigned char MASK_BED_ON = 0x10;

/** Inverse bitmask with bedroom bit off */
const unsigned char MASK_BED_OFF = 0xEF;

/** Bitmask with all light bits on */
const unsigned char MASK_ALL_ON = 0x1F;

/** Inverse bitmask with all light bits off */
const unsigned char MASK_ALL_OFF = 0x00;


/**
 *  This function simulates the actual control settings 
 *  for a lighting control system by printing out the
 *  settings that are passed to it in a control byte.
 *  In a non-simulated setting, this control byte would
 *  be sent to a memory address controlling (for example)
 *  a set of relays.
 *
 *  \param setting unsigned char containing the byte to 
 *         send to the lighting controller
 */
void control(unsigned char setting){
	
	cout << "Setting Lights" << endl
	     << "--------------" << endl;
	cout << " Garage: ";
	if( setting & MASK_GARAGE_ON)
		cout << "ON" << endl;
	else 
		cout << "OFF" << endl;

  	cout << "  Entry: ";
	if( setting & MASK_ENTRY_ON )
		cout << "ON" << endl;
	else 	
		cout << "OFF" << endl;


	cout << " Living: ";
	if( setting & MASK_LIVING_ON )
		cout << "ON" << endl;
	else 	
		cout << "OFF" << endl;

	cout << "Kitchen: ";
	if( setting & MASK_KITCHEN_ON )
		cout << "ON" << endl;
	else 	
		cout << "OFF" << endl;

	cout << "    Bed: ";
	if( setting & MASK_BED_ON )
		cout << "ON" << endl;
	else 	
		cout << "OFF" << endl;

	cout << endl;
}

/** 
 * Prints a menu for the lighting system, and gets a menu choice 
 * from the user (as an integer).
 * 
 * \param setting unsigned char contains the current state of the 
 *        lights to print light status from main menu.
 * 
 * \returns int containing the menu choice user entered
 */
int doMenu(unsigned char setting){
	int userChoice = 0;
	
	cout << "   MAIN MENU" << endl
	     << "----------------" << endl
             << "0) Exit Program " << endl;
	cout << "1)  Garage: ";
	if( setting & MASK_GARAGE_ON)
		cout << "(on)" << endl;
	else 
		cout << "(off)" << endl;

  	cout << "2)   Entry: ";
	if( setting & MASK_ENTRY_ON )
		cout << "(on)" << endl;
	else 	
		cout << "(off)" << endl;


	cout << "3)  Living: ";
	if( setting & MASK_LIVING_ON )
		cout << "(on)" << endl;
	else 	
		cout << "(off)" << endl;

	cout << "4) Kitchen: ";
	if( setting & MASK_KITCHEN_ON )
		cout << "(on)" << endl;
	else 	
		cout << "(off)" << endl;

	cout << "5)     Bed: ";
	if( setting & MASK_BED_ON )
		cout << "(on)" << endl;
	else 	
		cout << "(off)" << endl;
	
	cout << "Enter your choice: ";

	cout << endl << endl;

	cin >> userChoice;

	return userChoice;
}

/**
 * Toggles the light specified by the (user) menu entry in the control
 * byte.  This control byte should then be sent off to the lighting
 * controller.
 *
 * \param menuEntry int containing the menu choice the user entered
 * \param currentState unsigned char containing the current state of all the lights
 * 
 * \returns unsigned char containing the state of lights after toggling
 */
unsigned char toggleLight(int menuEntry, unsigned char currentState){
	
	switch( menuEntry ){
		case 1:
			if( currentState & MASK_GARAGE_ON)
				currentState = currentState & MASK_GARAGE_OFF;
			else 
				currentState = currentState | MASK_GARAGE_ON;
			break;

		case 2:
			if( currentState & MASK_ENTRY_ON )
				currentState = currentState & MASK_ENTRY_OFF;
			else 	
				currentState = currentState | MASK_ENTRY_ON;
			break;

		case 3:
			if( currentState & MASK_LIVING_ON )
				currentState = currentState & MASK_LIVING_OFF;
			else 	
				currentState = currentState | MASK_LIVING_ON;
			break;

		case 4:
			if( currentState & MASK_KITCHEN_ON )
				currentState = currentState & MASK_KITCHEN_OFF;
			else 	
				currentState = currentState | MASK_KITCHEN_ON;
			break;

		case 5:
			if( currentState & MASK_BED_ON )
				currentState = currentState & MASK_BED_OFF;
			else 	
				currentState = currentState | MASK_BED_ON;
			break;	
	}

	return currentState;
}

/**
 * Contains system initialization sequence, main control loop 
 * of the program, shutdown sequence.
 */
int main(){
	
	int userResponse = 0;

	unsigned char lightingState = 0;


	// When program starts, turn all lights on
	lightingState = MASK_ALL_ON;
	control(lightingState);

	// introduce program
	cout << "Home Lighting System" << endl;

	// main control loop
	userResponse = doMenu(lightingState);
	while (userResponse){
		lightingState = toggleLight(userResponse, lightingState);
		control(lightingState);
		userResponse = doMenu(lightingState);
	}

	// When leaving control of the program, turn all lights on
	lightingState = MASK_ALL_ON;
	control(lightingState);
}
