/*My raspberry study: 1*/
#include <wiringPi.h>
#include <iostream>
#include <time.h>

using namespace std;

#define	Trig 27
#define Echo 29

// call this function to start a nanosecond-resolution timer
struct timespec timer_start() {
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time) {
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}


int main(void)
{
	if (-1 == wiringPiSetup())
		cout << "Error! " << endl;

	pinMode(Trig, OUTPUT);
	digitalWrite(Trig, LOW);
	delay(30);
	pinMode(Echo, OUTPUT);
	digitalWrite(Echo, LOW);
	delay(100);

	cout << "Test start: " << endl;
	digitalWrite(Trig, HIGH);
	delayMicroseconds(20);

	digitalWrite(Trig, LOW);
	pinMode(Echo, INPUT);
	pullUpDnControl(Echo, PUD_UP);

	while (digitalRead(Echo) < 1)
		;
	//start = clock();
	struct timespec vartime = timer_start();
	while (digitalRead(Echo) == 1)
		;
	//stop = clock();
	long time_elapsed_nanos = timer_end(vartime);

	double distance = (double)(time_elapsed_nanos / 1000000 * 170) / 1000;
	cout << "Time: " << time_elapsed_nanos << " ns" << endl;
	cout << "Distance: " << distance << " m" << endl;


	return 0;
}
