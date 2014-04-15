#include "network_layer.h"



NetworkLayer ::  NetworkLayer(int nNeurons , int id){
			layerId = id;
			N = nNeurons;
			for(int i =0i<nNeurons;i++){
                Neuron neuron();
                Neurons.push_back(neuron); 
            }

}

void NetworkLayer :: updateLayer() {
	for(int i=0; i<Neurons.size(); i++) {
		Neurons[i].collectInputs();
	}
}
Vec  NetworkLayer:: getOutput(){
    Vec output; 
    
    for(int i=0;i<Neurons.size();i++){
        output.push_back(Neurons[i].getOutput());       
    }
    return output;

void NetworkLayer :: updateLayer(Vec In) {
	collectInputs(In);
}

NetworkLayer :: void backPropagate(){
	
		for(int i=0;i<N;i++){
			Neurons[i].collectInputs();
			Neurons[i].updateDel();
		}	
}



NetworkLayer :: void backPropagate(Vec t){
	
		for(int i=0;i<N;i++){
			Neurons[i].collectInputs();
			Neurons[i].updateDel(t);
		}	
}


NetworkLayer :: void updateWeights(){   //of input edges
	
	for(int i=0;i<N;i++){
			for(int j=0;j<Neurons[i].inputEdges.size();i++)
			   Neurons[i].inputEdges[j].setWeight(Neurons[i].inputEdges[j].getWeight() +  
			                                       (NETA *
			                                       Neurons[i].inputEdges[j].getStart().getDel() *
			                                       Neurons[i].getOutput()));	
		}	
	
}
