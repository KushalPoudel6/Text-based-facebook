/********* main.c ********
    Student Name 	= Kushal Poudel
    Student Number	= 101298706
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"
int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    connect_friends_to_posts(users);
    char name[MAX_USERNAME_LENGTH];
    fclose(csv_file);
    printf("*************************************\n");
    printf("Welome to text-based facebook! \n");
    printf("************************************* \n");
    unsigned short int user_choice = 0;
    user_t * user;
    char pass[MAX_PASSWORD_LENGTH];
    while(true)
    {
        printf("________________________________\n");
        printf("          MAIN MENU           \n");
        printf("________________________________\n");
        printf("1: Register new user \n2: Login with user information \n3: Exit \n");
        user_choice = get_input_usi();
        switch(user_choice)
        {
            case 1:
                printf("Enter the name of this user: \n");
                scanf("%s", name);
                
                if (check_unique_name(users, str_lower(name)))
                {
                    users = register_user(users, str_lower(name));
                }
                else{
                    printf("Not a unique name. \n");
                }
                break;
            case 2:
                printf("Enter username: \n");
                scanf("%s", name);
                user = find_user(users, str_lower(name));
                if (user == NULL) printf("No username like that exists.");
                else {
                    printf("Enter password for this account: \n");
                    scanf("%s", pass);
                    if (strcmp(pass, user->password) == 0)
                    {
                        logged_in_menu(users, user);
                    }
                    else{
                        printf("Wrong password there.");
                    }
                }
                break;
            case 3:
                printf("Goodbye... \n");
                teardown(users);
                return EXIT_SUCCESS;
            default:
                printf("Not a valid input, please try again. \n");
        }
    }



}