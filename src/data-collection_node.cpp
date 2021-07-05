#include <iostream>
#include <thread>
#include <string>
#include <sstream>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "data_collection/rtk.h"

#include "SparkFun_u-blox_GNSS_Arduino_Library.h"

// GPS object
SFE_UBLOX_GNSS myGPS;

int main(int argc, char** argv)
{

    ros::init(argc, argv, "ublox_rtk");
    ros::NodeHandle n;
    ros::Publisher rtk_pub = n.advertise<data_collection::rtk>("ublox_rtk", 1000);

    std::string port;
    ros::param::get("/TTY", port);

    // GPS Setting
    // if(argc == 1) {
    //     printf("\nublox_f9p_test <ublox_com> <pseudo_com> (ublox_f9p_test '/dev/ttyACM0')"); 
    //     return 0;
    // } else if (argc == 2) {
    //     for(int counter=0;counter<argc;counter++) 
    //         printf("\nargv[%d]: %s",counter,argv[counter]);        
    // } else if(argc >= 3) {
    //     printf ("\nMore number of arguments...");
    //     return 0;
    // } 
    //char * check = port.c_str();

    char* check = strcpy((char*)malloc(port.length()+1), port.c_str());
    std::cout << check << std::endl;

    Stream seriComm(check);
    seriComm.begin(38400);
    if (!seriComm.isConnected()) {
        printf ("Ublox is not connected. Please connect ublox GNSS module and try again...\n");
        return 0;
    }

    myGPS.begin(seriComm);
    myGPS.setNavigationFrequency(8); //Set output to 8 times a second
    myGPS.saveConfiguration(); //Save the current settings to flash and BBR

    int count = 0;

    ros::Rate loop_rate(10);
    
    printf ("\n--------------------------------------------------------\n");
    while(ros::ok()) {
        if (myGPS.getPVT()) {
            data_collection::rtk msg;

            std::stringstream datetime;
            datetime << myGPS.getDay() << "/" 
                     << myGPS.getMonth() << "/" 
                     << myGPS.getYear() << " " 
                     << myGPS.getHour() << ":" 
                     << myGPS.getMinute() << ":"
                     << myGPS.getSecond() << ":"
                     << myGPS.getMillisecond() << ":"
                     << myGPS.getNanosecond();

            msg.date_time = datetime.str();
            msg.latitude = myGPS.getLatitude() * 1e-7;
            msg.longitude = myGPS.getLongitude() * 1e-7;
            msg.altitude = myGPS.getAltitude();
            msg.altitudeMSL = myGPS.getAltitudeMSL();

            printf ("%02d/%02d/%02d %02d:%02d:%02d %d:%d\n", myGPS.getDay(), myGPS.getMonth(), myGPS.getYear(), 
                                                            myGPS.getHour(), myGPS.getMinute(), myGPS.getSecond(), 
                                                            myGPS.getMillisecond(), myGPS.getNanosecond());
            printf("Latitude                : %2.8f (deg)\n", myGPS.getLatitude() * 1e-7);
            printf("Longitude               : %2.8f (deg)\n", myGPS.getLongitude() * 1e-7);
            printf("Altitude                : %d (mm)\n", myGPS.getAltitude());
            printf("Altitude MSL            : %d (mm)\n", myGPS.getAltitudeMSL());

            rtk_pub.publish(msg);

        }
        ros::spinOnce();

        loop_rate.sleep();
    }

    return 1;
}
