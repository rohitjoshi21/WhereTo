#include <stdio.h>
#include <conio.h>
#include <string.h>

struct Route{
    int id;
    int medium; // 1 for Air, 2 for Road and 3 for Rail
    char name[20];
    char from[20];
    char to[20];
    char time[10];
    int price;
} allRoutes[30];
int totalRoutes;
char places[][20] = {"Kathmandu","Pokhara","Biratnagar","Birgunj","Butwal"};

//Function Declarations
int reserveTicket();
void cancelTicket();
void showOtherService();
void showPlaces();
void showRoutes(int,char[],char[]);
int loadRoutes();

//Main Program
int main(){
    int menuChoice;

    totalRoutes = loadRoutes();
//    printf("Total Routes:%d",totalRoutes);
//    showRoutes(0,"a","a");
    start:

    printf("TOURS AND TRAVELS\n\n");
    printf("\n\
----------------------------------\n\
1. Reserve a Ticket\n\
2. Cancel a Ticket\n\
3. Show all routes\n\
4. Other Services\n\
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
        showRoutes(0,"all","all");
        break;
    case 4:
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
    int ticketNumber, menuChoice, seatCount;
    int locIndex, destIndex;

    char location[20],destination[20];

    top:
    printf("\n\
----------------------------------\n\
1. Airways\n\
2. Roadways\n\
3. Railways\n\
----------------------------------\n");

    printf("\nChoose a options to continue !!! ");
    printf("--> ");
    scanf("%d",&menuChoice);
    getch();

    //Get the location and destination
    showPlaces();
    printf("\nChoose your departing location:\n");
    scanf("%d",&locIndex);
    strcpy(location,places[locIndex-1]);
    printf("\nChoose your destination:\n");
    scanf("%d",&destIndex);
    strcpy(destination,places[destIndex-1]);


    if(menuChoice==1 || menuChoice==2 || menuChoice==3){
            showRoutes(menuChoice,location,destination);
    }
    else{
        printf("\nInvalid Menu Choice[Please enter (1/2/3)]\n\n");
        goto top;
    }
    printf("Enter the route ID");
    printf("--> ");
    scanf("%d",&ticketNumber);

    printf("Enter number to seats to be booked");
    printf("--> ");
    scanf("%d",&seatCount);


//    return ticketNumber;
}

void cancelTicket(){
    printf("\nTickets Cancelled Successfully\n\n");
}

void showOtherService(){
    printf("\nOther Services\n\n");
}

void showPlaces(){
    //Finding total number of places in the array
    int num = sizeof(places) / sizeof(places[0]);

    printf("\n\n\Places\n");
    for(int i=0;i<num;i++){
        printf("\n%d. %s",i+1,places[i]);
    }
}

void showRoutes(int way, char loc[],char dest[]){

    printf("\n\nID\tMEDIUM\tNAME\t\t\tFROM\t\tTO\t\tTIME\t\tPRICE\n\n");
    for(int i=0;i<totalRoutes;i++){
        if(way!=0){
            if(allRoutes[i].medium!=way || strcmp(allRoutes[i].from,loc)!=0 || strcmp(allRoutes[i].to,dest)==0){
                continue;
            }
        }
        printf("%d\t%d\t%-20s\t%-15s\t%-15s\t%6s\t%d\n",allRoutes[i].id,allRoutes[i].medium,allRoutes[i].name,allRoutes[i].from,allRoutes[i].to,allRoutes[i].time,allRoutes[i].price);
    }
}

int loadRoutes(){
    FILE *fp;
    fp = fopen("routedata.txt","r");

    int i=0;
    while(fscanf(fp,"%d, %d, %[^,], %[^,], %[^,], %[^,], %d",&allRoutes[i].id,&allRoutes[i].medium,allRoutes[i].name,allRoutes[i].from,allRoutes[i].to,allRoutes[i].time,&allRoutes[i].price)!=EOF){
        i++;
    }
    fclose(fp);

    return i;
}
