#include <cs50.h>
#include <stdio.h>

void print_spaces(int height, int row_number);
void print_hashes(int row_number);

int main(void)
{       
    int height;
    do 
    {
        height = get_int("Height: ");
    } 
    while (height < 1 || height > 8);
    
    int gap = 2;
    for (int i = 1; i <= height; i++) 
    {
        //print the spaces to the left for that row
        print_spaces(height, i);
        //print the "#" for the row
        print_hashes(i);
        //Leave a gap in the middle of the row
        print_spaces(gap, 0);
        //print the "#" after the gap for that row
        print_hashes(i);
        //start the next row.
        printf("\n");
    }
}

//prints the spaces for a row
void print_spaces(int height, int row_number) 
{
    for (int k = height; k > row_number; k--) 
    {
        printf(" "); 
    }
}

//prints the hashes for a row
void print_hashes(int row_number)
{
    for (int j = 1; j <= row_number; j++) 
    {    
        printf("#");         
    } 
}

