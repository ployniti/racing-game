//This is the client program to interact with the user

#include "main.h"
#include "vehicle.h"
#include "DLL.h"

int main()
{
    int selected_option {0};
    bool agree {true};
    char answer;
    char input[SIZE];
    int length{0};
    
    while (agree && 4 != selected_option)
    {
        cout << "Welcome to the ultimate racing game!" << endl << endl;
        
        cout << "Please select from the options below:" << endl
             << "1) Street racing (with touring cars)" << endl
             << "2) Off road racing (with buggies)" << endl
             << "3) Track racing (with supercars)" << endl
             << "4) Quit" << endl;
        
        do 
        {
            cout << "Please enter a number from 1 to 4: ";
            cin >> selected_option;
            cin.ignore(100, '\n');
            cout << '\n';

            if (selected_option < 1 || selected_option > 4)
                cout << "Please only enter a number between 1 and 4, inclusive" << endl << endl;
        } while (selected_option < 1 || selected_option > 4);
        
        if (1 == selected_option)
        {
            //Setting up the touring cars
            cout << "Please enter touring car 1's name: ";
            cin.get(input, SIZE, '\n'); 
            cin.ignore(SIZE, '\n');

            touring_car v1(input);
            v1.set_body_style();
            v1.honk();
            
            cout << "Please enter touring car 2's name: ";
            cin.get(input, SIZE, '\n'); 
            cin.ignore(SIZE, '\n');

            touring_car v2(input);
            v2.set_body_style();
            v1.honk();

            //Initialize track
            get_length(length);
            DLL <touring_car> street_track(v1, v2, length);

            if (!street_track.create_track())
                cout << "Error creating track, please try again." << endl << endl;
            cout << '\n';
            
            cout << street_track.get_vehicle1() << endl;

            //Display vehicles' stat
            cout << "//*****************//" << endl;
            cout << v1 << endl;
            v1.display_stat();
            cout << '\n';
            cout << v2 << endl;
            v2.display_stat();
            cout << "//*****************//" << endl;
            cout << '\n';
            
            //Start racing
            cout << "//**Off to racing!**//" << endl << endl;
            street_track.display();

            while (!street_track.finished())
            {
                street_track.menu();
                street_track.display();
            }
            
            //Declare winner
            street_track.display_winner();
            cout << '\n';
        }

        else if (2 == selected_option)
        {
            //Setting up the buggies
            cout << "Please enter buggy 1's name: ";
            cin.get(input, SIZE, '\n'); 
            cin.ignore(SIZE, '\n');

            buggies v1(input);
            v1.set_frame_type();
            
            cout << "Please enter buggy 2's name: ";
            cin.get(input, SIZE, '\n'); 
            cin.ignore(SIZE, '\n');

            buggies v2(input);
            v2.set_frame_type();
            
            //Initialize track
            get_length(length);
            DLL <buggies> offroad_track(v1, v2, length);
            if (!offroad_track.create_track())
                cout << "Error creating track, please try again." << endl << endl;
            cout << '\n';
           
            //Display vehicles' stat
            cout << "//*****************//" << endl;
            cout << v1 << endl;
            v1.display_stat();
            cout << '\n';
            cout << v2 << endl;
            v2.display_stat();
            cout << "//*****************//" << endl;
            cout << '\n';

            //Start racing
            cout << "//**Off to racing!**//" << endl << endl;
            offroad_track.display();

            while (!offroad_track.finished())
            {
                offroad_track.menu();
                offroad_track.display();
            }
            
            //Declare winner
            offroad_track.display_winner();
            cout << '\n';
        }

        else if (3 == selected_option)
        {
            //Setting up the supercars
            cout << "Please enter supercar 1's name: ";
            cin.get(input, SIZE, '\n'); 
            cin.ignore(SIZE, '\n');

            supercar v1(input);
            v1.set_turbo();
            
            cout << "Please enter supercar 2's name: ";
            cin.get(input, SIZE, '\n'); 
            cin.ignore(SIZE, '\n');

            supercar v2(input);
            v2.set_turbo();
            
            //Initialize track
            get_length(length);
            DLL <supercar> track(v1, v2, length);
            if (!track.create_track())
                cout << "Error creating track, please try again." << endl << endl;
            cout << '\n';
           
            //Display vehicles' stat
            cout << "//*****************//" << endl;
            cout << v1 << endl;
            v1.display_stat();
            cout << '\n';
            cout << v2 << endl;
            v2.display_stat();
            cout << "//*****************//" << endl;
            cout << '\n';
            
            //Start racing
            cout << "//**Off to racing!**//" << endl << endl;
            track.display();

            while (!track.finished())
            {
                track.menu();
                track.display();
            }
            
            //Declare winner
            track.display_winner();
            cout << '\n';
        }

        if (4 != selected_option)
        {
            cout << "Would you like to do another race? (y/n): ";
            cin >> answer;
            cin.ignore(100, '\n');
            cout << '\n';

            if (answer != 'y' && answer != 'Y')
                agree = false;
        }
    }
    
    cout << "Thank you for racing!" << endl << endl;

    return 0;
}

//This is the function to prompt the user for the track length
//Argument: int
//Return: void
void get_length(int & length)
{
    do 
    {
        cout << "How long would you like the track to be? ";
        cin >> length;
        cin.ignore(100, '\n');
        cout << '\n';
        
        if (length <= 0)
            cout << "Please only enter a number greater than zero." << endl << endl;
        else if (length > 20)
            cout << "Please choose a smaller number than 20." << endl << endl;
    } while (length <= 0 || length > 20);
}
