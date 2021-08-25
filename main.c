#include <stdio.h>
#include <conio.h>


struct Route{
    int id;
    char name[20];
    char from[20];
    char to[20];
    char time[5];
    int price;
};

//Function Declarations
int reserveTicket();
void cancelTicket();
void showOtherService();
void showPlaces();
void showAirRoutes(str,str);
void showRoadRoutes(str,str);
void showRailRoutes(str,str);

//Main Program
int main(){
    int menuChoice;

    start:

    printf("TOURS AND TRAVELS\n\n");
    printf("\n\
----------------------------------\n\
1. Reserve a Ticket\n\
2. Cancel a Ticket\n\
3. Other Services\n\
----------------------------------\n");


    printf("\nChoose a options to continue !!! ");
    printf("--> ");
    scanf("%d",&menuChoice);

    switch(menuChoice){
    case 1:
        menuChoice = reserveTicket();
        break;
    case 2:
        cancelTicket();
        break;
    case 3:
        showOtherService();
        break;
    default:
        printf("\nInvalid Choice");

    }
    goto start;
    return 0;


}

//Function Definitions
int reserveTicket(){
    int ticketNumber,menuChoice;
    str location[20],destination[20];
    printf("\n\
----------------------------------\n\
1. Airways\n\
2. Roadways\n\
3. Railways\n\
----------------------------------\n");

    printf("\nChoose a options to continue !!! ");
    printf("--> ");
    scanf("%d",&menuChoice);

    //Get the location and destination
    showPlaces();
    printf("\nChoose your departing location:\n")
    location = gets();
    printf("\nChoose your destination:\n")
    destination = gets();

    switch(menuChoice){
    case 1:
        showAirRoutes(location,destination);
        break;

    case 2:
        showRoadRoutes(location,destination);
        break;

    case 3:
        showRailRoutes(location,destination);
        break;

    default:
        printf("\nInvalid Menu Choice[Please enter (1/2/3)]\n");

    }
    }
    return ticketNumber;
}

void cancelTicket(){
    printf("\nTickets Cancelled Successfully\n\n");
}

void showOtherService(){
    printf("\nOther Services\n\n");
}

void showPlaces(){
    printf("\n\n\
Places\n\
1.Kathmandu\n\
2.Pokhhara\n\
3.Biratnagar\n\
4.Birgunj\n\
5.Butwal\n\n");
}

void showAirRoutes(str loc,str dest){
    printf("\nAvailable Services\n\n");
    printf("Route: %s to %s\n\n",loc,dest);
    printf("TicketNo   Name   Departing Time    Price(per ticket)");
    printf("1001")
}
