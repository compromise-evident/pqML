/// pqML - let AI factor semiprimes and recognize primes &                      Run it: "apt install g++ geany libgmp-dev python3-torch". Open the .cpp in Geany.
///        composites. Or make your own train.txt                               Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
///        & test.txt. Uses PyTorch.


// Version 4.2.0
#include <fstream>
#include <gmp.h>
#include <iostream>
using namespace std;
int main()
{	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  /////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    ////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\      ///////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\        //////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\            ////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\              ///////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\       your       /////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\       controls       ///////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\                              ///////////////////////
	\\\\\\\\\\\\\\\\\\                                        ////////////////*/
	
	//                  Hidden layers (get new model per change)
	int                   number_of_layers =     2; //2B  max
	int                  neurons_per_layer =   100; //2B  max
	
	//                               Semiprimes+factors
	int                           p_length =    10; //50  max
	int                           q_length =    10; //50  max
	int                          pq_length =    20; //100 max
	int             semiprimes_for_testing =   100; //2B  max
	int            semiprimes_for_training =  1000; //2B  max
	
	//                               Primes+composites
	int         prime_and_composite_length =    20; //150 max
	int  primes_and_composites_for_testing =  1000; //2B  max
	int primes_and_composites_for_training = 10000; //2B  max
	
	//                                Options a,b,c,d
	int           loop_til_percent_correct =    97; //1 - 100
	
	/*////////////////                                        \\\\\\\\\\\\\\\\\\
	///////////////////////                              \\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////                      \\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
	
	ifstream in_stream;
	ofstream out_stream;
	
	cout << "\n(1) Model    (Create a new model and save it as one file.)"
	     << "\n(2) ezMNIST  (See if your model can generalize using ezMNIST.)"
	     << "\n(3) Evidence (See just the testing on ezMNIST without training.)"
	     << "\n÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷"
	     << "\n(4) Factors  (Generate new semiprimes+factors, ezMNIST style.)"
	     << "\n(5) Primes   (Generate new primes+composites, ezMNIST style.)"
	     << "\n(6) Train    (Train & test model on generated train.txt & test.txt.)"
	     << "\n(7) Test     (See just the testing on test.txt without training.)"
	     << "\n(8) Use      (Classify unlabeled version of test.txt with no spaces.)"
	     << "\n÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷×÷"
	     << "\n(a) Loop 2   (loop_til_percent_correct = " << loop_til_percent_correct << ".)"
	     << "\n(b) Loop 4,6 (loop_til_percent_correct = " << loop_til_percent_correct << ".)"
	     << "\n(c) Loop 5,6 (loop_til_percent_correct = " << loop_til_percent_correct << ".)"
	     << "\n(d) Loop 6   (loop_til_percent_correct = " << loop_til_percent_correct << ".)"
	     << "\n(e) Merge    (Merge models of any quantity.)"
	
	     << "\n\nOption: ";
	
	char user_option; cin >> user_option;
	
	
	
	
	
	//Input layer always eats 784. Output layer always gives 10.
	//Writes hidden layer architecture values to a file, to be used by the following 6 .py files.
	out_stream.open("Model/Python/depth_width.txt"); out_stream << number_of_layers << "\n" << neurons_per_layer << "\n"; out_stream.close();
	
	//Runs 1 .py file based on user option.
	if     (user_option == '1') {system("python3 ./Model/Python/model.py"   );} //   Model
	else if(user_option == '2') {system("python3 ./Model/Python/ezMNIST.py" );} //   ezMNIST
	else if(user_option == '3') {system("python3 ./Model/Python/evidence.py");} //   Evidence
	
	else if(user_option == '6') {system("python3 ./Model/Python/train.py"   );} //   Train
	else if(user_option == '7') {system("python3 ./Model/Python/test.py"    );} //   Test
	else if(user_option == '8') {system("python3 ./Model/Python/use.py"     );} //   Use
	
	
	
	
	
	//_______________________________________________Semiprimes+factors_______________________________________________//
	else if(user_option == '4')
	{	//Verbatim from semiprime-training-data.cpp.
		srand(time(0));
		char  p[ 50001] = {'\0'};
		char  q[ 50001] = {'\0'};
		char pq[200001] = {'\0'};
		mpz_t randomness; mpz_init(randomness);
		mpz_t prime_p   ; mpz_init(prime_p   );
		mpz_t prime_q   ; mpz_init(prime_q   );
		mpz_t product   ; mpz_init(product   );
		
		//Testing-data.
		cout << "\nGenerating testing-data...\n";
		out_stream.open("test.txt");
		for(int loops = 0; loops < semiprimes_for_testing;)
		{	for(int a = 0; a < p_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';} //Random p.
			for(int a = 0; a < q_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
			mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str( p, 10, prime_p);  //p made prime.
			mpz_set_str(randomness, q, 10); mpz_nextprime(prime_q, randomness); mpz_get_str( q, 10, prime_q);  //q made prime.
			mpz_mul(product, prime_p, prime_q);                                 mpz_get_str(pq, 10, product);  //pq made.
			int length = 0; for(int a = 0; pq[a] != '\0'; a++) {length++;} if(length != pq_length) {continue;} //Restarts if pq not pq_length.
			
			//Appends smaller prime to pq[].
			int prime_comparison = mpz_cmp(prime_p, prime_q);
			int pq_write_bookmark = pq_length;
			if(prime_comparison < 0) {for(int a = 0; a < p_length; a++) {pq[pq_write_bookmark] = p[a]; pq_write_bookmark++;}}
			else                     {for(int a = 0; a < q_length; a++) {pq[pq_write_bookmark] = q[a]; pq_write_bookmark++;}}
			
			//Saves to file.
			for(int pq_read_bookmark = pq_length; pq[pq_read_bookmark] != '\0'; pq_read_bookmark++)
			{	out_stream << pq[pq_read_bookmark] << " "; //Label first.
				for(int a = 0; a < pq_read_bookmark; a++) {out_stream << pq[a];} //The rest.
				out_stream << "\n";
			}
			
			loops++; cout << loops << " of " << semiprimes_for_testing << "\n";
		}
		out_stream.close();
		
		//Training-data (ditto but unique items.)
		cout << "\nGenerating training-data...\n";
		out_stream.open("train.txt");
		for(int loops = 0; loops < semiprimes_for_training;)
		{	for(int a = 0; a < p_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';} //Random p.
			for(int a = 0; a < q_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
			mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str( p, 10, prime_p);  //p made prime.
			mpz_set_str(randomness, q, 10); mpz_nextprime(prime_q, randomness); mpz_get_str( q, 10, prime_q);  //q made prime.
			mpz_mul(product, prime_p, prime_q);                                 mpz_get_str(pq, 10, product);  //pq made.
			int length = 0; for(int a = 0; pq[a] != '\0'; a++) {length++;} if(length != pq_length) {continue;} //Restarts if pq not pq_length.
			
			//Appends smaller prime to pq[].
			int prime_comparison = mpz_cmp(prime_p, prime_q);
			int pq_write_bookmark = pq_length;
			if(prime_comparison < 0) {for(int a = 0; a < p_length; a++) {pq[pq_write_bookmark] = p[a]; pq_write_bookmark++;}}
			else                     {for(int a = 0; a < q_length; a++) {pq[pq_write_bookmark] = q[a]; pq_write_bookmark++;}}
			
			//Saves to file.
			for(int pq_read_bookmark = pq_length; pq[pq_read_bookmark] != '\0'; pq_read_bookmark++)
			{	out_stream << pq[pq_read_bookmark] << " "; //Label first.
				for(int a = 0; a < pq_read_bookmark; a++) {out_stream << pq[a];} //The rest.
				out_stream << "\n";
			}
			
			loops++; cout << loops << " of " << semiprimes_for_training << "\n";
		}
		out_stream.close();
	}
	
	
	
	
	
	//________________________________________________Primes+composites_______________________________________________//
	else if(user_option == '5')
	{	//Verbatim from semiprime-training-data.cpp.
		srand(time(0));
		char p[50001] = {'\0'};
		char q[50001] = {'\0'};
		mpz_t randomness; mpz_init(randomness);
		mpz_t prime_p   ; mpz_init(prime_p   );
		
		//Testing-data.
		cout << "\nGenerating testing-data...\n";
		out_stream.open("test.txt");
		for(int loops = 0; loops < primes_and_composites_for_testing;)
		{	int which_one = (rand() % 2);
			if(which_one == 0)
			{	for(int a = 0; a < prime_and_composite_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';}     //Random p.
				mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str(p, 10, prime_p);                         //p made prime.
				out_stream << "1 " << p << "\n"; //Saves to file: label, prime.
			}
			else
			{	for(int compositeness = 1; compositeness != 0;)
				{	for(int a = 0; a < prime_and_composite_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
					mpz_set_str(randomness, q, 10); compositeness = mpz_probab_prime_p(randomness, 100);                                 //q used if composite.
				}
				mpz_get_str(q, 10, randomness);
				out_stream << "0 " << q << "\n"; //Saves to file: label, composite.
			}
			
			loops++; cout << loops << " of " << primes_and_composites_for_testing << "\n";
		}
		out_stream.close();
		
		//Training-data (ditto but unique items.)
		cout << "\nGenerating training-data...\n";
		out_stream.open("train.txt");
		for(int loops = 0; loops < primes_and_composites_for_training;)
		{	int which_one = (rand() % 2);
			if(which_one == 0)
			{	for(int a = 0; a < prime_and_composite_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';}     //Random p.
				mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str(p, 10, prime_p);                         //p made prime.
				out_stream << "1 " << p << "\n"; //Saves to file: label, prime.
			}
			else
			{	for(int compositeness = 1; compositeness != 0;)
				{	for(int a = 0; a < prime_and_composite_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
					mpz_set_str(randomness, q, 10); compositeness = mpz_probab_prime_p(randomness, 100);                                 //q used if composite.
				}
				mpz_get_str(q, 10, randomness);
				out_stream << "0 " << q << "\n"; //Saves to file: label, composite.
			}
			
			loops++; cout << loops << " of " << primes_and_composites_for_training << "\n";
		}
		out_stream.close();
	}
	
	
	
	
	
	//__________________________________________________Loop_option_2_________________________________________________//
	else if(user_option == 'a')
	{	cout << "Printing log...\n\n";
		for(long long round = 1;; round++)
		{	//ezMNIST (without print.)
			system("python3 ./Model/Python/ezMNIST.py > /dev/null 2>&1");
			
			//Calculates percent correct.
			long long total     = 0;
			long long correct   = 0;
			long long incorrect = 0;
			char file_byte_1;
			char file_byte_2;
			ifstream in_stream_1;
			ifstream in_stream_2;
			in_stream_1.open("results.txt");
			in_stream_2.open("ezMNIST/test-ezMNIST.txt");
			in_stream_1.get(file_byte_1);
			in_stream_2.get(file_byte_2);
			for(; in_stream_1.eof() == false;)
			{	total++;
				if(file_byte_1 == file_byte_2) {correct++  ;}
				else                           {incorrect++;}
				
				in_stream_1.get(file_byte_1); in_stream_1.get(file_byte_1);
				for(; file_byte_2 != '\n';) {in_stream_2.get(file_byte_2);} in_stream_2.get(file_byte_2);
			}
			in_stream_1.close();
			in_stream_2.close();
			
			cout << "Round " << round << ". Looping 2 til " << loop_til_percent_correct << "% correct (got ";
			double percent_correct = ((double(correct) / double(total)) * 100);
			cout.precision(15); cout << fixed << percent_correct << "%)\n";
			cout << "Misclassifies " << incorrect << " out of " << total << "\n\n";
			
			if(percent_correct >= loop_til_percent_correct) {break;}
		}
	}
	
	
	
	
	
	//________________________________________________Loop_options_4,6________________________________________________//
	else if(user_option == 'b')
	{	cout << "Printing log...\n\n";
		srand(time(0));
		for(long long round = 1;; round++)
		{	char  p[ 50001] = {'\0'};
			char  q[ 50001] = {'\0'};
			char pq[200001] = {'\0'};
			mpz_t randomness; mpz_init(randomness);
			mpz_t prime_p   ; mpz_init(prime_p   );
			mpz_t prime_q   ; mpz_init(prime_q   );
			mpz_t product   ; mpz_init(product   );
			
			//Testing-data.
			out_stream.open("test.txt");
			for(int loops = 0; loops < semiprimes_for_testing;)
			{	for(int a = 0; a < p_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';} //Random p.
				for(int a = 0; a < q_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
				mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str( p, 10, prime_p);  //p made prime.
				mpz_set_str(randomness, q, 10); mpz_nextprime(prime_q, randomness); mpz_get_str( q, 10, prime_q);  //q made prime.
				mpz_mul(product, prime_p, prime_q);                                 mpz_get_str(pq, 10, product);  //pq made.
				int length = 0; for(int a = 0; pq[a] != '\0'; a++) {length++;} if(length != pq_length) {continue;} //Restarts if pq not pq_length.
				
				//Appends smaller prime to pq[].
				int prime_comparison = mpz_cmp(prime_p, prime_q);
				int pq_write_bookmark = pq_length;
				if(prime_comparison < 0) {for(int a = 0; a < p_length; a++) {pq[pq_write_bookmark] = p[a]; pq_write_bookmark++;}}
				else                     {for(int a = 0; a < q_length; a++) {pq[pq_write_bookmark] = q[a]; pq_write_bookmark++;}}
				
				//Saves to file.
				for(int pq_read_bookmark = pq_length; pq[pq_read_bookmark] != '\0'; pq_read_bookmark++)
				{	out_stream << pq[pq_read_bookmark] << " "; //Label first.
					for(int a = 0; a < pq_read_bookmark; a++) {out_stream << pq[a];} //The rest.
					out_stream << "\n";
				}
				
				loops++;
			}
			out_stream.close();
			
			//Training-data (ditto but unique items.)
			out_stream.open("train.txt");
			for(int loops = 0; loops < semiprimes_for_training;)
			{	for(int a = 0; a < p_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';} //Random p.
				for(int a = 0; a < q_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
				mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str( p, 10, prime_p);  //p made prime.
				mpz_set_str(randomness, q, 10); mpz_nextprime(prime_q, randomness); mpz_get_str( q, 10, prime_q);  //q made prime.
				mpz_mul(product, prime_p, prime_q);                                 mpz_get_str(pq, 10, product);  //pq made.
				int length = 0; for(int a = 0; pq[a] != '\0'; a++) {length++;} if(length != pq_length) {continue;} //Restarts if pq not pq_length.
				
				//Appends smaller prime to pq[].
				int prime_comparison = mpz_cmp(prime_p, prime_q);
				int pq_write_bookmark = pq_length;
				if(prime_comparison < 0) {for(int a = 0; a < p_length; a++) {pq[pq_write_bookmark] = p[a]; pq_write_bookmark++;}}
				else                     {for(int a = 0; a < q_length; a++) {pq[pq_write_bookmark] = q[a]; pq_write_bookmark++;}}
				
				//Saves to file.
				for(int pq_read_bookmark = pq_length; pq[pq_read_bookmark] != '\0'; pq_read_bookmark++)
				{	out_stream << pq[pq_read_bookmark] << " "; //Label first.
					for(int a = 0; a < pq_read_bookmark; a++) {out_stream << pq[a];} //The rest.
					out_stream << "\n";
				}
				
				loops++;
			}
			out_stream.close();
			
			//Train (without print.)
			system("python3 ./Model/Python/train.py > /dev/null 2>&1");
			
			//Calculates percent correct.
			long long total     = 0;
			long long correct   = 0;
			long long incorrect = 0;
			char file_byte_1;
			char file_byte_2;
			ifstream in_stream_1;
			ifstream in_stream_2;
			in_stream_1.open("results.txt");
			in_stream_2.open("test.txt");
			in_stream_1.get(file_byte_1);
			in_stream_2.get(file_byte_2);
			for(; in_stream_1.eof() == false;)
			{	total++;
				if(file_byte_1 == file_byte_2) {correct++  ;}
				else                           {incorrect++;}
				
				in_stream_1.get(file_byte_1); in_stream_1.get(file_byte_1);
				for(; file_byte_2 != '\n';) {in_stream_2.get(file_byte_2);} in_stream_2.get(file_byte_2);
			}
			in_stream_1.close();
			in_stream_2.close();
			
			cout << "Round " << round << ". Looping 4,6 til " << loop_til_percent_correct << "% correct (got ";
			double percent_correct = ((double(correct) / double(total)) * 100);
			cout.precision(15); cout << fixed << percent_correct << "%)\n";
			cout << "Misclassifies " << incorrect << " out of " << total << "\n\n";
			
			if(percent_correct >= loop_til_percent_correct) {break;}
		}
	}
	
	
	
	
	
	//________________________________________________Loop_options_5,6________________________________________________//
	else if(user_option == 'c')
	{	cout << "Printing log...\n\n";
		srand(time(0));
		for(long long round = 1;; round++)
		{	char p[50001] = {'\0'};
			char q[50001] = {'\0'};
			mpz_t randomness; mpz_init(randomness);
			mpz_t prime_p   ; mpz_init(prime_p   );
			
			//Testing-data.
			out_stream.open("test.txt");
			for(int loops = 0; loops < primes_and_composites_for_testing;)
			{	int which_one = (rand() % 2);
				if(which_one == 0)
				{	for(int a = 0; a < prime_and_composite_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';}     //Random p.
					mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str(p, 10, prime_p);                         //p made prime.
					out_stream << "1 " << p << "\n"; //Saves to file: label, prime.
				}
				else
				{	for(int compositeness = 1; compositeness != 0;)
					{	for(int a = 0; a < prime_and_composite_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
						mpz_set_str(randomness, q, 10); compositeness = mpz_probab_prime_p(randomness, 100);                                 //q used if composite.
					}
					mpz_get_str(q, 10, randomness);
					out_stream << "0 " << q << "\n"; //Saves to file: label, composite.
				}
				
				loops++;
			}
			out_stream.close();
			
			//Training-data (ditto but unique items.)
			out_stream.open("train.txt");
			for(int loops = 0; loops < primes_and_composites_for_training;)
			{	int which_one = (rand() % 2);
				if(which_one == 0)
				{	for(int a = 0; a < prime_and_composite_length; a++) {p[a] = ((rand() % 10) + 48);}     if(p[0] == '0') {p[0] = '9';}     //Random p.
					mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str(p, 10, prime_p);                         //p made prime.
					out_stream << "1 " << p << "\n"; //Saves to file: label, prime.
				}
				else
				{	for(int compositeness = 1; compositeness != 0;)
					{	for(int a = 0; a < prime_and_composite_length; a++) {q[a] = ((rand() % 10) + 48);}     if(q[0] == '0') {q[0] = '9';} //Random q.
						mpz_set_str(randomness, q, 10); compositeness = mpz_probab_prime_p(randomness, 100);                                 //q used if composite.
					}
					mpz_get_str(q, 10, randomness);
					out_stream << "0 " << q << "\n"; //Saves to file: label, composite.
				}
				
				loops++;
			}
			out_stream.close();
			
			//Train (without print.)
			system("python3 ./Model/Python/train.py > /dev/null 2>&1");
			
			//Calculates percent correct.
			long long total     = 0;
			long long correct   = 0;
			long long incorrect = 0;
			char file_byte_1;
			char file_byte_2;
			ifstream in_stream_1;
			ifstream in_stream_2;
			in_stream_1.open("results.txt");
			in_stream_2.open("test.txt");
			in_stream_1.get(file_byte_1);
			in_stream_2.get(file_byte_2);
			for(; in_stream_1.eof() == false;)
			{	total++;
				if(file_byte_1 == file_byte_2) {correct++  ;}
				else                           {incorrect++;}
				
				in_stream_1.get(file_byte_1); in_stream_1.get(file_byte_1);
				for(; file_byte_2 != '\n';) {in_stream_2.get(file_byte_2);} in_stream_2.get(file_byte_2);
			}
			in_stream_1.close();
			in_stream_2.close();
			
			cout << "Round " << round << ". Looping 5,6 til " << loop_til_percent_correct << "% correct (got ";
			double percent_correct = ((double(correct) / double(total)) * 100);
			cout.precision(15); cout << fixed << percent_correct << "%)\n";
			cout << "Misclassifies " << incorrect << " out of " << total << "\n\n";
			
			if(percent_correct >= loop_til_percent_correct) {break;}
		}
	}
	
	
	
	
	
	//__________________________________________________Loop_option_6_________________________________________________//
	else if(user_option == 'd')
	{	cout << "Printing log...\n\n";
		for(long long round = 1;; round++)
		{	//Train (without print.)
			system("python3 ./Model/Python/train.py > /dev/null 2>&1");
			
			//Calculates percent correct.
			long long total     = 0;
			long long correct   = 0;
			long long incorrect = 0;
			char file_byte_1;
			char file_byte_2;
			ifstream in_stream_1;
			ifstream in_stream_2;
			in_stream_1.open("results.txt");
			in_stream_2.open("test.txt");
			in_stream_1.get(file_byte_1);
			in_stream_2.get(file_byte_2);
			for(; in_stream_1.eof() == false;)
			{	total++;
				if(file_byte_1 == file_byte_2) {correct++  ;}
				else                           {incorrect++;}
				
				in_stream_1.get(file_byte_1); in_stream_1.get(file_byte_1);
				for(; file_byte_2 != '\n';) {in_stream_2.get(file_byte_2);} in_stream_2.get(file_byte_2);
			}
			in_stream_1.close();
			in_stream_2.close();
			
			cout << "Round " << round << ". Looping 6 til " << loop_til_percent_correct << "% correct (got ";
			double percent_correct = ((double(correct) / double(total)) * 100);
			cout.precision(15); cout << fixed << percent_correct << "%)\n";
			cout << "Misclassifies " << incorrect << " out of " << total << "\n\n";
			
			if(percent_correct >= loop_til_percent_correct) {break;}
		}
	}
	
	
	
	
	
	//______________________________________________________Merge_____________________________________________________//
	else if(user_option == 'e')
	{	//Verbatim from StatMerge.cpp.
		bool average_instead_of_occurrence = false; //DEFAULT = false.  (false means
		//occurrence-based merging;  for retrieving original from corrupted copies.)
		
		//Gets path to FOLDER from user.
		cout << "\nDrop/enter FOLDER with files of equal size:\n";
		
		//..........Gets path then fixes it if drag-n-dropped, regardless of single-quote presence and "enter"
		//..........not being cleared, meaning you can have options before this, where the user presses enter.
		char path_to_file[10000] = {'\0'};
		{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
			cin.getline(path_to_file, 10000);
			if(path_to_file[0] == '\0')
			{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
				cin.getline(path_to_file, 10000);
			}
			if(path_to_file[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
			
			//..........Removes last space in path_to_file[].
			bool existence_of_last_space = false;
			for(int a = 9999; a > 0; a--)
			{	if(path_to_file[a] != '\0')
				{	if(path_to_file[a] == ' ') {path_to_file[a] = '\0'; existence_of_last_space = true;}
					break;
				}
			}
			
			//..........Removes encapsulating single-quotes in path_to_file[].
			bool existence_of_encapsulating_single_quotes = false;
			if(path_to_file[0] == '\'')
			{	for(int a = 0; a < 9999; a++)
				{	path_to_file[a] = path_to_file[a + 1];
					if(path_to_file[a] == '\0') 
					{	if(path_to_file[a - 1] != '\'') {cout << "\nBad path.\n"; return 0;}
						path_to_file[a - 1] = '\0';
						existence_of_encapsulating_single_quotes = true;
						break;
					}
				}
			}
			
			//..........Replaces all "'\''" with "'" in path_to_file[].
			int single_quote_quantity = 0;
			for(int a = 0; a < 10000; a++)
			{	if(path_to_file[a] == '\'') {single_quote_quantity++;}
			}
			
			if((single_quote_quantity                     >    0)
			&& (existence_of_last_space                  == true)
			&& (existence_of_encapsulating_single_quotes == true))
			{	if((single_quote_quantity % 3) != 0) {cout << "\nBad path.\n"; return 0;}
				
				for(int a = 0; a < 9997; a++)
				{	if(path_to_file[a] == '\'')
					{	int temp = (a + 1);
						for(; temp < 9997; temp++)
						{	path_to_file[temp] = path_to_file[temp + 3];
						}
					}
				}
			}
		}
		
		//Checks if FOLDER exists.
		in_stream.open(path_to_file);
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nNo such directory.\n"; return 0;}
		in_stream.close();
		
		//Gets location of the first encountered end-null coming from the left in path_to_file[].
		int path_to_file_null_bookmark;
		for(int a = 0; a < 10000; a++) {if(path_to_file[a] == '\0') {path_to_file_null_bookmark = a; break;}}
		
		//Gets list of file names from given directory.
		char ls[10000] = {"ls "};
		for(int a = 0; path_to_file[a] != '\0'; a++) {ls[a + 3] = path_to_file[a];} //..........Appends given path.
		ls[path_to_file_null_bookmark + 3] = ' '; //..........Appends commands.
		ls[path_to_file_null_bookmark + 4] = '>';
		ls[path_to_file_null_bookmark + 5] = ' ';
		ls[path_to_file_null_bookmark + 6] = 'f';
		system(ls);
		
		//Checks if FOLDER is empty.
		in_stream.open("f");
		char sniffed_one_file_character;
		in_stream.get(sniffed_one_file_character);
		if(in_stream.eof() == true) {in_stream.close(); cout << "\n\nNothing to process, the FOLDER is empty.\n"; return 0;}
		in_stream.close();
		
		//Counts number of files based on ls.
		long long number_of_files = 0;
		char garbage_byte;
		char temp_garbage_byte;
		in_stream.open("f");
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	if(garbage_byte == '\n') {number_of_files++;}
			temp_garbage_byte = garbage_byte;
			in_stream.get(garbage_byte);
		}
		in_stream.close();
		
		if(temp_garbage_byte != '\n') {number_of_files++                                                                      ;}
		if(number_of_files < 2      ) {cout << "\nMust have 2 or more files to merge, preferably 3+.\n"; remove("f"); return 0;}
		
		
		
		
		
		//This entire section can be removed.
		//Checks if all files are of equal size.
		cout << "\nChecking file sizes...\n";
		char COPY_path_to_file[10000];
		for(int a = 0; a < 10000; a++) {COPY_path_to_file[a] = path_to_file[a];}
		
		int COPY_path_to_file_null_bookmark = path_to_file_null_bookmark;
		COPY_path_to_file[COPY_path_to_file_null_bookmark] = '/';
		COPY_path_to_file_null_bookmark++;
		
		//..........Runs through all files.
		long long COPY_file_name_bytes_read_bookmark = -1;
		long long size_of_first_file;
		long long total_bytes = 0;
		bool ran_once = false;
		for(long long a = 0; a < number_of_files; a++)
		{	//..........Loads COPY_path_to_file[] with file name.
			in_stream.open("f");
			COPY_file_name_bytes_read_bookmark++;
			in_stream.seekg(COPY_file_name_bytes_read_bookmark, std::ios::beg); //..........Skips name Bytes that have been read.
			
			int COPY_path_to_file_write_bookmark = COPY_path_to_file_null_bookmark;
			
			in_stream.get(garbage_byte);
			for(; garbage_byte != '\n';)
			{	COPY_path_to_file[COPY_path_to_file_write_bookmark] = garbage_byte;
				COPY_path_to_file_write_bookmark++;
				COPY_file_name_bytes_read_bookmark++;
				in_stream.get(garbage_byte);
				
				if(in_stream.eof() == true) {cout << "\nError 1\n"; return 0;}
			}
			in_stream.close();
			
			COPY_path_to_file[COPY_path_to_file_write_bookmark] = '\0';
			
			//..........Gets file size.
			total_bytes = 0;
			in_stream.open(COPY_path_to_file);
			in_stream.get(garbage_byte);
			for(; in_stream.eof() == false;)
			{	in_stream.get(garbage_byte);
				total_bytes++;
			}
			in_stream.close();
			
			//..........Compares file size.
			if(ran_once == false) {size_of_first_file = total_bytes; ran_once = true;}
			if(size_of_first_file != total_bytes)
			{	cout << "\nFAILED! The following file is the first to be of\n"
				     << "a different size compared to ALL files before it:\n" ;
				
				for(int a = 0; COPY_path_to_file[a] != '\0'; a++) {cout << COPY_path_to_file[a];}
				
				cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				     << "\nSize of that file = " << total_bytes
				     << "\nSizes prior to it = " << size_of_first_file
				     << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
				
				remove("f");
				return 0;
			}
		}
		
		cout << "Merging " << number_of_files << " files, each " << total_bytes << " Bytes...\n";
		
		
		
		
		
		/*####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*######
		##'                                         '##
		#                   Begins.                   #
		#                                             #
		##,                                         ,##
		####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/
		path_to_file[path_to_file_null_bookmark] = '/';
		path_to_file_null_bookmark++;
		bool looped_at_least_once = false;
		long long bytes_to_skip = 0;
		long long megabytes_processed_announcement = 0;
		long long megabytes_processed_counter      = 0;
		long long byte_differences_announced       = 0;
		static long long distribution[250000][256]; //..........Can consume 512MB RAM.
		for(;;)
		{	//..........Clears distribution[][].
			for(int a = 0; a < 250000; a++)
			{	for(int b = 0; b < 256; b++) {distribution[a][b] = 0;}
			}
			
			//..........Runs through all files.
			long long file_name_bytes_read_bookmark = -1;
			for(long long a = 0; a < number_of_files; a++)
			{	//..........Loads path_to_file[] with file name.
				in_stream.open("f");
				file_name_bytes_read_bookmark++;
				in_stream.seekg(file_name_bytes_read_bookmark, std::ios::beg); //..........Skips name Bytes that have been read.
				int path_to_file_write_bookmark = path_to_file_null_bookmark;
				
				in_stream.get(garbage_byte);
				for(; garbage_byte != '\n';)
				{	path_to_file[path_to_file_write_bookmark] = garbage_byte;
					path_to_file_write_bookmark++;
					file_name_bytes_read_bookmark++;
					in_stream.get(garbage_byte);
					
					if(in_stream.eof() == true) {cout << "\nError 1\n"; return 0;}
				}
				in_stream.close();
				
				path_to_file[path_to_file_write_bookmark] = '\0';
				
				//..........Loads distribution[][]. 250kB are read from each file, and Byte occurrences are set. Next round is the next unread 250kB. From each file...
				int garbage_byte_normal;
				in_stream.open(path_to_file);
				in_stream.seekg(bytes_to_skip, std::ios::beg); //..........Skips FILE Bytes that have been read.
				in_stream.get(garbage_byte);
				for(int b = 0; in_stream.eof() == false; b++)
				{	if(b == 250000) {break;}
					garbage_byte_normal = garbage_byte;
					if(garbage_byte_normal < 0) {garbage_byte_normal += 256;}
					
					distribution[b][garbage_byte_normal]++;
					in_stream.get(garbage_byte);
				}
				in_stream.close();
			}
			
			//..........Append-writes 250kB portion of file.
			if(looped_at_least_once == false) {out_stream.open("MERGED"          );}
			else                              {out_stream.open("MERGED", ios::app);}
			
			for(int a = 0; a < 250000; a++)
			{	long long final_byte = 0;
				
				if(average_instead_of_occurrence == true)
				{	long long number_of_items = 0;
					for(int b = 0; b < 256; b++)
					{	if(distribution[a][b] != 0)
						{	number_of_items += distribution[a][b];
							final_byte += ((b + 1) * distribution[a][b]);
						}
					}
					
					if(number_of_items == 0) {out_stream.close(); remove("f"); cout << "\nAveraging done!\n\n\n"; return 0;}
					
					final_byte /= number_of_items;
					final_byte--;
				}
				else
				{	long long byte_differences_discovered = 0;
					long long most_tallies = 0;
					
					for(int b = 0; b < 256; b++)
					{	if(distribution[a][b] !=            0) {byte_differences_discovered++                    ;}
						if(distribution[a][b] >  most_tallies) {most_tallies = distribution[a][b]; final_byte = b;}
					}
					
					if(byte_differences_discovered > 1) {byte_differences_announced += (byte_differences_discovered - 1);}
					
					if(most_tallies == 0)
					{	if     (byte_differences_announced == 0) {cout << "\nDone! No Byte differences to reconcile.\n\n\n"                                ;}
						else if(byte_differences_announced == 1) {cout << "\nDone! 1 Byte difference reconciled.\n\n\n"                                    ;}
						else                                     {cout << "\nDone! " << byte_differences_announced << " Byte differences reconciled.\n\n\n";}
						
						out_stream.close(); remove("f"); return 0;
					}
				}
				
				if(final_byte < 128) {out_stream.put(final_byte      );}
				else                 {out_stream.put(final_byte - 256);}
			}
			out_stream.close();
			
			bytes_to_skip += 250000;
			looped_at_least_once = true;
			
			megabytes_processed_announcement++;
			if(megabytes_processed_announcement == 4)
			{	megabytes_processed_announcement = 0;
				megabytes_processed_counter++;
				cout << megabytes_processed_counter << "MB merged...\n";
			}
		}
	}
	
	else {cout << "\nInvalid.\n"; return 0;}
}
