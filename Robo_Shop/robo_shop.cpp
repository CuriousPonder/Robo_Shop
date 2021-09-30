#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <chrono>
#include <thread>
#include "utility.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
using namespace std;
/////////////
//CUSTOMER
/////////////
class Customer {
  public:
    Customer(string name, int customer_number, int phone_number, string email_address)
      : _name(name), _customer_number(customer_number), _phone_number(phone_number), _email_address(email_address) {}
    Customer() : _name("unknown"), _customer_number(0), _phone_number(0), _email_address("unknown") {}

    string to_string() {
			std::string s = std::to_string(_customer_number);
			std::string p = std::to_string(_phone_number);
			return "Customer: (" + _name + ", " +  s + ", " + p + ", " + _email_address + "," + ")";}

    string get_customer_name();
    string get_customer_email_address();
    int get_customer_phone_number();
    int get_customer_number();

  private:
    string _name;
    int _customer_number;
    int _phone_number;
    string _email_address;
};

string Customer::get_customer_name() {return _name;}
string Customer::get_customer_email_address() {return _email_address;}
int Customer::get_customer_phone_number() {return _phone_number;}
int Customer::get_customer_number() {return _customer_number;}
////////////////////
//SALES ASSOCIATE
////////////////////
class Sales_associate {
  public:
    Sales_associate(string name, int employee_number)
      : _name(name), _employee_number(employee_number) {}
    Sales_associate() : _name("unknown"), _employee_number(0) {}

    string to_string() {
			std::string s = std::to_string(_employee_number);
			return "Associate: (" + _name + ", " +  s  + ")";}

    string get_name();
    int get_employee_number();

  private:
    string _name;
    int _employee_number;
    
};

string Sales_associate::get_name() {return _name;}
int Sales_associate::get_employee_number() {return _employee_number;}
////////////////////////
//ROBOT PART
////////////////////////
class Robot_part
{
	public:
		Robot_part(string name, string description, string image_filename, double cost, int model_number)
			: _name{name}, _description{description}, _image_filename{image_filename}, _cost{cost}, _model_number{model_number} { }
			virtual string to_string(){
					std::string s = std::to_string(_model_number);
					std::string c = std::to_string(_cost);
					return "Part: (" + _name + ", " + _description + ", "+ _image_filename+ ", " + c+ ", " + s + ")";}
		
	protected:
		string _name;
		string _description;
		string _image_filename;
		double _cost;
		int _model_number;
};
/////////////////////////
//HEAD
////////////////////////
class Head : public Robot_part {
	public:
		Head(string name, string description, string image_filename, double cost, int model_number, double power) 
			: Robot_part(name, description, image_filename, cost, model_number),  _power{power} { } 
		
		string to_string() override{
			std::string s = std::to_string(_model_number);
			std::string c = std::to_string(_cost);
			std::string p = std::to_string(_power);
			return "Head: (" + _name + ", " + _description + ", "+ _image_filename+ ", " + c+ ", "+ p + ", " + s + ")";}
		double power() const {return _power;}
	private:
		double _power;
};
////////////////////////
//LOCOMOTOR
////////////////////////
class Locomotor : public Robot_part {
	public:
		Locomotor(string name, string description, string image_filename, double cost, int model_number, double max_power) 
			: Robot_part(name, description, image_filename, cost, model_number), _max_power{max_power} { }
		
		string to_string() override{
			std::string s = std::to_string(_model_number);
			std::string c = std::to_string(_cost);
			std::string p = std::to_string(_max_power);
			return "Locomotor: (" + _name + ", " + _description + ", "+ _image_filename+ ", " + c+ ", "+ p + ", " + s + ")";}
		double max_power() const {return _max_power;}
	private:
		double _max_power;
};
///////////////////////
//ARM
///////////////////////
class Arm : public Robot_part {
	public:
		Arm(string name, string description, string image_filename, double cost, int model_number, double max_power) 
			: Robot_part(name, description, image_filename, cost, model_number), _max_power{max_power} { }
		
		string to_string() override{
			std::string s = std::to_string(_model_number);
			std::string c = std::to_string(_cost);
			std::string p = std::to_string(_max_power);
			return "Arm: (" + _name + ", " + _description + ", "+ _image_filename+ ", " + c+ ", "+ p + ", " + s + ")";}
		
	private:
		double _max_power;
};
//////////////////////
//BATTERY
//////////////////////
class Battery : public Robot_part {
	public:
		Battery(string name, string description, string image_filename, double cost, int model_number, double power_available, double max_energy) 
			: Robot_part(name, description, image_filename, cost, model_number), _power_available(power_available), _max_energy{max_energy} { }
		
		string to_string() override{
			std::string s = std::to_string(_model_number);
			std::string c = std::to_string(_cost);
			std::string p = std::to_string(_max_energy);
			std::string pa = std::to_string(_power_available);
			return "Battery: (" + _name + ", " + _description + ", "+ _image_filename+ ", " + c+ ", "+ p + ", " + pa + ", " + s + ")";}
		
	private:
		double _power_available;
		double _max_energy;
};
///////////////////
//TORSO
//////////////////
class Torso : public Robot_part {
	public:
		Torso(string name, string description, string image_filename, double cost, int model_number, int battery_compartments, int max_arms) 
			: Robot_part(name, description, image_filename, cost, model_number), _battery_compartments{battery_compartments}, _max_arms{max_arms} { }
		
		string to_string() override{
			std::string s = std::to_string(_model_number);
			std::string c = std::to_string(_cost);
			std::string a = std::to_string(_max_arms);
			std::string bc = std::to_string(_battery_compartments);
			return "Torso: (" + _name + ", " + _description + ", "+ _image_filename+ ", " + c+ ", "+ a + ", " + bc + ", " + s + ")";}
		
	private:
		int _battery_compartments;
		int _max_arms;

};

// /////////////////////////////////////
//        	ROBOT MODEL
// /////////////////////////////////////

class Robot_model
{
	public:
		Robot_model(string _name, Head _head, Locomotor _locomotor, Torso _torso, Arm _arm, Battery _battery)
			: name(_name), head(_head), locomotor(_locomotor), torso(_torso), arm(_arm), battery(_battery) {} 
			
		double cost();
		double max_energy();
		double max_battery_life();
		
		string to_string() {
			string h, l, t, a, b;
			h = head.to_string();
			l = locomotor.to_string();
			t = torso.to_string();
			a = arm.to_string();
			b = battery.to_string();
			return "Robot Model: (" + name + ", " + h + ", "+ l + ", " + t + ", "+ a + ", " + b + ")";}
		

			
		
	private:
		string name;
		int model_number;
		Torso torso;
		Head head;
		Arm arm;
		Battery battery;
		Locomotor locomotor;
		
};
// /////////////////////////////////////
//    		   STORAGE
// /////////////////////////////////////
class Storage {
  public:

	void add_head(Head head_part);
	void add_loco(Locomotor loco_part);
	void add_arm(Arm arm_part);
	void add_battery(Battery bat_part);
	void add_torso(Torso tor_part);
	void add_customer(Customer cust);
	void add_associate(Sales_associate as);
	
	string head_to_string(int part_index);
    string loco_to_string(int part_index);
    string arm_to_string(int part_index);
    string bat_to_string(int part_index);
    string tor_to_string(int part_index);
	string customer_to_string(int part_index);
	string associate_to_string(int part_index);
	string model_to_string(int part_index);
	Head return_head(int idx);
	Arm return_arm(int idx);
	Locomotor return_loco(int idx);
	Battery return_bat(int idx);
	Torso return_tor(int idx);
    int number_of_heads();
    int number_of_locos();
    int number_of_tors();
    int number_of_arms();
    int number_of_bats();
	int number_of_customers();
	int number_of_associates();
	void add_model(Robot_model mod);
	int number_of_mods();
	string mod_to_string(int idx);
    vector<Head> head_parts;
    vector<Locomotor> loco_parts;
    vector<Torso> tor_parts;
    vector<Arm> arm_parts;
    vector<Battery> bat_parts;
    vector<Robot_model> models;
    
    vector<Customer> customers;
    vector<Sales_associate> associates;
};

int Storage::number_of_mods(){
	return models.size();
}
void Storage::add_model(Robot_model mod) {
  models.push_back(mod);
}

void Storage::add_head(Head head_part) {
  head_parts.push_back(head_part);
}
void Storage::add_loco(Locomotor loco_part) {
  loco_parts.push_back(loco_part);
}
void Storage::add_arm(Arm arm_part) {
  arm_parts.push_back(arm_part);
}
void Storage::add_battery(Battery bat_part) {
  bat_parts.push_back(bat_part);
}
void Storage::add_torso(Torso tor_part) {
  tor_parts.push_back(tor_part);
}
void Storage::add_customer(Customer cust){
  customers.push_back(cust);
}
void Storage::add_associate(Sales_associate as){
  associates.push_back(as);
}

string Storage::customer_to_string(int part_index){
  return customers[part_index].to_string();
}
string Storage::model_to_string(int part_index){
  return models[part_index].to_string();
}

string Storage::associate_to_string(int part_index){
  return associates[part_index].to_string();
}
string Storage::head_to_string(int part_index) {
  return head_parts[part_index].to_string();
}
string Storage::loco_to_string(int part_index) {
  return loco_parts[part_index].to_string();
}
string Storage::arm_to_string(int part_index) {
  return arm_parts[part_index].to_string();
}
string Storage::bat_to_string(int part_index) {
  return bat_parts[part_index].to_string();
}
string Storage::tor_to_string(int part_index) {
  return tor_parts[part_index].to_string();
}
string Storage::mod_to_string(int idx)
{
	return models[idx].to_string();
}
Head Storage::return_head(int idx)
{
	return head_parts[idx];
}
Arm Storage::return_arm(int idx)
{
	return arm_parts[idx];
}
Locomotor Storage::return_loco(int idx)
{
	return loco_parts[idx];
}
Battery Storage::return_bat(int idx)
{
	return bat_parts[idx];
}
Torso Storage::return_tor(int idx)
{
	return tor_parts[idx];
}
int Storage::number_of_heads() {
  return head_parts.size();
}
int Storage::number_of_locos() {
  return loco_parts.size();
}
int Storage::number_of_tors() {
  return tor_parts.size();
}
int Storage::number_of_arms() {
  return arm_parts.size();
}
int Storage::number_of_bats() {
  return bat_parts.size();
}
int Storage::number_of_customers() {
  return customers.size();
}
int Storage::number_of_associates() {
  return associates.size();
}

// /////////////////////////////////////
//    		  VIEW == BOX VIEW
// /////////////////////////////////////
class Box : public Fl_Box {
	bool dirty = true;  // set true to demo Exit dialog
	
	public:
	// Call base constructor
	Box(int X, int Y, int W, int H)
	: Fl_Box(X, Y, W, H) { }
	// Draw the lines any time FLTK needs to refresh the widget
	void draw() override;
	// Determine if any lines haven't been saved
	bool saved();
};

void Box::draw() 
{
	// Allow base class draw to operate
	Fl_Box::draw();
	// Draw the lines
}

bool Box::saved() 
{
	return !dirty;
}
// /////////////////////////////////////
//    		  VIEW
// /////////////////////////////////////
class View {
  public:
    View(Storage& store) : storage(store) { }
    string get_menu();
    string get_part_list();
    string get_head_list();
    string get_arm_list();
    string get_loco_list();
    string get_bat_list();
    string get_tor_list();
    string get_customer_list();
    string get_associate_list();
    string model_list();
 
    string get_help();
  private:
    Storage& storage;
};

string View::get_menu() {
    string menu = R"(
===============================
   Robo Lobo's Steely Deals
===============================

  Shop Manager
  ------------
  (1) Add Head
  (2) Add Locomoter
  (3) Add Arm
  (4) Add Battery
  (5) Add Torso
  (6) List all Parts

  Customer/Associate Manager
  -------
  (7) Add Customer
  (8) Add Associate
  (9) List all Customers
  (10) List all Associates

  Utility
  -------
  (11) Help
  (0) Exit 
  )";
    return menu;
}

string View::get_head_list() {
	string list = R"(
----------------------------
Catalog of Heads
----------------------------
)";

  if(storage.number_of_heads() > 0){
	  for(int i = 0; i < storage.number_of_heads(); ++i){
		list +=std::to_string(i) + ") " + storage.head_to_string(i) + '\n';
	  }
  }
  return list;
}

string View::get_arm_list() {
	string list = R"(
----------------------------
Catalog of Arms
----------------------------
)";

  if(storage.number_of_arms() > 0){
	  for(int i = 0; i < storage.number_of_arms(); ++i){
		list +=std::to_string(i) + ") " + storage.arm_to_string(i) + '\n';
	  }
  }
  return list;
}

string View::get_loco_list(){
	string list = R"(
----------------------------
Catalog of Locomotors
----------------------------
)";

  if(storage.number_of_locos() > 0){
	  for(int i = 0; i < storage.number_of_locos(); ++i){
		list +=std::to_string(i) + ") " + storage.loco_to_string(i) + '\n';
	  }
  }
  return list;
}
string View::model_list(){
	  
  string list = R"(
----------------------------
Catalog of Models
----------------------------
)";
  
  if(storage.number_of_mods() > 0){
	  for(int i = 0; i < storage.number_of_mods(); ++i){
		list +=std::to_string(i) + ") " + storage.model_to_string(i) + '\n';
	  }
  }
  
  return list;

}
string View::get_bat_list(){
	string list = R"(
----------------------------
Catalog of Batteries
----------------------------
)";

  if(storage.number_of_bats() > 0){
	  for(int i = 0; i < storage.number_of_bats(); ++i){
		list +=std::to_string(i) + ") " + storage.bat_to_string(i) + '\n';
	  }
  }
  return list;
}
string View::get_tor_list(){
	string list = R"(
----------------------------
Catalog of Torsos
----------------------------
)";

  if(storage.number_of_tors() > 0){
	  for(int i = 0; i < storage.number_of_tors(); ++i){
		list +=std::to_string(i) + ") " + storage.tor_to_string(i) + '\n';
	  }
  }
  return list;
}

string View::get_part_list() {
  
  string list = R"(
-----------------------
Catalog of Parts
-----------------------
)";
	
  /*for (int i=0; i<(storage.number_of_heads()+storage.number_of_locos()+storage.number_of_tors()+storage.number_of_arms()); ++i) {
    list += std::to_string(i) + ") " + storage.head_to_string(i)  +'\n'
		 + std::to_string(i) + ") " + storage.loco_to_string(i)  +'\n'
		 + std::to_string(i) + ") " + storage.tor_to_string(i)  +'\n'
		 + std::to_string(i) + ") " + storage.arm_to_string(i)  +'\n';
	}*/
  if(storage.number_of_heads() > 0){
	  for(int i = 0; i < storage.number_of_heads(); ++i){
		list +=std::to_string(i) + ") " + storage.head_to_string(i) + '\n';
	  }
  }
  
  if(storage.number_of_locos() > 0){
	  for(int i = 0; i < storage.number_of_locos(); ++i){
		list +=std::to_string(i) + ") " + storage.loco_to_string(i) + '\n';
	  }
  }
  
  if(storage.number_of_arms() > 0){
	  for(int i = 0; i < storage.number_of_arms(); ++i){
		list +=std::to_string(i) + ") " + storage.arm_to_string(i) + '\n';
	  }
  }
  if(storage.number_of_bats() > 0){
	  for(int i = 0; i < storage.number_of_bats(); ++i){
		list +=std::to_string(i) + ") " + storage.bat_to_string(i) + '\n';
	  }
  }
  

  if(storage.number_of_tors() > 0){
	  for(int i = 0; i < storage.number_of_tors(); ++i){
		list +=std::to_string(i) + ") " + storage.tor_to_string(i) + '\n';
	  }
  }
  if(storage.number_of_mods() > 0){
	  for(int i = 0; i < storage.number_of_mods(); ++i){
		list +=std::to_string(i) + ") " + storage.model_to_string(i) + '\n';
	  }
  }
  
  return list;

}
string View::get_customer_list() {
  string list = R"(
---------------------------
List of Robo Customers
---------------------------
)";
  for (int i=0; i<storage.number_of_customers(); ++i) {
    list += std::to_string(i) + ") " + storage.customer_to_string(i)  +'\n';
	}		
  return list;

}
string View::get_associate_list() {
  string list = R"(
---------------------------
List of Robo Associates
---------------------------
)";
  for (int i=0; i<storage.number_of_associates(); ++i) {
    list += std::to_string(i) + ") " + storage.associate_to_string(i)  +'\n';
	}
  return list;

}

string View::get_help() {
  return "Try harder.";
}

// /////////////////////////////////////
//    		  CONTROLLER 
// /////////////////////////////////////

class Controller {
  public:
    Controller (Storage& str, View& view) : storage(str), view(view) { }
    void gui();
    double get_double(string title, string prompt);
    int get_int(string title, string prompt);
    int get_int(string title, string prompt, int max_int);
    void cli();
    void execute_cmd(int cmd);
    string get_string(string title, string prompt);
  private:
    Storage& storage;
    
    View& view;
};
void Controller::gui() {
  Fl_JPEG_Image *jpg = new Fl_JPEG_Image("icon.jpg");
  string menu = view.get_menu() + "\nCommand: ";
  string no_label = "";
  int cmd = -1;
  while (cmd != 0) {
    fl_message_title("Robo Lobo's Steely Deals");
    fl_message_icon()->label(no_label.c_str());
    fl_message_icon()->labelsize(1);
    fl_message_icon()->image(*jpg);
    cmd = atoi(fl_input(menu.c_str(), 0));
    fl_message_icon()->image(0);
    execute_cmd(cmd);
  }
}

/*void Controller::cli() {
  int cmd = -1;
  while (cmd != 0) {
    cout << view.get_menu() << endl;
    cout << "Command: ";
    cin >> cmd;
    cin.ignore(); // consume \n
    execute_cmd(cmd);
  }
}*/
string Controller::get_string(string title, string prompt) {
  fl_message_title(title.c_str());
  fl_message_icon()->label("S");
  string result{fl_input(prompt.c_str(), 0)};
  return result;
}
int Controller::get_int(string title, string prompt) {
  int result;
  
   fl_message_title(title.c_str());
    fl_message_icon()->label("I");
    
    result = atoi(fl_input(prompt.c_str(), ""));
    fl_message_icon()->label("!");
  
  return result;
}

int Controller::get_int(string title, string prompt, int max_int) {
  string error = "Please enter an integer between 0 and " + max_int;
  int result;
  while(true) {
    fl_message_title(title.c_str());
    fl_message_icon()->label("I");
    result = atoi(fl_input(prompt.c_str(), 0));
    if (0 <= result && result <= max_int) break;
    fl_message_title("Invalid input");
    fl_message_icon()->label("!");
    fl_message(error.c_str());
  }
  return result;
}

double Controller::get_double(string title, string prompt) {
  double result;
  
    fl_message_title(title.c_str());
    fl_message_icon()->label("I");
    result = atof(fl_input(prompt.c_str(), ""));
    fl_message_icon()->label("!");
     
  
  return result;
}

void Controller::execute_cmd(int cmd) {
    if (cmd == 1 ) { // Add Head
    string name, description, image_filename;
    double cost = -1.0;
    double power = -1.0;
    int model_number = -1;
    name = get_string("Part", "Name: ");

    description = get_string(name, "Description: ");
    image_filename = get_string(name, "Image Filename: ");
    cost = get_double(name, "Cost of Part: ");
    power = get_double(name, "Total Power: ");
    model_number = get_int(name, "Model Number: ");
    Head *h1;
	h1 = new Head(name, description, image_filename, cost, model_number, power);
	storage.add_head(*h1);
    
   
    
    

 } else if (cmd == 2) { // Add Locomotor
    string name, description, image_filename;
    double cost = -1.0;
    double max_power = -1.0;
    int model_number = -1;
    
    
    name = get_string("Part", "Name: ");
    description = get_string(name, "Description: ");
    image_filename = get_string(name, "Image Filename: ");
    cost = get_double(name, "Cost of Part: ");
    max_power = get_double(name, "Total Max Power: ");
    model_number = get_int(name, "Model Number: ");
    
    Locomotor *l1;
	l1 = new Locomotor(name, description, image_filename, cost, model_number, max_power);
	storage.add_loco(*l1);

 }  else if (cmd == 3) { // Add Arm
    string name, description, image_filename;
    double cost = -1.0;
    double max_power = -1.0;
    int model_number = -1;
   
    
    name = get_string("Part", "Name: ");
    description = get_string(name, "Description: ");
    image_filename = get_string(name, "Image Filename: ");
    cost = get_double(name, "Cost of Part: ");
    max_power = get_double(name, "Total Max Power: ");
    model_number = get_int(name, "Model Number: ");
    
    Arm *a1;
	a1 = new Arm(name, description, image_filename, cost, model_number, max_power);
	storage.add_arm(*a1);

 }  else if (cmd == 4) { // Add Battery
    string name, description, image_filename;
    double cost = -1.0;
    double power_available = -1.0;
    double max_energy = -1.0;
    int model_number = -1;

    
    name = get_string("Part", "Name: ");
    description = get_string(name, "Description: ");
    image_filename = get_string(name, "Image Filename: ");
    cost = get_double(name, "Cost of Part: ");
    max_energy = get_double(name, "Max energy: ");
    power_available = get_double(name, "Total Power available: ");
    model_number = get_int(name, "Model Number: ");
    
    Battery *b1;
	b1 = new Battery(name, description, image_filename, cost, model_number, power_available, max_energy);
	storage.add_battery(*b1);

 }  
 else if (cmd == 5) { // Add Torso
    string name, description, image_filename;
    double cost = -1.0;
    int max_arms = -1; 
    int model_number = -1;
    int battery_compartments = -1;
    
    name = get_string("Part", "Name: ");
    description = get_string(name, "Description: ");
    image_filename = get_string(name, "Image Filename: ");
    cost = get_double(name, "Cost of Part: ");
    max_arms = get_int(name, "Max number of Arms: ");
    battery_compartments = get_int(name, "Number of Battery Compartments: ");
    model_number = get_int(name, "Model Number: ");
    
    Torso *t1;
	t1 = new Torso(name, description, image_filename, cost, model_number, max_arms, battery_compartments);
	storage.add_torso(*t1);

 } 
	else if (cmd == 6) { // List all parts
    string list = view.get_part_list();
    fl_message_title("List of All Parts");
    fl_message_icon()->label("P");
    fl_message(list.c_str());

 }  else if (cmd == 7) { // Add Customer
    string name, email_address; 
    int customer_number = -1, phone_number = -1;

    name = get_string("Customer", "Name: ");
    customer_number = get_int(name, "Customer Number: ");
    phone_number = get_int(name, "Phone Number: ");
    email_address = get_string(name, "Email Address: ");
    Customer *c1;
    c1 = new Customer(name, customer_number, phone_number, email_address);
    
    storage.add_customer(*c1);
    
    
 }  else if (cmd == 8) { // Add Associate
    string name;
    int employee_number = -1;

    name = get_string("Associate", "Name: ");
	employee_number = get_int(name, "Employee Number: ");
	Sales_associate *s1;
	s1 = new Sales_associate(name, employee_number);
	
    storage.add_associate(*s1);

 }  else if (cmd == 9) { // List all customers

    string list = view.get_customer_list();
    fl_message_title("List of All Customers");
    fl_message_icon()->label("C");
    fl_message(list.c_str());
    

 }	else if (cmd == 10) { // List all associates
    
	string list = view.get_associate_list();
    fl_message_title("List of All Associates");
    fl_message_icon()->label("A");
    fl_message(list.c_str());
    
 }	else if (cmd == 12) { // Create a Model

	int head, loco, bat, arm, tor;
	string prompt = view.get_part_list();
    fl_message_title("List of All Parts");
    fl_message_icon()->label("C");
    fl_message(prompt.c_str());
	string name;
	name = get_string("Robot Model", "Name: ");
	
	prompt = view.get_head_list() + "\n Head Number: ";
	head = get_int("Select a Head", prompt, storage.number_of_heads() - 1);
	
	prompt = view.get_loco_list() + "\n Locomotor Number: ";
	loco = get_int("Select a Locomotor", prompt, storage.number_of_locos() - 1);
	
	prompt = view.get_tor_list() + "\n Torso Number: ";
	tor = get_int("Select a Torso", prompt, storage.number_of_tors() - 1);

	
	prompt = view.get_arm_list() + "\n Arm Number: ";
	arm = get_int("Select an Arm", prompt, storage.number_of_arms() - 1);

	
	prompt = view.get_bat_list() + "\n Battery Number: ";
	bat = get_int("Select a Battery", prompt, storage.number_of_bats() - 1);
	
	
	
	Robot_model *r1;
	r1 = new Robot_model(name, storage.return_head(head), storage.return_loco(loco), storage.return_tor(tor), storage.return_arm(arm), storage.return_bat(bat));
	storage.add_model(*r1);
	
	
	
	
 } else if (cmd == 13) { // List all models
    
	string list = view.model_list();
    fl_message_title("Catalog of Models");
    fl_message_icon()->label("A");
    fl_message(list.c_str());
    
 }	else if (cmd == 11) { // Help
    string help = view.get_help();
    fl_message_title("Help");
    fl_message_icon()->label("H");
    fl_message(help.c_str());
 }  else if (cmd == 0) { // Exit
 }  else {
    cerr << "**** Invalid command - type 9 for help" << endl << endl;
 }
}


// /////////////////////////////////////
//        	Callbacks
// /////////////////////////////////////
Fl_Window *win;
Fl_Menu_Bar *menubar;
Box *box;
Storage storage;
View view{storage};
Controller controller(storage, view);
void B1(Fl_Widget* w, void* p)
{
	controller.execute_cmd(1);
}
void B2(Fl_Widget* w, void* p)
{
	controller.execute_cmd(2);
}
void B3(Fl_Widget* w, void* p)
{
	controller.execute_cmd(3);
}
void B4(Fl_Widget* w, void* p)
{
	controller.execute_cmd(4);
}
void B5(Fl_Widget* w, void* p)
{
	controller.execute_cmd(5);
}
void B6(Fl_Widget* w, void* p)
{
	controller.execute_cmd(6);
}
void B7(Fl_Widget* w, void* p)
{
	controller.execute_cmd(7);
}
void B8(Fl_Widget* w, void* p)
{
	controller.execute_cmd(8);
}
void B9(Fl_Widget* w, void* p)
{
	controller.execute_cmd(9);
}
void B10(Fl_Widget* w, void* p)
{
	controller.execute_cmd(10);
}
void B11(Fl_Widget* w, void* p)
{
	controller.execute_cmd(11);
}
void B12(Fl_Widget* w, void* p)
{
	controller.execute_cmd(12);
}
void B13(Fl_Widget* w, void* p)
{
	controller.execute_cmd(13);
}
void B0(Fl_Widget* w, void* p)
{
	controller.execute_cmd(0);
}
void CloseCB(Fl_Widget* w, void* p) 
{
	int selection = 1;
	if (!box->saved()) 
	{
		selection = fl_choice("Unsaved Robo. Exit anyway?", fl_no, fl_yes, 0);
	}
	if (selection == 1) 
	{
		win->hide();
	}
}
// /////////////////////////////////////
//        	M E N U 	I T E M S
// /////////////////////////////////////
Fl_Menu_Item menuitems[] = {
{ "&File", 0, 0, 0, FL_SUBMENU },
{ "&Quit", FL_ALT + 'q', (Fl_Callback *)CloseCB },
{ 0 },
{ "&Create/List", 0, 0, 0, FL_SUBMENU },
{ "&Head", 0,(Fl_Callback *)B1  },
{ "&Locomotor", 0,(Fl_Callback *)B2  },
{ "&Arm", 0,(Fl_Callback *)B3  },
{ "&Battery", 0,(Fl_Callback *)B4  },
{ "&Torso", 0,(Fl_Callback *)B5  },
{ "&Model", 0,(Fl_Callback *)B12  },
{ "&List All Parts", 0, (Fl_Callback *)B6  },
{ "&List All models", 0, (Fl_Callback *)B13  },
{ 0 },
{ "&Customer", 0, 0, 0, FL_SUBMENU },
{ "&Add", 0, (Fl_Callback *)B7  },
{ "&List All", 0, (Fl_Callback *)B9  },
{ 0 },
{ "&Sales Associate", 0, 0, 0, FL_SUBMENU },
{ "&Add", 0, (Fl_Callback *)B8  },
{ "&List All", 0, (Fl_Callback *)B10  },
{ 0 },
{ "&Help", 0, 0, 0, FL_SUBMENU },
{ "&Help Info", 0, (Fl_Callback *)B11  },
{ 0 },


{ 0 }
};
// /////////////////////////////////////
//              MAIN
// /////////////////////////////////////

int main() {
  
  
  fl_register_images();
  const int X = 640;
  const int Y = 480;
  win = new Fl_Window{X, Y, "Robo Lobo's Steely Deals"};
	
	// Install menu bar
	menubar = new Fl_Menu_Bar(0, 0, X, 30);
	menubar->menu(menuitems);
	
	// Create a view (a canvas on which to draw)
	box = new Box{0, 00, X, Y};
	
	// Sign up for callback
	win->callback(CloseCB, box);
	
	// Enable resizing
	win->resizable(*box);
	
	// Wrap it up and let FLTK do its thing
	win->end();
	win->show();
  /*controller.gui();*/
  
  Storage storage;
  
  View view{storage};
  Controller controller(storage, view);
  
  return(Fl::run());
  //controller.cli();
}

