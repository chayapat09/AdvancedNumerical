#include <iostream>

#include "Field.h"

int main() {
    
    std::cout << "Section 1\n";
    // Node is Each Node in cordinate x-y
    Node<double> n;
    n.val = 20;
    std::cout << "Node Val = " << n.val << "\n\n";








    std::cout << "Section 2\n";
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
    */
    // This 2D Field of type double consist of 7*7 Node<double>
    FIELD<Node<double> , double> field(7,7);
    field.printField();

    std::cout << "\n\n";








    std::cout << "Section 3\n";

    // Set cordinate (0,0) to node of val = 5.555
    field.set(0,0 , 5.555);
    Node<double> & node = field.get(0,0);
    std::cout << "Field (0,0) Node Val = " << node.val << "\n";

    // Same As
    std::cout << "Field (0,0) Node Val = " << field.get(0,0).val << '\n';

    // Same As
    std::cout << "Field (0,0) Node Val = " << field[0][0].val << "\n\n";
    
    // This is ok -> field[0][0].val++;

    // This Field can easily copy
    // Set some random xSize,ySize
    FIELD<Node<double> , double> field2(1,1);
    field2 = field;
    // OR FIELD<Node<double> , double> field2 = field;
    // OR FIELD<Node<double> , double> field2(field);
    field2.printField();

    std::cout << "\n\n";





    std::cout << "Section 4\n";
    // We constructed these field to Type-Srict Field
    // 1.VelocityField
    // 2.PressureField
    // 3.FG
    // 4.RHS

    VelocityField velocity(10,10);
    // velocity.u // u component of velocity
    // velocity.v // v component of velocity

    // Each component are [pointers to FIELD<Node<double> , double> ] or [FIELD<Node<double> , double> *]
    for (int x = 0 ; x < velocity.u->getXSize() ; x++) {
        for(int y = 0 ; y < velocity.u->getYSize() ; y++) {
            if (x - y == 0 || x + y == 9) {
                velocity.u->set(x,y , 1);
            }

        }
    }

    velocity.u->printField();

    std::cout << "\n\n";








    std::cout << "Section 5\n";

    // Same as Field we can easily copied these fields
    VelocityField v2;
    v2 = velocity;
    v2.u->printField();

}