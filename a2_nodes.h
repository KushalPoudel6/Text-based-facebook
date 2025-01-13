/********* nodes.h ********
    Student Name 	=   Kushal Poudel 
    Student Number	=   101298706
*/
#ifndef A2_NODES_H
#define A2_NODES_H

#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 15
#define MAX_CONTENT_LENGTH 250
//I would change the constants to the defines but not allowed to modify :(

/********** DON'T MODIFY **********/
// Structure to represent a linked list of users
typedef struct user
{
    char username[30];
    char password[15];
    struct friend *friends;
    struct post *posts;
    struct user *next;
} user_t;

// Structure to represent linked list of a user's posts
typedef struct friend
{
    char username[30];
    struct post **posts;
    struct friend *next;
}
friend_t;

// Structure to represent linked list of a user's posts
typedef struct post
{
    char content[250];
    struct post *next;
} post_t;

#endif