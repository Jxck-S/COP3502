#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAX_HOURS 24
#define MAX 100
#define MIN 1

int find_guess(int m, int n, int x[m+1][n+1]);


int main()

{

    int max_speed, max_location;

    scanf("%d", &max_speed);


    while(max_speed < MIN || max_speed > MAX)

    {

        scanf("%d", &max_speed);

    }


    scanf("%d", &max_location);


    while(max_location < MIN || max_location > MAX)

    {

        scanf("%d", &max_location);

    }


    int boats[max_location + 1][max_speed + 1];


    for(int i = 0; i <= max_location; i++)

    {

        for(int j = 0; j <= max_speed; j++)

        {

            boats[i][j] = i + j;

        }

    }


    int picture_no = 0;

    char response[20];

    int total = (max_location+1)*(max_speed+1);

    int guess;


    while(picture_no < MAX_HOURS)

    {

        guess = find_guess(max_location,max_speed, boats);


        /*for(int i = 0; i <= max_location; i++)

        {

            for(int j = 0; j<=max_speed;j++)

            {

                if(boats[i][j] != -1)

                {

                    check = find_mid(max_location, max_speed, boats, boats[i][j]);

                    if(check != -1)

                    {

                        guess = check;

                        break;

                    }


                    left = 0;

                    same = -1;

                    right = 0;

                    val = boats[i][j];

                    for(int p = 0; p <= max_location; p++)

                    {

                        for(int q = 0; q <= max_speed; q++)

                        {

                            if(boats[p][q] < val && !(boats[p][q] == -1))

                            {

                                left++;

                            }

                            else if(boats[p][q] == val && !(boats[p][q] == -1))

                            {

                                same++;

                            }

                            else if(boats[p][q] > val && !(boats[p][q] == -1))

                            {

                                right++;

                            }

                        }

                    }


                    if(same % 2 == 0 && (same > 0))

                    {

                        left++;

                        right++;

                    }

                    else if(same % 2 == 1 && !(same < 0))

                    {

                        if(left < right)

                        {

                            left++;

                        }

                        else if (right < left)

                        {

                            right++;

                        }

                        else

                        {

                            left++;

                        }

                    }


                    if(abs(left - right) <= 1 && abs(left - right) >= 0)

                    {

                        guess = val;

                        break;

                    }

                }

            }

            if(guess == val)

            {

                break;

            }

        }*/


        if(total == 1)

        {


            printf("! %d\n", guess);

            fflush(stdout);

            break;

        }


        printf("? %d\n", guess);

        fflush(stdout);


        scanf("%s", response);


        if(response[0] == 'W')

        {

            for(int i = 0; i <= max_location; i++)

            {

                for(int j = 0; j <= max_speed; j++)

                {

                    if(boats[i][j] <= guess && !(boats[i][j] == -1))

                    {

                        boats[i][j] = -1;

                        total--;

                    }

                    else if(!(boats[i][j] == -1))

                    {

                        boats[i][j] = boats[i][j] + j;

                    }

                }

            }

        }

        else if(response[0] == 'N')

        {

            scanf("%s", response);

            for(int i = 0; i <= max_location; i++)

            {

                for(int j = 0; j <= max_speed; j++)

                {

                    if(boats[i][j] >= guess&& !(boats[i][j] == -1))

                    {

                        boats[i][j] = -1;

                        total--;

                    }

                    else if (!(boats[i][j] == -1))

                    {

                        boats[i][j] = boats[i][j] + j;

                    }

                }

            }

        }

        else if(response[0] == 'B')

        {


            for(int i = 0; i <= max_location; i++)

            {

                for(int j = 0; j <= max_speed; j++)

                {

                    if(boats[i][j] != guess && !(boats[i][j] == -1))

                    {

                        boats[i][j] = -1;

                        total--;

                    }

                    else if (!(boats[i][j] == -1))

                    {

                        boats[i][j] = boats[i][j] + j;

                    }

                }

            }

        }


        picture_no++;

    }


    return 0;

}


int find_guess(int m, int n, int x[m+1][n+1])

{

    int y[(m+1)*(n+1)+2];

    int k = 0;

    int temp;

    for(int i = 0; i<=m;i++)

    {

        for(int j=0; j<=n; j++)

        {

            if(x[i][j] != -1)

            {

                y[k] = x[i][j];

                k++;

            }

        }

    }


    for(int i = 0; i < k; i++)

    {

        for(int j = i; j < k; j++)

        {

            if(y[i] > y[j])

            {

                temp = y[i];

                y[i] = y[j];

                y[j] = temp;

            }

        }

    }


    if(k == 1)

    {

        return y[0];

    }


    if(k % 2 == 0)

    {

        return y[(k/2) - 1];

    }

    else

    {

        return y[((k+1)/2) - 1];

    }

}


/*int find_min(int m, int n, int x[m + 1][n + 1])

{

    int min = m + (n * 24) + 1;


    for(int i = 0; i <= m ; i++)

    {

        for(int j = 0; j<= n; j++)

        {

            if(x[i][j] < min && !(x[i][j] == -1))

            {

                min = x[i][j];

            }

        }

    }


    return min;

}


int find_max(int m, int n, int x[m + 1][n + 1])

{

    int max = -1;


    for(int i = 0; i <= m ; i++)

    {

        for(int j = 0; j<= n; j++)

        {

            if(x[i][j] > max && !(x[i][j] == -1))

            {

                max = x[i][j];

            }

        }

    }


    return max;

}


int find_mid(int m, int n, int x[m + 1][n + 1], int val)

{

    int left = 0;

    int right = 0;

    int same = -1;

    for(int i = 0; i <= m; i++)

    {

        for(int j = 0; j <= n; j++)

        {

            if(x[i][j] < val && !(x[i][j] == -1))

            {

                left++;

            }

            else if(x[i][j] == val && !(x[i][j] == -1))

            {

                same++;

            }

            else if(x[i][j] > val && !(x[i][j] == -1))

            {

                right++;

            }

        }

    }


    if(same % 2 == 0)

    {

        left++;

        right++;

    }

    else

    {

        if(left < right)

        {

            left++;

        }

        else if (right < left)

        {

            right++;

        }

        else

        {

            left++;

        }

    }


    if(abs(left - right) <= 1 && abs(left - right) >= 0)

    {

        return val;

    }


    return -1;


}

*/