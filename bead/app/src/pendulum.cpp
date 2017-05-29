
using namespace std;

#include "pendulum.hpp"
using namespace cpl;

const double pi = 4 * atan(1.0);

const double g = 9.8;        // acceleration of gravity

double L = 1.0;              // length of pendulum
double q = 0.1;              // damping coefficient
double Omega_D = 1.0/3.0;    // frequency of driving force
double F_D = 0.2;            // amplitude of driving force
bool nonlinear;              // linear if false

Vector f(const Vector& x) {  // extended derivative vector
    double t = x[0];
    double theta = x[1];
    double omega = x[2];
    Vector f(3);             // Vector with 3 components
    f[0] = 1;
    f[1] = omega;
    if (nonlinear)
        f[2] = - (g/L) * sin(theta) - q * omega + F_D * sin(Omega_D * t);
    else
        f[2] = - (g/L) * theta - q * omega + F_D * sin(Omega_D * t);
    return f;
}


int main() {
	
	double theta=1, omega=0, tMax=100;
    /*cout << " Nonlinear damped driven pendulum\n"
         << " --------------------------------\n"
         << " Enter linear or nonlinear: ";
    string response;
    cin >> response;
   cout<< " Length of pendulum L: ";
    cin >> L;
    cout<< " Enter damping coefficient q: ";
    cin >> q;
    
	cout << " Enter driving frequencey Omega_D: ";
    cin >> Omega_D;
    cout << " Enter driving amplitude F_D: ";
    cin >> F_D;
	cout << " Enter theta(0) and omega(0): ";
    cin >> theta >> omega;
    cout << " Enter integration time t_max: ";
    cin >> tMax;*/

    double dt = 0.01;
    double accuracy = 1e-6;
    ofstream dataFile("pendulum.data");

    double t = 0;
    Vector x(3);
    x[0] = t;
    x[1] = theta;
    x[2] = omega;


//adaptive Runge-Kutta
    while (t < tMax) {
        adaptiveRK4Step(x, dt, accuracy, f);
        t = x[0], theta = x[1], omega = x[2];
        if (nonlinear) {
            while (theta >= pi) theta -= 2 * pi;
            while (theta < -pi) theta += 2 * pi;
        }
        double energy=L*L*omega*omega/2-L*g*cos(theta)+98;
        dataFile << t << '\t' << theta << '\t' << omega << '\t' << energy << '\n';
    }

//sima Runge-Kutta
    /*while (t < tMax) {
        RK4Step(x, dt, f);
        t = x[0], theta = x[1], omega = x[2];
        if (nonlinear) {
            while (theta >= pi) theta -= 2 * pi;
            while (theta < -pi) theta += 2 * pi;
        }
        double energy=L*L*omega*omega/2-L*g*cos(theta)+98;
        dataFile << t << '\t' << theta << '\t' << omega << '\t' << energy << '\n';
    }*/


// Euler-Cromer
    /*while (t < tMax){
        double a=f(x)[2];
        omega=omega+a*dt;
        theta=theta+omega*dt;
        t=t+dt;
        x[0] = t;
        x[1] = theta;
        x[2] = omega;
        if (nonlinear) {
            while (theta >= pi) theta -= 2 * pi;
            while (theta < -pi) theta += 2 * pi;
        }
        double energy=L*L*omega*omega/2-L*g*cos(theta)+98;
        dataFile << t << '\t' << theta << '\t' << omega << '\t' << energy << '\n';
    }*/


    /* Euler
     while (t < tMax){
        double a=f(x)[2];

        theta=theta+omega*dt;
        omega=omega+a*dt;
        t=t+dt;
        x[0] = t;
        x[1] = theta;
        x[2] = omega;
        if (nonlinear) {
            while (theta >= pi) theta -= 2 * pi;
            while (theta < -pi) theta += 2 * pi;
        }
        double energy=L*L*omega*omega/2-L*g*cos(theta)+98;
        dataFile << t << '\t' << theta << '\t' << omega << '\t' << energy << '\n';
    }*/


    cout << " Output data to file pendulum.data" << endl;
    dataFile.close();
}

