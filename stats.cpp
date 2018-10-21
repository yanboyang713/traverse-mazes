/********************************
*Filename:stats.cpp		*
*Login:by932			*								
*AssignmentNo:lab4		*
*DateLastModified:6/9/2014	*							
********************************/

#include <iostream>
#include <cstring>

using namespace std;

int *resizeArray(int *source, int len);

int main ()
{

	int input;
	int size = 2;
	int *array = new int [size];
	int sum = 0;
	int count = 0;
	cout << "Enter you positive numbers, when you input -1 STOP" << endl;
	//intput
	cin >> input;
	
	while (input != -1) {
		array[count] = input;
		cin >> input;
		
		
		if (++count == size) {
			size++;
			array = resizeArray(array, size);
		}
	}
	
	
	//sort
	int temp ;
	
	for(int x = 1; x < count; x++)
	{
		for (int y = 0; y < count-x; y++)
		{
			if(array[y] > array[y + 1])
			{
				temp = array[y + 1];			
				array[y + 1] = array[y];				
				array[y] = temp;
						
			}
						
		}
	}
	
	//sum
	for (int i = 0; i < count; i++)
	{
		sum += array[i];
		
	}
	//mean
	float mean = 0.0;
	mean = static_cast<float>(sum) / static_cast<float>(count);
	cout << endl;
	cout << "Mean = " << mean << endl;
	//median
	if (count % 2 != 0)
	{
		cout << "Median = " << array[count / 2] << endl;
	}
	else
	{
		float median = 0.0;
		median = (static_cast<float>(array[count / 2 - 1])
		 + static_cast<float>(array[count / 2])) / 2.0;
		cout << "Median = " << median << endl;
	}
	delete [] array;
	
	return 0;
}

int *resizeArray(int *source, int len)
{
	int *temp = new int[len];
	memcpy(temp, source, len * sizeof(int));
	delete [] source;
	return temp;
}

