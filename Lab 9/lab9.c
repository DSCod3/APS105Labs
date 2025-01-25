
#include "contactList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// IF IT'S EASIER, YOU NEED NOT BE OVERLY GENERAL/FLEXIBLE
// BUT CAN ASSUME THESE LIMITS
#define MAXCONTACTS 30 /* max # of contacts */
#define MAXPHONES 10 /* max # of phone numbers for each contact */

#define PHONE_NUMBER_MAX_LENGTH 12

typedef struct t_PhoneEntry
{
   struct t_PhoneEntry* _next;
   char _phone[PHONE_NUMBER_MAX_LENGTH + 1];
} PhoneEntry;

typedef struct t_ContactEntry
{
   struct t_ContactEntry *_next;
   char* _name;
   PhoneEntry* _phones; /* list of phones */
} ContactEntry;

ContactEntry* allContacts = NULL;

// INCLUDE YOUR OWN "HELPER" ROUTINES AS YOU SEE FIT


/* print contact list in alphabetical order of contact names */

void printContactEntry(ContactEntry* contact) {
   PhoneEntry* phoneEntry = contact->_phones;
   printf("Name: %s\n", contact->_name);
   printf("Phone(s):");
    
   while (phoneEntry)
   {
      printf(" %s", phoneEntry->_phone);
      phoneEntry = phoneEntry->_next;
   }
   printf("\n");
}

void printAllContacts() 
{
   ContactEntry* crtContact = allContacts;
   while (crtContact)
   {
      printContactEntry(crtContact);
      crtContact = crtContact->_next;
   }
}

void ListAllContacts()
{
   printAllContacts();
}

/* find the contact with a given name */

ContactEntry* findContact(const char* name)
{
   ContactEntry* crtContact = allContacts;
   while (crtContact)
   {
      int cmp = strcmp(name, crtContact->_name);
      if (cmp == 0)
         return crtContact;
      if (cmp < 0)
         return NULL; // assume list  is sorted
      crtContact = crtContact->_next;
   }
   return NULL; /* not found */
}

void addContact(ContactEntry* newContact)
{
  if (!allContacts)
   {
      allContacts = newContact;
   }
   else
   {
      ContactEntry* crtContact = allContacts;
      ContactEntry* prevContact = NULL;
      do
      {
         int cmp = strcmp(newContact->_name, crtContact->_name);
         if (cmp == 0)
         {
            fprintf(stderr, "Contact %s already exists. Ignoring\n", newContact->_name);
            return;
         }
         if (cmp < 0)
         {
            newContact->_next = crtContact;
            if (prevContact)
               prevContact->_next = newContact;
            else
               allContacts = newContact;
            return;
         }
       
         prevContact = crtContact;
         crtContact = crtContact->_next;
      } while (crtContact);
      prevContact->_next = newContact;
   }
}

/*
 * convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
void convertInputToDataStructure() {

   // YOUR CODE HERE
   ContactEntry* crtContact = NULL;
   int numEntries = sizeof(contactList) / sizeof(*contactList);
   //printf("Num entries %d\n", numEntries);

   
   for (int i = 0; i < numEntries; i++)
   {
      if (isalpha(contactList[i][0]))
      {
         /* new name; must add previous contact to my contact list */
         if (crtContact)
         {
            /* add to my list of contacts*/
            addContact(crtContact);
         }
         crtContact = (ContactEntry*)malloc(sizeof(ContactEntry));
         // TODO test against NULL
         crtContact->_name = (char*)malloc(strlen(contactList[i]));
         strcpy(crtContact->_name, contactList[i]);
         crtContact->_phones = NULL;
         crtContact->_next = NULL;
      }
      else if (isdigit(contactList[i][0]))
      {
         /* this is a phone number */
         PhoneEntry* phoneEntry = (PhoneEntry*)malloc(sizeof(PhoneEntry));
         strcpy(phoneEntry->_phone, contactList[i]);
         /* add to the list of phones for current contact */
         if (crtContact)
         {
            phoneEntry->_next = crtContact->_phones;
            crtContact->_phones = phoneEntry;
         }
         else
         {
            fprintf(stderr, "Malformed input. Phone number must be preceded by a name");
            exit(-1);
         }
      }
      else
      {
         fprintf(stderr, "Unexpected first character in input list %d\n", contactList[i][0]);
         exit(-1);
      }
   }
   /* add the last entry */
   if (crtContact)
   {
      /* add to my list of contacts*/
      addContact(crtContact);
   }
//   printAllContacts();
}


/*
 * printMenu - Prints out the user menu
 */
void printMenu() {
   printf("\n\nEnter a command by number\n");
   printf("1. List all contacts in alphabetical order\n");
   printf("2. Print phone(s) for a contact\n");
   printf("3. Find duplicate entries\n");
   printf("4. Delete contact\n");
   printf("5. Exit the program\n");
   printf("Your input: ");
}


void printContact(const char* name) 
{
   // YOUR CODE HERE
   ContactEntry* contactEntry = findContact(name);
   if (contactEntry)
   {
      printContactEntry(contactEntry);
   }
   else
   {
      printf("Contact not found\n");
   }
}

char* rtrim(char* str)
{
   int i;
   for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; i--)
      str[i] = '\0';
   return str;
}


void PrintContact()
{
   printf("Enter name: ");
   char name[256];
   char *s = fgets(name, sizeof(name), stdin);
   if (s)
   {
      s = rtrim(s); /* eliminate trailing \n*/
      printContact(s);
   }
}

/* delete contact from contact list */

void deleteContact(const char* name)
{
   ContactEntry* crtContact = allContacts;
   ContactEntry* prevContact = NULL;
   while (crtContact)
   {
      if (strcmp(name, crtContact->_name) == 0)
      {
         if (prevContact)
            prevContact->_next = crtContact->_next;
         else
            allContacts = crtContact->_next;
         PhoneEntry* crtPhoneEntry = crtContact->_phones;
         //printf("phones=%p\n", crtPhoneEntry);
         while (crtPhoneEntry)
         {
            PhoneEntry* next = crtPhoneEntry->_next;
            free(crtPhoneEntry);
            crtPhoneEntry = next;
         }
         //printf("deleted all phone entries\n");
         //printf("name=%s\n", crtContact->_name);
         free(crtContact->_name);
         //printf("Deleted name\n");
         free(crtContact);
         //printf("Deleted entry for %s\n", name);
         return;
      }
      prevContact = crtContact;
      crtContact = crtContact->_next;
   }
   printf("Contact not found\n");
}

/*
 * DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 * 
 */

void DeleteContact()
{
   printf("Enter name: ");
   char name[256];
   char* s = fgets(name, sizeof(name), stdin);
   if (s)
   {
      s = rtrim(s); /* eliminate trailing \n*/
      deleteContact(s);
   }
}


/*
 * findDuplicates finds the names of contacts with 
 * a phone number in common
 * 
 * 
 * 
 */

void FindDuplicates()
{
   int noDuplicates = 1;
   ContactEntry* baseEntry = allContacts;
   while (baseEntry)
   {
      ContactEntry* nextEntry = baseEntry->_next;
      while (nextEntry)
      {
         // If any of the phones in the baseEntry is the same as the phone in
         // the nextEntry, then we say they are duplicates
         PhoneEntry* ph1 = baseEntry->_phones;
         int foundDuplicate = 0;
         while (ph1 && !foundDuplicate)
         {
            PhoneEntry* ph2 = nextEntry->_phones;
            while (ph2 && !foundDuplicate)
            {
               if (strcmp(ph1->_phone, ph2->_phone) == 0)
               {
                  printf("%s and %s have a phone number in common\n", baseEntry->_name, nextEntry->_name);
                  foundDuplicate = 1;
                  noDuplicates = 0;
               }
               ph2 = ph2->_next;
            }
            ph1 = ph1->_next;
         }
         nextEntry = nextEntry->_next;
      }
      baseEntry = baseEntry->_next;
   }
   if (noDuplicates)
      printf("No duplicates found\n");
}

int main()
{
   // first move data from contactList.h to a data structure
   convertInputToDataStructure();
   
   char notDone = 1;
   while (notDone) {
      printMenu();
      char userChoice[100];
      char* s = fgets(userChoice, sizeof(userChoice), stdin);
      if (!s)
      {
         printf("Wrong input\n");
         continue;
      }
      s = rtrim(s); /* eliminate trailing \n */
      //printf("selection = %s\n", s);
      int userSelection = atoi(s);

      switch (userSelection) {
         case 1: ListAllContacts(); break;
         case 2: PrintContact(); break;
         case 3: FindDuplicates(); break;
         case 4: DeleteContact(); break;
         case 5: notDone = 0; break;
         default: printf("Bad command...\n"); break;
         }
     
   }
   
   // PUT ANY POST_RUN CODE HERE

   return 0;
}