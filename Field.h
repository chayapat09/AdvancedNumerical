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
        int max_x ;
        int max_y ;
        NodeT ** Field;

    public :
        FIELD(const int max_x,const int max_y) {
            this->max_x = max_x;
            this->max_y = max_y;
            this->Field = new NodeT*[max_x];
            for (int i = 0 ; i < max_x ; i++) {
                this->Field[i] = new NodeT[max_y];
            }

        }

        FIELD(const FIELD<NodeT,T> & other ) {
            this->max_x = other.max_x;
            this->max_y = other.max_y;
            this->Field = new NodeT*[max_x];

            for (int i = 0 ; i < max_x ; i++) {
                this->Field[i] = new NodeT[max_y];
            }
            for (int i = 0 ; i < other.max_x ; i++) {
                for (int j = 0 ; j < other.max_y ; j++) {
                    NodeT & tmp = other.Field[i][j];
                    set(i , j , tmp.val);
                }
            }
        }

        ~FIELD() {
            for (int i = 0 ; i < this->max_x ; i++) {
                delete[] this->Field[i];
            }
            delete[] this->Field;
        }


        void printField() {
            std::cout << "Size : " << "(x,y) = " << '(' << this->max_x << ',' << this->max_y << ')' << '\n';
            for (int y = this->max_y - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < this->max_x ; x++) {
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
            return this->max_x;
        }

        int getYSize() {
            return this->max_y;
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

        VelocityField(int x_max , int y_max) {
            this->u = new FIELD<FieldDouble>(x_max , y_max);
            this->v = new FIELD<FieldDouble>(x_max , y_max);
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
        PressureField(int x_max , int y_max) {
            this->p = new FIELD<FieldDouble>(x_max , y_max);
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