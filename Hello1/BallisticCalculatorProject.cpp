

#include <iostream>
#include <cmath>
#include <set>
#include <unordered_set>


using std::cout;
using std::endl;
using std::string;
using std::get;
using std::set;


class BallisticCalculator
{
private:
	float distance{};

	BallisticCalculator()
	{


			
	}


    // Krupp's formula
    float calculate()
	{
        float calculation = 0;

        
        return calculation;
	}

    float getDistance() const { return distance; }

    void setDistance(float distance) { this->distance = distance; }



};


// Projectile which we are firing
class Projectile {
private:
    float caliber{};
    float mass{};
    float velocity{};
    float coefficientOfDrag{};

 

public:

    Projectile(float caliber, float mass, float velocity, float coefficientOfDrag) {

        setCaliber(caliber);
        setMass(mass);
        setVelocity(velocity);
        setCOD(coefficientOfDrag);
        
    }


    float getCaliber() const { return caliber; }

    void setCaliber(float caliber) { this->caliber = caliber; }

    float getMass() const { return mass; }

    void setMass(float mass) { this->mass = mass; }

    float getVelocity() const { return velocity; }

    void setVelocity(float velocity) { this->velocity = velocity; }

    float getCOD() const { return coefficientOfDrag; }

    void setCOD(float coefficientOfDrag) { this->coefficientOfDrag = coefficientOfDrag; }

};

// Material for the Plate we are firing a projectile at
class Material {
private:
    float density{};
    float depth{};
    
    
    Material()
    {

    }

    float getDensity() const { return density; }

    void setDensity(float density) { this->density = density; }


    float getDepth() const { return depth; }

    void setDepth(float depth) { this->depth = depth; }
};


int main(){
    // Program Intro
    cout << "Ballistic Penetration Calculator Versus Mediums Program\n"
        << "This program is designed to implement the Krupp formula to simulate fired rounds"
        << "against differing mediums at differing distances. \n\n";

    Projectile cartridge556(556.00f, 5.0f, 1000.0f, 0.8f);
    Projectile shellAPM72(75.00f, 10.0f, 600.0f, 0.9f);




    // projectile property print,  test,  remove later
	cout << "Projectile Caliber " << shellAPM72.getCaliber() << "mm \n"
		 << "Velocity " << shellAPM72.getVelocity() << "ms \n"
		 << "Mass " << shellAPM72.getMass() << "kg \n"
		 << "Coefficient of drag " << shellAPM72.getCOD() << " \n";
}





