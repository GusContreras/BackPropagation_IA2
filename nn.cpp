#include "nn.h"
#include <iostream>


NN::NN()
{
    //ctor
}

NN::NN(const std::vector<int>& nodes)
{
    CreateRed(nodes);
}

std::vector<double> NN::FeedForward(std::vector<double>data)
{

    if(isEmpty()){
        throw "NN: Error Nueral Net is empty FeedForward()";
    }

    if(data.size() != Size){
        throw "NN: Error Input data not correct format";
    }

    if(!functionZ){
        throw "null ptr";
    }

    std::vector<double> temp;
    data.push_back(1.0);

    try{

        for(unsigned int i = 0; i < layers.size(); i++){

            for(unsigned int j = 0; j < layers[i].size(); j++){

                temp.push_back(layers[i].at(j).activate(data,functionZ));

            }

            data = temp;
            data.push_back(1.0); //adds input for bias
            temp.clear();

        }

        data.pop_back(); //removes -1 input for bias
        return data;

    }catch(const char *t){
        throw t;
    }

}


void NN::Delta(const std::vector<double>& data,const std::vector<double>& test,const double& factor){

    std::vector<double> error;
    std::vector<std::vector<double>> temp;
    std::vector<double> delta;

    //error vector
    if(data.size() != test.size()){
        throw "Error bastardo";
    }

    for(unsigned int i = 0; i < data.size(); i++){
        error.push_back(test[i] - data[i]);
    }

    for(int i = layers.size()-1; i >= 0; i--){

        for(unsigned int j = 0; j < layers[i].size(); j++){

            if(!error.empty()){
                temp.push_back(layers[i].at(j).delta(error[j],0,factor));

            }else{

                temp.push_back(layers[i].at(j).delta(0,delta[j],factor));

            }

        }

        if(!error.empty()){
            error.clear();
        }

        delta.clear(); // calculating deltas
        for(int t = 0; t < temp[0].size(); t++){
            double count = 0;
            for(unsigned int k = 0; k < temp.size(); k++){

                count += temp[k].at(t);

            }
            delta.push_back(count);
        }
        temp.clear();

    }


}


void NN::trainNetwork(const std::vector<std::vector<double>>& data,std::vector<std::vector<double>>& test,const int& N, const double& factor){

    for(int i = 0; i < N; i++){

        for(unsigned int j = 0; j < data.size(); j++){
            Delta(FeedForward(data[j]),test[j],factor);
        }

    }

}

void NN::setFunction(double(* point)(double i))
{
    if(point == nullptr){
        throw "NN: Error Invalid function Pointer setFunction()";
    }

    functionZ = point;
}

void NN::CreateRed(const std::vector<int>&nodes){

    layers.clear();
    //int count = 1;
    Size = nodes[0];


    std::random_device count;
    std::vector<Neuron> temp;

    //start at 1 because first layer is output.
    for(unsigned int i = 1; i < nodes.size(); i++){

        temp.clear();
        for(int j = 0; j < nodes[i]; j++){
            //Create number of synaptic weights based on previous layer..
            temp.push_back(Neuron(nodes[i-1],&count));
        }

        layers.push_back(temp);

    }
}

void NN::Clear(){
    layers.clear();
}

bool NN::isEmpty(){
    if(layers.size() < 1 ){
        return true;
    }
    return false;
}

void NN::Print(){

        if(isEmpty()){
            throw "NN: Error Neural Net is empty Print()";
        }

        try{

        for(unsigned int i = 0; i < layers.size(); i++){

            std::cout << "Capa - " << i << std::endl << std::endl;
            for(unsigned int j = 0; j < layers[i].size(); j++){

                std::cout << "Neurona " << j << layers[i].at(j) << std::endl;

            }


        }

    }catch(const char *t){
        throw t;
    }

}

int NN::DataInputSize(){
    if(isEmpty()){
        throw "NN: Error Neural Net is Empty DataInputSize()";
    }
    return layers[0].at(0).weights.size() - 1;

}
