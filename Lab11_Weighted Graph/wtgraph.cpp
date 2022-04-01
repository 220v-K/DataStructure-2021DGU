

//--------------------------------------------------------------------
//
//  Laboratory 14                                          wtgraph.cpp
//
//  Implementation of the Weighted Graph ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include "wtgraph.h"

//--------------------------------------------------------------------

WtGraph::WtGraph(int maxNumber)
    :maxSize(maxNumber),                            // �� �Ҵ��� �ƴ� ��� �ʱ�ȭ ����Ʈ�� ���� �ʱ�ȭ ����!
    size(0), 
    vertexList(new Vertex[maxNumber]),              // ���� �Ҵ�
    adjMatrix(new int[maxNumber * maxNumber]),
    pathMatrix(new int[maxNumber * maxNumber])      // vertex ������ v���� ��, �ִ� path ������ v(v-1)�̹Ƿ� maxNumber^2�� ũ��� �Ҵ�.
{
}

WtGraph::~WtGraph()
{
    delete[] vertexList;    // �Ҵ� ����.
    delete[] adjMatrix;
    delete[] pathMatrix;
}

//--------------------------------------------------------------------

int WtGraph::getIndex(char* v)  // char �迭 ���¸� �Է¹޾� �׷��� label�� ���� vertex�� index�� �˻�.
{
    string vertexstr, str = v;

    for (int i = 0; i < size; i++) 
    {
        vertexstr = vertexList[i].label;
        if (vertexstr == str)       //�����Ѵٸ�, �� index ��ȯ
            return i;
    }

    return -1;      //�������� �ʴ´ٸ�, -1 ��ȯ.
}

int WtGraph::getEdge(int row, int col)
{
    return adjMatrix[row * maxSize + col];
}

void WtGraph::setEdge(int row, int col, int wt) 
{
    adjMatrix[row * maxSize + col] = wt;
}

//--------------------------------------------------------------------

void WtGraph::insertVertex(Vertex newVertex)
{
    if (isFull() == true)       // ���� á�� �� ����ó��
        cout << ">> Graph is Full <<" << endl;
    else
    {
        string str1, str2;
        str2 = newVertex.label;

        for (int i = 0; i < size; i++)  // vertex�� �̹� �����ϸ�, Update (������, ����Ǵ� edge���� �״��).
        {
            str1 = vertexList[i].label;

            if (str1 == str2)
            {
                vertexList[i] = newVertex;
                return;                 // update �ߴٸ� size�� �ø��� �ʰ�, insertVertex ����.
            }
        }

        vertexList[size] = newVertex;   // ���ο� vertex��, array�� �ְ� ���� size�� +1

        for (int i = 0; i < size; i++)          // �����ϰ� �ִ� vertex��� ���� ���� vertex ������ ������ ����ġ�� infiniteEdgeWt�� �ʱ�ȭ����.
        {
            setEdge(i, size, infiniteEdgeWt);
        }
        for (int i = 0; i < size; i++)
        {
            setEdge(size, i, infiniteEdgeWt);
        }
        setEdge(size, size, infiniteEdgeWt);

        size++;     // size +1
    }
}

void WtGraph::insertEdge(char* v1, char* v2, int wt)
{
    int index1, index2;
    bool isError = false;

    index1 = getIndex(v1);
    index2 = getIndex(v2);

    if (index1 == -1 || index2 == -1)       // ���� vertex�� �Էµǰų�, weight�� ����� �Էµ��� ������ �״�� insertEdge ����.
    {
        cout << ">> Uninserted label of vertex <<" << endl;
        isError = true;
    }
    if (wt <= 0)
    {
        cout << ">> Edge's weight must be positive integer <<" << endl;
        isError = true;
    }
    if (isError)
        return;

    // Edge�� �̹� �����ϴ���, setEdge�� ���� weight�� update ��.
    // �ڱ� �ڽ����� ���ƿ��� Edge�� ���� ����.
    setEdge(index1, index2, wt);
    setEdge(index2, index1, wt);
}

//--------------------------------------------------------------------

bool WtGraph::retrieveVertex(char* v, Vertex& vData)
{
    int index;

    index = getIndex(v);        // vertexList���� �Էµ� ���ڰ� label�� vertex �˻�

    if (index == -1)            // �� ã���� false ��ȯ
        return false;
    else                        // ã���� true
        return true;
   
}

bool WtGraph::getEdgeWeight(char* v1, char* v2, int& wt)
{
    int index1, index2;
    string vertexstr, v1str = v1, v2str = v2;

    index1 = getIndex(v1);      // insertEdge������ ���� vertexList���� v1, v2�� �ش��ϴ� label�� ���� vertex �˻�.
    index2 = getIndex(v2);

    if (index1 == -1 || index2 == -1)       // ���� vertex�� �ԷµǸ� �״�� getEdgeWeight ����.
    {
        cout << ">> Uninserted label of vertex <<" << endl;
        return false;
    }

    wt = getEdge(index1, index2);
    if (wt == infiniteEdgeWt)
        return false;
    else
        return true;
}

//--------------------------------------------------------------------

void WtGraph::removeVertex(char* v)
{
    int removeindex = getIndex(v);
    for (int i = removeindex; i < size - 1; i++)      // ���� vertex���� vertex�� ������ �� ĭ�� ���
    {
        vertexList[i] = vertexList[i + 1];
    }

    for (int i = 0; i < size; i++)      // adjMatrix���� ���� [��]���� �� �� ������ ���
    {
        for (int j = removeindex; j < size; j++)
        {
            setEdge(i, j, getEdge(i, j + 1));
        }
        setEdge(i, size, infiniteEdgeWt);
    }
    for (int i = 0; i < size; i++)      // adjMatrix���� ���� [��]���� �� �� ������ ���
    {
        for (int j = removeindex; j < size; j++)
        {
            setEdge(j, i, getEdge(j + 1, i));
        }
        setEdge(size, i, infiniteEdgeWt);
    }

    size--;     // ���������� size�� -1
}

void WtGraph::removeEdge(char* v1, char* v2)       // v1, v2���� edge�� ������
{
    int index1 = getIndex(v1);
    int index2 = getIndex(v2);

    setEdge(index1, index2, infiniteEdgeWt);
    setEdge(index2, index1, infiniteEdgeWt);
}

//--------------------------------------------------------------------

void WtGraph::clear()
{
    for (int i = 0; i < maxSize * maxSize; i++)     // �� matrix ��� infinite�� ����.
    {
        adjMatrix[i] = infiniteEdgeWt;
        pathMatrix[i] = infiniteEdgeWt;
    }

    size = 0;   // size�� 0���� ����.
}

bool WtGraph::isEmpty() const   // Empty -> true
{
    if (size == 0)
        return true;
    else
        return false;
}

bool WtGraph::isFull() const    // Full -> true
{
    if (size == maxSize)
        return true;
    else
        return false;
}

//--------------------------------------------------------------------

void WtGraph::showStructure()

// Outputs a graph's vertex list, adjacency matrix, and path matrix.
// This operation is intended for testing/debugging purposes only.

{
    int wt,         // Edge weight
        row, col;   // Loop counters

    if (size == 0)
        cout << "Empty graph" << endl;
    else
    {
        cout << endl << "Vertex list : " << endl;
        for (row = 0; row < size; row++)
            cout << row << '\t' << vertexList[row].label << endl;

        cout << endl << "Edge matrix : " << endl << '\t';
        for (col = 0; col < size; col++)
            cout << col << '\t';
        cout << endl;
        for (row = 0; row < size; row++)
        {
            cout << row << '\t';
            for (col = 0; col < size; col++)
            {
                wt = getEdge(row, col);
                if (wt == infiniteEdgeWt)
                    cout << "- \t";
                else
                    cout << wt << '\t';
            }
            cout << endl;
        }

        cout << endl << "Path matrix : " << endl << '\t';
        for (col = 0; col < size; col++)
            cout << col << '\t';
        cout << endl;
        for (row = 0; row < size; row++)
        {
            cout << row << '\t';
            for (col = 0; col < size; col++)
            {
                wt = getPath(row, col);
                if (wt == infiniteEdgeWt)
                    cout << "- \t";
                else
                    cout << wt << '\t';
            }
            cout << endl;
        }
    }
}

//--------------------------------------------------------------------

// In-Lab

 int WtGraph::getPath(int row, int col)
 {
     return pathMatrix[row * maxSize + col];
 }

 void WtGraph::setPath(int row, int col, int wt) 
 {
     pathMatrix[row * maxSize + col] = wt;
 }

 void WtGraph::computePaths() 
 {
     for (int i = 0; i < maxSize * maxSize; i++)    // edge�� �����ϴ� path�� ��� pathMatrix�� �̸� �־� ����
     {
         pathMatrix[i] = adjMatrix[i];
     }
     for (int i = 0; i < maxSize; i++)
     {
         setPath(i, i, infiniteEdgeWt);
     }

     // j->k�� path�� ����ؼ� �־� �� ��. (j->m->k)
     for (int m = 0; m < size; m++)
     {
         for (int j = 0; j < size; j++)
         {
             for (int k = 0; k < size; k++)
             {
                 if (j == k || j == m || k == m)         // �� ���� edge�� �����ϴ� path�̰ų�, �ڱ� �ڽ����� ���ƿ��� ����̱� ������ �̹� pathMatrix�� �־����Ƿ�, ����.
                 { }
                 else if ( getPath(j, m) != infiniteEdgeWt && getPath(m, k) != infiniteEdgeWt )     // j->m, m->k�� path�� �����Ѵٸ�, j->k�� path�� �߰��ϰ� ��
                 {
                     if (getPath(j, k) > getPath(j, m) + getPath(m, k))     // �� ��, j->m->k�� j->k���� weight�� ���ٸ� j->m->k�� weight�� j->k path�� weight��
                         setPath(j, k, getPath(j, m) + getPath(m, k));
                     // j->k < j->m->k ���, j->k�� edge�� weight�� path�� weight�� �ϴ� ���� ������, �̹� ������ �� ���� �־��� ������ �ٲ� �ʿ� ����.
                 }
             }
         }
     }
 }