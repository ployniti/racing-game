//This is the .h file for the vehicle base class and the derived vehicle classes

#pragma once
#include "main.h"

//Exception handling structs
struct empty_name
{
    string msg {"Name is empty."};
};

struct error_set_name
{
    string msg {"Error setting name."};
};

struct exceed_max
{
    string msg {"Exceeding max speed."};
};

//Classes
class vehicle
{
    public:
        vehicle();
        vehicle(const char * input, int max_s, int current_s, bool off_r, int seats);
        vehicle(const vehicle & src);
        vehicle & operator=(const vehicle & src);
        ~vehicle();
        
        char * get_name() const;
        int get_speed() const;
        void display_stat() const;
        void display_current_speed() const;
        
        //Non-member Operators (not inherited!)
        friend bool operator==(const vehicle & v1, const vehicle & v2); //compare the vehicle's current speed
        friend bool operator==(const vehicle & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator==(const int & speed, const vehicle & v1); //compare the vehicle's current speed
        friend bool operator!=(const vehicle & v1, const vehicle & v2); //compare the vehicle's current speed
        friend bool operator!=(const vehicle & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator!=(const int & speed, const vehicle & v1); //compare the vehicle's current speed
        
        friend vehicle operator+(const vehicle & a_vehicle, const int & speed); //increase speed
        
        friend bool operator<(const vehicle & v1, const vehicle & v2); //compare vehicle's current speed
        friend bool operator<=(const vehicle & v1, const vehicle & v2); //compare vehicle's current speed
        friend bool operator>(const vehicle & v1, const vehicle & v2); //compare vehicle's current speed
        friend bool operator>=(const vehicle & v1, const vehicle & v2); //compare vehicle's current speed

        friend ostream & operator<<(ostream & cout, const vehicle & a_vehicle); //display the vehicle's stats
        friend istream & operator>>(istream & cin, vehicle & a_vehicle); //set the vehicle's name
        
        //Member operators
        vehicle & operator+=(const int & speed); //increase speed

    protected:
        char * name;
        int max_speed; //mph
        int current_speed; //mph
        bool off_road; //can go off road, true or false
        int seats;

        int display(ostream & cout) const;
        int set_name(istream & cin);
        bool greater_than(const vehicle & v2) const;
        bool greater_than_eq(const vehicle & v2) const;
        bool less_than(const vehicle & v2) const;
        bool less_than_eq(const vehicle & v2) const;
        //bool max_speed_not_eq(const vehicle & v2) const;
        //bool max_speed_eq(const vehicle & v2) const;
        bool speed_not_eq(const int & speed) const;
        bool speed_eq(const int & speed) const;
        int increase_speed(const int & speed);

    private:
        void copy(const vehicle & src);
};

class supercar : public vehicle
{
    public:
        supercar();
        supercar(const char * name, int max_s=400, int current_s=0, bool off_r=false, int seats=2);
        ~supercar();
        supercar(const supercar & src);
        supercar & operator=(const supercar & src);

        int set_turbo();
        void display_stat() const;
        
        //Non-member operators
        friend bool operator==(const supercar & v1, const supercar & v2); //compare the vehicle's current speed
        friend bool operator==(const supercar & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator==(const int & speed, const supercar & v1); //compare the vehicle's current speed
        friend bool operator!=(const supercar & v1, const supercar & v2); //compare the vehicle's current speed
        friend bool operator!=(const supercar & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator!=(const int & speed, const supercar & v1); //compare the vehicle's current speed
        
        friend supercar operator+(const supercar & v1, const int & speed); //increase speed
        
        friend bool operator<(const supercar & v1, const supercar & v2); //compare vehicle's current speed
        friend bool operator<=(const supercar & v1, const supercar & v2); //compare vehicle's current speed
        friend bool operator>(const supercar & v1, const supercar & v2); //compare vehicle's current speed
        friend bool operator>=(const supercar & v1, const supercar & v2); //compare vehicle's current speed
        
        friend ostream & operator<<(ostream & cout, const supercar & a_car);
        friend istream & operator>>(istream & cin, supercar & a_car);
        
    private:
        char * turbo_mode; //"high" etc.
        
        void copy(const supercar & src);
        int display(ostream & cout) const;
        int set_name(istream & cin);
        bool greater_than(const supercar & v2) const;
        bool greater_than_eq(const supercar & v2) const;
        bool less_than(const supercar & v2) const;
        bool less_than_eq(const supercar & v2) const;
        //bool max_speed_not_eq(const supercar & v2) const;
        //bool max_speed_eq(const supercar & v2) const;
        bool speed_not_eq(const int & speed) const;
        bool speed_eq(const int & speed) const;
        int increase_speed(const int & speed);
};

class touring_car : public vehicle
{
    public:
        touring_car();
        touring_car(const char * name, int max_s=35, int current_s=0, bool off_r=false, int seats=4);
        ~touring_car();
        
        int set_body_style();
        int honk();
        void display_stat() const;
        
        //Non-member operators
        friend bool operator==(const touring_car & v1, const touring_car & v2); //compare the vehicle's current speed
        friend bool operator==(const touring_car & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator==(const int & speed, const touring_car & v1); //compare the vehicle's current speed
        friend bool operator!=(const touring_car & v1, const touring_car & v2); //compare the vehicle's current speed
        friend bool operator!=(const touring_car & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator!=(const int & speed, const touring_car & v1); //compare the vehicle's current speed
        
        friend touring_car operator+(const touring_car & v1, const int & speed); //increase speed
        
        friend bool operator<(const touring_car & v1, const touring_car & v2); //compare vehicle's current speed
        friend bool operator<=(const touring_car & v1, const touring_car & v2); //compare vehicle's current speed
        friend bool operator>(const touring_car & v1, const touring_car & v2); //compare vehicle's current speed
        friend bool operator>=(const touring_car & v1, const touring_car & v2); //compare vehicle's current speed
        
        friend ostream & operator<<(ostream & cout, const touring_car & a_car);
        friend istream & operator>>(istream & cin, touring_car & a_car);
        
    private:
        string body_style; //"landaulet" etc.
        int horn;
        
        int display(ostream & cout) const;
        int set_name(istream & cin);
        bool greater_than(const touring_car & v2) const;
        bool greater_than_eq(const touring_car & v2) const;
        bool less_than(const touring_car & v2) const;
        bool less_than_eq(const touring_car & v2) const;
        //bool max_speed_not_eq(const touring_car & v2) const;
        //bool max_speed_eq(const touring_car & v2) const;
        bool speed_not_eq(const int & speed) const;
        bool speed_eq(const int & speed) const;
        int increase_speed(const int & speed);
};

class buggies : public vehicle
{
    public:
        buggies();
        buggies(const char * name, int max_s=70, int current_s=0, bool off_r=true, int seats=2);
        ~buggies();
        
        int set_frame_type();
        void display_stat() const;
        
        //Non-member operators
        friend bool operator==(const buggies & v1, const buggies & v2); //compare the vehicle's current speed
        friend bool operator==(const buggies & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator==(const int & speed, const buggies & v1); //compare the vehicle's current speed
        friend bool operator!=(const buggies & v1, const buggies & v2); //compare the vehicle's current speed
        friend bool operator!=(const buggies & v1, const int & speed); //compare the vehicle's current speed
        friend bool operator!=(const int & speed, const buggies & v1); //compare the vehicle's current speed

        friend buggies operator+(const buggies & v1, const int & speed); //increase speed
        
        friend bool operator<(const buggies & v1, const buggies & v2); //compare vehicle's current speed
        friend bool operator<=(const buggies & v1, const buggies & v2); //compare vehicle's current speed
        friend bool operator>(const buggies & v1, const buggies & v2); //compare vehicle's current speed
        friend bool operator>=(const buggies & v1, const buggies & v2); //compare vehicle's current speed
        
        friend ostream & operator<<(ostream & cout, const buggies & a_car);
        friend istream & operator>>(istream & cin, buggies & a_car);
    
    private:
        string frame_type; //"robust" etc.
        
        int display(ostream & cout) const;
        int set_name(istream & cin);
        bool greater_than(const buggies & v2) const;
        bool greater_than_eq(const buggies & v2) const;
        bool less_than(const buggies & v2) const;
        bool less_than_eq(const buggies & v2) const;
        //bool max_speed_not_eq(const buggies & v2) const;
        //bool max_speed_eq(const buggies & v2) const;
        bool speed_not_eq(const int & speed) const;
        bool speed_eq(const int & speed) const;
        int increase_speed(const int & speed);
};
