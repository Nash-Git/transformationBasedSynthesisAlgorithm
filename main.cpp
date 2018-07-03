#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//int cost = 0;
//int SWAP = 3;
//int Fred = 5;
//int gateCount = 0;

int main()
{
    int numFiles = 36;
    int num = 0;
    int i1[8], i2[8], i3[8];
    ifstream fin, in;
    in.open("input.txt");
    in >> i1[num] >> i2[num] >> i3[num];
    num++;
    while(!in.eof())
    {
        in >> i1[num] >> i2[num] >> i3[num];
        num++;
    }

    int a[8], b[8], c[8];
    for(int f = 0; f < numFiles; f++)
    {
    int SWAP = 3;
    int Fred = 5;
    int gateCount = 0;
    int cost = 0;

    ostringstream fileName;
    fileName << "crf3x3OneTwo_" << f << ".txt";
    ifstream fin;
    fin.open(fileName.str().c_str());

    num = 0;
    fin >> a[num] >> b[num] >> c[num];

    while(!fin.eof())
    {
        num++;
        fin >> a[num] >> b[num] >> c[num];
    }

    //cout << "num " << num << endl;
    cout << "Conservative Function " << f << endl;

    for(int i = 0; i < num; i++)
        cout << a[i] << " " << b[i] << " " << c[i] << endl;

    for(int i = 1; i <=6; i++)
    {
         for(int k = 2; k <=5; k++)
            if((a[k] == i1[k]) && (b[k] == i2[k]) && (c[k] == i3[k])) //testing to see if no transformation is required
                break;
    switch(i)
    {
        case 1:
        if(a[i])
        {
            int temp;
            for(int j = i; j <= 6; j++) //apply swap
            {
                temp = a[j];
                a[j] = c[j];
                c[j] = temp;
            }
            cout << "SWAP a and c" << endl;
            for(int i = 0; i < num; i++)
            {
                cout << a[i] << " " << b[i] << " " << c[i] << endl;
            }
            cost = cost + SWAP;
            gateCount++;
        }

        if(b[i]) //010 is in 001
        {
            int temp;
            for(int j = i; j <= 6; j++)
            {
                temp = b[j];
                b[j] = c[j];
                c[j] = temp;
            }
            cost = cost + SWAP;
            gateCount++;
            cout << "SWAP b and c" << endl;
            for(int i = 0; i < num; i++)
                cout << a[i] << " " << b[i] << " " << c[i] << endl;
        }
        break;

        case 2: //010 is not in pos. 100 is in 010's pos
        if(a[i])
        {
                int temp;
                for(int j = i; j <= 6; j++)
                {
                        temp = b[j];
                        b[j] = a[j];
                        a[j] = temp;
                }
                cost = cost + SWAP;
                gateCount++;
                cout << "Swap: a and b" << endl;
                for(int i = 0; i < num; i++)
                    cout << a[i] << " " << b[i] << " " << c[i] << endl;
        }

        break;

        case 3:
        if(a[i] && b[i]) //when 110 is in the pos of 011. apply positive FRED with control in on middle (b)
        {
            int temp;
            for(int j = i; j <=6; j++)
            {
                if(b[j])
            {
                temp = c[j];
                c[j] = a[j];
                a[j] = temp;
            }
            }
            cost = cost + Fred;
            gateCount++;
            cout << "Pos Fred. targets: a and c. Control: b" << endl;
            for(int i = 0; i < num; i++)
                cout << a[i] << " " << b[i] << " " << c[i] << endl;
        }
        if(a[i] && c[i]) //when 101 is in the pos of 011. apply positive FRED with control in on bottom line (c)
        {
            int temp;
            for(int j = i; j <=6; j++)
            {
                if(c[j])
                {
                temp = b[j];
                b[j] = a[j];
                a[j] = temp;
                }
            }
            cost = cost + Fred;
            gateCount++;
            cout << "Pos Fred. targets: a and b. Control: c" << endl;
            for(int i = 0; i < num; i++)
                cout << a[i] << " " << b[i] << " " << c[i] << endl;
        }
        break;

        case 5:
        if(a[i] && b[i]) //when 110 is in the pos of 101. apply positive FRED with control in on top line (a)
        {
            int temp;
            for(int j = i; j <=6; j++)
            {
                if(a[j])
            {
                temp = c[j];
                c[j] = b[j];
                b[j] = temp;
            }
            }
            cost = cost + Fred;
            gateCount++;
            cout << "Pos Fred. targets: b and c. Control: a" << endl;
            for(int i = 0; i < num; i++)
                    cout << a[i] << " " << b[i] << " " << c[i] << endl;

        }
        break;

    }
    }

    cout << endl;
    cout << "Quantum Cost: " << cost << endl;
    cout << "Gate Count: " << gateCount << endl;
    cout << endl;

    ostringstream outFileName;
    outFileName << "GC3x3QCSF_" << f << ".txt";
    ofstream out(outFileName.str().c_str(), ios::trunc|ios::out);
    out << gateCount << " " << cost;
    fin.close();
    out.close();
    }
    return 0;
}
