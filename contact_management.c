#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Contact {
    char name[50];
    char phone[15];
    struct Contact* next;
    struct Contact* prev;
};

struct Contact* head = NULL;
struct Contact* current = NULL;

void toLower(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int isValidPhone(char phone[]) {
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i]))
            return 0;
    }
    return 1;
}

void addContact() {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));

    printf("Enter Name: ");
    scanf("%s", newContact->name);

    do {
        printf("Enter 10-digit Phone: ");
        scanf("%s", newContact->phone);

        if (!isValidPhone(newContact->phone)) {
            printf(" Enter exactly 10 digits.\n");
        }

    } while (!isValidPhone(newContact->phone));

    newContact->next = head;
    newContact->prev = NULL;

    if (head != NULL)
        head->prev = newContact;

    head = newContact;
    current = head;

    printf("Contact Added Successfully!\n");
}

void displayContacts() {
    struct Contact* temp = head;

    if (temp == NULL) {
        printf("No contacts available.\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (temp != NULL) {
        printf("Name: %s, Phone: %s\n", temp->name, temp->phone);
        temp = temp->next;
    }
}

int compareNames(char a[], char b[]) {
    char x[50], y[50];
    strcpy(x, a);
    strcpy(y, b);
    toLower(x);
    toLower(y);
    return strcmp(x, y);
}

void searchContact() {
    char name[50];
    printf("Enter name to search: ");
    scanf("%s", name);

    struct Contact* temp = head;

    while (temp != NULL) {
        if (compareNames(temp->name, name) == 0) {
            current = temp;
            printf("Found -> Name: %s, Phone: %s\n", temp->name, temp->phone);
            return;
        }
        temp = temp->next;
    }

    printf("Contact not found!\n");
}

void deleteContact() {
    char name[50];
    printf("Enter name to delete: ");
    scanf("%s", name);

    struct Contact* temp = head;

    while (temp != NULL) {
        if (compareNames(temp->name, name) == 0) {

            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;

            free(temp);
            printf("Contact Deleted!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Contact not found!\n");
}

void updateContact() {
    char name[50];
    printf("Enter name to update: ");
    scanf("%s", name);

    struct Contact* temp = head;

    while (temp != NULL) {
        if (compareNames(temp->name, name) == 0) {

            do {
                printf("Enter new 10-digit phone: ");
                scanf("%s", temp->phone);

                if (!isValidPhone(temp->phone)) {
                    printf("Invalid! Enter exactly 10 digits.\n");
                }

            } while (!isValidPhone(temp->phone));

            printf("Contact Updated!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Contact not found!\n");
}

void nextContact() {
    if (current && current->next) {
        current = current->next;
        printf("Next -> Name: %s, Phone: %s\n", current->name, current->phone);
    } else {
        printf("No next contact.\n");
    }
}

void prevContact() {
    if (current && current->prev) {
        current = current->prev;
        printf("Previous -> Name: %s, Phone: %s\n", current->name, current->phone);
    } else {
        printf("No previous contact.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== CONTACT LIST MENU =====\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Update Contact\n");
        printf("6. Next Contact\n");
        printf("7. Previous Contact\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: updateContact(); break;
            case 6: nextContact(); break;
            case 7: prevContact(); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 8);

    return 0;
}