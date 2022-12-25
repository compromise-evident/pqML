/// pqML - train a model to recognize 18-digit primes, all models unique.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net)


/* Version 1.0.1. Purpose: if primes can be recognized, so might semiprimes. And
if that, perhaps their factors. Otherwise, this would serve as pretty-good-proof
that semiprimes are without reversal shortcuts; desirable  outcome  is  failure!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pqML trains on 10,000 items per pass  (5,000 primes & composites,)  modifies the
model, runs through  10,000  items again, then compares misclassification count.
Improved models overwrite the last. Training on  20  items had misclassification
down to 2 in 5 minutes. Training on the default  10,000 items takes much longer.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to run the program  -  Software package repositories for GNU+Linux operating
systems have all the tools you can imagine. Open a terminal and use this command
as root to install Geany and g++ on your computer: apt install geany g++   Geany
is a fast & lightweight text editor and Integrated Development Environment where
you can write and run code. g++ is the GNU compiler for C++ which allows written
code to run. The compiler operates in the background and displays errors in your
code as you will see in the lower Geany box. Make a new folder somewhere on your
machine. Paste this code into Geany. For clarity in auditing, enable indentation
guides: go to View >> Show Indentation Guides. Save the document as anything.cpp
within the newly-created folder. Use these shortcuts to run the program: F9, F5.
You may paste over this code with other  .cpp files, or open a new tab & repeat.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to make an executable with g++  -  Save this program as anything.cpp, open a
terminal, and type g++ then space. Drag & drop this saved file into the terminal
and its directory will be  appended to your pending entry. Click on the terminal
and press enter.   a.out now resides in the user directory, you may rename it to
anything.  To run that executable, simply drag and drop it into a terminal, then
click on the terminal and press enter.  Reminder:  executable's effect-directory
is /home/user or where you put the executable. Opening  .cpp  files in Geany and
hitting F9 creates the same executable--movable, renameable, drag & droppable.*/

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	cout << "\n(pq Machine Learning)\n\n"
	
	     << "(1) Train\n"
	     << "(2) Test\n\n"
	
	     << "Enter option: ";
	
	int user_option; cin >> user_option;
	ifstream in_stream;
	ofstream out_stream;
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Train_______________________________________________________/
	if(user_option == 1)
	{	//Checks if training data is missing.
		in_stream.open("Training_data");
		if(in_stream.fail() == true) {cout << "\nMissing file \"Training_data\""; in_stream.close(); return 0;}
		in_stream.close();
		
		//Checks if training data is at least 190kB.
		in_stream.open("Training_data");
		int byte_counter = 0;
		char garbage_byte;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	in_stream.get(garbage_byte);
			byte_counter++;
		}
		in_stream.close();
		
		if(byte_counter < 190000) {cout << "\nTraining_data corrupted."; return 0;}
		
		//Checks if model already exists.
		bool existence_of_file_Model = true;
		in_stream.open("Model");
		if(in_stream.fail() == true) {existence_of_file_Model = false;}
		in_stream.close();
		
		/*Creates model if missing (56 neurons total.)
		
		in  h1  h2  out
		
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o   o
		o   o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		o   o   o
		
		Input: 18 neurons. Hidden layers: 2 (18 neurons each.)
		Output neurons: 2--classes "prime" and "composite."
		Each neuron is 1 of 95 different hash algorithms.
		This way, neurons have bias, they affect, and are
		affected. Hashing is a simplification of "neuron
		connected to neurons before itself" and "weight."
		
		Each input    neuron takes a hash of the 18-digit input.
		Each hidden 1 neuron takes a hash of the previous column.
		Each hidden 2 neuron takes a hash of the previous column.
		Each output   neuron takes a hash of the previous column. */
		if(existence_of_file_Model == false)
		{	out_stream.open("Model");
			srand(time(0));
			for(int a = 0; a < 56; a++)
			{	int neuron = (rand() % 95);
				out_stream << char(neuron + 32);
			}
			out_stream.close();
		}
		
		//Checks if model is at least 56 Bytes.
		in_stream.open("Model");
		byte_counter = 0;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	in_stream.get(garbage_byte);
			byte_counter++;
		}
		in_stream.close();
		
		if(byte_counter < 56) {cout << "\nModel corrupted. Replace it with your backup/remove it and you'll get a new one."; return 0;}
		
		//Loads model.
		in_stream.open("Model");
		char input_model   [18];
		char hidden_1_model[18];
		char hidden_2_model[18];
		char output_model  [ 2];
		for(int a = 0; a < 18; a++) {in_stream.get(input_model   [a]); input_model   [a] -= 32;}
		for(int a = 0; a < 18; a++) {in_stream.get(hidden_1_model[a]); hidden_1_model[a] -= 32;}
		for(int a = 0; a < 18; a++) {in_stream.get(hidden_2_model[a]); hidden_2_model[a] -= 32;}
		for(int a = 0; a <  2; a++) {in_stream.get(output_model  [a]); output_model  [a] -= 32;}
		in_stream.close();
		
		//Prints model, then prints IMPROVED models while training (improvements are also overwritten to file "Model".)
		cout << "\nExit/continue at any time. Updating model changes until no misclassification...\n\n";
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		system("date");
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "Current model: ";
		for(int a = 0; a < 18; a++) {cout << char(input_model   [a] + 32);}
		for(int a = 0; a < 18; a++) {cout << char(hidden_1_model[a] + 32);}
		for(int a = 0; a < 18; a++) {cout << char(hidden_2_model[a] + 32);}
		cout << char(output_model[0] + 32)<< char(output_model  [1] + 32);
		cout << "\n";
		
		//Loads training data.
		in_stream.open("Training_data");
		char training_data[180000];
		int training_data_write_bookmark = 0;
		for(int a = 0; a < 10000; a++)
		{	for(int b = 0; b < 18; b++)
			{	in_stream.get(training_data[training_data_write_bookmark]);
				training_data[training_data_write_bookmark] -= 48; //..........-48 means actual value of digit.
				training_data_write_bookmark++;
			}
			in_stream.get(garbage_byte); //..........Skips \n
		}
		in_stream.close();
		
		//Runs all 10,000 items through the model once to set initial misclassification count so it can be compared upon changes to the model.
		int misclassification_log[10000];
		int misclassification_counter = 0;
		int training_data_read_bookmark = 0;
		int fire[18];
		for(int a = 0; a < 10000; a++)
		{	//..........Loading fire[] with 18 digits.
			for(int b = 0; b < 18; b++)
			{	fire[b] = training_data[training_data_read_bookmark];
				training_data_read_bookmark++;
			}
			
			//..........Processing fire[] as input neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
			int sum  = 0;
			for(int b = 0; b < 18; b++) {sum += fire[b];}
			for(int b = 0; b < 18; b++)
			{	fire[b] *= sum;
				fire[b] *= input_model[b];
				fire[b] %= 95;
			}
			
			//..........Processing fire[] as hidden 1 neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
			sum  = 0;
			for(int b = 0; b < 18; b++) {sum += fire[b];}
			for(int b = 0; b < 18; b++)
			{	fire[b] *= sum;
				fire[b] *= hidden_1_model[b];
				fire[b] %= 95;
			}
			
			//..........Processing fire[] as hidden 2 neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
			sum  = 0;
			for(int b = 0; b < 18; b++) {sum += fire[b];}
			for(int b = 0; b < 18; b++)
			{	fire[b] *= sum;
				fire[b] *= hidden_2_model[b];
				fire[b] %= 95;
			}
			
			//..........Processing fire[] as output neurons.
			sum  = 0;
			for(int b = 0; b < 18; b++) {sum += fire[b];}
			fire[0] = (sum * output_model[0]); fire[0] %= 95;
			fire[1] = (sum * output_model[1]); fire[1] %= 95;
			
			//..........Logs classification.
			if     ((fire[0] > 42) && ((fire[1] > 42))) {misclassification_log[a] = -1;} //..........Undesirable
			else if((fire[0] < 43) && ((fire[1] < 43))) {misclassification_log[a] = -1;} //..........Undesirable
			else if((fire[0] > 42) && ((fire[1] < 43))) {misclassification_log[a] =  0;} //..........Composite.
			else                                        {misclassification_log[a] =  1;} //..........Prime.
		}
		
		//..........Prints misclassification for current model. This log also exists for future pinning of who's misclassified.
		for(int a = 0; a < 5000; a++)
		{	if(misclassification_log[a] != 1) {misclassification_counter++;} //..........First 5,000 must be classified under prime.
		}
		
		for(int a = 5000; a < 10000; a++)
		{	if(misclassification_log[a] != 0) {misclassification_counter++;} //..........Remaining 5,000 must be classified under composite.
		}
		
		cout << "Misclassifies: " << misclassification_counter << " of 10000 training items.\n\n";
		
		//Loops: model modification, another pass of all 10,000 training items. Improved model is saved.
		srand(time(0));
		int best_misclassification = misclassification_counter;
		for(; misclassification_counter > 0;)
		{	//..........Randomly modifies a model neuron (no reversion even if modification unhelpful;
			//..........reversion without modifying deeply, exhausts--leaving no room for improvement.
			int random_layer  = (rand() %  4); random_layer++;
			int random_neuron = (rand() % 18);
			int random_output = (rand() %  2);
			
			if(random_layer == 1)
			{	input_model[random_neuron]++;
				input_model[random_neuron] %= 95;
			}
			else if(random_layer == 2)
			{	hidden_1_model[random_neuron]++;
				hidden_1_model[random_neuron] %= 95;
			}
			else if(random_layer == 3)
			{	hidden_2_model[random_neuron]++;
				hidden_2_model[random_neuron] %= 95;
			}
			else
			{	output_model[random_output]++;
				output_model[random_output] %= 95;
			}
			
			//..........Runs all 10,000 training items through the model again.
			int misclassification_counter = 0;
			int training_data_read_bookmark = 0;
			int fire[18];
			for(int a = 0; a < 10000; a++)
			{	//..........Loading fire[] with 18 digits.
				for(int b = 0; b < 18; b++)
				{	fire[b] = training_data[training_data_read_bookmark];
					training_data_read_bookmark++;
				}
				
				//..........Processing fire[] as input neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
				int sum  = 0;
				for(int b = 0; b < 18; b++) {sum += fire[b];}
				for(int b = 0; b < 18; b++)
				{	fire[b] *= sum;
					fire[b] *= input_model[b];
					fire[b] %= 95;
				}
				
				//..........Processing fire[] as hidden 1 neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
				sum  = 0;
				for(int b = 0; b < 18; b++) {sum += fire[b];}
				for(int b = 0; b < 18; b++)
				{	fire[b] *= sum;
					fire[b] *= hidden_1_model[b];
					fire[b] %= 95;
				}
				
				//..........Processing fire[] as hidden 2 neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
				sum  = 0;
				for(int b = 0; b < 18; b++) {sum += fire[b];}
				for(int b = 0; b < 18; b++)
				{	fire[b] *= sum;
					fire[b] *= hidden_2_model[b];
					fire[b] %= 95;
				}
				
				//..........Processing fire[] as output neurons.
				sum  = 0;
				for(int b = 0; b < 18; b++) {sum += fire[b];}
				fire[0] = (sum * output_model[0]); fire[0] %= 95;
				fire[1] = (sum * output_model[1]); fire[1] %= 95;
				
				//..........Logs classification.
				if     ((fire[0] > 42) && ((fire[1] > 42))) {misclassification_log[a] = -1;} //..........Undesirable
				else if((fire[0] < 43) && ((fire[1] < 43))) {misclassification_log[a] = -1;} //..........Undesirable
				else if((fire[0] > 42) && ((fire[1] < 43))) {misclassification_log[a] =  0;} //..........Composite.
				else                                        {misclassification_log[a] =  1;} //..........Prime.
			}
			
			//..........Counts misclassification.
			for(int a = 0; a < 5000; a++)
			{	if(misclassification_log[a] != 1) {misclassification_counter++;} //..........First 5,000 must be classified under prime.
			}
			
			for(int a = 5000; a < 10000; a++)
			{	if(misclassification_log[a] != 0) {misclassification_counter++;} //..........Remaining 5,000 must be classified under composite.
			}
			
			//..........Compares misclassification to previous.
			if(misclassification_counter < best_misclassification) //..........If helpful, sets new best misclassification. pqML must then beat that score.
			{	best_misclassification = misclassification_counter;
				
				//..........Overwrites model with improved model.
				out_stream.open("Model");
				for(int a = 0; a < 18; a++) {out_stream.put(input_model   [a] + 32);}
				for(int a = 0; a < 18; a++) {out_stream.put(hidden_1_model[a] + 32);}
				for(int a = 0; a < 18; a++) {out_stream.put(hidden_2_model[a] + 32);}
				out_stream.put(output_model[0] + 32);
				out_stream.put(output_model[1] + 32);
				out_stream.close();
				
				//..........Prints model.
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				system("date");
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				cout << "Updated model: ";
				for(int a = 0; a < 18; a++) {cout << char(input_model   [a] + 32);}
				for(int a = 0; a < 18; a++) {cout << char(hidden_1_model[a] + 32);}
				for(int a = 0; a < 18; a++) {cout << char(hidden_2_model[a] + 32);}
				cout << char(output_model[0] + 32)<< char(output_model  [1] + 32);
				cout << "\n";
				
				cout << "Misclassifies: " << misclassification_counter << " of 10000 training items.\n\n";
			}
		}
	}
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Test________________________________________________________/
	else if(user_option == 2)
	{	//Checks if file "test" is missing.
		in_stream.open("test");
		if(in_stream.fail() == true) {cout << "\nFile \"test\" is missing, it should contain at least 18 digits."; in_stream.close(); return 0;}
		in_stream.close();
		
		//Checks if file "test" is at least 18 Bytes.
		in_stream.open("test");
		int byte_counter = 0;
		char garbage_byte;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	in_stream.get(garbage_byte);
			byte_counter++;
		}
		in_stream.close();
		
		if(byte_counter < 18) {cout << "\nFile \"test\" must be at least 18 Bytes."; return 0;}
		
		//Checks if model is missing.
		in_stream.open("Model");
		if(in_stream.fail() == true) {cout << "\nFile \"Model\" is missing, it should contain at least 56 characters."; in_stream.close(); return 0;}
		in_stream.close();
		
		//Checks if model is at least 56 Bytes.
		in_stream.open("Model");
		byte_counter = 0;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	in_stream.get(garbage_byte);
			byte_counter++;
		}
		in_stream.close();
		
		if(byte_counter < 56) {cout << "\nModel corrupted. Replace/remove it and you'll get a new one upon training."; return 0;}
		
		//Loads model.
		in_stream.open("Model");
		char input_model   [18];
		char hidden_1_model[18];
		char hidden_2_model[18];
		char output_model  [ 2];
		for(int a = 0; a < 18; a++) {in_stream.get(input_model   [a]); input_model   [a] -= 32;}
		for(int a = 0; a < 18; a++) {in_stream.get(hidden_1_model[a]); hidden_1_model[a] -= 32;}
		for(int a = 0; a < 18; a++) {in_stream.get(hidden_2_model[a]); hidden_2_model[a] -= 32;}
		for(int a = 0; a <  2; a++) {in_stream.get(output_model  [a]); output_model  [a] -= 32;}
		in_stream.close();
		
		//Prints model.
		cout << "\n   Using model: ";
		for(int a = 0; a < 18; a++) {cout << char(input_model   [a] + 32);}
		for(int a = 0; a < 18; a++) {cout << char(hidden_1_model[a] + 32);}
		for(int a = 0; a < 18; a++) {cout << char(hidden_2_model[a] + 32);}
		cout << char(output_model[0] + 32)<< char(output_model  [1] + 32);
		cout << "\n";
		
		//Loads given number.
		in_stream.open("test");
		char test[18];
		for(int a = 0; a < 18; a++)
		{	in_stream.get(test[a]);
			test[a] -= 48; //..........-48 means actual value of digit.
		}
		in_stream.close();
		
		//Prints given number.
		cout << "  Given number: ";
		for(int a = 0; a < 18; a++) {cout << char(test[a] + 48);}
		cout << "\n";
		
		//Classifies given number.
		int fire[18];
		//..........Loading fire[] with 18 digits.
		for(int a = 0; a < 18; a++) {fire[a] = test[a];}
		
		//..........Processing fire[] as input neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
		int sum  = 0;
		for(int a = 0; a < 18; a++) {sum += fire[a];}
		for(int a = 0; a < 18; a++)
		{	fire[a] *= sum;
			fire[a] *= input_model[a];
			fire[a] %= 95;
		}
		
		//..........Processing fire[] as hidden 1 neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
		sum  = 0;
		for(int a = 0; a < 18; a++) {sum += fire[a];}
		for(int a = 0; a < 18; a++)
		{	fire[a] *= sum;
			fire[a] *= hidden_1_model[a];
			fire[a] %= 95;
		}
		
		//..........Processing fire[] as hidden 2 neurons. (Loaded with previous and operations applied constructively means both 1:1, and 1:all due to sum.)
		sum  = 0;
		for(int a = 0; a < 18; a++) {sum += fire[a];}
		for(int a = 0; a < 18; a++)
		{	fire[a] *= sum;
			fire[a] *= hidden_2_model[a];
			fire[a] %= 95;
		}
		
		//..........Processing fire[] as output neurons.
		sum  = 0;
		for(int a = 0; a < 18; a++) {sum += fire[a];}
		fire[0] = (sum * output_model[0]); fire[0] %= 95;
		fire[1] = (sum * output_model[1]); fire[1] %= 95;
		
		//..........Logs classification.
		int misclassification_log;
		if     ((fire[0] > 42) && ((fire[1] > 42))) {misclassification_log = -1;} //..........Undesirable
		else if((fire[0] < 43) && ((fire[1] < 43))) {misclassification_log = -1;} //..........Undesirable
		else if((fire[0] > 42) && ((fire[1] < 43))) {misclassification_log =  0;} //..........Composite.
		else                                        {misclassification_log =  1;} //..........Prime.
		
		//..........Prints classification.
		if     (misclassification_log == - 1) {cout << "Classification: undesirable, model needs more training.";}
		else if(misclassification_log ==   0) {cout << "Classification: composite"                              ;}
		else if(misclassification_log ==   1) {cout << "Classification: prime"                                  ;}
		else                                  {cout << "\n\n\nError! Classification must be -1, 0, or 1. You have " << misclassification_log;}
	}
	
	else {cout << "\nInvalid option, program ended.\n"; return 0;}
}
