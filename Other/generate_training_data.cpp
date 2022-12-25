///In 7 hours, creates a 190kB file containing 5,000 primes and 5,000 composites.

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ofstream out_stream;
	cout << "\nGenerating training data. Wait 7 hours total.\n\n";
	
	//Boolean sieve of Eratosthenes. Zeros are mapped to prime elements. Laughably, bool[] & char[] both consume 1 Byte.
	static bool sieve[1000000000] = {1, 1};
	for(int prime = 2; prime < 31623; prime++) //31,623 is sqrt(1,000,000,000) Sieve is 10^9 because 18-digit candidates must be tested with primes up to 10^9.
	{	for(; sieve[prime] == 1;) {prime++;} //Moves up the list if number already marked off.
		for(int a = prime + prime; a < 1000000000; a += prime) {sieve[a] = 1;} //Marks multiples (composites.)
		
		if(prime == 7) {cout << "Generating sieve. Wait 1 minute...\n\n";}
	}
	
	//Creates 5000 random 18-digit composites (~15 minutes.)
	cout << "Generating composites. Wait 25 minutes...\n\n";
	long primes    [5000] = {0};
	long composites[5000] = {0};
	int  composites_write_bookmark = 0;
	int  primes_write_bookmark     = 0;
	srand(time(0));
	
	for(; composites_write_bookmark < 5000;)
	{	//..........Creates 18-digit candidate.
		long candidate = 0;
		long multiplier = 1;
		for(int a = 0; a < 18; a++)
		{	long place_value = (rand() % 10);
			place_value *= multiplier;
			multiplier *= 10;
			
			candidate += place_value;
		}
		if(candidate < 100000000000000000) {candidate += 100000000000000000;}
		
		//..........Tests, not adjusts for compositeness. If prime, breaks out of for() & creates new candidate.
		long prime_divisor = 0;
		for(int a = 0; a < 1000000000; a++)
		{	if(sieve[a] == 0)
			{	if((candidate % prime_divisor) == 0)
				{	//..........Writes composite to composites[].
					composites[composites_write_bookmark] = candidate;
					composites_write_bookmark++;
					break;
				}
			}
			
			prime_divisor++; //..........Actually hops with zeros in sieve.
		}
	}
	
	//Creates 5,000 random 18-digit primes (~7 hours.)
	cout << "Generating primes. wait ~7 hours...\n\n";
	for(; primes_write_bookmark < 5000;)
	{	//..........Creates 18-digit candidate.
		long candidate = 0;
		long multiplier = 1;
		for(int a = 0; a < 18; a++)
		{	long place_value = (rand() % 10);
			place_value *= multiplier;
			multiplier *= 10;
			
			candidate += place_value;
		}
		if(candidate < 100000000000000000) {candidate += 100000000000000000;}
		
		//..........Adjusts for primality. for() is not exited until candidate is made prime.
		if((candidate % 2) == 0) {candidate++;} //..........Makes candidate odd.
		long prime_divisor = 0;
		for(int a = 0; a < 1000000000; a++)
		{	if(sieve[a] == 0)
			{	if((candidate % prime_divisor) == 0)
				{	candidate += 2;
					a = -1;
					prime_divisor = 0;
					continue;
				}
			}
			
			prime_divisor++; //..........Actually hops with zeros in sieve.
		}
		
		//..........Writes prime to primes[].
		primes[primes_write_bookmark] = candidate;
		primes_write_bookmark++;
		
		cout << "prime " << primes_write_bookmark << " of 5000 = " << primes[primes_write_bookmark - 1] << "\n";
	}
	
	//..........Writes training data to file "Training_data" (writes 5,000 primes then 5,000 composites.)
	out_stream.open("Training_data");
	for(int a = 0; a < 5000; a++) {out_stream << primes    [a] << "\n";}
	for(int a = 0; a < 5000; a++) {out_stream << composites[a] << "\n";}
	out_stream.close();
}
