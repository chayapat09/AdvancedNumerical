#ifndef _FIELD_INCLUDED_
#define _FIELD_INCLUDED_

#include <iostream>
#include <iomanip>
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

        friend std::istream& operator>>(std::istream& is, Node& node) {
            is >> node.val;
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, Node& node) {
            os << node.val;
            return os;
        }
};

template <typename NodeT , typename T >
class FIELD {

    /*
        A 2D FIELD IN CORDINATE x,y HANDLER
        Standared Cordinates Convention

        y = y_max -1 |-----------------|
                     |-----------------|
                     |-----------------|
        y = y        |-----------------|
                     |-----------------|
                     |-----------------|
        y = 0        |-----------------|
                     x = 0     x=x     x = x_max - 1

        All debugging and assertions of Fields can do here Ex. segmentation Fault || Force Boundary condition 
        and Exception of get(x,y) that out of bond
    */
    protected : 
        int xSize ;
        int ySize ;
        NodeT ** Field;

    public :

        FIELD(const int xSize,const int ySize) {
            this->xSize = xSize;
            this->ySize = ySize;
            if (xSize == 0 || ySize == 0) {
                throw "xSize and ySize Need to > 0";
            }
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

        FIELD& operator=(FIELD other) {
            using std::swap;
            
            swap(this->xSize , other.xSize);
            swap(this->ySize , other.ySize);
            swap(this->Field , other.Field);

            return *this;
        }

        NodeT* operator[](const int i) {
            return this->Field[i];
        }

        ~FIELD() {
            for (int i = 0 ; i < this->xSize ; i++) {
                delete[] this->Field[i];
            }
            delete[] this->Field;
        }

        // Overloading std::istream funcitons here
        friend std::istream& operator>>(std::istream& is, FIELD & field) {
            int xSize = 1;
            int ySize = 1;
            is >> xSize >> ySize;
            FIELD<NodeT , T> tmp(xSize,ySize);
            for (int y = ySize - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < xSize ; x++) {
                    is >> tmp[x][y];
                }
            }
            field = tmp;
            return is;
        }

        // Overloading std::ostream funcitons here
        friend std::ostream& operator<<(std::ostream& os, FIELD& field) {
            int xSize = field.getXSize();
            int ySize = field.getYSize();
            os << xSize << ' ' << ySize << '\n';
            for (int y = ySize - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < xSize ; x++) {
                    os << std::setprecision(10) << field[x][y] << ' ';
                }
                os << '\n';
            }
            return os;
        }


        void printField() {
            #ifdef DEBUG
            std::cout << "Size : " << "(x,y) = " << '(' << this->xSize << ',' << this->ySize << ')' << '\n';
            for (int y = this->ySize - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < this->xSize ; x++) {
                    std::cout << get(x,y) << ' ';
                }
                std::cout << '\n';
            }
            #endif
        }

        void set(int x , int y , T value) {
            NodeT & tmp = get(x,y);
            tmp.val = value;
        } 

        void setAll(T value){
            for (int y = this->ySize - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < this->xSize ; x++) {
                    (this->Field)[x][y].val = value;
                }
            }
        }
        
        T findMax(){
            if(this->xSize >= 1 && this->ySize >= 1){
                //has at least 1 point
                T maxVal = (this->Field)[0][0].val;
                for (int y = this->ySize - 1 ; y >= 0 ; y--) {
                    for (int x = 0 ; x < this->xSize ; x++) {
                        maxVal = std::max( maxVal, (this->Field)[x][y].val );
                    }
                }
                return maxVal;
            }
            throw "This field is still empty!";
        }

        T findAbsoluteMax(){
            if(this->xSize >= 1 && this->ySize >= 1){
                //has at least 1 point
                T maxVal = std::abs((this->Field)[0][0].val);
                for (int y = this->ySize - 1 ; y >= 0 ; y--) {
                    for (int x = 0 ; x < this->xSize ; x++) {
                        maxVal = std::max( maxVal, std::abs((this->Field)[x][y].val ));
                    }
                }
                return maxVal;
            }
            throw "This field is still empty!";
        }

        /*
            Use .vtk file extension format in paraview
        */
        void paraview_VTK(std::ofstream & myfile, ProgramParamerters & params){
            //------------------------------------------------------------//
            // Paraview header
            myfile << "# vtk DataFile Version 2.0\n";
            myfile << "FlowField\n";
            myfile << "ASCII\n";

            // Grid
            myfile << "DATASET STRUCTURED_GRID\n";
            myfile << "DIMENSIONS " << this->xSize << " " << 1 << " " << this->ySize << "\n";
            myfile << "POINTS " << this->ySize*1*this->xSize << " float\n";

            for (int y = this->ySize - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < this->xSize ; x++) {
                    myfile << params.geometryData.delx*x << " " << params.geometryData.dely*y << " 0\n";
                }
            }
            
            // Data
            myfile << "\n";
            myfile << "POINT_DATA";
            myfile << " " << this->xSize * this->ySize << "\n";

            myfile << "\n";
            myfile << "SCALARS PHI float 1\n";
            myfile << "LOOKUP_TABLE default\n";
            for (int y = this->ySize - 1 ; y >= 0 ; y--) {
                for (int x = 0 ; x < this->xSize ; x++) {
                    myfile << get(x,y) << '\n';
                }
            }

        }

        NodeT& get(int x , int y) {
            return (this->Field)[x][y];
        }

        int getXSize() const {
            return this->xSize;
        }

        int getYSize() const {
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

        friend std::istream& operator>>(std::istream& is, VelocityField & velocityField) {
            if (velocityField.u == nullptr) velocityField.u = new FIELD<FieldDouble>(1 , 1);
            if (velocityField.v == nullptr) velocityField.v = new FIELD<FieldDouble>(1 , 1);
            std::string tmp;
            is >> tmp;
            is >> (*velocityField.u);

            is >> tmp;
            is >> (*velocityField.v);
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os , VelocityField &velocityField) {
            if (velocityField.u == nullptr) throw "U is Null pointer please initialized it first!";
            if (velocityField.v == nullptr) throw "V is Null pointer please initialized it first!";
            os << "U" << '\n';
            os << (*velocityField.u);
            os << '\n';
            os << "V" << '\n';
            os << (*velocityField.v);

            return os;
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

        friend std::istream& operator>>(std::istream& is, PressureField & pressureField) {
            if (pressureField.p == nullptr) pressureField.p = new FIELD<FieldDouble>(1 , 1);
            std::string tmp;
            is >> tmp;
            if (tmp != "P") throw "pressureField >> Operator Failed !";
            is >> (*pressureField.p);

            return is;
        }

        friend std::ostream& operator<<(std::ostream& os , PressureField &pressureField) {
            if (pressureField.p == nullptr) throw "p is Null pointer please initialized it first!";

            os << "P" << '\n';
            os << (*pressureField.p);

            return os;
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
    #ifdef DEBUG
    std::cout << "Field Initialized" << '\n';
    std::cout << params.geometryData.imax << ' ' << params.geometryData.jmax << '\n';
    #endif

    velocity.u = new FIELD<FieldDouble>(params.geometryData.imax+2 , params.geometryData.jmax+2);
    velocity.v = new FIELD<FieldDouble>(params.geometryData.imax+2 , params.geometryData.jmax+2);

    pressure.p = new FIELD<FieldDouble>(params.geometryData.imax+2 , params.geometryData.jmax+2);

    (velocity.u)->setAll(params.problemParameters.UI);
    (velocity.v)->setAll(params.problemParameters.VI);
    (pressure.p)->setAll(params.problemParameters.PI);
}

#endif