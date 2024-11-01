/*
 * Ballistic Penetration Calculator Versus Mediums Program
 * This program is designed to implement the Krupp formula to simulate fired rounds
 * against differing mediums at differing distances.
 *
 * By: Tristan Stocks
*/


#include <iostream>
#include <cmath>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <list>



using std::cout;
using std::endl;
using std::string;
using std::get;
using std::set;





// Projectile which we are firing
class Projectile {
private:
	string projectileName;
	float diameter_caliber_{};
	float mass{};
	float velocity{};
	float coefficientOfDrag{};



public:
	Projectile() {}

	Projectile(string name, float diameterCaliber, float mass, float velocity, float coefficientOfDrag) {

		this->projectileName = name;
		this->diameter_caliber_ = diameterCaliber;
		this->mass = mass;
		this->velocity = velocity;
		this->coefficientOfDrag = coefficientOfDrag;

	}

	string getProjectileName() const { return projectileName; }

	void setProjectileName(string name) { this->projectileName = name; }

	float getCaliber() const { return diameter_caliber_; }

	void setCaliber(float caliber) { this->diameter_caliber_ = caliber; }

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
	// density is also another term for strength
	float density{};
	float depth{};

public:
	Material() {}

	Material(float density, float depth)
	{
		this->density = density;
		this->depth = depth;

	}

	float getDensity() const { return density; }

	void setDensity(float density) { this->density = density; }


	float getDepth() const { return depth; }

	void setDepth(float depth) { this->depth = depth; }
};

class BallisticCalculator
{
private:
	float distance{};
	Projectile x_projectile_;
	Material y_material_;

public:

	// pass by reference for calculations and follow on 
	BallisticCalculator(Projectile& obj_p_projectile, Material& obj_material)
	{
		x_projectile_ = obj_p_projectile;
		y_material_ = obj_material;
		calculate();


	}


	// Krupp's formula
	// e = [(MV^2cos(theta))    /    (Kd^(5/3)]^(3/4) when solved for e    
	//  e = thickness of plate, M = mass, V = Velocity,  K = Density,  d = diameter/caliber
	float calculate()
	{
		

		// MV^2cos(theta)
		float numerator = x_projectile_.getMass() * pow(x_projectile_.getVelocity(), 2.0f) * cos(30.00f);

		//2Kd^(5/3)
		// 5/3 ~ 1.666666667
		float denominator = 2 * y_material_.getDensity() * pow(x_projectile_.getCaliber(), (1.666666667f));

		//quotient ^ (3/4)
		float quotioent = numerator / denominator;

		// 3/4 ~ .75
		float calculation = pow(quotioent, 0.75f);

		return calculation;
	}

	float getDistance() const { return distance; }

	void setDistance(float distance) { this->distance = distance; }



};


int main() {
	// Program Intro
	cout << "Ballistic Penetration Calculator Versus Mediums Program\n"
		<< "This program is designed to implement the Krupp formula to simulate fired rounds"
		<< "against differing mediums at differing distances. \n\n";

	Projectile cartridge556("5.56 m855A1", 5.56f, 0.004f, 961.0f, 0.151f);
	Projectile shellAPM72("75mm",75.00f, 9.03556f, 588.26f, 0.9f);
	Material steel(0.66f, 10.0f);





	// projectile property print,  test,  remove later
	cout << "Projectile Diameter " << cartridge556.getCaliber() << "mm \n"
		<< "Velocity " << cartridge556.getVelocity() << "ms \n"
		<< "Mass " << cartridge556.getMass() << "kg \n"
		<< "Coefficient of drag " << cartridge556.getCOD() << " \n"
		<< "Material depth " << steel.getDepth() << "\n"
		<< "Calculation test " << BallisticCalculator(cartridge556, steel).calculate() << "\n\n\n"
		<< "Calculation test for " << shellAPM72.getProjectileName() << " " << BallisticCalculator(shellAPM72, steel).calculate() << "\n\n\n";
	/// 1.451950539
	///
	
}






