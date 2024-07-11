#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_USERS 100
#define MAX_PAYMENTS 100
#define EXTRA_MEAL_COST 5.0 // Cost per extra meal

// Data structure for Admin
struct Admin
{
    char username[50];
    char password[50];
    int logged_in; // Flag to check if admin is logged in (0 for logged out, 1 for logged in)
};

// Data structure for User
struct User
{
    char username[50];
    char password[50];
    char name[100];
    char address[200];
    char phone[15];
    int roll;
    int room_no;
    int meal_count;
    float meal_cost;
    int extra_meal_count;
    int has_permission; // Flag to indicate user's permissions (0 for no permission, 1 for permission)
};

// Data structure for Payment
struct Payment
{
    int user_roll;
    char method[10]; // Bkash or Nogod
    char user_number[15];
    char user_name[100];
    char user_address[200];
    int user_room_no;
    float amount;
};

// Global variables
struct Admin admin; // Single admin for simplicity
struct User users[MAX_USERS];
int user_count = 0;
struct Payment payments[MAX_PAYMENTS];
int payment_count = 0;

// Function prototypes
void adminSignIn();
void adminLogin();
void adminLogout();
void addStudentDetails();
void allocateRoom();
void addMealCost();
void addExtraMeal();
void addUserPermission();
void revokeUserPermission();
void viewStudentDetails();
void viewStudentPayments();
void userLogin();
void userLogout();
void requestExtraMeal();
void viewMealCost();
void viewMonthlyCost();
void addPaymentDetails(char method[]);
void generateReceipt(struct Payment *payment);
void displayMainMenu();

// Main function
int main()
{
    int choice;

    while (1)
    {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin); // Clear input buffer

        switch (choice)
        {
        case 1:
            adminSignIn();
            break;
        case 2:
            adminLogin();
            break;
        case 3:
            adminLogout();
            break;
        case 4:
            addStudentDetails();
            break;
        case 5:
            allocateRoom();
            break;
        case 6:
            addMealCost();
            break;
        case 7:
            addExtraMeal();
            break;
        case 8:
            addUserPermission();
            break;
        case 9:
            revokeUserPermission();
            break;
        case 10:
            viewStudentDetails();
            break;
        case 11:
            viewStudentPayments();
            break;
        case 12:
            userLogin();
            break;
        case 13:
            userLogout();
            break;
        case 14:
            requestExtraMeal();
            break;
        case 15:
            viewMealCost();
            break;
        case 16:
            viewMonthlyCost();
            break;
        case 17:
            addPaymentDetails("Bkash");
            break;
        case 18:
            addPaymentDetails("Nogod");
            break;
        case 19:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

// Function implementations

void adminSignIn()
{
    if (admin.logged_in)
    {
        printf("Admin %s is already signed in.\n", admin.username);
        return;
    }

    printf("Enter Admin Username: ");
    scanf("%s", admin.username);
    printf("Enter Admin Password: ");
    scanf("%s", admin.password);
    admin.logged_in = 1;
    printf("Admin %s signed in successfully.\n", admin.username);
}

void adminLogin()
{
    if (admin.logged_in)
    {
        printf("Admin %s is already logged in.\n", admin.username);
        return;
    }

    char username[50];
    char password[50];

    printf("Enter Admin Username: ");
    scanf("%s", username);
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0)
    {
        admin.logged_in = 1;
        printf("Admin %s logged in successfully.\n", admin.username);
    }
    else
    {
        printf("Invalid username or password. Login failed.\n");
    }
}

void adminLogout()
{
    if (!admin.logged_in)
    {
        printf("No admin is currently logged in.\n");
        return;
    }

    admin.logged_in = 0;
    printf("Admin %s logged out.\n", admin.username);
}

void addStudentDetails()
{
    if (!admin.logged_in)
    {
        printf("Admin login required to add student details.\n");
        return;
    }

    if (user_count >= MAX_USERS)
    {
        printf("Maximum number of users reached. Cannot add more.\n");
        return;
    }

    struct User newUser;

    printf("Enter Roll: ");
    scanf("%d", &newUser.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]s", newUser.name);
    printf("Enter Address: ");
    scanf(" %[^\n]s", newUser.address);
    printf("Enter Phone No: ");
    scanf("%s", newUser.phone);
    printf("Enter Room No: ");
    scanf("%d", &newUser.room_no);

    users[user_count] = newUser;
    user_count++;

    printf("Student details added successfully.\n");
}

void allocateRoom()
{
    // Implement room allocation logic
    printf("Room allocation feature is not implemented yet.\n");
}

void addMealCost()
{
    for (int i = 0; i < user_count; i++)
    {
        printf("Enter meal cost for %s: ", users[i].name);
        scanf("%f", &users[i].meal_cost);
    }
    printf("Meal costs updated successfully.\n");
}

void addExtraMeal()
{
    for (int i = 0; i < user_count; i++)
    {
        printf("Enter extra meal count for %s: ", users[i].name);
        scanf("%d", &users[i].extra_meal_count);
    }
    printf("Extra meals count updated successfully.\n");
}

void addUserPermission()
{
    if (!admin.logged_in)
    {
        printf("Admin login required to add user permission.\n");
        return;
    }

    int roll;
    printf("Enter user roll number to grant permission: ");
    scanf("%d", &roll);

    int found = 0;
    for (int i = 0; i < user_count; i++)
    {
        if (users[i].roll == roll)
        {
            users[i].has_permission = 1;
            printf("Permission granted to user %d (%s).\n", users[i].roll, users[i].name);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("User with roll number %d not found.\n", roll);
    }
}

void revokeUserPermission()
{
    if (!admin.logged_in)
    {
        printf("Admin login required to revoke user permission.\n");
        return;
    }

    int roll;
    printf("Enter user roll number to revoke permission: ");
    scanf("%d", &roll);

    int found = 0;
    for (int i = 0; i < user_count; i++)
    {
        if (users[i].roll == roll)
        {
            users[i].has_permission = 0;
            printf("Permission revoked for user %d (%s).\n", users[i].roll, users[i].name);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("User with roll number %d not found.\n", roll);
    }
}

void viewStudentDetails()
{
    printf("Student Details:\n");
    for (int i = 0; i < user_count; i++)
    {
        printf("Roll: %d, Name: %s, Address: %s, Phone: %s, Room No: %d\n", users[i].roll, users[i].name, users[i].address, users[i].phone, users[i].room_no);
    }
}

void viewStudentPayments()
{
    printf("Student Payments:\n");
    for (int i = 0; i < payment_count; i++)
    {
        printf("Payment Method: %s, User Roll: %d, Amount: %.2f\n", payments[i].method, payments[i].user_roll, payments[i].amount);
    }
}

void userLogin()
{
    char username[50];
    char password[50];

    printf("Enter User Username: ");
    scanf("%s", username);
    printf("Enter User Password: ");
    scanf("%s", password);

    int found = 0;
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            printf("User %s logged in successfully.\n", users[i].name);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Invalid username or password. User login failed.\n");
    }
}

void userLogout()
{
    printf("User logout feature is not implemented yet.\n");
}

void requestExtraMeal()
{
    int roll;
    printf("Enter your roll number to request extra meals: ");
    scanf("%d", &roll);

    int found = 0;
    for (int i = 0; i < user_count; i++)
    {
        if (users[i].roll == roll)
        {
            int extraMeals;
            printf("Enter number of extra meals requested: ");
            scanf("%d", &extraMeals);
            users[i].extra_meal_count += extraMeals;
            printf("Extra meals requested successfully for user %d (%s).\n", users[i].roll, users[i].name);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("User with roll number %d not found.\n", roll);
    }
}

void viewMealCost()
{
    for (int i = 0; i < user_count; i++)
    {
        float totalCost = users[i].meal_cost + (users[i].extra_meal_count * EXTRA_MEAL_COST);
        printf("User: %s (Roll: %d), Total Meal Cost: %.2f\n", users[i].name, users[i].roll, totalCost);
    }
}

void viewMonthlyCost()
{
    float totalMonthlyCost = 0.0;
    for (int i = 0; i < user_count; i++)
    {
        float totalCost = users[i].meal_cost + (users[i].extra_meal_count * EXTRA_MEAL_COST);
        totalMonthlyCost += totalCost;
    }
    printf("Total Monthly Cost for all users: %.2f\n", totalMonthlyCost);
}

void addPaymentDetails(char method[])
{
    if (!admin.logged_in)
    {
        printf("Admin login required to add payment details.\n");
        return;
    }

    struct Payment newPayment;

    printf("Enter User Roll: ");
    scanf("%d", &newPayment.user_roll);
    printf("Enter Amount: ");
    scanf("%f", &newPayment.amount);

    strcpy(newPayment.method, method); // Copy payment method (Bkash or Nogod)

    payments[payment_count] = newPayment;
    payment_count++;

    printf("Payment details added successfully.\n");
}

void generateReceipt(struct Payment *payment)
{
    // Implement receipt generation logic
    printf("Receipt generated for %s: %.2f\n", payment->user_name, payment->amount);
}

void displayMainMenu()
{
    printf("\nHostel Management System\n");
    printf("1. Admin Sign In\n");
    printf("2. Admin Login\n");
    printf("3. Admin Logout\n");
    printf("4. Add Student Details\n");
    printf("5. Allocate Room\n");
    printf("6. Add Meal Cost\n");
    printf("7. Add Extra Meal\n");
    printf("8. Add User Permission\n");
    printf("9. Revoke User Permission\n");
    printf("10. View Student Details\n");
    printf("11. View Student Payments\n");
    printf("12. User Login\n");
    printf("13. User Logout\n");
    printf("14. Request Extra Meal\n");
    printf("15. View Meal Cost\n");
    printf("16. View Monthly Cost\n");
    printf("17. Add Bkash Payment\n");
    printf("18. Add Nogod Payment\n");
    printf("19. Exit\n");
}
