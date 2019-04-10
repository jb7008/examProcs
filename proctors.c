#include <stdio.h> /* Includes printf, scanf */

#define INPUT_FILE "input4.txt" /* input file name */
#define HOURS_TO_MINS 3600 /* Hours to minutes conversion factor */
#define MINS_TO_SECS 60 /* Minutes to seconds conversion factor */
#define SECS_IN_DAY 86400 /* Number of seconds in day */

/* Gets the number of exams from file */
int get_num_exams(FILE *inp);
/* Gets the times from input file */
void populate_times(FILE *inp, int exam_times[][4], int num_exams);
/* Test case: prints times */
void print_times(int exam_times[][4], int num_exams);
/* Converts hours and minutes read to seconds from midnight */
void times_to_secs(int exam_times[][4], int exams_secs[][2], int num_exams);
/* Prints seconds */
void print_secs(int exam_secs[][2], int num_exams);
/* Finds number of proctors */
int find_procs(int exam_secs[][2], int num_exams);

int
main(void)
{
  FILE *inp; /* Pointer to input file */
  
  int num_exams, /* Number of exams */
    procs; /* Number of proctors needed */

  inp = fopen(INPUT_FILE, "r"); /* Opens input file for reading */

  /* Gets number of exams from file */
  num_exams = get_num_exams(inp);

  int exam_times[num_exams][4], /* Array of exams start and stop times in
                                   hours and minutes */
    exam_secs[num_exams][2]; /* Array of exams start and stop times in seconds
                                from midnight */
  /* Gets times in hour, min format */
  populate_times(inp, exam_times, num_exams);

  //print_times(exam_times, num_exams);

  /* Converts hours, min format to seconds from midnight */
  times_to_secs(exam_times, exam_secs, num_exams);

  //print_secs(exam_secs, num_exams);

  /* Gets the number of needed proctors */
  procs = find_procs(exam_secs, num_exams);
  /* Displays the needed number of proctors */
  printf("%d\n", procs);

  return 0;
}

/* Gets number of exams from file */
int get_num_exams(FILE *inp)
{
  int num_exams;
  fscanf(inp, "%d", &num_exams);
  return num_exams;
}

/* Fills array with exam times in hour, min format */
void populate_times(FILE *inp, int exam_times[][4], int num_exams)
{
  /* Reads start and stop hour/min into 2D array */
   for(int i = 0; i < num_exams; i++)
   {
     fscanf(inp, "%d:%d %d:%d", &exam_times[i][0], &exam_times[i][1],
                                &exam_times[i][2], &exam_times[i][3]);
   }
}

/* Displays read times */
void print_times(int exam_times[][4], int num_exams)
{
  for(int i = 0; i < num_exams; i++)
  {
    printf("%d:%d %d:%d\n", exam_times[i][0], exam_times[i][1], exam_times[i][2], exam_times[i][3]);
  }
}

/* Converts hour, min array of times to seconds from midnight */
void times_to_secs(int exam_times[][4], int exam_secs[][2], int num_exams)
{
  int hours,
    mins;
  for(int i = 0; i < num_exams; i++)
  {
    hours = exam_times[i][0];
    mins = exam_times[i][1];
    hours *= HOURS_TO_MINS;
    mins *= MINS_TO_SECS;
    exam_secs[i][0] = hours + mins;
    hours = exam_times[i][2];
    mins = exam_times[i][3];
    hours *= HOURS_TO_MINS;
    mins *= MINS_TO_SECS;
    exam_secs[i][1] = hours + mins;
  }

}

/* Prints times in seconds from midnight format */
void print_secs(int exam_secs[][2], int num_exams)
{
  for(int i = 0; i < num_exams; i++)
  {
    printf("%d - %d\n", exam_secs[i][0], exam_secs[i][1]);
  }
}

/* Finds number of needed proctors */
int find_procs(int exam_secs[][2], int num_exams)
{
  int time = 0, /* Start time of day */
    end = SECS_IN_DAY, /* Number of seconds in day */
    current_procs = 0,
    max_procs = 0;
  for(; time < end; time++) /* For every second in day */
  {
    for(int i = 0; i < num_exams; i++) /* For each time in exam times */
    {
      if(time == exam_secs[i][0]) /* Add proctor if start time is hit */
        current_procs++;
      if(time == exam_secs[i][1] + 1) /* Remove proctor if exam has ended */
        current_procs--;
    }
    if(current_procs > max_procs) /* Update max number of needed procs */
      max_procs = current_procs;
  }
  return max_procs;
}
