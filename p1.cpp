#include<iostream>
#include<fstream>
#include<map>
#include<assert.h>
#include<string>
using namespace std;
#define MAX_LENGTH 1024
struct inputDetails
{
	int branchAddress =0;
	string direction = "";
	int destinationAddress = 0;
};
struct localPredictionDetails
{
	int index = 0;
	int oldValue =0;
	int newValue =0;
	string prediction = "n";
};
struct globalPredictionDetails
{
	string index = "nnnnnn";
	int oldValue =0;
	int newValue =0;
	string prediction = "n";
};
struct selectorDetails
{
	int index = 0;
	int oldValue =0;
	int newValue =0;
	string finalPrediction = "n";
	string prediction = "n";
};
/*
 Function Declarations
*/
int readFromFile(map<int,string>&);
int inputDetailsExtraction(const map<int,string>,map<int,inputDetails>&);	
int	localPrediction(const map<int,inputDetails>,map<int,localPredictionDetails>&);
int	globalPrediction(const map<int,inputDetails>,map<int,globalPredictionDetails>&);
int	selector(const map<int,inputDetails>,const map<int,globalPredictionDetails>,const map<int,localPredictionDetails>,map<int,selectorDetails>&);
int	appendAndWriteToFile(const map<int,inputDetails>,const map<int,globalPredictionDetails>,const map<int,localPredictionDetails>,const map<int,selectorDetails>);
/*
	Author: Aditya Manjrekar
*/
int main()
{
	int flag = 0;
	map<int,string> input;
	map<int,inputDetails> inputDetailsMap;
	map<int,localPredictionDetails> localPredictionMap;
	map<int,globalPredictionDetails> globalPredictionMap;
	map<int,selectorDetails> selectorDetailsMap;
	// Read the data from the file into an object
	flag = readFromFile(input);
	assert(flag==1);
	//Store the Input String  in the Data Struct
	flag = inputDetailsExtraction(input,inputDetailsMap);	
	assert(flag==1);
	//lOCAL PREDICTION
	flag =	localPrediction(inputDetailsMap,localPredictionMap);
	assert(flag==1);
	//Global Prediction
	flag =	globalPrediction(inputDetailsMap,globalPredictionMap);
	assert(flag==1);
	//Selector
	flag =	selector(inputDetailsMap,globalPredictionMap,localPredictionMap,selectorDetailsMap);
	assert(flag==1);
	//add the prediction details in the File
	flag =	appendAndWriteToFile(inputDetailsMap,globalPredictionMap,localPredictionMap,selectorDetailsMap);
	assert(flag==1);
	return 0;
}
/*
	Author: ADitya Manjrekar
	Description: 	Reading line by line from the ext file and inserting the lines in the input map
*/
int readFromFile(map<int,string> &input)
{
	int inputCounter = 0;
	string line = "";
	while(cin>>line)
	{
		input.insert(make_pair(inputCounter,line));
		inputCounter++;
	}
	if(inputCounter<0)
		return 0;
	else 
		return 1;
}
/*
	Author: ADitya Manjrekar
	Description: 	extracting the brach address , direction and the destination address	and storing it in the inputDetails struct.
*/
int inputDetailsExtraction(const map<int,string> input,map<int,inputDetails> &inputDetailsMap)
{
	int totalNumberOfInputs = input.size();
	int counter =0;
	while (counter<totalNumberOfInputs)
	{
		inputDetails temp;
		string tempInput = "";
		tempInput = input.at(counter);
		temp.branchAddress = int(tempInput.at(0))-48;
		temp.direction = tempInput.at(1);
		temp.destinationAddress = int(tempInput.at(2))-48;
		inputDetailsMap.insert(make_pair(counter,temp));	
		counter++;
	}
	if(counter<0)
		return 0;
	else 
		return 1;
}
/*
	Author: Aditya Manjrekar
	Description: localPredictor based on input
*/
int	localPrediction(const map<int,inputDetails> inputDetailsMap,map<int,localPredictionDetails> &localPredictionMap)
{
	int totalNumberOfInputs = inputDetailsMap.size();
	int counter =0;
	while (counter<totalNumberOfInputs)
	{
		inputDetails temp;
		localPredictionDetails templocalPredictionDetails;
		temp = inputDetailsMap.at(counter);
		templocalPredictionDetails.index = temp.branchAddress;
		// set old Value
		{
			int sizelocalPredictionMap = localPredictionMap.size();
			if((sizelocalPredictionMap)!=0)
			{
				templocalPredictionDetails.oldValue = 0;
				for(int i=sizelocalPredictionMap-1;i>-1;i--)
				{
					localPredictionDetails temp1 = localPredictionMap.at(i);
					if(temp1.index == temp.branchAddress )
						{
							templocalPredictionDetails.oldValue = temp1.newValue;
							break;
						}
				}
			}
		}
		//New Value
		{
			if(temp.direction == "n")
			{
				templocalPredictionDetails.newValue = templocalPredictionDetails.oldValue-1;
			}
			else if(temp.direction == "t")
			{
				templocalPredictionDetails.newValue = templocalPredictionDetails.oldValue+1;
			}
			if(templocalPredictionDetails.newValue<0)
				templocalPredictionDetails.newValue=0;
			if(templocalPredictionDetails.newValue>3)
				templocalPredictionDetails.newValue=3;
		}
		//Prediction
		{
			if(templocalPredictionDetails.oldValue==0 )
			{
				templocalPredictionDetails.prediction = "n";
			}
			else if(templocalPredictionDetails.oldValue == 1)
			{
				templocalPredictionDetails.prediction = "n";
			}
			else if(templocalPredictionDetails.oldValue==2)
			{
				templocalPredictionDetails.prediction = "t";
			}
			else if( templocalPredictionDetails.oldValue == 3)
			{
				templocalPredictionDetails.prediction = "t";
			}
		}
		localPredictionMap.insert(make_pair(counter,templocalPredictionDetails));			
		counter++;
	}
	if(counter<0)
		return 0;
	else 
		return 1;
}
/*
	Author: Aditya Manjrekar
	Description: localPredictor based on input
*/
int	globalPrediction(const map<int,inputDetails> inputDetailsMap,map<int,globalPredictionDetails> &globalPredictionMap)
{
	int totalNumberOfInputs = inputDetailsMap.size();
	int counter =0;
	while (counter<totalNumberOfInputs)
	{
		inputDetails temp;
		globalPredictionDetails tempGlobalPredictionDetails;
		temp = inputDetailsMap.at(counter);
		int sizeGlobalPredictionMap = globalPredictionMap.size();
		if(counter>0)
		{
			string tempPrediction = temp.direction;
			string tempPreviousDirection = inputDetailsMap.at(counter-1).direction;
			string previousIndex = globalPredictionMap.at(counter-1).index;
			{
				//set Index
				tempGlobalPredictionDetails.index="";
				tempGlobalPredictionDetails.index.append(previousIndex);
				tempGlobalPredictionDetails.index.append(tempPreviousDirection);
				tempGlobalPredictionDetails.index.erase(0,1);
			}
					// set old Value
		{
			if(sizeGlobalPredictionMap!=0)
			{
				tempGlobalPredictionDetails.oldValue = 0;
				for(int i=sizeGlobalPredictionMap-1;i>-1;i--)
				{
					globalPredictionDetails temp = globalPredictionMap.at(i);
					if(temp.index == tempGlobalPredictionDetails.index)
						{
							tempGlobalPredictionDetails.oldValue = temp.newValue;
							break;
						}
				}
			}
		}
		//New Value
		{
			if(temp.direction == "n")
			{
				tempGlobalPredictionDetails.newValue = tempGlobalPredictionDetails.oldValue-1;

			}
			else if(temp.direction == "t")
			{
				tempGlobalPredictionDetails.newValue = tempGlobalPredictionDetails.oldValue+1;
			}
			if(tempGlobalPredictionDetails.newValue<0)
				tempGlobalPredictionDetails.newValue=0;
			if(tempGlobalPredictionDetails.newValue>3)
				tempGlobalPredictionDetails.newValue=3;
		}
			//Prediction
		{
			if(tempGlobalPredictionDetails.oldValue==0 )
			{
				tempGlobalPredictionDetails.prediction = "n";
			}
			else if(tempGlobalPredictionDetails.oldValue == 1)
			{
				tempGlobalPredictionDetails.prediction = "n";
			}
			else if(tempGlobalPredictionDetails.oldValue==2)
			{
				tempGlobalPredictionDetails.prediction = "t";
			}
			else if( tempGlobalPredictionDetails.oldValue == 3)
			{
				tempGlobalPredictionDetails.prediction = "t";
			}
		}
		}
		globalPredictionMap.insert(make_pair(counter,tempGlobalPredictionDetails));			
		counter++;
	}
	if(counter<0)
		return 0;
	else 
		return 1;
}
/*
	Author: Aditya Manjrekar
	Descriotion: Selector
*/
int	selector(const map<int,inputDetails> inputDetailsMap,const map<int,globalPredictionDetails> globalPredictionDetailsMap,const map<int,localPredictionDetails> localPredictionDetailsMap,map<int,selectorDetails>&selectorDetailsMap)
{
	int totalNumberOfInputs = inputDetailsMap.size();
	int counter =0;
	while (counter<totalNumberOfInputs)
	{
		inputDetails temp;
		globalPredictionDetails tempGlobalPredictionDetails;
		localPredictionDetails tempLocalPredictionDetails;
		selectorDetails tempSelectorDetails;
		temp = inputDetailsMap.at(counter);
		tempLocalPredictionDetails = localPredictionDetailsMap.at(counter);
		tempGlobalPredictionDetails = globalPredictionDetailsMap.at(counter);
		tempSelectorDetails.index = tempLocalPredictionDetails.index;
		int selectorDetailsMapSize = selectorDetailsMap.size();
		{
			//Old counter value
			if(selectorDetailsMapSize!=0)
			{
				tempSelectorDetails.oldValue = 0;
				for(int i=selectorDetailsMapSize-1;i>-1;i--)
				{
					selectorDetails temp = selectorDetailsMap.at(i);
					if(temp.index == tempLocalPredictionDetails.index)
						{
							tempSelectorDetails.oldValue = temp.newValue;
							break;
						}
				}
			}
		}
		string actualPrediction = temp.direction;
		string result = "";
		{
			if((tempLocalPredictionDetails.prediction == actualPrediction) && (tempGlobalPredictionDetails.prediction == actualPrediction))			
			{
				result = "d";
			}
			else if((tempLocalPredictionDetails.prediction != actualPrediction) && (tempGlobalPredictionDetails.prediction == actualPrediction))
			{
				result = "g";
			}
			else if((tempLocalPredictionDetails.prediction == actualPrediction) && (tempGlobalPredictionDetails.prediction != actualPrediction))
			{
				result = "l";
			}
			else if((tempLocalPredictionDetails.prediction != actualPrediction) && (tempGlobalPredictionDetails.prediction != actualPrediction))
			{
				result = "s";
			}
		}
		{
			//Set Prediction
			if(tempSelectorDetails.oldValue==0)
			{
				tempSelectorDetails.prediction = "l";
				tempSelectorDetails.finalPrediction = tempLocalPredictionDetails.prediction;
			}
			else if(tempSelectorDetails.oldValue==1)
			{
				tempSelectorDetails.prediction = "l";
				tempSelectorDetails.finalPrediction = tempLocalPredictionDetails.prediction;
			} 
			else if(tempSelectorDetails.oldValue==2)
			{
				tempSelectorDetails.prediction = "g";
				tempSelectorDetails.finalPrediction = tempGlobalPredictionDetails.prediction;
			}
			else if(tempSelectorDetails.oldValue==3)
			{
				tempSelectorDetails.prediction = "g";
				tempSelectorDetails.finalPrediction = tempGlobalPredictionDetails.prediction;
			}
		}		
							
		{
			//Set New Value
			if(result=="g")
			{
				tempSelectorDetails.newValue = tempSelectorDetails.oldValue+1;
				if(tempSelectorDetails.newValue>3)
					tempSelectorDetails.newValue = 3;
			}
			else if(result=="l")
			{
				tempSelectorDetails.newValue = tempSelectorDetails.oldValue-1;
				if(tempSelectorDetails.newValue<0)
					tempSelectorDetails.newValue = 0;
			}
			else
			{
				tempSelectorDetails.newValue = tempSelectorDetails.oldValue;
			}
		}			
		selectorDetailsMap.insert(make_pair(counter,tempSelectorDetails));			
		counter++;
	}
	if(counter<0)
		return 0;
	else 
		return 1;
}

/*
	Author: Aditya Manjrekar
	Description:	Append The results and store it in the file
*/
int	appendAndWriteToFile(const map<int,inputDetails> inputDetailsMap,const map<int,globalPredictionDetails> globalPredictionDetailsMap,const map<int,localPredictionDetails> localPredictionDetailsMap,const map<int,selectorDetails> selectorDetailsMap)
{
	int localCorrect=0,globalCorrect=0,tournamentAcc=0;
	int inputCounter = 0;
	int flag = 1;
	int totalNumberOfglobalPredictionDetails = globalPredictionDetailsMap.size();
	int counter =0;
	while (counter<totalNumberOfglobalPredictionDetails)
	{
		localPredictionDetails tempLocalPredictionDetails = localPredictionDetailsMap.at(counter);
		globalPredictionDetails tempGlobalPredictionDetails = globalPredictionDetailsMap.at(counter);
		selectorDetails tempSelectorDetails = selectorDetailsMap.at(counter);
		inputDetails tempInputDetails = inputDetailsMap.at(counter);
		string temp = "";
		temp.append(to_string(tempLocalPredictionDetails.index));
		temp.append(tempLocalPredictionDetails.prediction);
		temp.append(tempGlobalPredictionDetails.prediction);
		temp.append(tempSelectorDetails.prediction);
		temp.append(tempSelectorDetails.finalPrediction);
		temp.append(tempInputDetails.direction);
		temp.append("\n");
		if(temp.at(1) == temp.at(5))
		{
			localCorrect++;
		}
		if(temp.at(2) == temp.at(5))
		{
			globalCorrect++;
		}
		if(temp.at(4)==temp.at(5))
		{
			tournamentAcc++;
		}
		cout << temp;
		counter++;
	}
	if(counter<0)
		return 0;
	else 
		return 1;
}

