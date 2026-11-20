#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 50

struct Item
{
    int id;
    char name[50];
    float price;
    int quantity;
};

struct Item items[MAX_ITEMS] =
{
    {101, "Notebook", 40.00, 50},
    {102, "Pen", 10.00, 100},
    {103, "Pencil", 5.00, 100},
    {104, "Eraser", 5.00, 50},
    {105, "Sharpener", 8.00, 50},
    {106, "Scale", 10.00, 40},
    {107, "Marker", 25.00, 30},
    {108, "File", 20.00, 40},
    {109, "Drawing Book", 60.00, 25},
    {110, "Colour Pencils", 80.00, 20}
};

int count = 10;
int totalSales = 0;
float totalRevenue = 0.0;

void displayMenu();
void displayItems();
void addItem();
void searchItem();
void purchaseItem();
void updateStock();
void salesSummary();
int findItem(int id);a

int main()
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf("   STATIONERY SHOP MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Display Stationery Items\n");
        printf("2. Add New Item\n");
        printf("3. Search Item\n");
        printf("4. Purchase Item\n");
        printf("5. Update Stock\n");
        printf("6. Sales Summary\n");
        printf("7. Exit\n");

        printf("------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayItems();
                break;

            case 2:
                addItem();
                break;

            case 3:
                searchItem();
                break;

            case 4:
                purchaseItem();
                break;

            case 5:
                updateStock();
                break;

            case 6:
                salesSummary();
                break;

            case 7:
                printf("\nThank you for visiting our shop!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 7);

    return 0;
}

void displayItems()
{
    int i;

    printf("\n========== STATIONERY ITEMS ==========\n");

    printf("%-8s %-20s %-10s %-10s\n",
           "ID", "Name", "Price", "Stock");

    printf("------------------------------------\n");

    for(i = 0; i < count; i++)
    {
        printf("%-8d %-20s Rs.%-8.2f %-10d\n",
               items[i].id,
               items[i].name,
               items[i].price,
               items[i].quantity);
    }
}

void addItem()
{
    if(count >= MAX_ITEMS)
    {
        printf("\nInventory is full!\n");
        return;
    }

    printf("\nEnter Item ID: ");
    scanf("%d", &items[count].id);

    if(findItem(items[count].id) != -1)
    {
        printf("\nItem ID already exists!\n");
        return;
    }

    printf("Enter Item Name: ");
    scanf(" %49[^\n]", items[count].name);

    printf("Enter Item Price: ");
    scanf("%f", &items[count].price);

    printf("Enter Item Quantity: ");
    scanf("%d", &items[count].quantity);

    if(items[count].price < 0 || items[count].quantity < 0)
    {
        printf("\nInvalid price or quantity!\n");
        return;
    }

    count++;

    printf("\nItem added successfully!\n");
}

void searchItem()
{
    int id, index;

    printf("\nEnter Item ID to search: ");
    scanf("%d", &id);

    index = findItem(id);

    if(index != -1)
    {
        printf("\nItem Found!\n");
        printf("ID       : %d\n", items[index].id);
        printf("Name     : %s\n", items[index].name);
        printf("Price    : Rs.%.2f\n", items[index].price);
        printf("Quantity : %d\n", items[index].quantity);
    }
    else
    {
        printf("\nItem not found!\n");
    }
}

void purchaseItem()
{
    int id, quantity, index;
    float bill;

    printf("\nEnter Item ID: ");
    scanf("%d", &id);

    index = findItem(id);

    if(index == -1)
    {
        printf("\nItem not found!\n");
        return;
    }

    printf("Item Name: %s\n", items[index].name);
    printf("Price: Rs.%.2f\n", items[index].price);
    printf("Available Stock: %d\n", items[index].quantity);

    printf("Enter Quantity to Purchase: ");
    scanf("%d", &quantity);

    if(quantity <= 0)
    {
        printf("\nInvalid quantity!\n");
        return;
    }

    if(quantity > items[index].quantity)
    {
        printf("\nInsufficient Stock!\n");
        return;
    }

    bill = items[index].price * quantity;

    items[index].quantity -= quantity;

    totalSales++;
    totalRevenue += bill;

    printf("\n========== CUSTOMER BILL ==========\n");
    printf("Item Name : %s\n", items[index].name);
    printf("Quantity  : %d\n", quantity);
    printf("Price     : Rs.%.2f\n", items[index].price);
    printf("---------------------------------\n");
    printf("Total Bill: Rs.%.2f\n", bill);
    printf("=================================\n");

    printf("\nPurchase Successful!\n");
}

void updateStock()
{
    int id, quantity, index;

    printf("\nEnter Item ID: ");
    scanf("%d", &id);

    index = findItem(id);

    if(index == -1)
    {
        printf("\nItem not found!\n");
        return;
    }

    printf("Item Name: %s\n", items[index].name);
    printf("Current Stock: %d\n", items[index].quantity);

    printf("Enter New Stock Quantity: ");
    scanf("%d", &quantity);

    if(quantity < 0)
    {
        printf("\nInvalid quantity!\n");
        return;
    }

    items[index].quantity = quantity;

    printf("\nStock Updated Successfully!\n");
}

void salesSummary()
{
    printf("\n========== SALES SUMMARY ==========\n");
    printf("Total Transactions : %d\n", totalSales);
    printf("Total Revenue     : Rs.%.2f\n", totalRevenue);
    printf("=================================\n");
}


int findItem(int id)
{
    int i;

    for(i = 0; i < count; i++)
    {
        if(items[i].id == id)
        {
            return i;
        }
    }

    return -1;
}
