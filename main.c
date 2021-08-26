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

struct Ticket{
    int ticketNo;
    char bookedBy[20];
    int routeId;
    int seatCount;
} allTickets[30];
int totalTickets;

//Function Declarations
int reserveTicket();
void cancelTicket();
void showOtherService();
void showPlaces();
void showRoutes(int,char[],char[]);
int loadDatas();
void showTicket(int);
int addNewTicket(char[], int, int);
void clear();
//Main Program
int main(){
    int menuChoice;


    loadDatas();

//    showTicket(201);
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
    int routeId, menuChoice, seatCount;
    int locIndex, destIndex;
    char name[20];

    char location[20],destination[20];

    printf("Enter your name\n");
    printf("--> ");
    clear();
    gets(name);

    top:
    printf("\n\nHow do you want to travel?\n\n");
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

    printf("Enter the route ID\n");
    printf("--> ");
    scanf("%d",&routeId);

    printf("Enter number to seats to be booked\n");
    printf("--> ");
    scanf("%d",&seatCount);

    int ticketNo = addNewTicket(name,routeId,seatCount);

    printf("Thank you for using our sevice! Your ticket is ready");
    printf("\nPress any key to view your ticket....");
    getch();
    showTicket(ticketNo);

    printf("\nPress any key to continue.....\n");
    getch();

//    return ticketNumber;
}

void cancelTicket(){
    int ticketNo;
    printf("\nEnter your ticket no:\n");
    printf("--> ");
    scanf("%d",&ticketNo);

    printf("Here is your ticket:\n");
    showTicket(ticketNo);
    printf("Do you want to cancel it?(Y/N)");
    printf("--> ");
    clear();
    char r = getchar();
    if(r=='y' || r=='Y'){
        for(int i=0;i<totalTickets;i++){
            if(allTickets[i].ticketNo==ticketNo){
                allTickets[i].ticketNo = 0;

            }
        }
    }

    printf("\nTickets Cancelled Successfully\n\n");

    printf("\nPress any key to continue.....\n");
    getch();
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
            if(allRoutes[i].medium!=way || strcmp(allRoutes[i].from,loc)!=0 || strcmp(allRoutes[i].to,dest)!=0){
                continue;
            }
        }
        printf("%d\t%d\t%-20s\t%-15s\t%-15s\t%6s\t%d\n",allRoutes[i].id,allRoutes[i].medium,allRoutes[i].name,allRoutes[i].from,allRoutes[i].to,allRoutes[i].time,allRoutes[i].price);
    }
}

int loadDatas(){
    //Loading datas of available routes
    FILE *fp;
    fp = fopen("routedata.csv","r");

    int i=0;
    fscanf(fp, "%*[^\n]"); //Skip the first line of textfile containing columns name
    while(fscanf(fp,"%d, %d, %[^,], %[^,], %[^,], %[^,], %d",&allRoutes[i].id,&allRoutes[i].medium,allRoutes[i].name,allRoutes[i].from,allRoutes[i].to,allRoutes[i].time,&allRoutes[i].price)!=EOF){
        i++;
    }
    fclose(fp);
    totalRoutes = i;

    //Loading datas of booked tickets
    fp = fopen("ticketdata.csv","r");

    i=0;
    fscanf(fp, "%*[^\n]"); //Skip the first line of textfile containing columns name
    while(fscanf(fp,"%d, %[^,], %d, %d",&allTickets[i].ticketNo,allTickets[i].bookedBy,&allTickets[i].routeId,&allTickets[i].seatCount)!=EOF){
        i++;
    }
    fclose(fp);
    totalTickets = i;
}

void showTicket(int ticketNo){
    int i=0,j=0;
    for(i=0;i<totalTickets;i++){
        if(allTickets[i].ticketNo == ticketNo)
            break;
    }
    struct Ticket tic = allTickets[i];

    for(j=0;j<totalRoutes;j++){
        if(allRoutes[j].id == tic.routeId)
            break;
    }
    struct Route rte = allRoutes[j];

    printf("\n\n\
---------------------------------------------------------------\n\
Ticket Number: %d\n\
%s\n\
Ticket of: %s\n\
Route: %s to %s         Departing Time: %s\n\
Number of Seats: %d     Total Cost: %d\n\
----------------------------------------------------------------\n\n",ticketNo,rte.name,tic.bookedBy,rte.from,rte.to,rte.time,tic.seatCount,tic.seatCount*rte.price);
}

int addNewTicket(char name[], int routeId, int seatCount){

    FILE *fp;
    fp = fopen("ticketdata.csv","a+");

    //Getting the ticket number of last ticket added
    char ch;
    int lastTicketNumber;
    fseek(fp,0,SEEK_END);
    while(1){
        fseek(fp,-2,SEEK_CUR);
        ch = fgetc(fp);
        if(ch=='\n')
            break;
    }
    fscanf(fp,"%d",&lastTicketNumber);

    int ticketNumber = lastTicketNumber+1;
    int pos = totalTickets;

    //Adding new ticket to list of tickets
    allTickets[pos].ticketNo = ticketNumber;
    strcpy(allTickets[pos].bookedBy,name);
    allTickets[pos].routeId = routeId;
    allTickets[pos].seatCount = seatCount;

    //Writing ticket data to file
    fseek(fp,0,SEEK_END);
    fprintf(fp, "\n%d, %s, %d, %d",ticketNumber,name,routeId,seatCount);
    fclose(fp);

    return ticketNumber;

}

void clear(){
    while(getchar()!='\n');
}
