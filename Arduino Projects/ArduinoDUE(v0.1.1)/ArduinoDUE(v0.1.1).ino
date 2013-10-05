#include <time.h>


int samples;
int cycles;
float sampleAverage;
float cycleAverage;
int desiredCycleTimeSeconds;

int lastCycle;

String names[8] = {"Brake Position", "Throttle Position", "Temperature", "Oil Pressure", "Fuel Pressure", "Fuel Level", "Speed", "RPM"};
void setup(){
	Serial.begin(9600);	
	printHeaderLine();
	
}
void loop(){
	//	
	float cycleAverage;

	long start = millis();
	for(int i = 0; i < 8; i++)
	{
		Serial.print(printData(i, names[i]));				
		Serial.print("\t");
	}

	Serial.println();
	delay(10);
	long end = millis();
	lastCycle = (end - start);

	cycles++;

	updateCycleAverageTime(lastCycle);
	printCycleStats(longSampleName, longSample);
}	
void printHeaderLine()
{
	for (int i = 0; i < 8; i++)
	{
		Serial.print(names[i]);
		Serial.print("\t");
	}

	Serial.println();
}
int printData(int socket, String name)
{	
	return(analogRead(11 - socket));	
}
void printCycleStats(String longSample, long longSampleTime)
{
	long start = millis();
	Serial.print("Samples:\t");
	Serial.println(samples);	
	Serial.print("Cycles:\t");
	Serial.println(cycles);	
	Serial.print("Time last cycle:\t");
	Serial.print(lastCycle);
	Serial.println("ms");	
	Serial.print("Average cycle time:\t");
	Serial.print(float(cycleAverage));
	Serial.println("ms");
	Serial.print("Average SampleTime:\t");
	Serial.print(float(sampleAverage));
	Serial.println("ms");
	Serial.print("Long Sample:\t");
	Serial.print(longSample);
	Serial.print("\tTime:\t");
	Serial.print(longSampleTime);
	Serial.println("ms");
	long end = millis();
	Serial.print("Time printing data:\t");
	long time = end - start;
	Serial.print(time);
	Serial.println("ms");
}
float updateSampleAverageTime(long sampleTime)
{
	long totalTime = (sampleAverage * (samples - 1)) + sampleTime;
	return float(totalTime / samples);
}
float updateCycleAverageTime(long cycleTime)
{
	long totalTime = (cycleAverage * (cycles - 1)) + cycleTime;
	return float(totalTime / cycles);
}