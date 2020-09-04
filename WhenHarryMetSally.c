/*
When Harry Met Sally

Author: Yida Wang
Last date modified: September 10th, 2019

This program finds the earliest year in which Harry and Sally live in the same
city.
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

/* City IDs used in timelines. */
enum Cities{ London, Boston, Paris, Atlanta, Miami, 
             Tokyo, Metz, Seoul, Toronto, Austin };

int main(int argc, char *argv[]) {
   int	HarryTimeline[10];
   int	SallyTimeline[10];
   int	NumNums, Year=0;
   int  Load_Mem(char *, int *, int *);
   void Print_Timelines(int *, int *);

   if (argc != 2) {
     printf("usage: ./HW2-1 valuefile\n");
     exit(1);
   }
   NumNums = Load_Mem(argv[1], HarryTimeline, SallyTimeline);
   if (NumNums != 20) {
     printf("valuefiles must contain 20 entries\n");
     exit(1);
   }
   if (DEBUG)
     Print_Timelines(HarryTimeline, SallyTimeline);

      // Initialize variables
      int count = 1;                          // count is the number of year for Sally living in a place.
      int location = 1;                       // location is the city index for Sally.
      int answer = 0;                         // answer is the how many years have passed.

      // For loop controls Harry's time line.
      for (int i = 0; i < 5; i++){            // i controls each group of time and place for Harry.
        
        for (int j = 0; j < HarryTimeline[i*2]; j++){   // j controls Harry's year in i group.
        
          if (HarryTimeline[i*2+1] == SallyTimeline[location]){   // compare the city index. If they are the same, compute the output and exit.
        
            Year = 1990 + answer;             // calculate the year
            printf("Earliest year in which both lived in the same city: %d\n", Year);
            exit(0);
        
          }
          if (count == SallyTimeline[location-1]){      // if count reach the cap year in i group. location-1 is the time index for Sally.
        
            count = 1;                        // reset count to 1
            location += 2;                    // location = location + 2, move to the next location for Sally.
        
          }
          else{                               // if count doesn't reach the cap year.
            count++;                          // increase 1 year for Sally living in a place.
          }
          answer++;                           // increase the number of years have passed.
        }
      }
      
      printf("Earliest year in which both lived in the same city: %d\n", Year);
      exit(0);
}

/* This routine loads in up to 20 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray1[], int IntArray2[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     for (N=0; N < 20; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 if (N < 10)
	   IntArray1[N] = Value;
	 else
	   IntArray2[N-10] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}

/* Colors used to display timelines.
https://en.wikipedia.org/wiki/ANSI_escape_code#Colors */

const char *colors[10] = {"\x1b[30;41m", // red
			  "\x1b[30;42m", // green
			  "\x1b[30;43m", // yellow
			  "\x1b[30;44m", // blue
			  "\x1b[30;45m", // magenta
			  "\x1b[30;46m", // cyan (light blue)
			  "\x1b[30;47m", // white bkgd
			  "\x1b[30;103m", // bright yellow
			  "\x1b[30;104m", // bright blue
			  "\x1b[30;106m"}; // bright cyan

#define RESET      "\x1b[0m"

void Print_Years(){
  int i;
  printf("  ");
  for (i=90; i<120; i++){
    printf("%3d", i%100);
  }
  printf("\n");
}

void Print_Timeline(int Timeline[]){
  int j, duration, city;
  int scale = 3;
  char interval[6];
  for (j=0; j<10; j=j+2){
    duration = Timeline[j];
    city     = Timeline[j+1];
    snprintf(interval, sizeof(interval), "%%%dd", duration*scale);
    printf("%s", colors[city]); // start highlighting in city's color
    printf(interval, city);
  }
  printf(RESET); // stop highlighting
  printf("\n");
}


void Print_Timelines(int HarryTimeline[], int SallyTimeline[]) {
  Print_Years();
  printf("H: ");

  Print_Timeline(HarryTimeline);

  printf("S: ");
  Print_Timeline(SallyTimeline);
}

