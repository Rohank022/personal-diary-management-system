#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_MEETINGS 100
#define MAX_NOTES 100 
#define MAX_CONTACTS 100
#define MAX_PASSWORD_LEN 100



struct Notes
 {
    char date[20];
    char time[20];
    char title[100];
    char details[500];
};
struct Meetings
 {
    char date[20];
    char time[20];
    char title[20];
    char details[500];
    char name[50];
    char phone[20];
    char email[20];
    char address[50];
};
struct Contacts
 {
    char name[50];
    char phone[20];
    char email[20];
};

void addRecord();
void addNotes();
void loadNotes();
void addMeetings();
void loadMeetings();
void addContacts();
void loadContacts();
void viewRecord();
void editRecord();
void deleteRecord();
void editPassword();
void editNotes();
void editMeetings();
void editContacts();
int login();
void deleteNotes();
void deleteMeetings();
void deleteContacts();




int main() {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(hConsole, (FOREGROUND_BLUE | FOREGROUND_GREEN));
	
    	
    char option;
   if (login())
    do {
    	system("Cls");
    	
        printf("\n\n\t*********************************************\n");
        printf("\t*             PERSONAL DIARY MENU             *\n");
        printf("\t*********************************************\n\n");
      
        printf("\t\t [1] ADD RECORD\n");
        printf("\t\t [2] VIEW RECORD\n");
        printf("\t\t [3] EDIT RECORD\n");
        printf("\t\t [4] DELETE RECORD\n");
        printf("\t\t [5] EDIT PASSWORD\n");
        printf("\t\t [6] EXIT\n\n");
        
        printf("\t\t Select Option : ");
        
        option = getch();
        printf("%c\n", option);
        
        switch(option) {
            case '1':
                system("cls");
                addRecord();
                break;
            case '2':
                system("cls");
                viewRecord();
                break;
            case '3':
                system("cls");
                editRecord();
                break;
            case '4':
                system("cls");
                deleteRecord();
                break;
            case '5':
                system("cls");
                editPassword();
                break;
            case '6':
                system("cls");
                printf("\n\t\tThank you for using Personal Diary Management System!\n");
                break;
            default:
                system("cls");
                printf("\n\t\tInvalid option! Please try again...\n");
                getch();
                break;
        }
    } while(option != '6');
    
    
    
    return 0;
}


void addRecord() {
    char option;
    
    do {
        printf("\n\t*********************************************\n");
        printf("\t*               ADD RECORD MENU              *\n");
        printf("\t*********************************************\n\n");
        
        printf("\t Select a record type:\n");
        printf("\t [1] Notes\n");
        printf("\t [2] Meetings\n");
        printf("\t [3] Contacts\n");
        printf("\t [4] Back to main menu\n\n");
        
        printf("\tSelect Option : ");
        
        option = getch();
        printf("%c\n", option);
        
        switch(option) {
            case '1':
            	system("cls");
                addNotes();
                break;
            case '2':
            	system("cls");
                addMeetings();
                break;
            case '3':
            	system("cls");
                addContacts();
                break;
            case '4':
            	system("cls");
                printf("\nReturning to main menu...\n");
                break;
            default:
            	system("cls");
                printf("\nInvalid option! Please try again.\n");
                break;
        }
        system("cls");
    } while(option != '4');
    
}

void addNotes()
{
    struct Notes n;

    printf("\n\t*********************************************\n");
    printf("\t*                  ADD NOTES                 *\n");
    printf("\t*********************************************\n\n");

    printf("\tEnter date (DD/MM/YYYY): ");
    scanf("%19s", n.date);
    

    printf("\tEnter time (HH:MM): ");
    scanf("%19s", n.time);

    printf("\tEnter title: ");
    scanf("%99s", n.title);

    printf("\tEnter details: ");
    scanf("%499s", n.details);

    // Save the record to a file
    FILE *fp;
    fp = fopen("notes.txt", "a");
    if (fp == NULL)
    {
        printf("\nError opening file!");
        return;
    }

    fprintf(fp, "%s,%s,%s,%s\n", n.date, n.time, n.title, n.details);
    fclose(fp);

    printf("\n\tRecord added successfully!\n");
     printf("\n\t Press any key to continue...");
    getch();
}


void addMeetings()
{
    struct Meetings m;

    printf("\n\t*********************************************\n");
    printf("\t*              ADD MEETING                   *\n");
    printf("\t*********************************************\n\n");

    printf("\tEnter date (DD/MM/YYYY): ");
    scanf("%19s", m.date);

    printf("\tEnter time (HH:MM): ");
    scanf("%19s", m.time);

    // Open the meetings file for reading
    FILE *fp = fopen("meetings.txt", "r");
    if (fp == NULL) {
    
    	
    	printf("\n\t  :: Create your 1st meeting :: \n");
    	 
    	goto m;
	}
	else
	{
		 char line[600];
        while (fgets(line, sizeof(line), fp))
	   {
    	
        struct Meetings existing;
        sscanf(line, "%19[^,],%19[^,],%99[^,],%499[^,],%49[^,],%19[^,],%19[^,],%49[^\n]",
            existing.date, existing.time, existing.title, existing.details, existing.name,
            existing.phone, existing.email, existing.address);
        if (strcmp(existing.date, m.date) == 0 && strcmp(existing.time, m.time) == 0)
		 {
            printf("\n\tThere is already a meeting scheduled at this time!\n");
            fclose(fp);
            printf("\tPress any key to return to the previous menu...");
            getch();
            return; 
          }
        }
        
        fclose(fp);
		 
	}
        
    // Read the existing meetings and check if there's a conflict
   

    

    // If there's no conflict, prompt the user for the rest of the meeting information
   m: printf("\tEnter title: ");
    scanf("%99s", m.title);

    printf("\tEnter details: ");
    scanf("%499s", m.details);

    printf("\tEnter name: ");
    scanf("%49s", m.name);

    printf("\tEnter phone: ");
    scanf("%19s", m.phone);

    printf("\tEnter email: ");
    scanf("%19s", m.email);

    printf("\tEnter address: ");
    scanf("%49s", m.address);

    // Save the meeting to the file
    fp = fopen("meetings.txt", "a");
    if (fp == NULL) {
        printf("\nError opening file!");
        return;
    }

    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", m.date, m.time, m.title, m.details, m.name, m.phone, m.email, m.address);
    fclose(fp);

    printf("\n\tMeeting added successfully!\n");
    
    printf("\n\t Press any key to continue...");
    getch();
}



void addContacts()
{
    struct Contacts c;

    printf("\n\t*********************************************\n");
    printf("\t*               ADD CONTACTS                 *\n");
    printf("\t*********************************************\n\n");

   c:  printf("\tEnter name: ");
    scanf("%49s", c.name);

    printf("\tEnter phone number: ");
    scanf("%19s", c.phone);

    printf("\tEnter email: ");
    scanf("%19s", c.email);

    // Save the contact to a file
    FILE *fp = fopen("contacts.txt", "a");
    if (fp == NULL) {
        printf("\nError opening file!");
        return;
    }

    fprintf(fp, "%s,%s,%s\n", c.name, c.phone, c.email);
    fclose(fp);

    printf("\n\tContact added successfully!\n");
     printf("\n\t Press any key to continue...");
    getch();
}






void viewRecord() {
    int option;
    do {
    	system("Cls");
    	
        printf("\n\t*********************************************\n");
        printf("\t*                 VIEW RECORD                *\n");
        printf("\t*********************************************\n\n");

        printf("\t Select a record type:\n");
        printf("\t [1] Notes\n");
        printf("\t [2] Meetings\n");
        printf("\t [3] Contacts\n");
        printf("\t [4] Back to main menu\n");
        printf("\t Select Option : ");
        option = getch();
        printf("%d\n", option);

        switch(option) {
            case '1':
                system("cls");
                loadNotes();
                break;
            case '2':
                system("cls");
                loadMeetings();
                break;
            case '3':
                system("cls");
                loadContacts();
                break;
            case '4':
                printf("\n\n\t\t\tReturning to main menu…\n\n");
                break;
            default:
                printf("\n\n\t\t\tInvalid option! Press any key to try again...\n\n");
                getch();
        }

    } while(option != '4');

    system("cls");
}

void loadNotes() {
    int choice;
    printf("\n\t*********************************************\n");
    printf("\t*                    NOTES                    *\n");
    printf("\t*********************************************\n\n");
    printf("\n\t 1) Search by Date \n");
    printf("\t 2) View all \n\t 3) Back \n\t Select : ");
    scanf("%d",&choice);
   

    if (choice == 1)
	 {
        // Search by Date
        char searchDate[20];
        printf("\n\tEnter the date (MM/DD/YYYY): ");
        scanf("%s", searchDate);
        
        system("Cls");
        
        printf("\n\t*********************************************\n");
        printf("\t*                NOTES ON %s                 *\n", searchDate);
        printf("\t*********************************************\n\n");

        // Open the file for reading
        FILE* fp = fopen("notes.txt", "r");
        if (fp == NULL) {
        	
        	printf("\n\t There are no Notes available \n");
        	printf("\n\t Create your first note \n\t Go to Main Menu 1) Add Records");
        	
        }
        else
        {
        	 system("Cls");
        struct Notes note;
        char line[600];  // buffer to hold each line
        int count = 0;
        while (fgets(line, sizeof(line), fp) != NULL)
		 {
            sscanf(line, "%19[^,],%19[^,],%99[^,],%499[^\n]",
                note.date, note.time, note.title, note.details);
            if (strcmp(note.date, searchDate) == 0)
			 {
                count++;
                printf("\n\n\n\tNote %d:\n", count);
                printf("\tDate: %s\n", note.date);
                printf("\tTime: %s\n", note.time);
                printf("\tTitle: %s\n", note.title);
                printf("\tDetails: %s\n", note.details);
                printf("\t...............................\n");
            } 
          }
          
          fclose(fp);

        if (count == 0) 
		   {
            printf("\n\tNo notes found for the given date!\n");
           }
        	
		}
       
    }
	
	else if (choice == 2) 
	{
        // View all
        system("Cls");
        printf("\n\t*********************************************\n");
        printf("\t*                 ALL NOTES                 *\n");
        printf("\t*********************************************\n\n");

        // Open the file for reading
        FILE* fp = fopen("notes.txt", "r");
        if (fp == NULL)
		{
            printf("\n\t There are no Notes available \n");
        	printf("\n\t Create your first note \n\t Go to Main Menu 1) Add Records");
    
        }
        else
        {
		
        // Read each note from the file and display all notes
        struct Notes notes[MAX_NOTES];
        int count = 0;
        char line[600];  // buffer to hold each line
        while (fgets(line, sizeof(line), fp) != NULL)
		 {
            sscanf(line, "%19[^,],%19[^,],%99[^,],%499[^\n]",
                notes[count].date, notes[count].time, notes[count].title, notes[count].details);
            count++;
         }

        fclose(fp);

        // Display the notes based on their index in the array
        for (int i = 0; i < count; i++) 
		{
            printf("\tNote %d:\n", i + 1);
            printf("\tDate: %s\n", notes[i].date);
            printf("\tTime: %s\n", notes[i].time);
            printf("\tTitle: %s\n", notes[i].title);
            printf("\tDetails: %s\n", notes[i].details);
            printf("\t...............................\n");
        }
    }
    }
	
	else if (choice==3)
	{
        return ;
    }
    
    else {
    	printf("\nInvalid choice!\n");
	}
	
	printf("\n\t Press any key to continue....");
	getch();
}


void loadMeetings() {
    int choice;
    printf("\n\t*********************************************\n");
    printf("\t*                  MEETINGS                  *\n");
    printf("\t*********************************************\n\n");
    printf("\n\t 1) Search by Date \n");
    printf("\t 2) View all \n\t 3) Back \n\t Select : ");
    scanf("%d", &choice);

    if (choice == 1) 
	{
        // Search by Date
        char searchDate[20];
        printf("\n\tEnter the date (MM/DD/YYYY): ");
        scanf("%s", searchDate);
        
        system("Cls");
        
        printf("\n\t*********************************************\n");
        printf("\t*              MEETINGS ON %s                *\n", searchDate);
        printf("\t*********************************************\n\n");

        // Open the file for reading
        FILE* fp = fopen("meetings.txt", "r");
        if (fp == NULL) {
            printf("\n\t There are no Meetings available \n");
        	printf("\n\t Create your first meeting \n\t Go to Main Menu 1) Add Records");
        }

        // Read each meeting from the file and display only the meetings with matching date
        struct Meetings meetings;
        char line[700];  // buffer to hold each line
        int count = 0;
        while (fgets(line, sizeof(line), fp) != NULL) 
      	{ 
		    sscanf(line, "%19[^,],%19[^,],%99[^,],%499[^,],%49[^,],%19[^,],%19[^,],%49[^\n]\n", 
                  meetings.date, meetings.time, meetings.title, meetings.details, 
                  meetings.name, meetings.phone, meetings.email, meetings.address);
         if (strcmp(meetings.date, searchDate) == 0) 
		 {
                count++;
                printf("\tMeeting %d:\n", count);
                 printf("\tDate: %s\n", meetings.date);
                 printf("\tTime: %s\n", meetings.time);
        printf("\tTitle: %s\n", meetings.title);
        printf("\tDetails: %s\n", meetings.details);
        printf("\tName: %s\n", meetings.name);
        printf("\tPhone: %d\n",meetings.phone);
        printf("\tEmail: %s\n",meetings.email);
        printf("\tAddress: %s\n",meetings.address);
        printf("\t...............................\n");
            }
            
             fclose(fp);

        if (count == 0) {
            printf("\n\tNo meetings found for the given date!\n");
        }
        }
    
    
        
         
    } 
	
	else if (choice == 2) 
	{
        // View all
        system("Cls");
        
        printf("\n\t*********************************************\n");
        printf("\t*                 ALL MEETINGS                 *\n");
        printf("\t*********************************************\n\n");

        // Open the file for reading
        FILE* fp = fopen("meetings.txt", "r");
        if (fp == NULL) {
            printf("\n\t There are no Meetings available \n");
        	printf("\n\t Create your first meeting \n\t Go to Main Menu 1) Add Records");
        	printf("\n\t Press any key to continue....");
        	getch();
            return;
        }
        
         struct Meetings meetings[MAX_MEETINGS];
    int count = 0;

    while (fscanf(fp, "%19[^,],%19[^,],%99[^,],%499[^,],%49[^,],%19[^,],%19[^,],%49[^\n]\n", 
                  meetings[count].date, meetings[count].time, meetings[count].title, meetings[count].details, 
                  meetings[count].name, meetings[count].phone, meetings[count].email, meetings[count].address) == 8) {
        count++;
    }

    fclose(fp);

    // Display the meetings based on their index in the array
    for (int i = 0; i < count; i++) {
        printf("\tMeeting %d:\n", i+1);
        printf("\tDate: %s\n", meetings[i].date);
        printf("\tTime: %s\n", meetings[i].time);
        printf("\tTitle: %s\n", meetings[i].title);
        printf("\tDetails: %s\n", meetings[i].details);
        printf("\tName: %s\n", meetings[i].name);
        printf("\tPhone: %d\n",meetings[i].phone);
        printf("\tEmail: %s\n",meetings[i].email);
        printf("\tAddress: %s\n",meetings[i].address);
        printf("\t...............................\n");
        
    }
	
     }
	else if (choice==3) {
        return ;
    }
    
    else {
    	printf("\nInvalid choice!\n");
	}   
    printf("\n\t Press any key to continue....");
        getch();
}
        

void loadContacts()
{
	
    int choice;
   
    printf("\n\t*********************************************\n");
    printf("\t*                  CONTACTS                  *\n");
    printf("\t*********************************************\n\n");
    printf("\n\t 1) Search by Name \n");
    printf("\t 2) View all \n\t 3) Back \n\t Select : ");
    scanf("%d",&choice);

    if (choice == 1)
	 {
        // Search by Name
        char searchName[50];
        printf("\n\tEnter the name to search: ");
        scanf("%s", searchName);
        system("Cls");
        printf("\n\t*********************************************\n");
        printf("\t*              CONTACTS FOR %s               *\n", searchName);
        printf("\t*********************************************\n\n");

        // Open the file for reading
        FILE *fp = fopen("contacts.txt", "r");
        if (fp == NULL) {
           
           printf("\n\t There are no Contacts available \n");
        	printf("\n\t Add your first contact \n\t Go to Main Menu 1) Add Records");
        }
        else
        {
		
        // Read each contact from the file and display only the contacts with matching name
        struct Contacts contact;
        int count = 0;
        while (fscanf(fp, "%49[^,],%19[^,],%19[^\n]\n", contact.name, contact.phone, contact.email) == 3) 
		  {
            if (strcmp(contact.name, searchName) == 0)
			 {
                count++;
                printf("\tContact %d:\n", count);
                printf("\tName: %s\n", contact.name);
                printf("\tPhone: %s\n", contact.phone);
                printf("\tEmail: %s\n", contact.email);
                printf("\t...............................\n");
             }
        
          }
         fclose(fp);

        if (count == 0) {
            printf("\n\tNo notes found for the given date!\n");
        }
       }
     
    }
        
    else if (choice == 2) 
	{
    	
    	system("Cls");
        	 printf("\n\t*********************************************\n");
        printf("\t*                 ALL CONTACTS                 *\n");
        printf("\t*********************************************\n\n");

        // Open the file for reading
        FILE* fp = fopen("contacts.txt", "r");
        if (fp == NULL) {
           printf("\n\t There are no Contacts available \n");
        	printf("\n\t Add your first contact \n\t Go to Main Menu 1) Add Records");
        }
            
        struct Contacts contacts[MAX_CONTACTS];
         int count = 0;

        while (fscanf(fp, "%49[^,],%19[^,],%19[^\n]\n", contacts[count].name, contacts[count].phone, contacts[count].email) == 3)
	    {
        count++;
       }

    fclose(fp);

    // Display the contacts based on their index in the array
    for (int i = 0; i < count; i++) {
        printf("\tContact %d:\n", i+1);
        printf("\tName: %s\n", contacts[i].name);
        printf("\tPhone: %s\n", contacts[i].phone);
        printf("\tEmail: %s\n", contacts[i].email);
        printf("\t...............................\n");
    }
    
   
  
   }
   
   
  else if (choice==3)
   {
        return ;
    }
    
    else
	 {
    	printf("\nInvalid choice!\n");
	}
	
	printf("\n\t Press any key to continue....");
    getch();
    
            
            
}

void editRecord() 
{
	printf("\n\t*********************************************\n");
    printf("\t*                EDIT RECORDS                *\n");
    printf("\t*********************************************\n\n");
	
    int option;
    printf("\t  Select an option:\n");
    printf("\t [1] Edit notes\n");
    printf("\t [2] Edit meetings\n");
    printf("\t [3] Edit contacts\n");
    printf("\t [4] Back to main menu\n");
    printf("\t --> ");
    scanf("%d", &option);
    switch (option) {
        case 1:
        	system("Cls");
            editNotes();
            break;
        case 2:
        	system("Cls");
            editMeetings();
            break;
        case 3:
        	system("Cls");
            editContacts();
            break;
         case '4':
            printf("\n\n\t\t\tReturning to main menu…\n\n");
            break;
        default:
            printf("\n\n\t\t\tInvalid option! Please try again.\n\n");
       
    }
}

void editNotes()
{
    printf("\n\t*********************************************\n");
    printf("\t*                EDIT NOTES                  *\n");
    printf("\t*********************************************\n\n");
    
    // Open the file for reading
    FILE *fp = fopen("notes.txt", "r");
    if (fp == NULL)
    {
         printf("\n\t There are no notes available to edit\n");
         printf("\n\t Add your first note \n\t Go to Main Menu 1) Add Records");
    }

    else
    {
	
    struct Notes notes[100];
    int count = 0;

    while (fscanf(fp, "%19[^,],%19[^,],%99[^,],%499[^\n]\n", notes[count].date, notes[count].time, notes[count].title, notes[count].details) == 4)
    {
        count++;
    }

    fclose(fp);

    // Display the notes based on their index in the array
    for (int i = 0; i < count; i++)
    {
        printf("Note %d:\n", i+1);
        printf("\tDate: %s\n", notes[i].date);
        printf("\tTime: %s\n", notes[i].time);
        printf("\tTitle: %s\n", notes[i].title);
        printf("\tDetails: %s\n\n", notes[i].details);
    }

    // Ask the user which note to edit
    int index;
    printf("Enter the index of the note you want to edit: ");
    scanf("%d", &index);

    if (index < 1 || index > count)
    {
        printf("Invalid index!\n");
        return;
    }

    index--;

    // Update the selected note
    printf("\nEnter new date (DD/MM/YYYY): ");
    scanf("%19s", notes[index].date);

    printf("Enter new time (HH:MM): ");
    scanf("%19s", notes[index].time);

    printf("Enter new title: ");
    scanf("%99s", notes[index].title);

    printf("Enter new details: ");
    scanf("%499s", notes[index].details);

    // Write the updated notes back to the file
    fp = fopen("notes.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file!");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s,%s,%s,%s\n", notes[i].date, notes[i].time, notes[i].title, notes[i].details);
    }

    fclose(fp);
    
    printf("\nNote %d updated successfully!\n", index+1);
   }

    
     printf("\n\t Press any key to continue...");
    getch();
}

void editMeetings()
{
    printf("\n\t*********************************************\n");
    printf("\t*               EDIT MEETING                 *\n");
    printf("\t*********************************************\n\n");

    // Open the file for reading and writing
    FILE *fp = fopen("meetings.txt", "r");
    if (fp == NULL) {
         printf("\n\t There are no meetings available to edit\n");
         printf("\n\t Add your first meeting \n\t Go to Main Menu 1) Add Records");
    }
    else
    {
	
    struct Meetings meetings[MAX_MEETINGS];
    int count = 0;

    while (fscanf(fp, "%19[^,],%19[^,],%99[^,],%499[^,],%49[^,],%19[^,],%19[^,],%49[^\n]\n", 
                  meetings[count].date, meetings[count].time, meetings[count].title, meetings[count].details, 
                  meetings[count].name, meetings[count].phone, meetings[count].email, meetings[count].address) == 8) {
        count++;
    }


   fclose(fp);
   
   for (int i = 0; i < count; i++) {
        printf("Meeting %d:\n", i+1);
        printf("\tDate: %s\n", meetings[i].date);
        printf("\tTime: %s\n", meetings[i].time);
        printf("\tTitle: %s\n", meetings[i].title);
        printf("\tDetails: %s\n", meetings[i].details);
        printf("\tName: %s\n", meetings[i].name);
        printf("\tPhone: %d\n",meetings[i].phone);
        printf("\tEmail: %s\n",meetings[i].email);
        printf("\tAddress: %s\n",meetings[i].address);
        
    }
    
    // Get the index of the meeting to be edited
     int index;
    printf("Enter the index of the note you want to edit: ");
    scanf("%d", &index);

    if (index < 1 || index > count)
    {
        printf("Invalid index!\n");
        return;
    }
    
    index--;

    // Display the details of the selected meeting
    printf("\nSelected meeting:\n");
    printf("\tDate: %s\n", meetings[index].date);
    printf("\tTime: %s\n", meetings[index].time);
    printf("\tTitle: %s\n", meetings[index].title);
    printf("\tDetails: %s\n", meetings[index].details);
    printf("\tName: %s\n", meetings[index].name);
    printf("\tPhone: %s\n", meetings[index].phone);
    printf("\tEmail: %s\n", meetings[index].email);
    printf("\tAddress: %s\n", meetings[index].address);

    // Prompt the user to enter the new details of the meeting
    printf("\nEnter the new details of the meeting:\n");
    printf("\tEnter date (DD/MM/YYYY): ");
    scanf("%19s", meetings[index].date);

    printf("\tEnter time (HH:MM): ");
    scanf("%19s", meetings[index].time);

    printf("\tEnter title: ");
    scanf("%99s", meetings[index].title);

    printf("\tEnter details: ");
    scanf("%499s", meetings[index].details);

    printf("\tEnter name: ");
    scanf("%49s", meetings[index].name);

    printf("\tEnter phone: ");
    scanf("%19s", meetings[index].phone);

    printf("\tEnter email: ");
    scanf("%19s", meetings[index].email);

    printf("\tEnter address: ");
    scanf("%49s", meetings[index].address);

    // Overwrite the old meeting with the updated meeting
     fp = fopen("meetings.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file!");
        return;
    }
    for (int i = 0; i < count; i++) 
	{
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", meetings[i].date, meetings[i].time, meetings[i].title, meetings[i].details, meetings[i].name, meetings[i].phone,meetings[i].email,meetings[i].address);
     }
 
     fclose(fp);
     
      printf("\nMeeting %d updated successfully!\n", index+1);
      
   } 
       printf("\n\t Press any key to continue...");
    getch();
 
}

void editContacts()
{
    printf("\n\t*********************************************\n");
    printf("\t*               EDIT CONTACT                 *\n");
    printf("\t*********************************************\n\n");

    // Open the file for reading
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
         printf("\n\t There are no contacts available to edit\n");
         printf("\n\t Add your first contact \n\t Go to Main Menu 1) Add Records");
    }

    else
    {
	
    struct Contacts contacts[MAX_CONTACTS];
    int count = 0;

    while (fscanf(fp, "%49[^,],%19[^,],%19[^\n]\n", contacts[count].name, contacts[count].phone, contacts[count].email) == 3) {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++) {
        printf("Contact %d:\n", i+1);
        printf("\tName: %s\n", contacts[i].name);
        printf("\tPhone: %d\n",contacts[i].phone);
        printf("\tEmail: %s\n",contacts[i].email);
        }
        
        
         int index;
    printf("Enter the index of the note you want to edit: ");
    scanf("%d", &index);

    if (index < 1 || index > count)
    {
        printf("Invalid index!\n");
        return;
    }
    
    index--;

    // Display the details of the selected meeting
    printf("\nSelected contact :\n");
    printf("\tName: %s\n", contacts[index].name);
    printf("\tPhone: %s\n", contacts[index].phone);
    printf("\tEmail: %s\n", contacts[index].email);
    
     printf("\nEnter the new details of the meeting:\n");
     printf("\tEnter name: ");
    scanf("%49s", contacts[index].name);

    printf("\tEnter phone: ");
    scanf("%19s", contacts[index].phone);

    printf("\tEnter email: ");
    scanf("%19s", contacts[index].email);
    
    fp = fopen("contacts.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file!");
        return;
    }
    for (int i = 0; i < count; i++) 
	{
        fprintf(fp, "%s,%s,%s\n", contacts[i].name, contacts[i].phone,contacts[i].email);
     }
 
     fclose(fp);
     
      printf("\nConttact %d updated successfully!\n", index+1);
      
   } 
       printf("\n\t Press any key to continue...");
    getch();
 
 
}


int login() {
    int option;
    char input[20];
    printf("\n\n\n\n\n\t\t\t\t   WELCOME TO PERSONAL DIARY MANAGEMENT");
    printf("\n\n\n\n\n\t\t\t\t-------------------------------------------\n");

    char password[MAX_PASSWORD_LEN];
    FILE* fp = fopen("pass.dat", "r");
    if (fp == NULL) {
        // If the password file doesn't exist, set the default password
        printf("\t\t\t\t\tCreating password file...\n");
        printf("\t\t\t\t Default password is set to 'password'\n\t\t\t You can change it anytime from the edit password option\n");
        fp = fopen("pass.dat", "w");
        fprintf(fp, "password");
        fclose(fp);

        // Open the newly created password file
        fp = fopen("pass.dat", "r");
        if (fp == NULL) {
            printf("\t\t\t\tError opening password file!\n");
            return 0;
        }
    }

    fgets(password, MAX_PASSWORD_LEN, fp);
    fclose(fp);

    // remove newline character from password string
    password[strcspn(password, "\n")] = '\0';

    do {
        printf("\n\n\n\n\n\t\t\t\t\t Enter Password : ");
        scanf("%s", input);

        if(strcmp(input, password) != 0) {
            printf("\n\t\t\t\tInvalid password!\n");
            printf("\n\t\t\t\tPress '1' to try again or '2' to exit :");

            do {
                option = getchar();
                fflush(stdin); // clear input buffer
            } while(option != '1' && option != '2');

            if(option == '2') {
                return 0;
            }
            system("cls"); // clear screen for another try
        }
    } while (strcmp(input, password) != 0);

    return 1;
}


void editPassword() {
    char password[MAX_PASSWORD_LEN];
    char input[MAX_PASSWORD_LEN];
    int option;
    FILE* fp = fopen("pass.dat", "r");
    if (fp == NULL) {
        printf("\t\t\nError opening password file!\n");
        return;
    }
    fgets(password, MAX_PASSWORD_LEN, fp);
    fclose(fp);


     password[strcspn(password, "\n")] = '\0';
     
      printf("\n\t*********************************************\n");
    printf("\t*               EDIT PASSWORD                  *\n");
    printf("\t*********************************************\n\n");
    
     do {
        printf("\tEnter old password: ");
         
         scanf("%s", input);
        
         if (strcmp(input, password) != 0)
		  {
            printf("\tInvalid password!\n");
            printf("\t1) Try again\n");
            printf("\t2) Go back to previous menu\n");
            printf("\tChoose an option: ");
             do {
                option = getchar();
                fflush(stdin); // clear input buffer
            } while(option != '1' && option != '2');

            if(option == '2') {
                return ;
            }
            system("cls");
            
        }
   } while(strcmp(input, password) != 0);


    printf("\tEnter new password: ");
    char newPassword[MAX_PASSWORD_LEN];
    scanf("%s", newPassword);

    fp = fopen("pass.dat", "w");
    if (fp == NULL) {
        printf("Error opening password file!\n");
        return;
    }
    fputs(newPassword, fp);
    fclose(fp);

    printf("\n\tPassword updated!\n");
    printf("\n\t Press any key to continue...");
    getch();
    
    
}

void deleteRecord() 
{
    char type[20];
    int i, j;
    int deleteIndex = -1;
    char confirm;
    
    int option, count = 0;
    do
    {
	system("Cls");
    
    printf("\n\t*********************************************\n");
    printf("\t*              DELETE RECORD                  *\n");
    printf("\t*********************************************\n\n");
    
    printf("\tSelect the record type to edit:\n");
    printf("\t [1] Notes\n");
    printf("\t [2] Meetings\n");
    printf("\t [3] Contacts\n");
    printf("\t [4] Back to main menu\n");
    
    printf("\t Enter your choice (1-4): ");
    scanf("%d", &option);
    
     switch (option) {
        case 1:
        	system("Cls");
            deleteNotes();
            break;
        case 2:
        	system("Cls");
            deleteMeetings();
            break;
        case 3:
        	system("Cls");
            deleteContacts();
            break;
         case '4':
            printf("\n\n\t\t\tReturning to main menu…\n\n");
            break;
        default:
            printf("\n\n\t\t\tInvalid option! Please try again.\n\n");
        }
		
		}while(option!=4);
        
}

void deleteNotes()
{
    printf("\n\t*********************************************\n");
    printf("\t*              DELETE NOTES                  *\n");
    printf("\t*********************************************\n\n");

    // Open the file for reading
    FILE *fp = fopen("notes.txt", "r");
    if (fp == NULL)
    {
        printf("\n\t There are no notes available to delete\n");
         printf("\n\t Add your first note \n\t Go to Main Menu 1) Add Records");
    }

    else
    {
	
    struct Notes notes[100];
    int count = 0;

    while (fscanf(fp, "%19[^,],%19[^,],%99[^,],%499[^\n]\n", notes[count].date, notes[count].time, notes[count].title, notes[count].details) == 4)
    {
        count++;
    }

    fclose(fp);

    // Display the notes based on their index in the array
    for (int i = 0; i < count; i++)
    {
        printf("Note %d:\n", i+1);
        printf("\tDate: %s\n", notes[i].date);
        printf("\tTime: %s\n", notes[i].time);
        printf("\tTitle: %s\n", notes[i].title);
        printf("\tDetails: %s\n\n", notes[i].details);
    }

    // Ask the user which note to delete
    int index;
    printf("Enter the index of the note you want to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > count)
    {
        printf("Invalid index!\n");
        return;
    }

    index--;

    // Remove the selected note from the array
    for (int i = index; i < count - 1; i++)
    {
        notes[i] = notes[i+1];
    }

    count--;

    // Write the updated notes back to the file
    fp = fopen("notes.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file!");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s,%s,%s,%s\n", notes[i].date, notes[i].time, notes[i].title, notes[i].details);
    }

    fclose(fp);

    printf("\n\t Note %d deleted successfully!\n", index+1);
     }
    
    printf("\n\t Press any key to continue...");
    getch();
}

void deleteMeetings()
{
    printf("\n\t*********************************************\n");
    printf("\t*              DELETE MEETING                *\n");
    printf("\t*********************************************\n\n");

    // Open the file for reading and writing
    FILE *fp = fopen("meetings.txt", "r+");
    if (fp == NULL) {
        printf("\n\t There are no meetings available to delete\n");
         printf("\n\t Add your first meeting \n\t Go to Main Menu 1) Add Records");
    }

    else
    {
	
    struct Meetings meetings[MAX_MEETINGS];
    int count = 0;

    while (fscanf(fp, "%19[^,],%19[^,],%99[^,],%499[^,],%49[^,],%19[^,],%19[^,],%49[^\n]\n", 
                  meetings[count].date, meetings[count].time, meetings[count].title, meetings[count].details, 
                  meetings[count].name, meetings[count].phone, meetings[count].email, meetings[count].address) == 8) {
        count++;
    }

    fclose(fp);
   
    for (int i = 0; i < count; i++) {
        printf("Meeting %d:\n", i+1);
        printf("\tDate: %s\n", meetings[i].date);
        printf("\tTime: %s\n", meetings[i].time);
        printf("\tTitle: %s\n", meetings[i].title);
        printf("\tDetails: %s\n", meetings[i].details);
        printf("\tName: %s\n", meetings[i].name);
        printf("\tPhone: %s\n",meetings[i].phone);
        printf("\tEmail: %s\n",meetings[i].email);
        printf("\tAddress: %s\n",meetings[i].address);
        
    }
    
    // Get the index of the meeting to be deleted
    int index;
    printf("Enter the index of the meeting you want to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > count)
    {
        printf("Invalid index!\n");
        return;
    }
    
    index--;


    // Shift all the meetings after the deleted meeting one index to the left
    for (int i = index; i < count-1; i++)
    {
        meetings[i] = meetings[i+1];
    }
    count--;

    // Overwrite the file with the updated meetings
    fp = fopen("meetings.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file!");
        return;
    }
    for (int i = 0; i < count; i++) 
    {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", meetings[i].date, meetings[i].time, meetings[i].title, meetings[i].details, meetings[i].name,meetings[i].phone,meetings[i].email,meetings[i].address);

     }
     
      fclose(fp);

    printf("\nNote %d deleted successfully!\n", index+1);
    
    }
     printf("\n\t Press any key to continue...");
    getch();


}

void deleteContacts() {
    printf("\n\t*********************************************\n");
    printf("\t*              DELETE CONTACT                *\n");
    printf("\t*********************************************\n\n");

    // Open the file for reading
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
        printf("\n\t There are no contacts available to delete\n");
         printf("\n\t Add your first contact \n\t Go to Main Menu 1) Add Records");
    }

    else
    {
	
    struct Contacts contacts[MAX_CONTACTS];
    int count = 0;

    while (fscanf(fp, "%49[^,],%19[^,],%19[^\n]\n", contacts[count].name, contacts[count].phone, contacts[count].email) == 3) {
        count++;
    }

    fclose(fp);

    // Display the contacts to the user
    for (int i = 0; i < count; i++) {
        printf("Contact %d:\n", i+1);
        printf("\tName: %s\n", contacts[i].name);
        printf("\tPhone: %s\n", contacts[i].phone);
        printf("\tEmail: %s\n", contacts[i].email);
    }

    // Ask the user which contact to delete
    int index;
    printf("Enter the index of the contact you want to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > count)
    {
        printf("Invalid index!\n");
        return;
    }

    index--;

    // Move all contacts after the deleted one up by one position in the array
    for (int i = index; i < count-1; i++) {
        strcpy(contacts[i].name, contacts[i+1].name);
        strcpy(contacts[i].phone, contacts[i+1].phone);
        strcpy(contacts[i].email, contacts[i+1].email);
    }

    count--;

    // Open the file for writing
    fp = fopen("contacts.txt", "w");
    if (fp == NULL)
    {
        printf("\nError opening file!");
        return;
    }

    // Write the updated contacts to the file
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(fp);

    printf("\nContact %d deleted successfully!\n", index+1);
     }
     printf("\n\t Press any key to continue...");
    getch();
}

