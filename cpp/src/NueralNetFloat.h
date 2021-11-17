#pragma once
#include <random>
#include <cmath>
using namespace std;

class NueralNet{
private:
public:
random_device r;
//Интервал инициализации начального состояния весов связей 
float f_range = 0.5F;   
//Епсилон 
const float E = 2.718281828459045F;
    
NueralNet();
    
float random(float low, float high) ;

//Прямое прохождение нейро сети
void forWards(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL) ;

//Обратное прохождение тестовая функция
void revWards(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL) ;

//Рандомные веса вызывають при старте нейро сети один раз
void randoms(vector<vector<float>> &we) ;

//Ошибка для каждого нейрона
void findError(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL) ;

//Коректировка связий
void backWards(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL, float &k) ;

//Ошибка нейрона внейшнего слоя
void fixOutError(float IDL[], vector<vector<float>> &ouL) ;

//Сигмойда
float sigmoid(float &x) ;

};
