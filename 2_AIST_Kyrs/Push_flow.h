#pragma once
#include <Windows.h>
#include<iostream>
#include< iomanip >
#include <fstream>
#include<string>

using namespace std;
using namespace Push_flow;


namespace Push_flow
{
    void matrix(int** Matrix, int size)
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                cout << setw(4) << Matrix[i][j];
                if (j == size - 1)
                    cout << endl;
            }
        cout << endl;
    }
    void push(int beg_edge, int end_edge, int** flow, int* excess, int** thr_cap, int n)
    {
        int d = min(excess[beg_edge], thr_cap[beg_edge][end_edge] - flow[beg_edge][end_edge]);
        flow[beg_edge][end_edge] += d;
        flow[end_edge][beg_edge] = -flow[beg_edge][end_edge];
        excess[beg_edge] -= d;
        excess[end_edge] += d;
    }

    void lift(int beg_edge, int* height, int** flow, int** thr_cap, int n)
    {
        int d = 1000000;
        for (int i = 0; i < n; i++)
            if (thr_cap[beg_edge][i] - flow[beg_edge][i] > 0)
                d = min(d, height[i]);
        if (d == 1000000)
            return;
        height[beg_edge] = d + 1;
    }
    int overflow(int* excess, int n)
    {
        int i = 1;
        while ((excess[i] <= 0) && (i < n - 1))
            i++;
        if (i == n - 1)
            return -1;
        else
            return i;
    }
    int algorithm(int** thr_cap, int** flow, int n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                flow[i][j] = 0;
        for (int i = 1; i < n; i++)
        {
            flow[0][i] = thr_cap[0][i];
            flow[i][0] = -thr_cap[0][i];
        }
        int* height = new int[n];
        height[0] = n;
        for (int i = 1; i < n; i++) height[i] = 0;
        int* excess = new int[n];
        excess[0] = 0;
        for (int i = 1; i < n; i++) excess[i] = flow[0][i];
        int i;
        while ((i = overflow(excess, n)) != -1)
        {
            int j = 0;
            while (((thr_cap[i][j] - flow[i][j] <= 0) || (height[i] != height[j] + 1)) && (j < n))
                j++;
            if (j < n)
                push(i, j, flow, excess, thr_cap, n);
            else
                lift(i, height, flow, thr_cap, n);
        }
        int flow = excess[n - 1];
        cout << "Maximum flow: " << flow << endl;
        return flow;
    }
    int findatop(char top, char* tops, int sizetops)
    {
        for (int i = 0; i < sizetops; i++)
        {
            if (top == tops[i])
                return i;
        }
        return -1;
    }
    void matrixentry(ifstream& file, int** Matrix, int size, char* top)
    {
        string line; string selection;
        int sizetop = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                Matrix[i][j] = 0;
        while (!file.eof())
        {
            getline(file, line);
            int firstspace = line.find(" ");
            int secondspace = line.find(" ", firstspace + 1);
            selection = line.substr(0, firstspace);
            char firstop = selection[0];
            selection = line.substr(firstspace + 1, secondspace - firstspace - 1);
            char secondtop = selection[0];
            selection = line.substr(secondspace + 1);
            int cost = atoi(selection.c_str());
            if (findatop(firstop, top, sizetop) == -1)
            {
                top[sizetop] = firstop; sizetop++;
            }
            if (findatop(secondtop, top, sizetop) == -1)
            {
                top[sizetop] = secondtop; sizetop++;
            }
            Matrix[findatop(firstop, top, sizetop)][findatop(secondtop, top, sizetop)] = cost;
        }
    }
}

