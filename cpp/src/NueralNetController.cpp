#include "NueralNetController.h"





NueralNetController::NueralNetController(float lern) {
    lerning = lern;
    net = new NueralNet();
    layers = new vector<vector<vector<float>>>;
    weights = new vector<vector<vector<float>>>;
}

NueralNetController::NueralNetController(vector<string> stri, float lern) {
    lerning = lern;
    net = new NueralNet();
    layers = new vector<vector<vector<float>>>;
    weights = new vector<vector<vector<float>>>;
    loadNueralNetControllerState(stri);
}

NueralNetController::~NueralNetController(){
    delete layers;
    delete weights;
    delete net;
}

float NueralNetController::sq(float n) {
    return n * n;
}

void NueralNetController::reversWards() {
    for (int i = layers->size() - 2; i >= 0; i--) {
        net->revWards(layers->at(i + 1), weights->at(i), layers->at(i));
    }
}

void NueralNetController::learns(int x) {
    forWards();
    fixOutError(x);
    findError();
    backWards();
}

void NueralNetController::learns(float x[]) {
    forWards();
    fixOutError(x);
    findError();
    backWards();
}

void NueralNetController::startNueralNetController() {
    bias();
    addWeight();
    randoms();
}

void NueralNetController::addLayer(int c) {
    vector<vector<float>> *t_layers = new vector<vector<float>>();
    for (int x=0;x<c;x++){
        t_layers->push_back(vector<float>(2));
    }
    layers->push_back(*t_layers);
    delete t_layers;
}

void NueralNetController::addWeight() {
    vector<vector<float>> *t_weigth = new vector<vector<float>>();
    
    if (layers->size() > 1) {
        for (int i = 0; i < layers->size() - 1; i++) {
                for (int x=0;x<layers->at(i + 1).size();x++){
                    t_weigth->push_back(vector<float>(layers->at(i).size()));
                }
                weights->push_back(*t_weigth);
            t_weigth->clear();
        }
    }
    delete t_weigth;
}

 void NueralNetController::setData(float data[],int len_data, int c) {
    for (int e = 0; e < len_data; e++) {
        layers->at(c)[e][0] = data[e];
    }
}

 void NueralNetController::bias() {
    for (int i = 0; i < layers->size() - 1; i++) {
        layers->at(i)[layers->at(i).size() - 1][0] = 0.99F;
    }
}

 void NueralNetController::forWards() {
    for (int i = 0; i < layers->size() - 1; i++) {
        net->forWards(layers->at(i), weights->at(i), layers->at(i + 1));
    }
}

 void NueralNetController::backWards() {
    for (int i = layers->size() - 1; i >= 0; i--) {
        if (i - 1 < 0) {
            break;
        }
        net->backWards(layers->at(i - 1), weights->at(i - 1), layers->at(i), lerning);
    }
}

 float NueralNetController::getError() {
    float error = 0;
    for (int w = 0; w < layers->at(layers->size() - 1).size(); w++) {
        error += sq(abs(layers->at(layers->size() - 1)[w][1]));
    }
    return error;
}

 void NueralNetController::findError() {
    int glo = layers->size() - 2;
    while (glo > -1) {
        net->findError(layers->at(glo), weights->at(glo), layers->at(glo + 1));
        glo--;
    }
}

vector<vector<float>> NueralNetController::getLayer(int x) {
    return layers->at(x);
}

 void NueralNetController::fixOutError(int p) {
    for (int r = 0; r < layers->at(layers->size() - 1).size(); r++) {
        if (p == r) {
            layers->at(layers->size() - 1)[r][1] = 1 - layers->at(layers->size() - 1)[r][0];
        } else {
            layers->at(layers->size() - 1)[r][1] = 0 - layers->at(layers->size() - 1)[r][0];
        }
    }
}

 void NueralNetController::fixOutError(float p[]) {
    for (int r = 0; r < layers->at(layers->size() - 1).size(); r++) {
        layers->at(layers->size() - 1)[r][1] = p[r] - layers->at(layers->size() - 1)[r][0];
    }
}

 void NueralNetController::randoms() {
    for (int i = 0; i < weights->size(); i++) {
        net->randoms(weights->at(i));
    }
}

void NueralNetController::loadNueralNetControllerState(vector<string> stri) {
    stringstream strStrem;
    strStrem<<stri[0];
    while(strStrem){
        int _layer = 0;
        strStrem>>_layer;
        if(_layer!=0){
            addLayer(_layer);
        }
    }
    addWeight();
    bias();
    strStrem.clear();
// Second row is start the weight of nueralnet    
    int s = 1;
    for (int i = 0; i < weights->size(); i++) {
        for (int x = 0; x < weights->at(i)[0].size(); x++) {
                int z = 0;
                strStrem<<stri[s];
                float d = 0;
                while(strStrem >> d){
                    if(d!=0){
                        weights->at(i)[z][x] = d;
                        z++;
                    }else{
                        strStrem.clear();
                        break;
                    }
                }
                strStrem.clear();
            s++;
        }
    }
}

 vector<string> NueralNetController::saveNueralNetControllerState() {
    string builder = "";
    stringstream strStrem;
    vector<string> weigh;
    for (int i = 0; i < layers->size(); i++) {
        strStrem<<layers->at(i).size();
        strStrem<<" ";
    }
    getline(strStrem,builder);
    weigh.push_back(builder);
    builder = "";
    strStrem.clear();
    for (int i = 0; i < weights->size(); i++) {
        for (int x = 0; x < weights->at(i)[0].size(); x++) {
            for (int u = 0; u < weights->at(i).size(); u++) {
                strStrem<< weights->at(i)[u][x];
                strStrem<<" ";
            }
            strStrem<<"\n";
        }
    }
    while(strStrem){
        getline(strStrem,builder);
        weigh.push_back(builder);
        builder = "";
    }
    return weigh;
}

