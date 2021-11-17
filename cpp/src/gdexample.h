#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H
#include <iostream>
#include <sstream>


#include <OS.hpp>
#include <Godot.hpp>
#include <Node.hpp>
#include <Engine.hpp>
#include "NueralNetController.h"

#include <String.hpp>
#include <Array.hpp>
#include <PoolArrays.hpp>
#include <Variant.hpp>


namespace godot {

class NueronNet : public Node {
    GODOT_CLASS(NueronNet, Node)

private:
    
public:
    NueralNetController *brain;
    

    static void _register_methods();
    NueronNet();
    ~NueronNet();
    
    void startNueralNetController() ;
    void setData(Array data,int len_data, int c);
    
    void addLayer(int c);
    void learns(Array x);
    void forWards();
    float getError();
    Array getLayer(int x);
    
    float* arrayToFloat(Array data);
    Array saveNueralNetControllerState();
    void loadNueralNetControllerState(PoolStringArray stri) ;
    
    void _init(); 
    void _process(float delta);
};

}

#endif 
