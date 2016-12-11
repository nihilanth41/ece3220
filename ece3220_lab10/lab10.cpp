#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;



// Input: 'Word'
// output: e.g. .... . ._.. etc
// See L14

#define NUM_LETTERS 26
string Letters = "abcdefghijklmnopqrstuvwxyz";
string mCode[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };


class Message { 
	protected: string msg;

	public:
		   virtual void printInfo(void);
		   // Constructors
		   Message();
		   Message(string m);
		   //Destructor
		   ~Message();
};

Message::Message() { 
	// Empty constructor ask user for input:
	cout << "Enter a message: ";
	cin >> msg;
}

Message::Message(string m) {
	// Get user input from command line args
	msg = m;
}

void Message::printInfo(void) {
	// Print message string to stdout
	cout << "Original text: " << msg << endl;
	cout << endl;
}

Message::~Message() {
}

class morseCodeMessage : public Message {
	protected: 
		string *translated_msg;
		void translate();
	public:
		// Override virtual:
		void printInfo();
		// Constructor
		morseCodeMessage();
		// Destructor
		~morseCodeMessage();
};

morseCodeMessage::morseCodeMessage() {
	translated_msg = new string[msg.length()];
	translate();
}

morseCodeMessage::~morseCodeMessage() {
	delete[] translated_msg;
}


void morseCodeMessage::translate() {
	for(int i=0; i<msg.length(); i++)
	{
		for(int j=0; j<NUM_LETTERS; j++)
		{
			if(msg[i] == Letters[j])
			{
				translated_msg[i] = mCode[j];
				break;
			}
		}
	}
}

void morseCodeMessage::printInfo() {
	cout << "Original text: " << msg << endl;
	cout << "Morse code: ";
	for(int i=0; i<msg.length(); i++)
	{
		cout << translated_msg[i];
	}
	cout << endl;
	cout << endl;
}

class morseCodeLED : public morseCodeMessage {  
	private:
		int fd;
		unsigned long *baseptr;
		// Data register, data-direction register
		unsigned long *PBDR,*PBDDR;
		void gpio_init(void);
	public:	
		// Override virtual
		void printInfo(void);
		//Constructor
		morseCodeLED();
		//morseCodeLED(string msg);
		//Destructor
	//	~morseCodeLED();


};

void morseCodeLED::gpio_init(void) {
	fd = open("/dev/mem", O_RDWR|O_SYNC);	// open the special file /dem/mem
	if(fd == -1){
		printf("\nError: cannot open /dev/mem.\nAre you root?\n");
		exit(-1);  // failed open
	}

	// We need to map Address 0x80840000 (beginning of the page)
	baseptr = (unsigned long*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x80840000);
	if(baseptr == MAP_FAILED){
		printf("\nError: Unable to map memory space \n");
		exit(-2);
	}  // failed mmap
	close(fd);

	// To access other registers in the page, we need to offset the base pointer to reach the
	// corresponding addresses. Those can be found in the board's manual.
	PBDR = baseptr + 1;	// Address of port B DR is 0x80840004
	PBDDR = baseptr + 5;	// Address of port B DDR is 0x80840014
	
	*PBDDR &= 0xFFFFFFFE;	// configures port B0 as input (first push button). You could use: &= ~0x01
	// Set B5-B7 as output
	*PBDDR |= 0xE0;
	// All LED off
	*PBDR &= 0x00;
}

morseCodeLED::morseCodeLED() {
	// Message class default constructor asks user for input
	// morseCodeMessage does the translation 
	// To verify this we can print the translated msg to stdout
	cout << "Original text: " << msg << endl;
	cout << "Morse code: ";
	for(int i=0; i<msg.length(); i++)
	{
		cout << translated_msg[i];
	}
	cout << "\n";
	// Set pushbutton 1 as input, 3 LED outputs.
	gpio_init();
}

void morseCodeLED::printInfo(void) {
	// Lab 10 implement MorseCodeToLights in MorseCodeMessage
	//for each string in array
	for(int i=0; i<msg.length(); i++)
	{
		string mc = translated_msg[i];
		//for each char in string
		for(int j=0; j<mc.length(); j++)
		{
			usleep(500000);
			char c = mc[j];
			if(c == '.')
			{
				// RED LED => B5
				// Turn on B5
				*PBDR |= 0x20;
				cout << "Red" << endl;
				// Delay 0.5 seconds between morse code characters 
				usleep(500000);
				// Off
				*PBDR &= ~0x20;
			}
			else if(c == '-') 
			{
				// YELLOW LED => B6 
				// On
				*PBDR |= 0x40;
				cout << "Yellow" << endl;
				// Delay 0.5 seconds between morse code characters 
				usleep(500000);
				// Off
				*PBDR &= ~0x40;
			}
			else 
			{
				cout << "Character not morse code: " << c << endl;
			}
		}
		// Delay 1 second between ascii characters
		sleep(1);
	}
	// Pulse green LED to signify the end of the word
	// GREEN LED => B7
	// On
	*PBDR |= 0x80;
	cout << "Green" << endl;
	// Delay 1 second
	sleep(1);
	// Off
	*PBDR |= 0x80;
	
	// All LED off
	*PBDR &= 0x00;
}

class messageStack {
	public:
		// Fixed stack size
		// replace with LL eventually
		Message *stack[10]; 
		messageStack(Message *);
		int stack_top_index;
		int num_obj;
		//~messageStack();
		void pop();         //LIFO
		void push(Message *); //LIFO
		void printStack();
	private:

};

messageStack::messageStack(Message *m) {
	stack_top_index = 9;
	num_obj = 0;
	push(m);
}

void messageStack::printStack(void) {
	cout << "Stack top index: " << stack_top_index << endl;
	cout << "-------------------" << endl;

	for(int i=stack_top_index; i<10; i++)
	{
		cout << "Current index: " << i << endl;
		stack[i]->printInfo();
	}
}


void messageStack::pop(void) {
	if(num_obj == 0)
	{
		stack_top_index = 9;
		cout << "Stack empty\n";
		return;
	}
	else
	{
		num_obj--;
		(stack_top_index > 9) ? stack_top_index=9 : stack_top_index++;
	}
}


void messageStack::push(Message *m) {
	if(num_obj == 0)
	{
		stack[stack_top_index] = m;
	}
	else
	{
		if(stack_top_index == 0)
		{
			cout << "Stack full\n"; 
			return;
		}
		stack[--stack_top_index] = m;
	}
	num_obj++;
}


int main(int argc, char **argv) {

	if(argc > 1) 
	{
		// Print the msg without translation
		// This is just to demonstrate the base class functionality
		Message m1 = Message(argv[1]);
		m1.printInfo();

	}

	morseCodeLED l1 = morseCodeLED();
	l1.printInfo();

	// Ask user for message to translate
	//morseCodeMessage m1 = morseCodeMessage();
	//m1.printInfo();
	//morseCodeMessage m2 = morseCodeMessage();
	//morseCodeMessage m3 = morseCodeMessage();

	//messageStack ms1 = messageStack(&m1);
	//ms1.push(&m2);
	//ms1.push(&m3);

	//ms1.printStack();

	//ms1.pop();
	//ms1.printStack();
	//ms1.pop();
	//ms1.printStack();

	// My terrible stack implementation doesn't handle empty or full case correctly
	//	ms1.pop();
	//	ms1.printStack();

	//	ms1.push(&m1);
	//	ms1.printStack();

	return 0;
}



