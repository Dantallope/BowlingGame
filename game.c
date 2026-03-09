#include <stdio.h>
#include "ansi-colors.h"

void setUpPins(char arr[], int len);
void printPins(char arr[], int len);
int game(char arr[], int len);
int check(char arr[], int len, int var);
int main()
{
    printf("Bowling Game!\n");
    printf("A two player game where you take turns knocking down pins(I) and the last one to knock over a pin wins!\n");
    printf("If the pin you select had another next to it, you may knock that one over as well, or you can just do the one by pressing 0.\n\n");

    int pinLength;
    do
    {
        printf("How many pins (3-10) :");
        scanf("%d", &pinLength);

        if (pinLength < 3 || pinLength > 10)
        {
            printf("Please pick an acceptable number of pins (3-10)\n");
        }
    } while (pinLength < 3 || pinLength > 10);

    char pins[pinLength];
    setUpPins(pins, pinLength);
    printPins(pins, pinLength);
    int pinUp = 1;
    int player = 0;
    while (pinUp)
    {
        if (player == 0)
        {
            printf("\n%sPlayer 1's%s turn\n", RED, CRESET);
        }
        else
        {
            printf("\n%sPlayer 2's%s turn\n", GRN, CRESET);
        }

        if (game(pins, pinLength))
        {
            printPins(pins, pinLength);
            pinUp = check(pins, pinLength, player);

            if (pinUp)
            {
                player = (player == 0) ? 1 : 0;
            }
        }
    }
    return 0;
}

void setUpPins(char arr[], int len)
{

    for (int i = 0; i < len; i++)
    {
        arr[i] = '8';
    }
}

void printPins(char arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%c ", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", i + 1);
    }
}

int game(char arr[], int len)
{
    int choice;
    printf("Choose a pin (1-%d): ", len);
    scanf("%d", &choice);

    int idx = choice - 1;

    if (idx < 0 || idx >= len)
    {
        printf("Invalid pin number\n");
        return 0;
    }

    if (arr[idx] != '8')
    {
        printf("That pin is already down\n");
        return 0;
    }

    arr[idx] = 'o';

    int left = idx - 1;
    int right = idx + 1;

    int leftUp = (left >= 0 && arr[left] == '8');
    int rightUp = (right < len && arr[right] == '8');

    if (!leftUp && !rightUp)
    {
        return 1;
    }

    printf("You may also knock down an adjacent pin: ");
    if (leftUp)
        printf("%d ", left + 1);
    if (rightUp)
        printf("%d ", right + 1);
    printf("Or press 0 to skip: ");

    int choice2;
    scanf("%d", &choice2);

    if (choice2 == 0)
        return 1;

    int idx2 = choice2 - 1;
    if ((idx2 == left && leftUp) || (idx2 == right && rightUp))
    {
        arr[idx2] = 'o';
        return 1;
    }
    else
    {
        printf("Not a valid adjacent pin.\n");
        return 1;
    }
}

int check(char arr[], int len, int var)
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == '8')
        {
            return 1;
        }
    }
    int player = var + 1;
    printf("\nPlayer %d wins!!", player);
    return 0;
}