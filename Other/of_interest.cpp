//This is an experimental pqML setup that keeps switching between 100 and 10,000
//training items as you watch the switching interfere with the model--forcing it
//to reset yet at the same time, bring misclassification down in less #of steps.

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	cout << "\n(pq Machine Learning)\n\n";
	
	int user_option = 1; //cin >> user_option;
	ifstream in_stream;
	ofstream out_stream;
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Train_______________________________________________________/
	if((user_option == 1) || (user_option == 2))
	{	
		int alternator = 1;
		int dependent;
		for(;;)
		{	if(alternator == 1) {alternator = 2;}
			else                {alternator = 1;} 
			
			if(alternator == 1) {user_option = 1;}
			else                {user_option = 2;}
			
			if(user_option == 1) {dependent = 60000;}
			else                 {dependent =  2200;}
			
			//Checks if training data is missing.
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
			
			//Prints model, later prints IMPROVED models while training (improvements are also overwritten to file "Model".)
			cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
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
			int number_of_training_items = 10000;
			if(user_option == 1)
			{	for(int a = 0; a < 94050; a++) {in_stream.get(garbage_byte);} //..........Skips 1st 4,950 items so the next 100 are 50 primes & 50 composites.
				number_of_training_items = 100;
			}
			
			char training_data[180000] = {0};
			int training_data_write_bookmark = 0;
			for(int a = 0; a < number_of_training_items; a++)
			{	for(int b = 0; b < 18; b++)
				{	in_stream.get(training_data[training_data_write_bookmark]);
					training_data[training_data_write_bookmark] -= 48; //..........-48 means actual value of digit.
					training_data_write_bookmark++;
				}
				in_stream.get(garbage_byte); //..........Skips \n
			}
			in_stream.close();
			
			//Runs all 100 or 10,000 items through the model once to set initial misclassification count so it can be compared upon changes to the model.
			int misclassification_log[10000];
			int misclassification_counter = 0;
			int training_data_read_bookmark = 0;
			int fire[18];
			for(int a = 0; a < number_of_training_items; a++)
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
			if(user_option == 1)
			{	for(int a = 0; a < 50; a++)
				{	if(misclassification_log[a] != 1) {misclassification_counter++;} //..........First 50 must be classified under prime.
				}
				
				for(int a = 50; a < 100; a++)
				{	if(misclassification_log[a] != 0) {misclassification_counter++;} //..........Remaining 50 must be classified under composite.
				}
				
				cout << "Misclassifies: " << misclassification_counter << " of 100 training items.\n\n";
			}
			else
			{	for(int a = 0; a < 5000; a++)
				{	if(misclassification_log[a] != 1) {misclassification_counter++;} //..........First 5,000 must be classified under prime.
				}
				
				for(int a = 5000; a < 10000; a++)
				{	if(misclassification_log[a] != 0) {misclassification_counter++;} //..........Remaining 5,000 must be classified under composite.
				}
				
				cout << "Misclassifies: " << misclassification_counter << " of 10000 training items.\n\n";
			}
			
			
			
			
			
			//Loops: model modification, another pass of all 100 or 10,000 training items. Improved model is saved.
			srand(time(0));
			int model_iteration = 0;
			long long loops = 0;
			int best_misclassification = misclassification_counter;
			int exhaustion_counter = 0;
			for(int limit = 0; limit < dependent; limit++)
			{	loops++;
				if(loops == 9223372036854775807) {loops = 0;}
				
				//..........Randomly modifies a model neuron (WITH reversion if modification unhelpful;
				int random_layer  = (rand() %  4); random_layer++;
				int random_neuron = (rand() % 18);
				int random_output = (rand() %  2);
				int random_VALUE  = (rand() % 95);
				int temp_random_VALUE;
				
				if     (random_layer == 1) {temp_random_VALUE = input_model   [random_neuron]; input_model   [random_neuron] = random_VALUE;}
				else if(random_layer == 2) {temp_random_VALUE = hidden_1_model[random_neuron]; hidden_1_model[random_neuron] = random_VALUE;}
				else if(random_layer == 3) {temp_random_VALUE = hidden_2_model[random_neuron]; hidden_2_model[random_neuron] = random_VALUE;}
				else                       {temp_random_VALUE = output_model  [random_output]; output_model  [random_output] = random_VALUE;}
				
				//..........Runs all 100 or 10,000 training items through the model again.
				int misclassification_counter = 0;
				int training_data_read_bookmark = 0;
				int fire[18];
				for(int a = 0; a < number_of_training_items; a++)
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
				if(user_option == 1)
				{	for(int a = 0; a < 50; a++)
					{	if(misclassification_log[a] != 1) {misclassification_counter++;} //..........First 50 must be classified under prime.
					}
					
					for(int a = 50; a < 100; a++)
					{	if(misclassification_log[a] != 0) {misclassification_counter++;} //..........Remaining 50 must be classified under composite.
					}
				}
				else
				{	for(int a = 0; a < 5000; a++)
					{	if(misclassification_log[a] != 1) {misclassification_counter++;} //..........First 5,000 must be classified under prime.
					}
					
					for(int a = 5000; a < 10000; a++)
					{	if(misclassification_log[a] != 0) {misclassification_counter++;} //..........Remaining 5,000 must be classified under composite.
					}
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
					model_iteration++;
					cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					system("date > date.txt");
					
					in_stream.open("date.txt");
					for(int a = 0; a < 27; a++) {in_stream.get(garbage_byte); cout << garbage_byte;}
					in_stream.close();
					remove("date.txt");
					
					cout << " (update " << model_iteration << ", " << "run " << loops << " since last)\n"
					     << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
					     << "Updated model: ";
					
					loops = 0;
					for(int a = 0; a < 18; a++) {cout << char(input_model   [a] + 32);}
					for(int a = 0; a < 18; a++) {cout << char(hidden_1_model[a] + 32);}
					for(int a = 0; a < 18; a++) {cout << char(hidden_2_model[a] + 32);}
					cout << char(output_model[0] + 32)<< char(output_model  [1] + 32);
					cout << "\n";
					
					if(user_option == 1) {cout << "Misclassifies: " << misclassification_counter <<   " of 100 training items.\n\n";}
					else                 {cout << "Misclassifies: " << misclassification_counter << " of 10000 training items.\n\n";}
					
					exhaustion_counter = 0;
				}
				else //..........Reverts model change if unhelpful.
				{	if(exhaustion_counter < 5320) //Does not revert if exhausted tries, keeps last try and continues with another until exhausted and so on (2+ char changes.)
					{	if     (random_layer == 1) {input_model   [random_neuron] = temp_random_VALUE;}
						else if(random_layer == 2) {hidden_1_model[random_neuron] = temp_random_VALUE;}
						else if(random_layer == 3) {hidden_2_model[random_neuron] = temp_random_VALUE;}
						else                       {output_model  [random_output] = temp_random_VALUE;}
					}
					
					exhaustion_counter++;
				}
				
				if(exhaustion_counter > 5320) {exhaustion_counter = 0;}
			}
			
			cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			     << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			     << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
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
