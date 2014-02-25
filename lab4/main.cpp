#include "neural_network.h"
#include <vector>
#include <cstdlib>
#include <fstream>
string OP;
double NETA;
double MOMENTUM_FACTOR;
//char *OP = malloc(10*sizeof(char));
void  genTT(string op	,vector<Vec> &reti , vector<Vec> &reto);
void getTruthTableLsd(int n, vector< Vec > &input, vector< Vec > &output);
void printTT(vector <Vec> , vector <Vec>);
int getFilesize() ;
vector<Vec> getTrainingInput(int nfold, int partForValidation) ;
vector<Vec> crossValinput(int nfold, int partForValidation);
vector<Vec> crossValOutput(int nfold, int partForValidation);
vector<Vec> getTrainingOutput(int nfold, int partForValidation);



using namespace std;

int getInputSize(string op) {
	if(op.compare("XOR") == 0) return 2;
	else if(op.compare("NAND") == 0) return 2;
	else if(op.compare("NOR") == 0) return 2;
	else if(op.compare("PALINDROME") == 0) return 5;
	else if(op.compare("Majority") == 0) return 5;
	else if(op.compare("Parity") == 0) return 6;
	else if(op.compare("LSD") == 0) return 7;
	else return -1;
}

int main(){
  
    NETA =0.2;
    printf("Enter Learning rate \n");
    scanf("%lf",&NETA);
    
    printf("Enter Momentum \n");
    scanf("%lf",&MOMENTUM_FACTOR );
    
    cout<<"Give the OPERATOR to train on:"<<endl;
    cin>>OP;
    //cout<<OP<<endl;		
    	
    Vec in2;	
    int vsize;	
    if(OP!="Tweet" && OP != "Iris"){
    	vsize = getInputSize(OP);	
	in2.resize(vsize);
	}
    
    int nlayers;
		
    cout<<"Enter number of layers in the Neural Network:"<<endl;
    cin>>nlayers;		
    NeuralNetwork nn(nlayers,1);
    
    if(OP!="Tweet" && OP != "Iris"){
    	nn.addInputLayer(vsize);
	}
    //nn.addHiddenLayer(7);
    
    int hl=1;
    while(hl<=nlayers-2) {	//No. of hidden layers is 2 less than total
	 int nneuron; 	
	 cout<<"Enter number of neurons in hidden layer "<<hl<<" :"<<endl;
	 cin>>nneuron;
   	 nn.addHiddenLayer(nneuron);
	 hl++;
    }	

   // nn.addOutputLayer(1);
    
   // nn.generateEdges();
  //  printf("************\n");
    vector< Vec> ins;
    vector< Vec > outs;
    if(OP == "LSD") {
	nn.generateEdges();
        getTruthTableLsd(1,ins,outs);
    	nn.addAllTrainData(ins, outs);
    }
    
    
    else if(OP == "Tweet" || OP == "Iris") {
		cout<<"In1----------"<<endl;
		
		vector<Vec> inputVec = getTrainingInput(5 , 5);
    	
    	
    	vector<Vec> outputVec = getTrainingOutput(5, 5); 
    	vector<Vec> validatingInputs = crossValinput(5, 5);
    	vector<Vec> validatingOutputs = crossValOutput(5, 5);

		assert(validatingInputs.size() == validatingOutputs.size());
		printf("Sizes are %d %d %d %d \n", validatingInputs.size() , validatingOutputs.size() , inputVec.size() , outputVec.size()); 
		
    	
    	printf("Sizes are %d %d \n" , inputVec[0].size() , inputVec[0].size());
    	
    	
    		
		for(int nhj=0;nhj<inputVec.size();nhj++){
			printVec(outputVec[nhj]);
			cout<<" : ";
			printVec(inputVec[nhj]);
		}
    	
    	
    	
		Vec OutputResult;

		
		
		nn.addInputLayer(inputVec[0].size());
		nn.addOutputLayer(2);
    
		cout<<"Input Layer added!"<<endl;
		nn.generateEdges();
		cout<<"Edges Generated!"<<endl;
    	nn.addAllTrainData(inputVec, outputVec);
        printf("Training Done!\n");
		printf("Generating validation inputs \n");
		
		
		
		
		int NumberSucceeded = 0;
		
		
		for(int nhj=0;nhj<inputVec.size();nhj++){
			OutputResult = nn.getOutput(inputVec[nhj]);
			cout<<"\n---------------------------"<<nhj<<"    "<<OutputResult.size()<<endl;
			cout<<"Expected: ";
			printVec(outputVec[nhj]);
			cout<<"\n Result : ";
			printVec(OutputResult);
			NumberSucceeded += equal(OutputResult , outputVec[nhj]);
		}
		
		
		cout<<"Accuracy  on Trained % is : "<<(NumberSucceeded * 100)/inputVec.size()<<endl;
		
		
		
		NumberSucceeded = 0;
		
		for(int nhj=0;nhj<validatingInputs.size();nhj++){
			OutputResult = nn.getOutput(validatingInputs[nhj]);
			cout<<"\n---------------------------"<<nhj<<"    "<<OutputResult.size()<<endl;
			cout<<"Expected: ";
			printVec(validatingOutputs[nhj]);
			cout<<"\n Result : ";
			printVec(OutputResult);
			NumberSucceeded += equal(OutputResult , validatingOutputs[nhj]);
		}
		
		
		cout<<"Accuracy  % is : "<<(NumberSucceeded * 100)/validatingInputs.size()<<endl;
		return 0;
    }
    
    else if(OP == "IRIS") {
		
    
	}
	
    else {
		nn.addOutputLayer(1);
		nn.generateEdges();   
       	genTT(OP,ins,outs);
    	nn.addAllTrainData(ins, outs);
	}	

    //printTT(ins,outs);
//    nn.addAllTrainData(ins, outs);
    int rem;
   
   
    while(1){
        printf("Enter inputs \n");
        for(rem=0; rem<vsize; rem++) {
            scanf("%lf",&in2[rem]);
        }
    nn.getOutput(in2);
    nn.print();
    }
    
    return 1;
}
