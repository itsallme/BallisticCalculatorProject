

#include <iostream>
#include <cmath>
#include <set>
#include <unordered_set>



using std::cout;
using std::endl;
using std::string;
using std::get;
using std::set;





// Projectile which we are firing
class Projectile {
private:
	float diameter_caliber_{};
	float mass{};
	float velocity{};
	float coefficientOfDrag{};



public:
	Projectile() {}

	Projectile(float caliber, float mass, float velocity, float coefficientOfDrag) {

		this->diameter_caliber_ = caliber;
		this->mass = mass;
		this->velocity = velocity;
		this->coefficientOfDrag = coefficientOfDrag;

	}


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
	float calculate()
	{
		float calculation = 0.00f;



		calculation = x_projectile_.getVelocity() + y_material_.getDepth();

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

	Projectile cartridge556(556.00f, 5.0f, 1000.0f, 0.8f);
	Projectile shellAPM72(75.00f, 10.0f, 600.0f, 0.9f);
	Material steel(10.0f, 10.0f);





	// projectile property print,  test,  remove later
	cout << "Projectile Caliber " << cartridge556.getCaliber() << "mm \n"
		<< "Velocity " << cartridge556.getVelocity() << "ms \n"
		<< "Mass " << cartridge556.getMass() << "kg \n"
		<< "Coefficient of drag " << cartridge556.getCOD() << " \n"
		<< "Material depth " << steel.getDepth() << "\n"
		<< "Calculation test " << BallisticCalculator(cartridge556, steel).calculate();

}





