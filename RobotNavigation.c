#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int maximumLen = 0,
minimumLen = 100;
int maximumfS = 0,
minimumfS = 0;
int maxTurn = 0, 
minTurn = 100;
int startPoint = 0;
int endPoint = 39;

#define length 9
int worldSpace[length][length] =
    {
                    { 1, 0, 1, 0, 1, 0, 0, 0, 1},
                    { 0, 0, 1, 0, 0, 0, 0, 0, 1},
                    { 1, 0, 0, 0, 1, 0, 1, 0, 1},
                    { 1, 0, 1, 0, 1, 0, 0, 0, 1},
                    { 1, 0, 1, 0, 1, 0, 0, 0, 1},
                    { 1, 0, 1, 0, 1, 0, 0, 0, 1},{ 1, 0, 1, 0, 1, 0, 0, 1, 1},
                    { 0, 0, 1, 0, 1, 0, 0, 0, 0},
                    { 1, 0, 1, 0, 1, 1, 0, 0, 0},};
int generation[50][length + 1];
void randomFill()
{
    srand(time(0));   
    for (int g = 0; g < 50; g++)
    {
        for (int o = length; o < length + 1; o++)
            generation[g][o] = rand() % 2;   // assign value to last element
        for (int c = 1; c < length - 1; c++)
            generation[g][c] = rand() % length; //assign value to 1__6 elements
        generation[g][0] = startPoint; 
        generation[g][length - 1] = endPoint;
    }
}
int noSteps(int chr)
{
    int noSteps = 0;
    noSteps++;
    for (int r = 1; r < length; r++)
    {
        noSteps += abs(generation[chr][r - 1] - generation[chr][r]);
        noSteps++;
    }
    return noSteps;
}
int turns(int chr)
{
    int turns = 0;
    for (int r = 1; r < length; r++)
    {
        if (abs(generation[chr][r - 1] - generation[chr][r]) != 0)
        {
            turns += 2;
        }
    }
    return turns;
}
int infSteps(int chr)
{
    int infstep = 0;
    if (generation[chr][length])
    {
        if (!generation[chr][length + 1])
        {
            for (int r = 1; r < length; r++)
            {
                if (generation[chr][r] >= generation[chr][r - 1])
                {
                    for (int c = generation[chr][r - 1]; c <= generation[chr][r]; c++)
                        if (worldSpace[r][c] == 1)
                        {
                            infstep++;
                        }
                }
                else
                {
                    for (int c = generation[chr][r]; c <= generation[chr][r - 1]; c++)
                        if (worldSpace[r][c] == 1)
                        {
                            infstep++;
                        }
                }
            }
        }
        if (generation[chr][length + 1])
        {
            for (int r = 0; r < length - 1; r++)
            {
                if (generation[chr][r] >= generation[chr][r + 1])
                {
                    for (int c = generation[chr][r + 1]; c <= generation[chr][r]; c++)
                        if (worldSpace[r][c])
                        {
                            infstep++;
                        }
                }
                else
                {
                    for (int c = generation[chr][r]; c <= generation[chr][r + 1]; c++)
                        if (worldSpace[r][c])
                        {
                            infstep++;
                        }
                }
            }
        }
    }
    if (!generation[chr][length])
    {
        if (!generation[chr][length + 1])
        {
            for (int c = 1; c < length; c++)
            {
                if (generation[chr][c] >= generation[chr][c - 1])
                {
                    for (int r = generation[chr][c - 1]; r <= generation[chr][c]; r++)
                        if (worldSpace[r][c] == 1)
                        {
                            infstep++;
                        }
                }
                else
                {
                    for (int r = generation[chr][c]; r <= generation[chr][c - 1]; r++)
                        if (worldSpace[r][c] == 1)
                        {
                            infstep++;
                        }
                }
            }
        }
        if (generation[chr][length + 1])
        {
            for (int c = 0; c < length - 1; c++)
            {
                if (generation[chr][c] >= generation[chr][c + 1])
                {
                    for (int r = generation[chr][c + 1]; r <= generation[chr][c]; r++)
                        if (worldSpace[r][c] == 1)
                        {
                            infstep++;
                        }
                }
                else
                {
                    for (int r = generation[chr][c]; r <= generation[chr][c + 1]; r++)
                        if (worldSpace[r][c] == 1)
                        {
                            infstep++;
                        }
                }
            }
        }
    }
    return infstep;
}
float fitness_fn(int chromosome)
{
    float ff = (float)(1 - ((float)(infSteps(chromosome) - minimumfS) / (float)(maximumfS - minimumfS)));
    float fl = (float)(1 - ((float)(noSteps(chromosome) - minimumLen) / (float)(maximumLen - minimumLen)));
    float ft = (float)(1 - ((float)(turns(chromosome) - minTurn) / (float)(maxTurn - minTurn)));
    int wf = 100;
    int wl = 1;
    int wt = 1;
    float f = (float)((wf * ff) + (wl * fl) + (wt * ft));
    return f;
}
void maxVal()
{
    for (int i = 0; i < 50; i++)
    {
        if (maximumLen < noSteps(i))
        {
            maximumLen = noSteps(i);
        }
        if (minimumLen > noSteps(i))
        {
            minimumLen = noSteps(i);
        }
        if (maxTurn < turns(i))
        {
            maxTurn = turns(i);
        }
        if (minTurn > turns(i))
        {
            minTurn = turns(i);
        }
        if (maximumfS < infSteps(i))
        {
            maximumfS = infSteps(i);
        }
        if (minimumfS > infSteps(i))
        {
            minimumfS = infSteps(i);
        }
    }
}

void display(int chr)
{
    system("chcp 65001");
    system("cls");
    int temp[length][length];
    for (int r = 0; r < length; r++)
    {
        for (int c = 0; c < length; c++)
        {
            temp[r][c] = 0;
        }
    }
    if (generation[chr][length])
    {
        if (generation[chr][length + 1])
        {
            temp[length - 1][length - 1] = 1;
            for (int r = 0; r < length - 1; r++)
            {
                if (generation[chr][r] >= generation[chr][r + 1])
                {
                    for (int c = generation[chr][r + 1]; c <= generation[chr][r]; c++)
                    {
                        temp[r][c] = 1;
                    }
                } 
                else if (generation[chr][r + 1] >= generation[chr][r])
                {
                    for (int c = generation[chr][r]; c <= generation[chr][r + 1]; c++)
                    {
                        temp[r][c] = 1;
                    }
                }
            }
        }
        else if (!generation[chr][length + 1])
        {
            temp[0][0] = 1;
            for (int r = 1; r < length; r++)
            {
                if (generation[chr][r] >= generation[chr][r - 1])
                {
                    for (int c = generation[chr][r - 1]; c <= generation[chr][r]; c++)
                    {
                        temp[r][c] = 1;
                    }
                }
                else if (generation[chr][r - 1] >= generation[chr][r])
                {
                    for (int c = generation[chr][r]; c <= generation[chr][r - 1]; c++)
                    {
                        temp[r][c] = 1;
                    }
                }
            }
        }
    }
    if (!generation[chr][length])
    {
        if (generation[chr][length + 1])
        {
            temp[length - 1][endPoint] = 1;
            for (int c = 0; c < length - 1; c++)
            {
                if (generation[chr][c] >= generation[chr][c + 1])
                {
                    for (int r = generation[chr][c + 1]; r <= generation[chr][c]; r++)
                    {
                        temp[r][c] = 1;
                    }
                }
                else if (generation[chr][c + 1] >= generation[chr][c])
                {
                    for (int r = generation[chr][c]; r <= generation[chr][c + 1]; r++)
                    {
                        temp[r][c] = 1;
                    }
                }
            }
        }
        if (!generation[chr][length + 1])
        {
            temp[0][0] = 1;
            for (int c = 1; c < length; c++)
            {
                if (generation[chr][c] >= generation[chr][c - 1])
                {
                    for (int r = generation[chr][c - 1]; r <= generation[chr][c]; r++)
                    {
                        temp[r][c] = 1;
                    }
                }
                else if (generation[chr][c - 1] >= generation[chr][c])
                {
                    for (int r = generation[chr][c]; r <= generation[chr][c - 1]; r++)
                    {
                        temp[r][c] = 1;
                    }
                }
            }
        }
    }
    for (int r = 0; r < length; r++)
    {
        for (int c = 0; c < length; c++)
        {
            if (worldSpace[r][c] && temp[r][c])
            {
                printf(" ◘ ");
            }
            else if (worldSpace[r][c])
            {
                printf(" ■ ");
            }
            else if (temp[r][c] && temp[r][c + 1])
            {
                printf(" X ");
            }
            else if (temp[r][c] && !temp[r][c + 1] && temp[r + 1][c])
            {
                printf(" ▼ ");
            }
            else if (temp[r][c] && !temp[r][c + 1] && temp[r - 1][c])
            {
                printf(" ▲ ");
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
}

void selection_fn()
{
    for (int k = 0; k < 49; k++)
    {
        for (int i = 0; i < 49; i++)
        {
            if (fitness_fn(i) < fitness_fn(i + 1)) // arrange according to ascending order of fitness value
            {
                for (int j = 0; j < length + 1; j++)
                {
                    int temp[length + 1];
                    temp[j] = generation[i][j];
                    generation[i][j] = generation[i + 1][j]; // for swaping value
                    generation[i + 1][j] = temp[j];
                }
            }
        }
    }
}

void crossover_fn()
{
    srand(time(0));
    int cutPoint = rand() % (length - 2) + 1;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < cutPoint; j++)
        {
            generation[i + 25][j] = generation[i][j];
        }
        for (int j = cutPoint; j < length + 2; j++)
        {
            generation[i + 25][j] = generation[i + 1][j];
        }
    }
}
void mutataion_fn()
{
    srand(time(0));
    for (int i = 0; i < 50; i += 2)
        generation[i][(rand() % (length - 2)) + 1] = rand() % length;
}

int checkRep(int gen)
{
    float fit[800];
    fit[gen] = fitness_fn(0);
    if (gen >= 30)
    {
        if (fitness_fn(0) == fit[gen - 30])
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    display(0);
    randomFill();
    for (int i = 0; i < 9000; i++)
    {
        crossover_fn();
        mutataion_fn();
        maxVal();
        selection_fn();
        printf("gen > %d inf step > %d  \n", i, infSteps(0));
        if (infSteps(0) == 0)
        {
            break;
        }
    }
    printf("length = %d  turns = %d infStep = %d", noSteps(0), turns(0), infSteps(0));
    return 0;
}