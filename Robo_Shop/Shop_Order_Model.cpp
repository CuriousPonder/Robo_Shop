#include <string>
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

// /////////////////////////////////////
//             S H O P
// /////////////////////////////////////

class Shop
{
	public:
	void create_new_robot_part();
	
	void create_new_robot_model();
	
	void create_new_customer();
	
	void create_new_sales_associate();
	
	void save(string filneame);
	
	void open(string filename);
	
	private:
	
	//Order order;
	//Robot_part robot_parts;
	//View view;
	//Robot_model robot_models;
	//Customer customers;
	//Sales_associate sales_associates;
	
};

class Robot_model
{
	public:
		double cost();
		double max_energy();
		double max_battery_life();
		
	private:
		string name;
		int model_number;
		Robot_part Torso;
		Robot_part Head;
		Robot_part Arm;
		Robot_part Battery;
		Robot_part Locomotor;
		
};

class Order
{
	public:
		double robot_cost();
		double extended_price();
		
	private:
	
		int order_number;
		string date;
		Customer customer;
		Sales_associate sales_associate;
		Robot_model robot_model;
		int status;
};
