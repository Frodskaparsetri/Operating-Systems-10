#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SUDOKU_ROWS 9
#define MAX_SUDOKU_COLLUMNS 9
#define IS_VALID 1
#define IS_INVALID 0

int sudokuMap[] = {
    6, 2, 4, 5, 3, 9, 1, 8, 7,
    5, 1, 9, 7, 2, 8, 6, 3, 4,
    8, 3, 7, 6, 1, 4, 2, 9, 5,
    1, 4, 3, 8, 6, 5, 7, 2, 9,
    9, 5, 8, 2, 4, 7, 3, 6, 1,
    7, 6, 2, 3, 9, 1, 4, 5, 8,
    3, 7, 1, 9, 5, 6, 8, 4, 2,
    4, 9, 6, 1, 8, 2, 5, 7, 3,
    2, 8, 5, 4, 7, 3, 9, 1, 6};

typedef struct
{
    int yStart;
    int xStart;
    int width;
    int height;
    int isValid;
} sudokuSection;

int *validationMap;

void *rowValidator(void *params);

int main(int argc, char *argv[])
{
    sudokuSection *sections = (sudokuSection *)malloc(sizeof(sudokuSection) * MAX_SUDOKU_ROWS);

    pthread_t tids[MAX_SUDOKU_ROWS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    for (int i = 0; i < MAX_SUDOKU_ROWS; i++)
    {
        sections[i].xStart = 0;
        sections[i].yStart = i;
        sections[i].height = 1;
        sections[i].width = 9;
        sections[i].isValid = 0;

        pthread_create(&tids[i], &attr, rowValidator, &sections[i]);
    }

    int isInvalid = 0;
    for (int i = 0; i < MAX_SUDOKU_ROWS; i++)
    {
        pthread_join(tids[i], NULL);

        if (!sections[i].isValid)
        {
            isInvalid = 1;
            break;
        }
    }

    if (isInvalid == IS_VALID)
    {
        printf("Invalid\n");
    }
    else
    {
        printf("Valid\n");
    }

    free(validationMap);
    free(sections);

    return 0;
}

void *rowValidator(void *params)
{
    int sum = 0;

    sudokuSection *data = params;
    for (int y = 0; y < data->height; y++)
    {
        int yOffset = y + data->yStart;

        for (int x = 0; x < data->width; x++)
        {
            int xOffset = x + data->xStart;
            int cellValue = sudokuMap[data->width * yOffset + xOffset];

            sum += cellValue;
        }
    }

    printf("Thread - Sum: %d\n", sum);
    if (sum == 45)
    {
        data->isValid = IS_VALID;
    }
    else
    {
        data->isValid = IS_INVALID;
    }

    pthread_exit(0);
}