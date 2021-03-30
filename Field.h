#ifndef _FIELD_INCLUDED_
#define _FIELD_INCLUDED_

#include <iostream>
#include "ProgramParameters.h"
#define FieldDouble Node<double> , double

template <typename T>
class Node {
    public :
        T val;

        Node(T val) {
            this->val = val;
        }
        Node() {
            this->val = 0;
        }
};

template <typename NodeT , typename T >
class FIELD {
    // A 2D FIELD IN CORDINATE x,y HANDLER

    /*
        Standared Cordinates Convention

        y = y_max -1 |-----------------|
                     |-----------------|
                     |-----------------|
        y = y        |-----------------|
                     |-----------------|
                     |-----------------|
        y = 0        |-----------------|
                     x = 0     x=x     x = x_max - 1
    */
    protected : 
        int xSize ;
        int ySize ;
        NodeT ** Field;

    public :
        FIELD(const int xSize,const int ySize) {
            this->xSize = xSize;
            this->ySize = ySize;
            this->Field = new NodeT*[xSize];
            for (int i = 0 ; i < xSize ; i++) {
                this->Field[i] = new NodeT[ySize];
            }

        }

        FIELD(const FIELD<NodeT,T> & other ) {
            this->xSize = other.xSize;
            this->ySize = other.ySize;
            this->Field = new NodeT*[xSize];

            for (int i = 0 ; i < xSize ; i++) {
                this->Field[i] = new NodeT[ySize];
            }
            for (int i = 0 ; i < other.xSize ; i++) {
                for (int j = 0 ; j < other.ySize ; j++) {
                    NodeT & tmp = other.Field[i][j];
                    set(i , j , tmp.val);
                }
            }
        }

        ~FIELD() {
            for (int i = 0 ; i < this->xSize ; i++) {
                delete[] this->Field[i];
            }
            delete[] this->Field;
        }


        void printField() {
            std::cout << "Size : " << "(x,y) = " << '(' << this->xSize << ',' << this->ySize << ')' << '\n';
            for (int y = this->ySize - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < this->xSize ; x++) {
                    NodeT tmp = get(x,y);
                    std::cout << tmp.val << ' ';
                }
                std::cout << '\n';
            }
        }

        void set(int x , int y , T value) {
            NodeT & tmp = get(x,y);
            tmp.val = value;
        } 

        NodeT& get(int x , int y) {
            return (this->Field)[x][y];
        }

        int getXSize() {
            return this->xSize;
        }

        int getYSize() {
            return this->ySize;
        }

        void saveField() {
            // TODO SAVE FIELD TO FILES
        }

        void readField() {
            // TODO READ FIELD FROM FILES
        }

};

class VelocityField {
    public :
        FIELD< FieldDouble > * u;
        FIELD< FieldDouble > * v;

        VelocityField() {
            this->u = nullptr;
            this->v = nullptr;
            return;
        }

        VelocityField(int xSize , int ySize) {
            this->u = new FIELD<FieldDouble>(xSize , ySize);
            this->v = new FIELD<FieldDouble>(xSize , ySize);
        }
        
        VelocityField(const VelocityField & other) {
            u = new FIELD< FieldDouble > (*other.u);
            v = new FIELD< FieldDouble > (*other.v);
        }

        VelocityField& operator=(VelocityField other) {
            using std::swap;
            swap(this->u , other.u);
            swap(this->v , other.v);

            return *this;
        }
        ~VelocityField() {
            delete this->u;
            delete this->v;
        }
};

class PressureField {
    public :
        FIELD< FieldDouble > * p;

        PressureField() {
            this->p = nullptr;
        }
        PressureField(int xSize , int ySize) {
            this->p = new FIELD<FieldDouble>(xSize , ySize);
        }
        PressureField(const PressureField & other) {
            this->p = new FIELD< FieldDouble > (*other.p);
        }

        PressureField& operator=(PressureField other) {
            using std::swap;
            swap(this->p , other.p);

            return *this;
        }
        ~PressureField() {
            delete this->p;
        }
};

// Abstract function
// void INIT_UVP(VelocityField &velocity , PressureField &pressure , ProgramParamerters &params);


// Function implemantation
void INIT_UVP(VelocityField &velocity , PressureField &pressure , ProgramParamerters &params) {
    // NOTE FREE THESE VARIABLES
    std::cout << "Field Initialized" << '\n';
    std::cout << params.geometryData.imax << ' ' << params.geometryData.jmax << '\n';
    velocity.u = new FIELD<FieldDouble>(params.geometryData.imax , params.geometryData.jmax);
    velocity.v = new FIELD<FieldDouble>(params.geometryData.imax , params.geometryData.jmax);

    pressure.p = new FIELD<FieldDouble>(params.geometryData.imax , params.geometryData.jmax);
}

#endif