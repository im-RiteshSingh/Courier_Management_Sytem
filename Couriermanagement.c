#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

struct Package 
{
    char id[10];
    char sender[50];
    char receiver[50];
    char address[100];
    char status[20];
    float weight;
};

void start();
void add_package();
void search_package();
void update_package();
void delete_package();
void display_packages();


int checkLogin(char username[], char password[]) {
    char buffer[256];
    FILE *fp = fopen("users.txt", "r");
    while (fgets(buffer, 256, fp)) {
        char *saved_username = strtok(buffer, ",");
        char *saved_password = strtok(NULL, ",");
        saved_password[strcspn(saved_password, "\n")] = 0; 
        if (strcmp(username, saved_username) == 0 && strcmp(password, saved_password) == 0) {
            fclose(fp);
            return 1; 
        }
    }
    fclose(fp);
    return 0; 
}


void createUser(char username[], char password[]) 
{
    FILE *fp = fopen("users.txt", "a");
    fprintf(fp, "%s,%s\n", username, password);
    fclose(fp);

}


int main() 
{
    int choice;
    char username[256], password[256];

    do {
        printf("************************************************\n");
        printf("*  WELCOME TO COURIER MANAGEMENT SYSTEM        *\n");
        printf("************************************************\n\n");
        printf("Please select an option from the menu below:\n");
        printf("1. Login\n");
        printf("2. Sign up\n");
        printf("3. Quit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
            case 1:
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", password);
                if (checkLogin(username, password)) {
                    printf("\n************************************************\n");
                    printf("*             LOGIN SUCCESSFUL! WELCOME        *\n");
                    printf("************************************************\n\n");
                    start();
                } else {
                    printf("\n************************************************\n");
                    printf("*             INVALID USERNAME OR PASSWORD      *\n");
                    printf("************************************************\n\n");
                }
                break;
            case 2:
                printf("Enter your desired username: ");
                scanf("%s", username);
                printf("Enter your desired password: ");
                scanf("%s", password);
                createUser(username, password);
                printf("\n************************************************\n");
                printf("*              ACCOUNT CREATED SUCCESSFULLY!    *\n");
                printf("************************************************\n\n");
                break;
            case 3:
                printf("\n************************************************\n");
                printf("*                  GOODBYE!                      *\n");
                printf("************************************************\n\n");
                break;
            default:
                printf("\n************************************************\n");
                printf("*              INVALID CHOICE! TRY AGAIN         *\n");
                printf("************************************************\n\n");
                break;
        }
    } while (choice != 3);

    return 0;
}


void start() {
    int choice;
    while(1) {
        printf("\n*********************************************\n");
        printf("*           COURIER MANAGEMENT SYSTEM       *\n");
        printf("*********************************************\n\n");
        printf("Please select an option from the menu below:\n");
        printf("1. Insert Package\n");
        printf("2. Search Package\n");
        printf("3. Update Package\n");
        printf("4. Delete Package\n");
        printf("5. Display All Packages\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_package();
                break;
            case 2:
                search_package();
                break;
            case 3:
                update_package();
                break;
            case 4:
                delete_package();
                break;
            case 5:
                display_packages();
                break;
            case 6:
                printf("\n********************************************\n");
                printf("*                 GOODBYE!                 *\n");
                printf("********************************************\n\n");
                exit(0);
            default:
                printf("\n********************************************\n");
                printf("*           INVALID CHOICE! TRY AGAIN       *\n");
                printf("********************************************\n\n");
        }
    }
}








void add_package() {
    struct Package package;
    FILE *fp;    

    printf("\n********************************************\n");
    printf("*               ADD A NEW PACKAGE          *\n");
    printf("********************************************\n\n");
    printf("Please enter the following details:\n");
    printf("Package ID: ");
    scanf("%s", package.id);
    printf("Sender name: ");
    scanf(" %[^\n]", package.sender);
    printf("Receiver name: ");
    scanf(" %[^\n]", package.receiver);
    printf("Delivery address: ");
    scanf(" %[^\n]", package.address);
    printf("Package weight (in kg): ");
    scanf("%f", &package.weight);

    strcpy(package.status, "In Transit");

    fp = fopen("packages.txt", "a+");
    if(fp == NULL) {
        printf("\n********************************************\n");
        printf("*          ERROR OPENING PACKAGES FILE!     *\n");
        printf("********************************************\n\n");
        return;
    }

    fwrite(&package, sizeof(package), 1, fp);

    printf("\n********************************************\n");
    printf("*          PACKAGE ADDED SUCCESSFULLY!     *\n");
    printf("********************************************\n\n");

    fclose(fp);
}



void search_package() {
    char id[10], name[50];
    int option, found = 0;
    struct Package package;
    FILE *fp;

    printf("\n**************************************");
    printf("\n*         Search Package Menu        *");
    printf("\n**************************************\n");
    printf("1. Search by ID\n");
    printf("2. Search by Sender Name\n");
    printf("3. Search by Receiver Name\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            printf("\nEnter package ID: ");
            scanf("%s", id);
            break;
        case 2:
            printf("\nEnter sender name: ");
            scanf(" %[^\n]", name);
            break;
        case 3:
            printf("\nEnter receiver name: ");
            scanf(" %[^\n]", name);
            break;
        default:
            printf("\nInvalid choice!\n");
            return;
    }

    fp = fopen("packages.txt", "a+");
    if(fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\n**************************************");
    printf("\n*             Search Results         *");
    printf("\n**************************************\n");
    while(fread(&package, sizeof(package), 1, fp)) {
        switch(option) {
            case 1:
                if(strcmp(package.id, id) == 0) {
                    found = 1;
                }
                break;
            case 2:
                if(strcmp(package.sender, name) == 0) {
                    found = 1;
                }
                break;
            case 3:
                if(strcmp(package.receiver, name) == 0) {
                    found = 1;
                }
                break;
        }

        if(found) {
            printf("Package ID: %s\n", package.id);
            printf("Sender Name: %s\n", package.sender);
            printf("Receiver Name: %s\n", package.receiver);
            printf("Delivery Address: %s\n", package.address);
            printf("Package Weight: %.2f kg\n", package.weight);
            printf("Package Status: %s\n", package.status);
            printf("\n");
            break;
        }
    }

    if(!found) {
        printf("Package Not Found\n");
    }

    fclose(fp);
}



void update_package() {
    char id[10];
    int found = 0, option;
    struct Package package;
    FILE *fp, *temp;

    printf("\nEnter package ID: ");
    scanf("%s", id);

    fp = fopen("packages.txt", "a+");
    if(fp == NULL) {
        printf("Error opening file!");
        return;
    }

    temp = fopen("temp.txt", "a+");
    if(temp == NULL) {
        printf("Error opening file!");
        return;
    }

    while(fread(&package, sizeof(package), 1, fp)) {
        if(strcmp(package.id, id) == 0) {
            found = 1;
            printf("\n**************************************");
            printf("\n*           Package Found            *");
            printf("\n**************************************");
            printf("\n1. Update Sender Name");
            printf("\n2. Update Receiver Name");
            printf("\n3. Update Delivery Address");
            printf("\n4. Update Package Weight");
            printf("\nEnter your choice: ");
            scanf("%d", &option);

            switch(option) {
                case 1:
                    printf("\nEnter new sender name: ");
                    scanf(" %[^\n]", package.sender);
                    break;
                case 2:
                    printf("\nEnter new receiver name: ");
                    scanf(" %[^\n]", package.receiver);
                    break;
                case 3:
                    printf("\nEnter new delivery address: ");
                    scanf(" %[^\n]", package.address);
                    break;
                case 4:
                    printf("\nEnter new package weight: ");
                    scanf("%f", &package.weight);
                    break;
                default:
                    printf("\nInvalid choice!\n");
                    return;
            }

            printf("\n**************************************");
            printf("\n*          Package Updated           *");
            printf("\n**************************************");
            printf("\nPackage ID: %s", package.id);
            printf("\nSender Name: %s", package.sender);
            printf("\nReceiver Name: %s", package.receiver);
            printf("\nDelivery Address: %s", package.address);
            printf("\nPackage Weight: %.2f kg", package.weight);
            printf("\nPackage Status: %s\n", package.status);
        }

        fwrite(&package, sizeof(package), 1, temp);
    }

    if(!found) {
        printf("\n**************************************");
        printf("\n*        Package Not Found           *");
        printf("\n**************************************\n");
    }

    fclose(fp);
    fclose(temp);

    remove("packages.txt");
    rename("temp.txt", "packages.txt");
}



void delete_package() {
    char id[10];
    int found = 0;
    struct Package package;
    FILE *fp, *temp;

    printf("\n**************************************");
    printf("\n*            Delete Package         *");
    printf("\n**************************************");

    printf("\n\nEnter package ID: ");
    scanf("%s", id);

    fp = fopen("packages.txt", "r");
    if(fp == NULL) {
        printf("Error opening file!");
        return;
    }

    temp = fopen("temp.txt", "w");
    if(temp == NULL) {
        printf("Error opening file!");
        return;
    }

    while(fread(&package, sizeof(package), 1, fp)) {
        if(strcmp(package.id, id) != 0) {
            fwrite(&package, sizeof(package), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if(found) {
        remove("packages.txt");
        rename("temp.txt", "packages.txt");

        printf("\nPackage Deleted\n");
    } else {
        remove("temp.txt");

        printf("\nPackage Not Found\n");
    }
}



void display_packages() {
    
    struct Package package;
   FILE *fp;

    fp = fopen("packages.txt", "r");
    if(fp == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("\n**************************************");
    printf("\n*         Package Information        *");
    printf("\n**************************************");
    printf("\nID\tSender\t\tReceiver\tWeight\tStatus");
    printf("\n--------------------------------------------------\n");

    while(fread(&package, sizeof(package), 1, fp)) {
        printf("%s\t%s\t%s\t%.2f\t%s\n", package.id, package.sender, package.receiver, package.weight, package.status);
    }

    fclose(fp);
}