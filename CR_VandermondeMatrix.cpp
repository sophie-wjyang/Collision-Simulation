//Ryan Chang
//Assignment 0 - 4.3.4 C Programming Assingment
//September 17, 2020

#include <iostream>
#include <cmath>

using namespace std;

//DOT PRODUCT METHOD---------------------------------
double dotProduct(double row[], double column[], int numTerms) // takes the 1D arrays and the number of terms
{
    double sum = 0; // answer to the dot product

    for (int i = 0; i < numTerms; i++) //repeat for the number of terms in the row/columns
    {
        sum += (row[i] * column[i]); //add the terms
    }
    return sum;
} // note - since the row length for the Vt is always = to column lenth for V, we don't consider when they aren't equal since it's redundant

// the same is true for the VtV inverse with Vt as well as the Vtv inverse Vt with y

//MAIN METHOD-----------------

int main()
{
    //DRIVER------

    //Prompt user
    int n; // the number of elements in the x,y data entres
    int p; // degree of the polynomial

    cout << "Enter number of x/y-values: ";
    cin >> n;

    cout << "Enter degree of the polynomial: ";
    cin >> p;

    // Create arrays
    double x[n]; //create x,y data entries of size n
    double y[n];

    cout << "\n";

    for (int i = 0; i < c; i++) //iternate throw x
    {
        cout << "Enter x value " << i + 1 << " :"; //prompt
        cin >> x[i];
    }

    cout << "\n";

    for (int i = 0; i < n; i++) // iterate through y
    {
        cout << "Enter y value " << i + 1 << " :";
        / prompt
                    cin >>
            y[i];
    }

    cout << "\n";

    //X, Y Table Output-----------

    //Pinrt x table
    cout << "Xvalues: \n";
    for (int i = 0; i < n; i++)
    {
        cout << x[i] << "\n";
    }

    cout << "\n";

    //Pinrt y table
    cout << "Yvalues: \n";
    for (int i = 0; i < n; i++)
    {
        cout << y[i] << "\n";
    }

    cout << "\n";

    // VANERMONDE MATRIX------------------------

    //Create Matrix
    doube V[n][p + 1]; // vandermonde matrix with dimensions number of x-elements by the degree of the polynomial + 1

    for (int i = 0; i < n; i++) //iterate through 2D array
    {
        for (int j = p; j >= 0; j--)
        {
            V[i][p - j] = std::pow(x[i], (double)j); // set value to x to the power of the respective degree
        }
    }

    //Print Matrix
    cout << "Vandermonde Matrix: ";

    for (int i = 0; i < n; i++) //iterate through matrix
    {
        cout << "\n"; // make a new line for each row

        for (int j = 0; j < p + 1; j++)
        {
            cout << V[i][j] << " "; // print value
        }
    }

    cout << "\n\n";

    //VANDERMONDE TRANSPOSE MATRIX

    //Create matrix
    double Vt[p + 1][n]; // vandermonde transpose with dimensions of the degree of the polynomial + 1 by the number of x-elements

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        for (int j = 0; j < n; j++)
        {
            Vt[i][j] = V[j][i]; // flip coordinate from vandermonde matrix
        }
    }

    //Print Matrix

    cout << "Vandermonde Transpose Matrix: ";

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        cout << "\n"; // make a new line for each row

        for (int j = 0; j < n; j++)
        {
            cout << Vt[i][j] << " "; //print value
        }
    }

    cout << "\n\n";

    //VtV Matrix------------------------------------------

    //Create Matrix
    doube VtV[p + 1][p + 1]; //VtV matrix has dimensions based on the degree of the polynomial

    double rowVt[n]; //1D array holding the row values in the vandermonde transpose matrix
    double clmV[n];  //1D array holding the column values in the vandermonde matrix

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        for (int j = 0; j < p + 1; j++)
        {
            for (int r = 0; r < n; r++) //adding values to separate array for row values in Vt
            {
                rowVt[r] = Vt[i][r];
            }

            for (int c = 0; c < n; c++) //adding values to seperate array for column values in V
            {
                clmV[c] = V[c][j];
            }

            VtV[i][j] = dotProduct(rowVt, clmV, n); //calculate dot product for cell values
        }
    }

    //Print matrix
    cout << "VtV Matrix: ";

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        cout << "\n"; // make a new line for each row

        for (int j = 0; j < p; j++)
        {
            cout << VtV[i][j] << " "; //print value
        }
    }

    cout << "\n\n";

    //VtV AUGMENTED MATRIX-------------------

    //create augmented matrix for VtV
    double aug[p + 1][2 * p + 2]; the colums are doubled to account for the identity matrix 

    for (int i =0; i <p+1; i++)
    {
        for (int j = 0; jj < p + 1; j++)
        {
            aug[i][j] = VtV[i][j]; // copy over the VtV to the augmented matrix

            //Placing the 1,0 for the identity matrix
            if (i == j)
            {
                aug[i][j + p + 1] = 1; // if the row is equal to the column number the identity matrix value is set to 1
            }
            else
            {
                aug[i][j + p + 1] = 0; // if the row is not equal to the column number the identity matrx value is set to 0
            }
        }
    }

    //Print Matrix
    cout << "VtV Augmented Matrix: ";

    for (int i = 0; i < p + 1; i++)
    {
        cout << "\n"; //make a new line for each row

        for (int j = 0; j < 2 * p + 2; j++)
        {
            cout << aug[i][j] << " "; //print value
        }
    }

    cout << "\n\n";

    //VtV INVERSE MATRIX------------------

    //Create Vtv Inverse Matrix
    double VtVInverse[p + 1][p + 1]; //dimensions of matrix are same as VtV (based on polynomial degree)

    int switchRow; // tracks row to swithc with

    //Algorithm to reduce VtV to an identity matrix------------------------------

    //we fine a pivot row where the leading coefficient is not 0 and subtract every row by the pivot until all the vlaues in column 0 is 0
    //we then move the pivot the next row and subtract every other row by the pivot until all the values in column 1 is 0
    //continue this process until the identnity matrix is created on the left side

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        //Switch rows if the inteded pivot has a leading coefficient of 0
        switchRow = i + 1; // if a switch is required it has to be at least the one below

        while (aug[i][i] == 0) // keep looking until a row without a leading coefficient of 0 is found
        {
            double temp[p + 1][2 * p + 2]; //temporary array to modify the augmented VtV array

            for (int c = 0; c < 2 * p + 2; c++) //iterate through
            {
                for (int r = 0; r < p + 1; r++)
                {
                    temp[c][r] = aug[c][r]; //copy over the augmented array
                }
            }

            if (temp[switchRow][i] != 0) //if the next row doesn't have a leading coefficient of 0
            {
                for (int cV = 0; cV < 2 * p + 2; cV++)
                {
                    aug[i][cV] = temp[switchRow][cV]; //swapp the values from the two rows
                    aug[switchRow][cV] = temp[i][cV];
                }
            }

            else //if the next row also has a leading coefficient of 0, move to the next row to keep looking
            {
                swithRow++;
            }
        }

        //Divide pivot by the value of the leading coefficient so that it become 1 (to convert to identity matrix)
        double coefficient = aug[i][i];

        for (int cV = 0; cV < 2 * p + 2; cV++)
        {
            aug[i][cV] /= coefficient;
        }

        //Subtract each row by the pivot
        for (int nR = 0; nR < p + 1; nR++) //iterate through all the other rows
        {
            if (nR != i)
            {
                double nextCoeff = aug[nR][i]; //find the coefficient of the next row

                for (int cV = 0; cV < 2 * p + 2; cV++) //iterate through columns
                {
                    aug[nR][cV] -= nextCoeff * aug[i][cV]; //subtract each row with the pivot multiplied by the row's coefficient to make it 0
                }
            }
        }
    }

    //Get the VtV inverse from the right side of augmented VtV after alogirthm---------
    for (int i = 0; i < p + 1; i++)
    {
        for (int j = 0; j < p + 1; j++)
        {
            VtVInverse[i][j] = aug[i][j + p + 1];
        }
    }

    //Print Matrix
    cout << "VtV Inverse Matrix: ";

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        cout << "\n"; // make a new line for each row

        for (int j = 0; j < p + 1; j++)
        {
            cout << VtVInverse[i][j] << " "; //print value
        }
    }

    cout << "\n\n";

    // (VtV INVERSE)(Vt) MATRIX--------------------------------------

    //Create matrix
    double VtVInverseVt[p + 1][n]; //since VtVInverse has p+1 rows and Vt has n columns the dimensions are p+1 x n

    double rowVtVInverse[p + 1]; // 1D array hold ing the row values in the vanderrmonde transpose matrix
    double clmVt[p + 1];         //1D array holding the column values in the vandermonde matrix

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        for (int j = 0; j < n; j++)
        {
            for (int r = 0; r < p + 1; r++) //adding values to separate array for row values in Vt
            {
                rowVtVInverse[r] = VtVInverse[i][r];
            }

            for (int c = 0; c < p + 1; c++) //adding values to seperate array for column values in V
            {
                clmVt[c] = Vt[c][j];
            }

            VtVInverseVt[i][j] = dotProduct(rowVtVInverse, clmVt, p + 1); //calculate dot product for cell value
        }
    }

    //Print Matrix
    cout << "(VtVInverse)(Vt) Matrix: ";

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        cout << "\n"; //make a new line for each row

        for (int j = 0; j < n; j++)
        {
            cout << VtVInverseVt[i][j] << " "; // print value
        }
    }

    cout << "\n\n";

    //(VtV INVERSE)(Vt)(y) MATRIX--------------------------

    //creat matrix
    double finalCoeff[p + 1]; //final coefficients - number is based on the degree of the polynomial

    double rowVtVInverseVt[n]; // 1D array holding the rorw values inthe vandermonde transpose matrix

    for (int i = 0; i < p + 1; i++) // iterate through matrix
    {
        for (int r = 0; r < n; r++) //adding values to seperate array for row values in Vt
        {
            rowVtVInverseVt[r] = VtVInverseVt[i][r];
        }

        finalCoeff[i] = dotProduct(rowVtVInverseVt, y, n); //calculate dot product for each cell value
    }

    // Print final coefficients
    cout << "Final Coefficients: ";

    for (int i = 0; i < p + 1; i++) //iterate through matrix
    {
        cout << "\n";          //makek a new line for each row
        cout << finalCoeff[i]; //print value
    }

    cout << "\n\n";
}