/*
 * This program inputs two numbers from the user, a lower and upper bound, and determines the sequence of increasingly-
 * additive prime numbers between them. For example, given the inputs 4 and 20, the output would be 5, 7, 13. The variables
 * are declared and assigned in C code, while the core logic is written in assembly language.
 *
 * Spencer Peace
 * CSC 362-001
 * Dr. Richard Fox
 * 11/12/19
 * Project 4
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	// Declare int variables to store user input of lower and upper bounded numbers as well as the running total and the current output number
	int lowerBound, upperBound, sum = 0, outputNum;

	// Test
	int secondOutput;

	// Store user input for lower bound for calculations
	printf("Please input the lower bound: ");
	scanf("%d", &lowerBound);

	// Store user input for upper bound for calculations
	printf("Please input the upper bound: ");
	scanf("%d", &upperBound);

	/* Write program in C first, test functionality, then convert to assembly
	for (int i = lowerBound; i <= upperBound; i++) {
		if (i <= sum) {
			continue;
		}
		for (int j = 2; j <= i; j++) {
			if (j == i) { // if the only factor of i is itself, that means it is prime. Add it to the sum and print it.
				sum += i;
				printf("%d ", i);
				break;
			} else if (i % j == 0) { // if i is divisible by any of the numbers from 2 - i, it is not prime so we skip it.
				break;
			}
		}
	}
	printf("\n%d", sum); // Print out the sum for testing purposes
	*/

	/*
		Some notes on my program for reference:
		ebx = i
		top = outer for loop
		outerNext = increment i, move to next iteration
		ecx = j
		eax = accumulator
		edx = remainder of division
	
	*/

	// Begin main assembly code
	__asm {
					mov ebx, lowerBound // store lowerBound in the ebx register and use it as a de-facto loop counter. The reason why I do this is because ECX gets erased when printf is called. 
		top:		cmp ebx, upperBound // Outer for loop
					jg xout // if i > upperBound, exit the loop and end the program
					cmp ebx, sum
					jle outerNext // if i <= sum, go to next iteration (continue)
					mov ecx, 2 // set ecx to be the loop counter in the inside variable, i.e. j
		inner:		cmp ecx, ebx
					jg outerNext // if j > i, go to the next iteration of the outer loop
					cmp ecx, ebx
					jne elif // if j != i, jump to the else if clause. Otherwise, add i to sum and print it, seeing as it is both prime and increasingly additive.
					mov eax, sum
					add eax, ebx // sum + i
					mov sum, eax // sum = sum + i
					mov outputNum, ebx // outputNum = i
					jmp print // unconditionally break to printing out number
		elif:		mov edx, 0 // clear out edx to hold the remainder of the division, used to test if a i is evenly divisible by j
					mov eax, ebx // accumulator <- i
					div ecx // divide i by j, store quotient in eax, remainder in edx
					cmp edx, 0
					je outerNext // if i is evenly divisible by j, jump to the next iteration of the outer loop, as it is not prime
		xelse:		inc ecx
					jmp inner // increment inner loop
		print:		nop	// placeholder for unconditional breaks to the print statement and next iteration of the outer loop
	};

	printf("%d ", outputNum); // Output a number if it is both prime and increasingly additive

	__asm {
		outerNext:	inc ebx // Label to begin the next iteration of the outer loop
					jmp top
		xout:		nop
	}

	return 0;
}

/*

Output:

Please input the lower bound: 4
Please input the upper bound: 20
5 7 13
C:\Users\Spencer\source\repos\Project4\Debug\Project4.exe (process 3716) exited with code 0.
Press any key to close this window . . .

Please input the lower bound: 10
Please input the upper bound: 100
11 13 29 59
C:\Users\Spencer\source\repos\Project4\Debug\Project4.exe (process 10028) exited with code 0.
Press any key to close this window . . .

Please input the lower bound: 3
Please input the upper bound: 1000
3 5 11 23 43 89 179 359 719
C:\Users\Spencer\source\repos\Project4\Debug\Project4.exe (process 6384) exited with code 0.
Press any key to close this window . . .

Please input the lower bound: 300
Please input the upper bound: 5000
307 311 619 1249 2503 4993
C:\Users\Spencer\source\repos\Project4\Debug\Project4.exe (process 16080) exited with code 0.
Press any key to close this window . . .

*/