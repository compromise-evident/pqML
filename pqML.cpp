/// pqML - let AI factor up to 66-digit semiprimes, and                         Run it: "apt install g++ geany libgmp-dev libdlib-dev". Open the .cpp in Geany.
///        recognize up to 98-digit primes & composites.                        Append "-lgmp -ldlib" to Geany's compile & build commands. Hit F9 once. F5 to run.
///        All generated in the style of ezMNIST, which
///        is included to test model for generalization.


// Version 3.0.0
//#include <dlib/dnn.h>   //temporarily disabled for faster compile time.
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
	
	//                               Semiprimes+factors
	int                           p_length =    33; //max: 33 for pqML, 50k  actual
	int                           q_length =    33; //max: 33 for pqML, 50k  actual
	int                          pq_length =    66; //max: 66 for pqML, 100k actual
	int             semiprimes_for_testing =  1000; //max: 2B
	int            semiprimes_for_training = 50000; //max: 2B
	
	//                               Primes+composites
	int         prime_and_composite_length =    98; //max: 98 for pqML, 50k  actual
	int  primes_and_composites_for_testing = 10000; //max: 2B
	int primes_and_composites_for_training = 90000; //max: 2B
	
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
	
	cout << "\n(1) Create a new random model and save it in one folder."
	     << "\n(2) Train & test model for generalization using ezMNIST."
	     << "\n(3) Train & test model on your data, prime or semiprime;"
	     << "\n"
	     << "\n(4) Generate new semiprimes+factors, ezMNIST style."
	     << "\n(5) Generate new primes+composites, ezMNIST style."
	
	     << "\n\nOption: ";
	
	int user_option; cin >> user_option;
	if((user_option != 1) && (user_option != 2) && (user_option != 3) && (user_option != 4) && (user_option != 5)) {cout << "\nInvalid.\n"; return 0;}
	
	
	
	
	
	//_______________________________________________________Create___________________________________________________//
	if(user_option == 1)
	{	
	}
	
	
	
	
	
	//_________________________________________________________Run____________________________________________________//
	if((user_option == 2) || (user_option == 3))
	{	
	}
	
	
	
	
	
	//_____________________________________________________Semiprimes_________________________________________________//
	if(user_option == 4)
	{	//Verbatim from semiprime-training-data.cpp except for no padded, no ios::app for file output.
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
	
	
	
	
	
	//_______________________________________________________Primes___________________________________________________//
	if(user_option == 5)
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
}
