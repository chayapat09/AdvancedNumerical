#include <iostream>
#include <vector>

using namespace std;

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
    protected : 
        int max_x ;
        int max_y ;
        NodeT ** Field;

    public :
        FIELD(const int max_x,const int max_y) {
            this->max_x = max_x;
            this->max_y = max_y;
            this->Field = new NodeT*[max_x];
            for (int i = 0 ; i < max_y ; i++) {
                this->Field[i] = new NodeT[max_y];
            }

        }

        void printField() {
            cout << "Size : " << "(x,y) = " << '(' << this->max_x << ',' << this->max_y << ')' << '\n';
            for (int i = 0 ; i < this->max_x ; i++) {
                for (int j = 0 ; j < this->max_y ; j++) {
                    NodeT tmp = get(i,j);
                    cout << tmp.val << ' ';
                }
                cout << '\n';
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

        }

        void readField() {

        }

};

struct VelocityField {
    FIELD< Node<double> , double > u;
    FIELD< Node<double> , double > v;
}
struct PressureField {
    FIELD< Node<double> , double > p;
};

const int I_MAX = 10;
const int J_MAX = 10;

int main() {
    FIELD< Node<double> , double > x(I_MAX,J_MAX);

    
}