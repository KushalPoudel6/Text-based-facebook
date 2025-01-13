/*****************
    Student Name 	=   Kushal Poudel
    Student Number	= 101298706
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#define STARTING_DISPLAY 3
// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   user_t *new_user = malloc(sizeof(user_t));
   assert(new_user != NULL);
   strncpy(new_user->username, username, sizeof(new_user->username) - 1);
   new_user->username[sizeof(new_user->username) - 1] = '\0';

   strncpy(new_user->password, password, sizeof(new_user->password) - 1);
   new_user->password[sizeof(new_user->password) - 1] = '\0';

   new_user->friends = NULL;
   new_user->posts = NULL;
   new_user->next = NULL;
   // if it's the first user or if it should be at the head of the linked list
   if (users == NULL || strcmp(username, users->username) <= 0)
   {
      new_user->next = users;
      return new_user;
   }
   user_t *head = users;
   while (head->next != NULL)
   {
      if (strcmp(username, head->next->username) <= 0) // adding it to the middle of the list
      {
         user_t *temp = head->next;
         head->next = new_user;
         new_user->next = temp;
         return users;
      }
      head = head->next;
   }
   head->next = new_user; // adding to the end of the list
   return users;
}

/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *current = users;
   if (current == NULL)
      return NULL;
   while (current != NULL)
   {
      if (strcmp(username, current->username) == 0)
         return current;
      current = current->next;
   }
   return NULL;
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *friend = malloc(sizeof(friend_t));
   assert(friend != NULL);
   strncpy(friend->username, username, sizeof(friend->username) - 1);
   friend->username[sizeof(friend->username) - 1] = '\0';
   friend->next = NULL;
   return friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *newf = create_friend(friend);
   friend_t *current = user->friends;
   if (current == NULL)
   {
      user->friends = newf;
      return;
   } // If there is no other friends
   if (strcmp(friend, current->username) <= 0) // If the new friend should be at the start of list
   {
      newf->next = user->friends;
      user->friends = newf;
      return;
   }
   while (current->next != NULL)
   {
      if (strcmp(friend, current->next->username) <= 0)
      {
         friend_t *temp = current->next;
         current->next = newf;
         newf->next = temp;
         return;
      }
      current = current->next;
   }
   current->next = newf; // add the new friend to end of list
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   if (user->friends == NULL)
      return false;
   friend_t *head = user->friends;
   if (strcmp(head->username, friend_name) == 0) // if you must remove the first friend
   {
      user->friends = head->next;
      free(head);
      return true;
   }

   while (head->next != NULL)
   {
      if (strcmp(head->next->username, friend_name) == 0)
      {
         friend_t *new_next = head->next->next;
         free(head->next);
         head->next = new_next;
         return true;
      }

      head = head->next;
   }
   // Friend not found
   return false;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *post = malloc(sizeof(post_t));
   assert(post != NULL);
   post->next = NULL;
   strncpy(post->content, text, sizeof(post->content) - 1);
   post->content[sizeof(post->content) - 1] = '\0';
   return post;
}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{
   post_t *post = create_post(text);
   post->next = user->posts;
   user->posts = post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
   if (user->posts == NULL)
      return false;
   post_t *temp = user->posts;
   user->posts = user->posts->next;
   free(temp);
   return true;
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
   printf("---------------------------------------------------------------------\n");
   printf("                    %s's posts \n", user->username);
   if (user->posts == NULL)
   {
      printf("This user has no posts. \n");
      return;
   }
   post_t *head = user->posts;
   unsigned short int i = 1;
   while (head->next != NULL)
   {
      printf("%hu. %s \n", i, head->content);
      head = head->next;
      i++;
   }
   printf("%hu. %s \n", i, head->content);
   printf("---------------------------------------------------------------------\n");
   return;
}

/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
   if (user->friends == NULL)
   {
      printf("This user has no friends :( \n");
      return;
   }
   friend_t *head = user->friends;
   unsigned short int i = 1;
   while (head->next != NULL)
   {
      printf("%hu-    %s \n", i, head->username);
      head = head->next;
      i++;
   }
   printf("%hu-    %s \n", i, head->username);
   return;
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_posts_by_n(user_t *users, int number)
{
   if (users == NULL)
   {
      printf("This user does not exist. \n");
      return;
   }
   post_t *current = users->posts;
   unsigned short int counter = 1;
   char userChoice;
   while (current != NULL && counter <= number)
   {
      printf("%hu. %s \n", counter, current->content);
      counter++;
      current = current->next;
   }

   while (userChoice != 'n' && userChoice != 'N' && current != NULL)
   {
      printf("Do you want to display more posts? (y/n), (Y/N) \n");
      scanf(" %c", &userChoice);
      if (userChoice == 'y' || userChoice == 'Y')
      {
         for (int i = 0; i < 3 && current != NULL; current = current->next, i++)
         {
            printf("%hu. %s \n", counter, current->content);
            counter++;
         }
      }
      else if (userChoice == 'n' || userChoice == 'N')
      {
         printf("No more posts will be displayed. \n");
         return;
      }
      else
      {
         printf("Not a valid input. Input y or Y for more posts. Input n or N to return to the main menu \n");
      }
   }

   printf("These are all of this users posts. \n");
   return;
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *temp_u, *head_u;
   friend_t *temp_f, *head_f;
   post_t *temp_p, *head_p;
   head_u = users;
   while (head_u != NULL)
   {
      temp_u = head_u->next;

      head_f = head_u->friends;
      head_p = head_u->posts;

      while (head_f != NULL) // freeing all friends of this user
      {
         temp_f = head_f->next;
         free(head_f);
         head_f = temp_f;
      }
      while (head_p != NULL) // freeing all posts of this user
      {
         temp_p = head_p->next;
         free(head_p);
         head_p = temp_p;
      }
      free(head_u);
      head_u = temp_u;
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu(char *name)
{
   printf("***********************************\n");
   printf("        Welcome %s:             \n", name);
   printf("***********************************\n");
   printf("1. Manage profile (change password)  \n");
   printf("2. Manage posts (add/remove)  \n");
   printf("3. Manage friends (add/remove)  \n");
   printf("4. Display a friends posts  \n");
   printf("5. Exit  \n");
   printf("-----------------------------------\n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   srand(time(NULL));
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}

/*
   Get unsigned short integer user input.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
unsigned short int get_input_usi(void)
{
   unsigned short int value;
   do
   {
      scanf(" %hu", &value);
      if (value < 0)
      {
         printf("Error: Value must be positive.\n");
      }

   } while (value < 0);

   return value;
}

user_t *register_user(user_t *users, char *name)
{
   char password[MAX_PASSWORD_LENGTH];
   printf("Enter the password (mininmum 8 characters): \n");
   scanf("%s", password);
   if (is_length_at_least_x(password, 8))
   {
      printf("*** User Added! *** \n");
      return add_user(users, name, password);
   }
   printf("Password not long enough \n");
   return users;
}

void manage_profile(user_t *users, user_t *user)
{
   if (user == NULL)
   {
      printf("***************************\n");
      printf("       USER NOT FOUND      \n");
      printf("***************************\n");
      return;
   }

   char pass[MAX_PASSWORD_LENGTH];
   printf("Enter the password for this account: \n");
   scanf("%s", pass);
   if (strcmp(pass, user->password) == 0)
   {
      printf("Enter the new password (Max 15 characters) \n");
      scanf("%s", user->password);
      printf("*** Password Changed ***! \n");
   }
   else
   {
      printf("Wrong password buddy.\n");
      return;
   }
}

void manage_posts(user_t *users, user_t *user)
{
   if (user == NULL)
   {
      printf("***************************\n");
      printf("       USER NOT FOUND      \n");
      printf("***************************\n");
      return;
   }
   printf("---------------------------\n");
   printf("  Managing %s's posts     \n", user->username);
   printf("---------------------------\n");

   unsigned short int userChoice = 0;
   bool is_deleted = false;
   while (userChoice != 3)
   {
      if (user->posts == NULL)
      {
         printf("NOTE: THIS USER HAS NO POSTS \n");
      }
      printf("1. Add a new post \n2. Remove a post \n3. Return to main menu \n");
      userChoice = get_input_usi();
      switch (userChoice)
      {
      case 1:
         char post[MAX_CONTENT_LENGTH];
         printf("Content of the post: \n");
         scanf(" %[^\n]s", post);
         add_post(user, post);
         display_all_user_posts(user);
         break;
      case 2:
         is_deleted = delete_post(user);
         if (is_deleted)
         {
            printf("Post sucessfully deleted \nUpdated list:");
            display_all_user_posts(user);
         }
         else
         {
            printf("Unable to delete post :( \n");
         }
         break;
      case 3:
         return;
      default:
         printf("Invalid choice, please re-input a value \n");
      }
   }
}

void manage_friends(user_t *users, user_t *user)
{
   user_t *friend;
   if (user == NULL)
   {
      printf("***************************\n");
      printf("       USER NOT FOUND      \n");
      printf("***************************\n");
      return;
   }
   printf("--------------------------------\n");
   printf(" Managing %s's friends     \n", user->username);
   printf("--------------------------------\n");

   unsigned short int userChoice = 0;
   while (true)
   {
      printf("1. Add a new friend \n2. Remove a friend \n3. Return to main menu \n Enter your choice:");
      userChoice = get_input_usi();
      switch (userChoice)
      {
      case 1:
         char new_f[MAX_USERNAME_LENGTH];
         printf("Name of friend: \n");
         scanf(" %s", new_f);
         friend = find_user(users, new_f);
         if (friend == NULL)
         {
            printf("This user is not registered! \n");
         }
         else
         {
            add_friend(user, new_f);
            printf("%s has been added to the list. \n", new_f);
            friend_t *head = user->friends;
            while (strcmp(head->username, new_f) != 0) head = head->next;
            head->posts = &friend->posts;
         }

         break;
      case 2:
         char f_name[MAX_USERNAME_LENGTH];
         printf("List of %s's friends: \n", user->username);
         display_user_friends(user);
         if (user->friends != NULL)
         {
            printf("Enter a friend's name to delete:");
            scanf(" %s", f_name);
            if (delete_friend(user, f_name))
            {
               printf("--------------------------------------------\n");
               printf("Updated list of friends: \n");
               display_user_friends(user);
               printf("--------------------------------------------\n");
            }
            else
            {
               printf("Invalid friend's name \n \n");
            }
         }

         break;
      case 3:
         return;
      default:
         printf("Invalid choice, please re-input a value \n");
      }
   }
}

void logged_in_menu(user_t *users, user_t *logged_user)
{
   unsigned short int user_choice = 0;
   while (true)
   {
      print_menu(logged_user->username);
      user_choice = get_input_usi();
      switch (user_choice)
      {
      case 1:
         manage_profile(users, logged_user);
         break;
      case 2:
         manage_posts(users, logged_user);
         break;
      case 3:
         manage_friends(users, logged_user);
         break;
      case 4:
         printf("The name of the friend whose posts you would like to see: \n");
         char name[MAX_USERNAME_LENGTH];
         scanf("%s", name);
         if (is_friend(logged_user, name))
         {
            display_posts_by_n(find_user(users, name), STARTING_DISPLAY);
         }
         else
         {
            printf("Not your friend ! \n");
         }
         break;
      case 5:
         printf("Logging out... \n");
         return;
      default:
         break;
      }
   }
}

char *str_lower(char *str)
{
   char *head = str;
   while (*str != '\0')
   {
      // Check if the character is uppercase (ASCII 'A' to 'Z') then add 32 to get lowercase
      if (*str >= 'A' && *str <= 'Z')
      {
         *str = *str + 32;
      }
      str++;
   }
   return head;
}

bool check_unique_name(user_t *users, char *name)
{
   user_t *current = users;
   while (current != NULL)
   {
      if (strcmp(current->username, name) == 0)
      {
         return false;
      }
      current = current->next;
   }
   return true;
}

bool is_length_at_least_x(const char *str, int x)
{
   if (str == NULL)
      return false;

   int length = 0;
   while (*str)
   {
      length++;
      if (length >= x)
      {
         return true;
      }
      str++;
   }
   return false;
}

bool is_friend(user_t *user, char *name)
{
   friend_t *current = user->friends;
   while (current != NULL)
   {
      if (strcmp(name, current->username) == 0)
      {
         return true;
      }
      current = current->next;
   }
   return false;
}

void connect_friends_to_posts(user_t *users)
{
   for (user_t *current_user = users; current_user != NULL; current_user = current_user->next)
   {
      // Iterate through the friends of the current user
      for (friend_t *current_friend = current_user->friends; current_friend != NULL; current_friend = current_friend->next)
      {
         user_t *associated_user = users;
         while (associated_user != NULL)
         {
            if (strcmp(associated_user->username, current_friend->username) == 0)
            {
               current_friend->posts = &associated_user->posts;
               break;
            }
            associated_user = associated_user->next;
         }

         // If no associated user was found, set the friend's post pointer to NULL
         if (associated_user == NULL)
         {
            current_friend->posts = NULL;
         }
      }
   }
}