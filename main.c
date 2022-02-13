#include <stdio.h>
#include <stdlib.h>

int numOfPagesinFrame;
char algorithm[50];
int pageRefrence[4096];
int pages;
int pageFault=0;
int i,j,k,a,p;

int getLru(int array[])  //function to get index of lru element
{
    int maxTime = -10000;
    int index;
    for(int i=0; i<numOfPagesinFrame; i++)
    {
        if(array[i]>maxTime)
        {
            maxTime = array[i];
            index = i;
        }
    }
    return index;
}

/////////////////////////////FIFO//////////////////////////
void FIFO()
{
    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int frame[numOfPagesinFrame];

    for(i=0; i<numOfPagesinFrame; i++)
    {
        frame[i]=NULL;
    }

    for(i=0; i<pages; i++)
    {
        printf("%02d ",pageRefrence[i]);
        int found=0;

        for(j=0; j<numOfPagesinFrame; j++)
        {
            if(pageRefrence[i]==frame[j])
            {
                found = 1;
            }
        }

        if(found==1)
        {
            printf("    ");
            for(int k=0; k<numOfPagesinFrame; k++)
            {
                if(frame[k]==NULL)
                {
                    continue;
                }
                printf("%02d ",frame[k]);
            }
        }

        else if(found==0)
        {
            if(frame[p] == NULL)
            {

                frame[p] = pageRefrence[i];
                p++;

                printf("    ");
                for(int k=0; k<numOfPagesinFrame; k++)
                {
                    if(frame[k]==NULL)
                    {
                        continue;
                    }
                    printf("%02d ",frame[k]);
                }
                if(p == numOfPagesinFrame)
                {
                    p=0;
                }
            }
            else
            {
                pageFault++;
                frame[p] = pageRefrence[i];
                p++;

                printf("F   ");
                for(int k=0; k<numOfPagesinFrame; k++)
                {
                    if(frame[k]==NULL)
                    {
                        continue;
                    }
                    printf("%02d ",frame[k]);
                }
                if(p == numOfPagesinFrame)
                {
                    p=0;
                }
            }
        }
        printf("\n");
    }
}

/////////////////////////////LRU//////////////////////////

void LRU()
{
    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int frame[numOfPagesinFrame];
    int usedCheck[numOfPagesinFrame];
    int index;

    for(int i=0; i<numOfPagesinFrame; i++)
    {
        frame[i]=NULL;
        usedCheck[i]=0;
    }

    for(int i=0; i<pages; i++)
    {
        printf("%02d ",pageRefrence[i]);
        int found=0;
        int emptySpot=0;

        for(int j=0; j<numOfPagesinFrame; j++)
        {
            if(pageRefrence[i]==frame[j])
            {
                found=1;
                index = j;
            }
        }


        if(found == 0)
        {
            for(int j=0; j<numOfPagesinFrame; j++)
            {
                if(frame[j]==NULL)
                {
                    emptySpot = 1;
                    frame[j] = pageRefrence[i];
                    printf("    ");
                    for(int k=0; k<numOfPagesinFrame; k++)
                    {
                        if(frame[k]==NULL)
                        {
                            continue;
                        }
                        printf("%02d ",frame[k]);
                    }

                    for(a=0; a<numOfPagesinFrame; a++)
                    {
                        usedCheck[a]++;
                    }
                    usedCheck[j]=0;
                    break;
                }
            }

            if(emptySpot == 0)
            {
                pageFault++;
                int p = getLru(usedCheck);
                frame[p] = pageRefrence[i];
                for(int a=0; a<numOfPagesinFrame; a++)
                    usedCheck[a]++;
                usedCheck[p] = 0;
                printf("F   ");
                for(int k=0; k<numOfPagesinFrame; k++)
                {
                    if(frame[k]==NULL)
                    {
                        continue;
                    }
                    printf("%02d ",frame[k]);
                }
            }
        }

        else if(found == 1)
        {
            printf("    ");
            for(int k=0; k<numOfPagesinFrame; k++)
            {
                if(frame[k]==NULL)
                {
                    continue;
                }
                printf("%02d ",frame[k]);
            }
            for(a=0; a<numOfPagesinFrame; a++)
            {
                usedCheck[a]++;
            }
            usedCheck[index]=0;
        }
        printf("\n");
    }
}

/////////////////////////////OPTIMAL//////////////////////////

void OPTIMAL ()
{
    printf("Replacement Policy = OPTIMAL\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int frame[numOfPagesinFrame];
    int temp[numOfPagesinFrame];
    int maximum;

    for(i = 0; i < numOfPagesinFrame; i++)
    {
        frame[i] = NULL;
    }

    for(i = 0; i < pages; i++)
    {
        printf("%02d ",pageRefrence[i]);
        int found =0;
        int emptySpot = 0;

        for(j = 0; j < numOfPagesinFrame; j++)
        {

            if(frame[j] == pageRefrence[i])
            {
                found = 1;
                emptySpot = 1;
                printf("    ");
                for(j = 0; j < numOfPagesinFrame; j++)
                {
                    if(frame[j] == NULL)
                    {
                        continue;
                    }
                    printf("%02d ", frame[j]);
                }
            }
        }

        if(found == 0)
        {
            for(j = 0; j < numOfPagesinFrame; j++)
            {
                if(frame[j] == NULL)
                {
                    frame[j] = pageRefrence[i];
                    emptySpot = 1;
                    printf("    ");

                    for(j = 0; j < numOfPagesinFrame; j++)
                    {
                        if(frame[j] == NULL)
                        {
                            continue;
                        }
                        printf("%02d ", frame[j]);

                    }
                }
            }
        }

        if(emptySpot == 0)
        {
            int flag =0;
            for(j = 0; j < numOfPagesinFrame; j++)
            {
                temp[j] = NULL;

                for(k = i; k < pages; k++)
                {
                    if(frame[j] == pageRefrence[k])
                    {
                        temp[j] = k;
                    }
                }
            }
            for(j = 0; j < numOfPagesinFrame; j++)
            {
                if(temp[j] == NULL)
                {
                    p = j;
                    flag = 1;
                    break;
                }
            }
            if(flag ==0)
            {
                maximum = temp[0];
                p = 0;
                for(j = 0; j < numOfPagesinFrame; j++)
                {
                    if(temp[j] > maximum)
                    {
                        maximum = temp[j];
                        p = j;
                    }
                }
            }

            frame[p] = pageRefrence[i];
            pageFault++;

            printf("F   ");
            for(j = 0; j < numOfPagesinFrame; j++)
            {
                if(frame[j] == NULL)
                    continue;
                printf("%02d ", frame[j]);
            }
        }
        printf("\n");
    }
}



int main()
{
    scanf("%d",&numOfPagesinFrame);
    scanf("%s",algorithm);
    int i=0;
    int temp=0;
    while(1)
    {
        scanf("%d",&temp);
        if(temp==-1)
        {
            break;
        }
        else
        {
            pageRefrence[i]=temp;
            i++;
        }
    }
    pages=i;

    if(strcmp("FIFO",algorithm)==0)
    {
        FIFO();
    }
    else if(strcmp("LRU",algorithm)==0)
    {
        LRU();
    }
    else if(strcmp("OPTIMAL",algorithm)==0)
    {
        OPTIMAL();
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",pageFault);
    return 0;
}
