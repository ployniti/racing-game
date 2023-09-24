//This is the code to implement the base vehicle class and derived classes in the hierarchy

#include "vehicle.h"

/*VEHICLE*/
//Default constructor
vehicle::vehicle():name(nullptr), max_speed(0), current_speed(0), off_road(false), seats(0)
{
}

//Constructor with arguments
vehicle::vehicle(const char * input, int max_s, int current_s, bool off_r, int num):
                max_speed(max_s), current_speed(current_s), off_road(off_r), seats(num) 
{
    if (input)
    {
        name = new char [strlen(input)+1];
        strcpy(name,input);
    }
    else
        name = nullptr;
}

//Copy constructor
vehicle::vehicle(const vehicle & src):name(nullptr)
{
    copy(src);
}

//Assignment operator
vehicle & vehicle::operator=(const vehicle & src)
{
    if (this == &src) return *this;

    if (name)
        delete [] name;

    copy(src);

    return *this;
}

//This is the copy function to perform a deep copy of a vehicle object
//Argument: vehicle object
//Return: void
void vehicle::copy(const vehicle & src)
{
    if (!src.name) return;

    name = new char [strlen(src.name)+1];
    strcpy(name, src.name);

    max_speed = src.max_speed;
    current_speed = src.current_speed;
    off_road = src.off_road;
    seats = src.seats;
}

//Destructor
vehicle::~vehicle()
{
    if (name)
    {
        delete [] name;
        name = nullptr;
    }

    max_speed = 0;
    current_speed = 0;
    off_road = false;
    seats = 0;
}

//This is the function to return the name of the vehicle
//Argument: none
//Return: char ptr
char * vehicle::get_name() const
{
    return name;
}

//This is the function to return the current speed of the vehicle
//Argument: none
//Return: int
int vehicle::get_speed() const
{
    return current_speed;
}

//Overloaded <<, this function displays the info of a vehicle
//Arguments: ostream object and a vehicle object
//Return: ostream object
ostream & operator<<(ostream & cout, const vehicle & a_vehicle)
{
    empty_name empty;
    
    if (!a_vehicle.display(cout))
        throw (empty);

    return cout;
}

//This is a display function to display the info of a vehicle
//Argument: ostream object
//Return: int 
int vehicle::display(ostream & cout) const
{
    if (!name)
        return 0;
    
    cout << name;

    return 1;
}

//This function displays the vehicle's stat in a formatted way
//Argument: none
//Return: void
void vehicle::display_stat() const
{
    cout << "Max speed: " << max_speed << endl
         << "Seats: " << seats << endl;

    if (off_road)
        cout << "Off road: Yes" << endl;
    else
        cout << "Off road: No" << endl;
}

//This function displays the vehicle's current speed in a formatted way
//Argument: none
//Return: void
void vehicle::display_current_speed() const
{
    cout << "Current speed: " << current_speed;
}

//Overloaded >>, this function to set the vehicle's name
//Arguments: istream object and a vehicle object
//Return: istream object
istream & operator>>(istream & cin, vehicle & a_vehicle)
{
    error_set_name error;

    if (!a_vehicle.set_name(cin))
        throw (error);
    
    return cin;
}

//This is the function to set the vehicle's name
//Argument: istream object
//Return: int, 1 for success, 0 for failure
int vehicle::set_name(istream & cin)
{
    char temp[SIZE];
    cin.get(temp, SIZE, '\n');

    if (name)
        delete [] name;

    name = new char [strlen(temp)+1];
    strcpy(name, temp);
    return 1;
}

//Overloaded ==, this compares the current speed of the car
//Arguments: two vehicle objects
//Return: bool
bool operator==(const vehicle & v1, const vehicle & v2)
{
    return v1.speed_eq(v2.current_speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a vehicle object and an int
//Return: bool
bool operator==(const vehicle & v1, const int & speed)
{
    return v1.speed_eq(speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a vehicle object and an int
//Return: bool
bool operator==(const int & speed, const vehicle & v1)
{
    return v1.speed_eq(speed);
}

//This function compares if the max speed of the vehicles are equal
//Argument: vehicle object
//Return: bool
bool vehicle::speed_eq(const int & speed) const
{
    return current_speed == speed;
}

//Overloaded ==, this compares the current speed of the car
//Arguments: two vehicle objects
//Return: bool
bool operator!=(const vehicle & v1, const vehicle & v2)
{
    return v1.speed_not_eq(v2.current_speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a vehicle object and an int
//Return: bool
bool operator!=(const vehicle & v1, const int & speed)
{
    return v1.speed_not_eq(speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a vehicle object and an int
//Return: bool
bool operator!=(const int & speed, const vehicle & v1)
{
    return v1.speed_not_eq(speed);
}

//This function compares if the max speed of the vehicles are NOT equal
//Argument: vehicle object
//Return: bool
bool vehicle::speed_not_eq(const int & speed) const
{
    return current_speed != speed;
}

//Overloaded +, increase the current speed of the vehicle
//Argument: vehicle object and an int for the adding speed
//Return: vehicle object
vehicle operator+(const vehicle & a_vehicle, const int & speed)
{
    exceed_max max;

    vehicle temp(a_vehicle); //create a temp for vehicle

    if (!temp.increase_speed(speed))
        throw (max);

    return temp;
}

//This is the function to increase the current speed of the car if it won't exceed the max speed
//Argument: int for the speed
//Return: int, 1 for success, 0 for failure
int vehicle::increase_speed(const int & speed)
{
    //Check if adding the speed would exceed the max_speed
    int temp = current_speed + speed;

    if (temp <= max_speed) //within limit
    {
        current_speed = temp;
        return 1;
    }

    return 0;
}

//Overloaded +=, increase the current speed of the vehicle
//Argument: int for the adding speed
//Return: vehicle object
vehicle & vehicle::operator+=(const int & speed)
{
    exceed_max max;

    //Check if adding the speed would exceed the max_speed
    int temp = current_speed + speed;

    if (temp <= max_speed) //within limit
        current_speed = temp;
    else
        throw (max);

    return *this;
}

//Overloaded <, compare the current speed of the vehicle
//Argument: two vehicle objects
//Return: bool
bool operator<(const vehicle & v1, const vehicle & v2)
{
    return v1.less_than(v2);
}

//This function compares if the current speed of v1 is less than v2
//Argument: vehicle object
//Return: bool
bool vehicle::less_than(const vehicle & v2) const
{
    return current_speed < v2.current_speed;
}

//Overloaded <=, compare the current speed of the vehicle
//Argument: two vehicle objects
//Return: bool
bool operator<=(const vehicle & v1, const vehicle & v2)
{
    return v1.less_than_eq(v2);
}

//This function compares if the current speed of v1 is less than or equal to v2
//Argument: vehicle object
//Return: bool
bool vehicle::less_than_eq(const vehicle & v2) const
{
    return current_speed <= v2.current_speed;
}

//Overloaded >, compare the current speed of the vehicle
//Argument: two vehicle objects
//Return: bool
bool operator>(const vehicle & v1, const vehicle & v2)
{
    return v1.greater_than(v2);
}

//This function compares if the current speed of v1 is greater than v2
//Argument: vehicle object
//Return: bool
bool vehicle::greater_than(const vehicle & v2) const
{
    return current_speed > v2.current_speed;
}

//Overloaded >=, compare the current speed of the vehicle
//Argument: two vehicle objects
//Return: bool
bool operator>=(const vehicle & v1, const vehicle & v2)
{
    return v1.greater_than_eq(v2);
}

//This function compares if the current speed of v1 is greater than or equal to v2
//Argument: vehicle object
//Return: bool
bool vehicle::greater_than_eq(const vehicle & v2) const
{
    return current_speed >= v2.current_speed;
}

/*SUPERCAR*/
//Default constructor
supercar::supercar():vehicle(), turbo_mode(nullptr) 
{
}

//Constructor with arguments
supercar::supercar(const char * name, int max_s, int current_s, bool off_r, int seats):
                   vehicle(name, max_s, current_s, off_r, seats), turbo_mode(nullptr)
{
}

//Copy constructor
supercar::supercar(const supercar & src):vehicle(src), turbo_mode(nullptr)
{
    copy(src);
}

//Assignment operator
supercar & supercar::operator=(const supercar & src)
{
    if (this == &src)
        return *this;

    if (turbo_mode)
        delete [] turbo_mode;

    vehicle::operator=(src);

    copy(src);

    return *this;
}

//This is the copy function to perform a deep copy of a supercar object
//Argument: supercar object
//Return: void
void supercar::copy(const supercar & src)
{
    if (!src.turbo_mode) return;  

    turbo_mode = new char [strlen(src.turbo_mode)+1];
    strcpy(turbo_mode, src.turbo_mode);
}

//Destructor
supercar::~supercar()
{
    if (turbo_mode)
    {
        delete [] turbo_mode;
        turbo_mode = nullptr;
    }
}

//Overloaded <<, this function displays the info of a supercar
//Arguments: ostream object and a supercar object
//Return: ostream object
ostream & operator<<(ostream & cout, const supercar & a_car)
{
    empty_name empty;

    if (!a_car.display(cout))
        throw (empty);

    return cout;
}

//This is a display function to display the info of a supercar
//Argument: ostream object
//Return: int 
int supercar::display(ostream & cout) const
{
    int count = vehicle::display(cout);
    
    return count;
}

//This function displays the vehicle's stat in a formatted way
//Argument: none
//Return: void
void supercar::display_stat() const
{
    vehicle::display_stat();

    if (turbo_mode)
        cout << "Turbo mode: " << turbo_mode << endl;
}

//Overloaded >>, this function to set the vehicle's name
//Arguments: istream object and a vehicle object
//Return: istream object
istream & operator>>(istream & cin, supercar & a_car)
{
    error_set_name error;

    if (!a_car.set_name(cin))
        throw (error);
    
    return cin;
}

//This is the function to set the vehicle's name
//Argument: istream object
//Return: int, 1 for success, 0 for failure
int supercar::set_name(istream & cin)
{
    return vehicle::set_name(cin);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: two supercar objects
//Return: bool
bool operator==(const supercar & v1, const supercar & v2)
{
    return v1.speed_eq(v2.current_speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a supercar object and an int
//Return: bool
bool operator==(const supercar & v1, const int & speed)
{
    return v1.speed_eq(speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a supercar object and an int
//Return: bool
bool operator==(const int & speed, const supercar & v1)
{
    return v1.speed_eq(speed);
}

//This function compares if the max speed of the supercars are equal
//Argument: supercar object
//Return: bool
bool supercar::speed_eq(const int & speed) const
{
    return vehicle::speed_eq(speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: two supercar objects
//Return: bool
bool operator!=(const supercar & v1, const supercar & v2)
{
    return v1.speed_not_eq(v2.current_speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a supercar object and an int
//Return: bool
bool operator!=(const supercar & v1, const int & speed)
{
    return v1.speed_not_eq(speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a supercar object and an int
//Return: bool
bool operator!=(const int & speed, const supercar & v1)
{
    return v1.speed_not_eq(speed);
}

//This function compares if the max speed of the supercars are NOT equal
//Argument: supercar object
//Return: bool
bool supercar::speed_not_eq(const int & speed) const
{
    return vehicle::speed_not_eq(speed);
}

//Overloaded +, increase the current speed of the supercar
//Argument: supercar object and an int for the adding speed
//Return: supercar object
supercar operator+(const supercar & a_car, const int & speed)
{
    exceed_max max;

    supercar temp(a_car); //create a temp for supercar

    if (!temp.increase_speed(speed))
        throw (max);

    return temp;
}

//This is the function to increase the current speed of the car if it won't exceed the max speed
//Argument: int for the speed
//Return: int, 1 for success, 0 for failure
int supercar::increase_speed(const int & speed)
{
    return vehicle::increase_speed(speed);
}

//Overloaded <, compare the current speed of the supercar
//Argument: two supercar objects
//Return: bool
bool operator<(const supercar & v1, const supercar & v2)
{
    return v1.less_than(v2);
}

//This function compares if the current speed of v1 is less than v2
//Argument: supercar object
//Return: bool
bool supercar::less_than(const supercar & v2) const
{
    return vehicle::less_than(v2);
}

//Overloaded <=, compare the current speed of the supercar
//Argument: two supercar objects
//Return: bool
bool operator<=(const supercar & v1, const supercar & v2)
{
    return v1.less_than_eq(v2);
}

//This function compares if the current speed of v1 is less than or equal to v2
//Argument: supercar object
//Return: bool
bool supercar::less_than_eq(const supercar & v2) const
{
    return vehicle::less_than_eq(v2);
}

//Overloaded >, compare the current speed of the supercar
//Argument: two supercar objects
//Return: bool
bool operator>(const supercar & v1, const supercar & v2)
{
    return v1.greater_than(v2);
}

//This function compares if the current speed of v1 is greater than v2
//Argument: supercar object
//Return: bool
bool supercar::greater_than(const supercar & v2) const
{
    return vehicle::greater_than(v2);
}

//Overloaded >=, compare the current speed of the supercar
//Argument: two supercar objects
//Return: bool
bool operator>=(const supercar & v1, const supercar & v2)
{
    return v1.greater_than_eq(v2);
}

//This function compares if the current speed of v1 is greater than or equal to v2
//Argument: supercar object
//Return: bool
bool supercar::greater_than_eq(const supercar & v2) const
{
    return vehicle::greater_than_eq(v2);
}

//This function sets the supercar's turbo_mode
//Argument: none
//Return: int, 1 for success, 0 for failure
int supercar::set_turbo()
{
    char input[SIZE];

    cout << "What turbo mode would you like to set for " << name << "? ";
    cin.get(input, SIZE, '\n');
    cin.ignore(SIZE, '\n');

    if (!input) return 0;

    if (turbo_mode)
        delete [] turbo_mode;

    turbo_mode = new char [strlen(input)+1];
    strcpy(turbo_mode, input);

    return 1;
}

/*TOURING_CAR*/
//Default constructor
touring_car::touring_car():horn(0)
{
}

//Constructor with arguments
touring_car::touring_car(const char * name, int max_s, int current_s, bool off_r, int seats):
                         vehicle(name, max_s, current_s, off_r, seats), horn(0)
{
}

//Destructor
touring_car::~touring_car()
{
    body_style.clear();
    horn = 0;
}

//Overloaded <<, this function displays the info of a touring_car
//Arguments: ostream object and a touring_car object
//Return: ostream object
ostream & operator<<(ostream & cout, const touring_car & a_car)
{
    empty_name empty;

    if (!a_car.display(cout))
        throw (empty);

    return cout;
}

//This is a display function to display the info of a touring_car
//Argument: ostream object
//Return: int 
int touring_car::display(ostream & cout) const
{
    int count = vehicle::display(cout);

    return count;
}

//This function displays the vehicle's stat in a formatted way
//Argument: none
//Return: void
void touring_car::display_stat() const
{
    vehicle::display_stat();

    if (!body_style.empty())
        cout << "Body style: " << body_style << endl;
    
    cout << "Horn: " << horn << endl;
}

//Overloaded >>, this function to set the vehicle's name
//Arguments: istream object and a vehicle object
//Return: istream object
istream & operator>>(istream & cin, touring_car & a_car)
{
    error_set_name error;
    
    if (!a_car.set_name(cin))
        throw (error);
    
    return cin;
}

//This is the function to set the vehicle's name
//Argument: istream object
//Return: int, 1 for success, 0 for failure
int touring_car::set_name(istream & cin)
{
    return vehicle::set_name(cin);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: two touring_car objects
//Return: bool
bool operator==(const touring_car & v1, const touring_car & v2)
{
    return v1.speed_eq(v2.current_speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a touring_car and an int
//Return: bool
bool operator==(const touring_car & v1, const int & speed)
{
    return v1.speed_eq(speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a touring_car and an int
//Return: bool
bool operator==(const int & speed, const touring_car & v1)
{
    return v1.speed_eq(speed);
}

//This function compares if the max speed of the touring_cars are equal
//Argument: touring_car object
//Return: bool
bool touring_car::speed_eq(const int & speed) const
{
    return vehicle::speed_eq(speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: two touring_car objects
//Return: bool
bool operator!=(const touring_car & v1, const touring_car & v2)
{
    return v1.speed_not_eq(v2.current_speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a touring_car object and an int
//Return: bool
bool operator!=(const touring_car & v1, const int & speed)
{
    return v1.speed_not_eq(speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a touring_car object and an int
//Return: bool
bool operator!=(const int & speed, const touring_car & v1)
{
    return v1.speed_not_eq(speed);
}

//This function compares if the max speed of the touring_cars are NOT equal
//Argument: touring_car object
//Return: bool
bool touring_car::speed_not_eq(const int & speed) const
{
    return vehicle::speed_not_eq(speed);
}

//Overloaded +, increase the current speed of the touring_car
//Argument: touring_car object and an int for the adding speed
//Return: touring_car object
touring_car operator+(const touring_car & a_car, const int & speed)
{
    exceed_max max;

    touring_car temp(a_car); //create a temp for touring_car

    if (!temp.increase_speed(speed))
        throw (max);

    return temp;
}

//This is the function to increase the current speed of the car if it won't exceed the max speed
//Argument: int for the speed
//Return: int, 1 for success, 0 for failure
int touring_car::increase_speed(const int & speed)
{
    return vehicle::increase_speed(speed);
}

//Overloaded <, compare the current speed of the touring_car
//Argument: two touring_car objects
//Return: bool
bool operator<(const touring_car & v1, const touring_car & v2)
{
    return v1.less_than(v2);
}

//This function compares if the current speed of v1 is less than v2
//Argument: touring_car object
//Return: bool
bool touring_car::less_than(const touring_car & v2) const
{
    return vehicle::less_than(v2);
}

//Overloaded <=, compare the current speed of the touring_car
//Argument: two touring_car objects
//Return: bool
bool operator<=(const touring_car & v1, const touring_car & v2)
{
    return v1.less_than_eq(v2);
}

//This function compares if the current speed of v1 is less than or equal to v2
//Argument: touring_car object
//Return: bool
bool touring_car::less_than_eq(const touring_car & v2) const
{
    return vehicle::less_than_eq(v2);
}

//Overloaded >, compare the current speed of the touring_car
//Argument: two touring_car objects
//Return: bool
bool operator>(const touring_car & v1, const touring_car & v2)
{
    return v1.greater_than(v2);
}

//This function compares if the current speed of v1 is greater than v2
//Argument: touring_car object
//Return: bool
bool touring_car::greater_than(const touring_car & v2) const
{
    return vehicle::greater_than(v2);
}

//Overloaded >=, compare the current speed of the touring_car
//Argument: two touring_car objects
//Return: bool
bool operator>=(const touring_car & v1, const touring_car & v2)
{
    return v1.greater_than_eq(v2);
}

//This function compares if the current speed of v1 is greater than or equal to v2
//Argument: touring_car object
//Return: bool
bool touring_car::greater_than_eq(const touring_car & v2) const
{
    return vehicle::greater_than_eq(v2);
}

//This is the function to set the body_style of the touring car
//Argument: none
//Return: int, 1 for success, 0 for failure
int touring_car::set_body_style()
{
    if (!body_style.empty())
        body_style.clear();
    
    cout << "What body style would you like for " << name << "? ";
    getline(cin, body_style);

    return 1;
}

//This is the function to set the volume of the horn
//Argument: none
//Return: int, 1 for success, 0 for failure
int touring_car::honk()
{
    cout << "How loud would you like to honk? ";
    cin >> horn;
    cin.ignore(100, '\n');
    
    return 1;
}

/*BUGGIES*/
//Default constructor
buggies::buggies()
{
}

//Constructor with arguments
buggies::buggies(const char * name, int max_s, int current_s, bool off_r, int seats):
                         vehicle(name, max_s, current_s, off_r, seats)
{
}

//Destructor
buggies::~buggies()
{
    frame_type.clear();
}

//Overloaded <<, this function displays the info of a buggies
//Arguments: ostream object and a buggies object
//Return: ostream object
ostream & operator<<(ostream & cout, const buggies & a_car)
{
    empty_name empty;

    if (!a_car.display(cout))
        throw (empty);

    return cout;
}

//This is a display function to display the info of a buggies
//Argument: ostream object
//Return: int 
int buggies::display(ostream & cout) const
{
    int count = vehicle::display(cout);
    
    return count;
}

//This function displays the vehicle's stat in a formatted way
//Argument: none
//Return: void
void buggies::display_stat() const
{
    vehicle::display_stat();

    if (!frame_type.empty())
        cout << "Frame type: " << frame_type << endl;
}

//Overloaded >>, this function to set the vehicle's name
//Arguments: istream object and a vehicle object
//Return: istream object
istream & operator>>(istream & cin, buggies & a_car)
{
    error_set_name error;
    
    if (!a_car.set_name(cin))
        throw (error);
    
    return cin;
}

//This is the function to set the vehicle's name
//Argument: istream object
//Return: int, 1 for success, 0 for failure
int buggies::set_name(istream & cin)
{
    return vehicle::set_name(cin);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: two buggies objects
//Return: bool
bool operator==(const buggies & v1, const buggies & v2)
{
    return v1.speed_eq(v2.current_speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a buggies object and an int
//Return: bool
bool operator==(const buggies & v1, const int & speed)
{
    return v1.speed_eq(speed);
}

//Overloaded ==, this compares the current speed of the car
//Arguments: a buggies object and an int
//Return: bool
bool operator==(const int & speed, const buggies & v1)
{
    return v1.speed_eq(speed);
}

//This function compares if the current speed of the buggiess are equal
//Argument: buggies object
//Return: bool
bool buggies::speed_eq(const int & speed) const
{
    return vehicle::speed_eq(speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: two buggies objects
//Return: bool
bool operator!=(const buggies & v1, const buggies & v2)
{
    return v1.speed_not_eq(v2.current_speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a buggies object and an int
//Return: bool
bool operator!=(const buggies & v1, const int & speed)
{
    return v1.speed_not_eq(speed);
}

//Overloaded !=, this compares the current speed of the car
//Arguments: a buggies object and an int
//Return: bool
bool operator!=(const int & speed, const buggies & v1)
{
    return v1.speed_not_eq(speed);
}

//This function compares if the current speed of the buggiess are NOT equal
//Argument: buggies object
//Return: bool
bool buggies::speed_not_eq(const int & speed) const
{
    return vehicle::speed_not_eq(speed);
}

//Overloaded +, increase the current speed of the buggies
//Argument: buggies object and an int for the adding speed
//Return: buggies object
buggies operator+(const buggies & a_car, const int & speed)
{
    exceed_max max;

    buggies temp(a_car); //create a temp for buggies

    if (!temp.increase_speed(speed))
        throw (max);

    return temp;
}

//This is the function to increase the current speed of the car if it won't exceed the max speed
//Argument: int for the speed
//Return: int, 1 for success, 0 for failure
int buggies::increase_speed(const int & speed)
{
    return vehicle::increase_speed(speed);
}

//Overloaded <, compare the current speed of the buggies
//Argument: two buggies objects
//Return: bool
bool operator<(const buggies & v1, const buggies & v2)
{
    return v1.less_than(v2);
}

//This function compares if the current speed of v1 is less than v2
//Argument: buggies object
//Return: bool
bool buggies::less_than(const buggies & v2) const
{
    return vehicle::less_than(v2);
}

//Overloaded <=, compare the current speed of the buggies
//Argument: two buggies objects
//Return: bool
bool operator<=(const buggies & v1, const buggies & v2)
{
    return v1.less_than_eq(v2);
}

//This function compares if the current speed of v1 is less than or equal to v2
//Argument: buggies object
//Return: bool
bool buggies::less_than_eq(const buggies & v2) const
{
    return vehicle::less_than_eq(v2);
}

//Overloaded >, compare the current speed of the buggies
//Argument: two buggies objects
//Return: bool
bool operator>(const buggies & v1, const buggies & v2)
{
    return v1.greater_than(v2);
}

//This function compares if the current speed of v1 is greater than v2
//Argument: buggies object
//Return: bool
bool buggies::greater_than(const buggies & v2) const
{
    return vehicle::greater_than(v2);
}

//Overloaded >=, compare the current speed of the buggies
//Argument: two buggies objects
//Return: bool
bool operator>=(const buggies & v1, const buggies & v2)
{
    return v1.greater_than_eq(v2);
}

//This function compares if the current speed of v1 is greater than or equal to v2
//Argument: buggies object
//Return: bool
bool buggies::greater_than_eq(const buggies & v2) const
{
    return vehicle::greater_than_eq(v2);
}

//This is the function to set the frame_type for a buggies
//Argument: none
//Return: int, 1 for success, 0 for failure
int buggies::set_frame_type()
{
    if (!frame_type.empty())
        frame_type.clear();
    
    cout << "What frame type would you like for " << name << "? ";
    getline(cin, frame_type);

    return 1;
}
