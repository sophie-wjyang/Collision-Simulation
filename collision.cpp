//CR, ZR, DE, WA, YS
//Fall 2020
#include <bits/stdc++.h>
using namespace std;

struct Vec2
{                        //We define a struct called Vec2 (a 2 dimensional vector) which will have methods covering all the vector operations needed as well as additional ones for utility.
    double x = 0, y = 0; //members of this struct will have two values; one in each of the x and y directions.

    double magnitude_squared() const
    { //This method returns a double value equaling the square of the magnitude. (magnitude^2 = x^2 + y^2). Const in the function prevents the values of member x and y from being altered.

        return x * x + y * y;
    }

    double magnitude() const
    { //This method returns a double value equaling the magnitude by utilizing the magnitude squared function and taking the square root (magnitude = sqrt(magnitude_squared())).
        return sqrt(magnitude_squared());
    }

    Vec2 unit() const
    { //This method returns an instance of the Vec2 struct. The members of this instance will have values equal to the members of the current struct scaled accordingly such that the magnitude of our new instance will be equal to 1.
        double m = magnitude();
        return {x / m, y / m};
    }

    Vec2 operator-() const
    { //In C++, we can make operators to work for user defined classes. This means C++ has the ability to provide the operators with a special meaning for a data type, this ability is known as operator overloading. We perform operator overloading here by having “-” returns an instance of the Vec2 struct. The members of this instance will be the negative members of the current struct.
        return {-x, -y};
    }

    Vec2 operator+(const Vec2 &other) const
    { //We perform operator overloading here by having “+” returns an instance of the Vec2 struct. The members of this instance will be the vector sum of the members of the current struct and the members of the struct that is passed in.
        return {x + other.x, y + other.y};
    }

    Vec2 operator*(double scalar) const
    { //This method returns an instance of the Vec2 struct, which will be the result of scalar-vector multiplication between some given scalar and the current vector
        return {x * scalar, y * scalar};
    }

    friend Vec2 operator*(double scalar, const Vec2 &vec)
    { //We overload another operator overload by passing through a scalar as well as another Vec2. This overloaded function is different in that we can access the members of a friend Vec2.
        return {vec.x * scalar, vec.y * scalar};
    }
};

int main()
{
    //variable initialization
    vector<double> mass(2), spring_constant(2), radius(2);
    vector<Vec2> position(2), velocity(2);

    int steps;
    double dt, time = 0;

    //prompting for input
    cout << "Enter the dt (s): ";
    cin >> dt;

    cout << "Enter the number of steps: ";
    cin >> steps;

    cout << "Mass of ball 1 (kg): ";
    cin >> mass[0];

    cout << "Mass of ball 2 (kg): ";
    cin >> mass[1];

    cout << "Spring constant of ball 1 (N m^(-1)): ";
    cin >> spring_constant[0];

    cout << "Spring constant of ball 2 (N m^(-1)): ";
    cin >> spring_constant[1];

    cout << "Radius of ball 1 (m): ";
    cin >> radius[0];

    cout << "Radius of ball 2 (m): ";
    cin >> radius[1];

    cout << "Initial x position of ball 1 (m): ";
    cin >> position[0].x;
    cout << "Initial y position of ball 1 (m): ";
    cin >> position[0].y;

    cout << "Initial x position of ball 2 (m): ";
    cin >> position[1].x;
    cout << "Initial y position of ball 2 (m): ";
    cin >> position[1].y;

    cout << "Initial x velocity of ball 1 (m s^(-1)): ";
    cin >> velocity[0].x;
    cout << "Initial y velocity of ball 1 (m s^(-1)): ";
    cin >> velocity[0].y;

    cout << "Initial x velocity of ball 2 (m s^(-1)): ";
    cin >> velocity[1].x;
    cout << "Initial y velocity of ball 2 (m s^(-1)): ";
    cin >> velocity[1].y;

    //In our simulation, the colliding objects effectively act as balls of springs. The springs act in series, and produce a combined spring constant. Here we compute the combined spring constant, using the relationship that the reciprocal of the combined spring constant is the sum of the reciprocals of the original springs constants.
    auto spring_constant_combined = 1.0 / (1.0 / spring_constant[0] + 1.0 / spring_constant[1]);

    //For loop that iterates and produces the values of the simulation
    for (int i = 0; i < steps; i++)
    {
        //For each step, we output relevant values for the user
        cout << time << "," << position[0].x << "," << position[0].y << "," << position[1].x << ",";
        cout << position[1].y << "," << velocity[0].x << "," << velocity[0].y << "," << velocity[1].x << "," << velocity[1].y << endl;

        //declaring vectors each containing two Vec2 objects. The first denotes the respective value of the vector (a physics vector) in the x-dimension. The second denotes the respective value of the vector in the y-dimension.
        vector<Vec2> force(2);
        vector<Vec2> acceleration(2);

        auto relative_position = position[1] + (-position[0]); //we find second ball relative to the first

        //we check to see if the displacements between the relative positions differ by a magnitude greater than the sum of the radii. If so, then the two balls are in contact.
        if (relative_position.magnitude() <= radius[0] + radius[1])
        {
            auto length_difference = (radius[0] + radius[1]) - relative_position.magnitude();
            //We find the displacement of the springs that acts along the line connecting the centers of the two balls. Note that this line is changing in the case of a glancing collision.
            force[0] = -length_difference * spring_constant_combined * relative_position.unit();
            //Using Hooke’s Law, the magnitude of the force acting on the first ball is given by the negative combined spring constant multiplied by the displacement vector. The direction of the force is found using relative_position.unit();. We then scalar multiply the relative position unit with the magnitude to achieve the desired force vector..
            force[1] = -force[0]; //Using Newton’s Third Law of Motion
        }

        //For loop that updates the vectors of acceleration, velocity, and displacement
        for (int j = 0; j < 2; j++)
        {
            acceleration[j] = 1.0 / mass[j] * force[j];       //using Newton’s Second Law of Motion
            velocity[j] = velocity[j] + acceleration[j] * dt; // v=v0 + at
            position[j] = position[j] + velocity[j] * dt;     // s = s0 + vt
            // note that the above + operation untilizes operation overload, so both dimensions are being added
        }

        time += dt; // increments the value of time, equal to the sum of all the time differentials across the total number of steps
    }

    return 0; //End of program
}
