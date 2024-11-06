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
#include <vector>




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
	string matName;
	float density{};
	float depth{};
	

public:
	Material() {}

	Material(string matName, float density, float depth)
	{
		this->density = density;
		this->depth = depth;
		this->matName = matName;
	}

	string getMatName() { return matName; }

	float getDensity() const { return density; }

	void setDensity(float density) { this->density = density; }

	float getDepth() const { return depth; }

	void setDepth(float depth) { this->depth = depth; }
};

class BallisticCalculator{
private:
	float theta = 0.00f;
	Projectile x_projectile_;
	Material y_material_;


public:

	// pass by reference for calculations and follow on 
	BallisticCalculator(Projectile& obj_p_projectile, Material& obj_material)
	{
		x_projectile_ = obj_p_projectile;
		y_material_ = obj_material;
		
	}


	// Krupp's formula
	// e = [ (MV^2cos(theta)) / (Kd^(5/3) ]^(3/4) when solved for e    
	//  e = thickness of plate, M = mass, V = Velocity,  K = Density,  d = diameter/caliber
	float calculatePenetrationDepth()
	{
		

		// MV^2cos(theta)
		float numerator = x_projectile_.getMass() * pow(x_projectile_.getVelocity(), 2.0f) * cos(theta);

		//2Kd^(5/3)
		// 5/3 ~ 1.666666667
		float denominator = 2 * y_material_.getDensity() * pow(x_projectile_.getCaliber(), (5.00f / 3.00f));

		//quotient 
		float quotioent = numerator / denominator;

		// quotient ^ 3/4 ~ .75
		float penDepthCalc = pow(quotioent, 0.75f);

		return penDepthCalc;
	}

	// 1/2(MV^2) = K(ed^2/cos(theta))(e/d)^1/3
	string didItPen(){
		string penResult = "Penetration unsuccesful";

		//1/2(MV^2)
		float energy = .5 * (x_projectile_.getMass() * pow(x_projectile_.getVelocity(), 2));

		// K(ed^2)/cos(theta)
		float first = y_material_.getDensity() * ((y_material_.getDepth() * pow(x_projectile_.getCaliber(), 2)) / (cos(theta)));
				
		// (e/d)^1/3
		float second = pow((y_material_.getDepth() / x_projectile_.getCaliber()), 1.00/3.00);

		// K(ed^2/cos(theta))(e/d)^1/3
		float rightSideEquation = first * second;

		if (energy >= rightSideEquation) {
			return penResult = "Penetrated succesfully";
		} 

		return penResult;
	}	

};

class Result {

private:
	float penetrationDepth;
	string penned;


public:
	string projectileName;
	string materialName;
	float diameter_caliber_{};
	float mass{};
	float velocity{};
	float coefficientOfDrag{};
	float density{};
	float depth{};



	Result(Projectile xProjectile, Material yMaterial) {
		
		// Ballistic Calculation records
		BallisticCalculator BC = BallisticCalculator(xProjectile, yMaterial);

		penetrationDepth = BC.calculatePenetrationDepth();
		penned = BC.didItPen();

		// Projectile Records
		projectileName = xProjectile.getProjectileName();
		diameter_caliber_ = xProjectile.getCaliber();
		mass = xProjectile.getMass();
		velocity = xProjectile.getVelocity();
		coefficientOfDrag = xProjectile.getCOD();

		// Material Records
		materialName = yMaterial.getMatName();
		density = yMaterial.getDensity();
		depth = yMaterial.getDepth();
		
	}

	float getPenetrationDepth() { return penetrationDepth; };

	void setPenetrationDepth(float penDepth) {
		penetrationDepth = penDepth;
	}

	string getPenned() { return penned;  }

	void setPenned(string penned) { this->penned = penned; }	


};

class ResultLibrary {

public:
	std::vector<Result> LibraryEntries;
	std::vector<Result>::iterator itr;
	ResultLibrary(Result entry){
		addResult(entry);


	}

	void addResult(Result entry) {
		LibraryEntries.push_back(entry);
	}

	void showResults() {
		
		for (itr = LibraryEntries.begin(); itr != LibraryEntries.end(); itr++) {



			cout << "Projectile Stats: \n"
				<< LibraryEntries.data()->projectileName << "\n"
				<< "Caliber " << LibraryEntries.data()->diameter_caliber_ << " mm\n"
				<< "Velocity " << LibraryEntries.data()->velocity << " ms\n"
				<< "Coefficient of Drag " << LibraryEntries.data()->coefficientOfDrag << " Cd\n\n"
				<< "Material Stats: \n"
				<< LibraryEntries.data()->materialName << "\n"
				<< "Thickness " << LibraryEntries.data()->depth << " mm\n"
				<< "Strength \"Special Treatment Steel\" (STS) Rating " << LibraryEntries.data()->density << " Q\n\n"
				<< "Penetration Data:\n"
				<< LibraryEntries.data()->getPenned() << " \n"
				<< "With a penetration depth of "
				<< LibraryEntries.data()->getPenetrationDepth() << " mm\n\n\n";

		}
	}
	
};


int main() {
	// Program Intro
	cout << "Ballistic Penetration Calculator Versus Mediums Program\n"
		<< "This program is designed to implement the Krupp formula to simulate fired rounds "
		<< "against differing mediums at differing distances. \n\n";


	Projectile cartridge556("5.56 m855A1", 5.56f, 0.004f, 961.00f, 0.151f);
	Projectile shellAPM72("75mm",75.00f, 9.03556f, 588.26f, 0.90f);
		
	// Materials gathered from 
	// http://www.navweaps.com/index_nathan/metalprpsept2009.php 
	Material steel("Average Construction Steel", 0.80f, 10.00f);
	Material HTsteel("Light Armor Steel (High Tensile)", 0.85f, 10.00f);
	Material EHSDsteel("Extra-High-Strength Silicon Magnese", 0.90f, 10.00f);
	
	Result Test1Results = Result(cartridge556,steel);
	Result Test2Results = Result(shellAPM72, steel);

	ResultLibrary* Resultlog = new ResultLibrary(Test1Results);
	
	Resultlog->addResult(Test2Results);

	Resultlog->showResults();

}






