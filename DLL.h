//This is the .h file for the node and DLL classes

#pragma once
#include "main.h"

//Template classes
template <typename T>
class node
{
    public:
        typedef node<T>* node_ptr;
        
        node();
        node(T* & v1, T* & v2);
        node(const node & src);
        node & operator=(const node & src);
        ~node();
        node_ptr & get_next();
        node_ptr & get_prev();
        void set_next(node_ptr new_next);
        void set_prev(node_ptr new_prev);
        T* & get_data(const int & i); //i is the index of the array 
        void display() const;
        
    private:
        array <T*, 2> vehicles;
        node_ptr next;
        node_ptr prev;
        
        void copy(const node<T> & src);
};

template <typename T>
class DLL
{
    public:
        typedef node<T>* node_ptr;
        
        DLL();
        DLL(const T & v1, const T & v2, const int & track_length);
        DLL(const DLL & src); //copy constructor
        DLL & operator=(const DLL & src);
        ~DLL();
        
        node_ptr & get_tail(); //return the node pointed by tail
        node_ptr & get_head(); //return the node pointed by head
        T & get_vehicle1(); //return vehicle1 reference
        T & get_vehicle2(); //return vehicle2 reference
        int get_length(); //return the track_length
        void display() const;
        int create_track(); //generate a DLL after user pick racing type
        int update_track(); //update the position of the vehicles in the DLL by updating pointers in nodes
        void menu();
        bool finished() const; //check if one of the pointers in node is not null
        void display_winner() const; //display the winning vehicle in the last node

    private:
        node_ptr head;
        node_ptr tail;
        T vehicle1;
        T vehicle2;
        int track_length;

        void display(const node_ptr & head, int & segment) const;
        int create_track(node_ptr & head, int & added);
        int update_track(node_ptr & head, bool & moved1, bool & moved2);
        void copy(node_ptr & head, const node_ptr & src);
        void remove_all(node_ptr & head);
};

#include "DLL.tpp"
