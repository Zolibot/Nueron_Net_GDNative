#include "NueralNetFloat.h"



NueralNet::NueralNet(){
    
    
}


float NueralNet::random(float low, float high) {
    default_random_engine e1(r());
    uniform_real_distribution<float> float_dist(low, high);
    //float mean = float_dist(e1);
        return float_dist(e1);;
}

//Прямое прохождение нейро сети
void NueralNet::forWards(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL) {
    for (int i = 0; i < weN.size(); i++) {
        ouL[i][0] = (float) 0.0;
        for (int u = 0; u < weN[0].size(); u++) {
            ouL[i][0] += inL[u][0] * weN[i][u];
        }
        ouL[i][0] = sigmoid(ouL[i][0]);
    }
}

//Обратное прохождение тестовая функция
void NueralNet::revWards(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL) {
    for (int i = 0; i < weN[0].size(); i++) {
        ouL[i][0] = 0.0F;
        for (int u = 0; u < weN.size(); u++) {
            ouL[i][0] += inL[u][0] * weN[u][i];
        }
        ouL[i][0] = sigmoid(ouL[i][0]);
    }
}

//Рандомные веса вызывають при старте нейро сети один раз
void NueralNet::randoms(vector<vector<float>> &we) {
    for (int i = 0; i < we.size(); i++) {
        for (int r = 0; r < we[0].size(); r++) {
            we[i][r] = random(-f_range, f_range);
        }
    }
}

//Ошибка для каждого нейрона
void NueralNet::findError(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL) {
    for (int i = 0; i < weN[0].size() - 1; i++) {
        inL[i][1] = 0.0f;
        for (int u = 0; u < weN.size(); u++) {
            inL[i][1] += weN[u][i] * ouL[u][1];
        }
    }
}

//Коректировка связий
void NueralNet::backWards(vector<vector<float>> &inL, vector<vector<float>> &weN, vector<vector<float>> &ouL, float &k) {
    for (int i = 0; i < weN.size(); i++) {
        for (int u = 0; u < weN[0].size(); u++) {
            weN[i][u] += k * ouL[i][1] * ouL[i][0] * (1 - ouL[i][0]) * inL[u][0];
        }
    }
}

//Ошибка нейрона внейшнего слоя
void NueralNet::fixOutError(float IDL[], vector<vector<float>> &ouL) {
    for (int i = 0; i < sizeof(*IDL)/sizeof(float); i++) {
        ouL[i][1] = IDL[i] - ouL[i][0];
    }
}

//Сигмойда
float NueralNet::sigmoid(float &x) {
    float y = (float) (1 / (1 + pow((float) E, -x)));
    return y;
}



