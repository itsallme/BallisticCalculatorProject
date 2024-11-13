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
#include <fstream>
#include <random>




using std::cout;
using std::endl;
using std::string;
using std::get;
using std::set;
using std::ios;






// Projectile which we are firing
class Projectile {
	
private:
	string projectileName;
	float diameter_caliber_{};
	float mass{};
	float velocity{};
	float coefficientOfDrag{};
	float immutabletempVelocity{};



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

	void setTempVelocity(float veloctiy) { this->immutabletempVelocity = velocity; }

	float getTempVelocity() { return immutabletempVelocity; }

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
	float velocity = 0.00f;
	float caliber = 0.00f;
	Projectile x_projectile_;
	Material y_material_;


public:

	// pass by reference for calculations and follow on 
	BallisticCalculator(Projectile& obj_p_projectile, Material& obj_material)
	{
		x_projectile_ = obj_p_projectile;
		y_material_ = obj_material;
		
	}

	BallisticCalculator(Projectile& obj_p_projectile, Material& obj_material, float theta) {

		x_projectile_ = obj_p_projectile;
		y_material_ = obj_material;
		this->theta = theta;

	}


	// Krupp's formula
	// e = [ (MV^2cos(theta)) / (Kd^(5/3) ]^(3/4) when solved for e    
	//  e = thickness of plate, M = mass, V = Velocity,  K = Density,  d = diameter/caliber
	float calculatePenetrationDepth()
	{
		

		// MV^2cos(theta)
		float numerator = x_projectile_.getMass() * pow(x_projectile_.getVelocity(), 2.0f) * cosf(theta);

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
		float first = y_material_.getDensity() * ((y_material_.getDepth() * pow(x_projectile_.getCaliber(), 2)) / (cosf(theta)));
				
		// (e/d)^1/3
		float second = pow((y_material_.getDepth() / x_projectile_.getCaliber()), 1.00/3.00);

		// K(ed^2/cos(theta))(e/d)^1/3
		float rightSideEquation = first * second;

		if (energy >= rightSideEquation) {
			return penResult = "Penetrated succesfully";
		} 

		return penResult;
	}

	float getTheta() { return theta; }
	
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
	float theta{};


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

	Result(Projectile xProjectile, Material yMaterial, float theta) {

		// Ballistic Calculation records
		BallisticCalculator BC = BallisticCalculator(xProjectile, yMaterial, theta);

		penetrationDepth = BC.calculatePenetrationDepth();
		penned = BC.didItPen();

		// theta, vertical strike angle 
		this->theta = BC.getTheta();

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
	
	ResultLibrary(Result entry){
		addResult(entry);


	}

	void addResult(Result entry) {
		LibraryEntries.push_back(entry);
	}

	// show everything
	void showResults() {
		int count = 1;

		// formatting for easy result display, later implement into chart/table.
		for (auto i : LibraryEntries ) {
			
			cout << "Test run: " << count++ << "\n"
				<< "Projectile Stats: \n"
				<< i.projectileName << "\n"
				<< "Caliber " << i.diameter_caliber_ << " mm\n"
				<< "Velocity " << i.velocity << " ms\n"
				<< "Coefficient of Drag " << i.coefficientOfDrag << " Cd\n\n"
				<< "Material Stats: \n"
				<< i.materialName << "\n"
				<< "Thickness " << i.depth << " mm\n"
				<< "Strength \"Special Treatment Steel\" (STS) Rating " << i.density << " Q\n"
				// radian * 57.2957795 = degrees
				<< "Angle of penetration " << i.theta * 57.2957795 << " degrees\n\n"
				<< "Penetration Data:\n"
				<< i.getPenned() << " \n"
				<< "With a penetration depth of "
				<< i.getPenetrationDepth() << " mm\n__________________________________________________________\n\n";
		
		}

		cout << "End of program\n\n\n";

		createCSV();

	}

	void createCSV() {

		std::fstream fout;
		

		

		fout.open("BallisticCalc.csv", ios::out | ios::app);
			
						

		for (auto i : LibraryEntries) {

			fout << i.projectileName << ", "
				<< "Caliber" << ", "
				<< i.diameter_caliber_ << ", "
				<< "Velocity" << ", "
				<< i.velocity << ", "
				<< i.materialName << ", "
				<< "Material Thickness " << ", " 
				<< i.depth << ", "
				<< "Material Density" << ","
				<< i.density << ", "
				<< "Angle of penetration " << ", " 
				// radians * 57.2957795 = degrees
				<< i.theta * 57.2957795 << ", "
				<< "Penetration Depth" << ","
				<< i.getPenetrationDepth() << ", "
				<< i.getPenned() << ",\n";

		}


	}


	
};


int main() {
	// Program Intro
	cout << "Ballistic Penetration Calculator Versus Mediums Program\n"
		<< "This program is designed to implement the Krupp formula to simulate fired rounds "
		<< "against differing mediums at differing distances. \n\n";
	// Projectile pulled from here
	// https://en.wikipedia.org/wiki/5.56%C3%9745mm_NATO
	Projectile cartridge556("5.56 m855A1", 5.56f, 0.004f, 961.00f, 0.151f);

	// 
	Projectile shellAPM72("75mm", 75.00f, 9.03556f, 588.26f, 0.90f);

	// Materials gathered from 
	// http://www.navweaps.com/index_nathan/metalprpsept2009.php 
	Material steel("Average Construction Steel", 0.80f, 10.00f);
	Material HTsteel("Light Armor Steel (High Tensile)", 0.85f, 10.00f);
	Material EHSDsteel("Extra-High-Strength Silicon Magnese", 0.90f, 10.00f);

	Material testSteel("Average Construction Steel", 0.80f, 39.00f);



	// Test criteria, might put into array and cycle through to make code more efficient

	Result Test1Results = Result(cartridge556, steel);
	/*
	Result Test1aResults = Result(cartridge556, HTsteel);
	Result Test1bResults = Result(cartridge556, EHSDsteel);

	Result Test2Results = Result(shellAPM72, steel);
	Result Test2aResults = Result(shellAPM72, HTsteel);
	Result Test2bResults = Result(shellAPM72, EHSDsteel);

	ResultLibrary* Resultlog = new ResultLibrary(Test1Results);

	Resultlog->addResult(Test1aResults);
	Resultlog->addResult(Test1bResults);
	Resultlog->addResult(Test2Results);
	Resultlog->addResult(Test2aResults);
	Resultlog->addResult(Test2bResults);
	*/
	// normal result log
	//Resultlog->showResults();

	// random values for 
	ResultLibrary* RandomResultLog = new ResultLibrary(Test1Results);


	// randomizer
	std::normal_distribution<float> normDist(cartridge556.getVelocity(), 5.00f);
	std::mt19937 generator;

	// theta randomizer
	std::normal_distribution<float> thetaDist(0.00f, 1.00f);

	// TODO: fill arrays with user input

	float tempNum;
	
	float randVelArray[1000];
	float randThetaArray[1000];

	// array fill random velocity
	for (int i = 0; i < 1000; i++) {
		tempNum = normDist(generator);
		randVelArray[i] = tempNum;
	}
	// array fill random theta
	for (int i = 0; i < 1000; i++) {
		tempNum = thetaDist(generator);
		randThetaArray[i] = tempNum;
		
	}



	// radian randomizer for theta and impact angle 
	for (int y = 0; y < 1000; y++) {

		if (randThetaArray[y] < -1.00f) {
			randThetaArray[y] += 1.00f;
		}

		if (randThetaArray[y] > 1.00f) {
			randThetaArray[y] -= 1.00f;
		}
		
		float tempTheta = randThetaArray[y];
		Test1Results = Result(cartridge556, testSteel, tempTheta);
		RandomResultLog->addResult(Test1Results);

	}
	

	/*
	// velocity randomizer 
	for (int i = 0; i < 1000; i++) {
		
		Projectile randCatridge556 = cartridge556;

		randCatridge556.setVelocity(randVelArray[i]);

		Test1Results = Result(randCatridge556, testSteel);

		RandomResultLog->addResult(Test1Results);
				
	}
	
	RandomResultLog->showResults();

	*/
	

}






