#include <chrono>
#include <random>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUMBYTESPERMB 1048576

using namespace std;

int main()
{
	random_device rd;
	negative_binomial_distribution<int> nb(3, 0.5);

	bool failed = false;

	while (!failed)
	{
		if (rd() % 7)
		{
			uint64_t bytes = (16 + (rd() % 496)) * NUMBYTESPERMB;
			void* bigArray = malloc(bytes);

			if (bigArray)
			{
				memset(bigArray, 0, bytes);
				fprintf(stdout, "Allocated %llu bytes\n", (unsigned long long)bytes);

				int waitTime = nb(rd);
				fprintf(stdout, "Waiting %d minutes\n", waitTime);
				sleep(waitTime * 60);

				free(bigArray);
			}
			else
			{
				fprintf(stderr, "Allocate memory failed, exiting\n");
				failed = true;
			}
		}
		else
		{
			int waitTime = nb(rd);
			fprintf(stdout, "Waiting %d minutes\n", waitTime);
			sleep(waitTime * 60);
		}
	}

	exit(EXIT_FAILURE);
}