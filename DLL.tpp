//This is the code to implement the node and DLL class templates

#pragma once
#include "main.h"

/*NODE*/
//Default constructor
template <typename T>
node<T>::node():next(nullptr), prev(nullptr)
{
    vehicles = {nullptr, nullptr}; //array of 2 vehicle pointers
}

//Constructor with data argument, takes in two vehicle pointers by reference
template <typename T>
node<T>::node(T* & v1, T* & v2):next(nullptr), prev(nullptr)
{
    vehicles.at(0) = v1;
    vehicles.at(1) = v2;
}

//Copy constructor
template <typename T>
node<T>::node(const node & src):next(nullptr), prev(nullptr)
{
    copy(src);
}

//Assignment operator
template <typename T>
node<T> & node<T>::operator=(const node & src)
{
    if (this == &src)
        return *this;

    if (next)
    {
        delete next;
        next = prev = nullptr;
    }
    
    //Set the pointers to null
    for (int i=0; i<2; ++i)
        vehicles.at(i) = nullptr;
    
    copy(src);

    return *this;
}

//This function copies a the data in a node from another node
//Argument: node<T> object
//Return: void
template <typename T>
void node<T>::copy(const node & src)
{
    //Copy array of vehicle pointers
    for (int i=0; i<2; ++i)
        vehicles.at(i) = src.vehicles.at(i);
}

//Destructor
template <typename T>
node<T>::~node()
{
    for (int i=0; i<2; ++i)
        vehicles.at(i) = nullptr;

    if (next)
    {
        delete next;
        next = prev = nullptr;
    }
}

//This function sets the next pointer of the node to another address
//Argument: node pointer to the new address
//Return: void
template <typename T>
void node<T>::set_next(typename node<T>::node_ptr new_next)
{
    next = new_next;
}

//This function sets the previous pointer of the node to another address
//Argument: node pointer to the new address
//Return: void
template <typename T>
void node<T>::set_prev(typename node<T>::node_ptr new_prev)
{
    prev = new_prev;
}

//This is the function gets the next pointer of the node object
//Argument: none
//Return: node_ptr
template <typename T>
typename node<T>::node_ptr & node<T>::get_next()
{
    return next;
}

//This is the function gets the previous pointer of the node object
//Argument: none
//Return: node_ptr
template <typename T>
typename node<T>::node_ptr & node<T>::get_prev()
{
    return prev;
}

//This is the function get the T* (vehicle pointer) in the vehicles array, could be nullptr
//Argument: int for the index to access
//Return: T* (vehicle pointer)
template <typename T>
T* & node<T>::get_data(const int & i)
{
    return vehicles.at(i);
}

//This is the function to loop through the vehicles array and display the vehicles' info
//Argument: none
//Return: void
template <typename T>
void node<T>::display() const
{
    //Display vehicles' info
    for (auto i : vehicles)
    {
        if (i) //check if not null
        {
            cout << *i << endl;
            (*i).display_current_speed();
            cout << endl << endl;
        }
        else
            cout << "___" << endl;
    }
    
    //Display status, comparing vehicles' current speed
    if (vehicles.at(0) && vehicles.at(1))
    {
        //v1 is faster than v2
        if (*(vehicles.at(0)) > *(vehicles.at(1)))
            cout << *(vehicles.at(0)) << " is ahead!";

        //v2 is faster than v1
        else if (*(vehicles.at(1)) > *(vehicles.at(0)))
            cout << *(vehicles.at(1)) << " is ahead!";
        
        //v1 and v2 have the same current speed
        else if (*(vehicles.at(0)) == *(vehicles.at(1)))
            cout << *(vehicles.at(0)) << " and " 
                 << *(vehicles.at(1)) << " are tied!";
    }

    cout << endl << endl;
}

/*DLL*/
//Default constructor
template <typename T>
DLL<T>::DLL():head(nullptr), tail(nullptr), track_length(0)
{
}

//Constructor with arguments, taking in vehicle objects and the length of the track
template <typename T>
DLL<T>::DLL(const T & v1, const T & v2, const int & len):head(nullptr), tail(nullptr), track_length(len)
{
    vehicle1 = v1;
    vehicle2 = v2;
}

//Copy constructor
template <typename T>
DLL<T>::DLL(const DLL & src):head(nullptr), tail(nullptr), track_length(0)
{
    //Copy the track if exists
    if (src.head)
        copy(head, src.head);
    
    vehicle1 = src.vehicle1;
    vehicle2 = src.vehicle2;
    track_length = src.track_length;
}

//Assignment operator
template <typename T>
DLL<T> & DLL<T>::operator=(const DLL & src)
{
    if (this == &src)
        return *this;
    
    if (head)
    {
        remove_all(head);
        tail = head; //set tail to nullptr
    }

    copy(head, src.head);
    vehicle1 = src.vehicle1;
    vehicle2 = src.vehicle2;
    track_length = src.track_length;
    
    return *this;
}

//This function copies a src DLL to the current DLL object
//Argument: node_ptr for the current object's head and a node_ptr for the src object's head 
//Return: void
template <typename T>
void DLL<T>::copy(typename DLL<T>::node_ptr & head, const typename DLL<T>::node_ptr & src)
{
    if (!src)
    {
        this->tail = head; //tail = head;
        return;
    }
    
    //Temporary node, passing vehicle pointers to node constructor with arguments
    node_ptr temp = new node<T> (src->get_data(0), src->get_data(1));
    
    if (!head)
    {
        head = temp;
        head->set_next(nullptr);
        head->set_prev(nullptr);
        copy(head, src->get_next()); //passing head first since its the first node added
    }
    else
    {
        temp->set_prev(head);
        head->set_next(temp);
        head->get_next()->set_next(nullptr);
        copy(head->get_next(), src->get_next());
    }
    
    return;
}

//Destructor
template <typename T>
DLL<T>::~DLL()
{
    if (head)
    {
        remove_all(head);
        tail = head; //set tail to nullptr
    }
}

//This is the function to remove all nodes in the DLL
//Argument: node pointer to head
//Return: void
template <typename T>
void DLL<T>::remove_all(typename DLL<T>::node_ptr & head)
{
    if (!head) return;

    remove_all(head->get_next());

    delete head;
    head = nullptr;
}

//This is the function to return the tail pointer in the DLL
//Argument: none
//Return: tail node pointer
template <typename T>
typename DLL<T>::node_ptr & DLL<T>::get_tail()
{
    return tail;
}

//This is the function to return the head pointer in the DLL
//Argument: none
//Return: head node pointer
template <typename T>
typename DLL<T>::node_ptr & DLL<T>::get_head()
{
    return head;
}

//This is the function to return the track_length
//Argument: none
//Return: int for the track_length
template <typename T>
int DLL<T>::get_length()
{
    return track_length;
}

//This is the function to return the vehicle1 object by reference
//Argument: none
//Return: T object reference
template <typename T>
T & DLL<T>::get_vehicle1()
{
    return vehicle1;
}

//This is the function to return the vehicle2 object by reference
//Argument: none
//Return: T object reference
template <typename T>
T & DLL<T>::get_vehicle2()
{
    return vehicle2;
}

//This is the wrapper function to add a certain number of nodes into the DLL
//Argument: node pointer to head
//Return: int, 1 for success, 0 for failure
template <typename T>
int DLL<T>::create_track()
{
    if (head || !track_length) return 0; //track already exists or no length

    int added {0}; //keeps track of the number of nodes added

    return create_track(head, added);
}

//This is the function to add a certain number of nodes into the DLL
//Argument: node pointer to head and an int to keep track of node added
//Return: int, 1 for success, 0 for failure
template <typename T>
int DLL<T>::create_track(typename DLL<T>::node_ptr & head, int & added)
{
   int count {0};

   if (added == track_length)
   {
       tail = head; //set tail to the last node
       return 1;
   }
   
   if (!head)
   {
       //First node of the track has the pointers set to the two vehicles
       T* v1 = &vehicle1;
       T* v2 = &vehicle2;
       
       head = new node<T> (v1,v2);
       head->set_next(nullptr);
       head->set_prev(nullptr);
       
       ++added;
       count = create_track(head, added);
   }
   else
   {
       head->get_next() = new node<T>;
       head->get_next()->set_next(nullptr);
       head->get_next()->set_prev(head);
        
       ++added;
       count = create_track(head->get_next(), added);
   }

   return count;
}

//This is the wrapper function to display all nodes in a DLL, showing the progress of the cars on the track
//Argument: none
//Return: void
template <typename T>
void DLL<T>::display() const
{
    if (!head) return;

    int segment {1};

    display(head, segment);
}

//This is the function to display all nodes in a DLL, showing the progress of the cars on the track
//Argument: none
//Return: void
template <typename T>
void DLL<T>::display(const typename DLL<T>::node_ptr & head, int & segment) const
{
    if (!head) return;
    
    cout << "Segment: " << segment << endl;
    head->display();
    ++segment;

    display(head->get_next(), segment);
}

//This is the function to check if the race is finished by checking if the vehicle pointers at the last node is set
//Argument: none
//Return: bool, true for finished, false for not
template <typename T>
bool DLL<T>::finished() const
{
    if (tail->get_data(0) || tail->get_data(1)) //one of the vehicle is in the last node!
        return true;
    return false;
}

//This is the menu interface to race the vehicles
//Argument: none
//Return: void
template <typename T>
void DLL<T>::menu()
{
    int selected_option {0};
    int speed {0};
    bool agree {true};
    char answer;
    
    cout << "Please select from the options below:" << endl;
    cout << "1) Increase " << vehicle1.get_name() << "'s speed" << endl
         << "2) Increase " << vehicle2.get_name() << "'s speed" << endl
         << "3) Advance to next segment" << endl;
    
    while (agree && 3 != selected_option)
    {
        do 
        {
            cout << "Please select enter a number from 1 to 3: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 3)
                cout << "Please only enter a number between 1 and 3, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 3);
        
        if (1 == selected_option)
        {
            cout << "How much would you like to increase " << vehicle1.get_name() << " speed by? ";
            cin >> speed;
            cin.ignore(100, '\n');
            
            try
            {
                vehicle1 += speed;
                vehicle1.display_current_speed();
                cout << endl;
            }
            catch (exceed_max max)
            {
                cout << max.msg << endl;
            }
        } 
        else if (2 == selected_option)
        {
            cout << "How much would you like to increase " << vehicle2.get_name() << " speed by? ";
            cin >> speed;
            cin.ignore(100, '\n');
            
            try
            {
                vehicle2 += speed;
                vehicle2.display_current_speed();
                cout << endl;
            }
            catch (exceed_max max)
            {
                cout << max.msg << endl;
            }
        } 
        else if (3 == selected_option)
        {
            if (!update_track())
                cout << "Error updating track, please try again." << endl << endl;
        }
        
        if (3 != selected_option)
        {
            cout << "Would you like to take another action? (y/n): ";
            cin >> answer;
            cin.ignore(100, '\n');
            cout << '\n';

            if (answer != 'y' && answer != 'Y')
                agree = false;
        }
    }
}

//This is the wrapper function to update the position of the vehicles on the track
//Argument: none
//Return: int, 1 for success, 0 for failure
template <typename T>
int DLL<T>::update_track()
{
    if (!head) return 0;
    
    if ((vehicle1 == 0) && (vehicle2 == 0)) //Speed of vehicles' are still 0 so no need to update the track
    {
        cout << "Both vehicles' speed is zero! Please add speed to race." << endl << endl;
        return -1;
    }
    
    bool moved1 {false};
    bool moved2 {false};

    return update_track(head, moved1, moved2);
}

//This is the function to update the position of the vehicles on the track
//Arguments: node pointer to head of DLL, bool values for whether the vehicles have been moved
//Return: int, 1 for success, 0 for failure
template <typename T>
int DLL<T>::update_track(typename DLL<T>::node_ptr & head, bool & moved1, bool & moved2)
{
    //int count {0};
    if (!head->get_next())
        return 1;
    
    if (!moved1)
    {
        if (!head->get_next()->get_data(0) && head->get_data(0))
        {
            if (vehicle1.get_speed() > 0)
            {
                head->get_data(0) = nullptr;
                head->get_next()->get_data(0) = &vehicle1;
                moved1 = true;
            }
        }
    }
    
    if (!moved2)
    {
        if (!head->get_next()->get_data(1) && head->get_data(1))
        {
            if (vehicle2.get_speed() > 0)
            {
                head->get_data(1) = nullptr;
                head->get_next()->get_data(1) = &vehicle2;
                moved2 = true;
            }
        }
    }
    
    return update_track(head->get_next(), moved1, moved2);
}

//This is the function to display the winner at the end of the race by checking the last node in the track
//If there are two vehicles, we compare their speed. If not, we declare the vehicle that got there first the winner
//Argument: none
//Return: void
template <typename T>
void DLL<T>::display_winner() const
{
    if (tail)
    {
        if (tail->get_data(0) && tail->get_data(1)) //both at the end of the race
        {
            if (vehicle1 > vehicle2)
                cout << vehicle1 << " won!" << endl;
            else if (vehicle1 < vehicle2)
                cout << vehicle2 << " won!" << endl;
            else if (vehicle1 == vehicle2)
                cout << "It's a tie!" << endl;
        }
        else if (tail->get_data(0) && !tail->get_data(1))
            cout << vehicle1 << " won!" << endl;
        else if (tail->get_data(1) && !tail->get_data(0))
            cout << vehicle2 << " won!" << endl;
    }
}
