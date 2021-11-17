#include "gdexample.h"


using namespace godot;

void NueronNet::_register_methods() {
    register_method("_process", &NueronNet::_process);
    register_method("addLayer", &NueronNet::addLayer);
    register_method("startNueralNetController", &NueronNet::startNueralNetController);
    
    
    register_method("setData", &NueronNet::setData);
    register_method("learns", &NueronNet::learns);
    register_method("getError", &NueronNet::getError);
    register_method("getLayer", &NueronNet::getLayer);

    
    register_method("forWards", &NueronNet::forWards);
    register_method("saveNueralNetControllerState", &NueronNet::saveNueralNetControllerState);
    register_method("loadNueralNetControllerState", &NueronNet::loadNueralNetControllerState);
}

NueronNet::NueronNet() {
    brain = new NueralNetController(0.1F);
}

NueronNet::~NueronNet() {
    // add your cleanup here
    delete brain;
}

void NueronNet::addLayer(int c){
    brain->addLayer(c);
}

void NueronNet::startNueralNetController() {
    brain->startNueralNetController();
}

void NueronNet::setData(Array data,int len_data, int c){
    brain->setData(arrayToFloat(data),len_data, c);
}

void NueronNet::learns(Array data){
    brain->learns(arrayToFloat(data));
}

void NueronNet::forWards(){
    brain->forWards();
}

float NueronNet::getError() {
    return brain->getError();
}

Array NueronNet::getLayer(int x){
    vector<vector<float>> load = brain->getLayer(x);
    Array out;
    Array temp;
    for (int x =0;x<load.size();x++){
        for(int y=0;y<load[0].size();y++){
            temp.append(load[x][y]);
        }
        out.append(temp.duplicate());
        temp.clear();
    }
    return out;
}

Array NueronNet::saveNueralNetControllerState(){
    vector<string> save = brain->saveNueralNetControllerState();
    Array out;
    for(int x =0;x<save.size();x++){   
        out.append(save.at(x).c_str());
    }
    return out;
}

void NueronNet::loadNueralNetControllerState(PoolStringArray stri){
    vector<string> load;
    for(int x =0;x<stri.size();x++){
        load.push_back(string(stri[x].ascii().get_data()));
    }
    brain->loadNueralNetControllerState(load);
}

float* NueronNet::arrayToFloat(Array data){
    float *a = new float[data.size()];
    for(int x=0;x<data.size();x++){
        a[x] = data[x];
    }
    return a;
}

void NueronNet::_init() {
    // initialize any variables here
}

void NueronNet::_process(float delta) {
} 


