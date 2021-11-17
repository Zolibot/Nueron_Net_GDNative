#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "NueralNetFloat.h"

using namespace std;


class NueralNetController {
private:
public:
vector<vector<vector<float>>> *layers;
vector<vector<vector<float>>> *weights;
NueralNet *net;
float lerning;

NueralNetController(float lerning);

NueralNetController(vector<string> stri, float lerning);

~NueralNetController();    

float sq(float n);

void reversWards();

void learns(int x);

void learns(float x[]);

void startNueralNetController();

void addLayer(int c);

void addWeight();
    
void setData(float data[],int len_data, int c);

void bias();

void forWards();

void backWards();

float getError();

void findError();

vector<vector<float>> getLayer(int x);

void fixOutError(int p);

void fixOutError(float p[]);

void randoms();

void loadNueralNetControllerState(vector<string> stri);

vector<string> saveNueralNetControllerState();

};

