

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
    :maxSize(maxNumber),                            // 값 할당이 아닌 멤버 초기화 리스트로 변수 초기화 해줌!
    size(0), 
    vertexList(new Vertex[maxNumber]),              // 동적 할당
    adjMatrix(new int[maxNumber * maxNumber]),
    pathMatrix(new int[maxNumber * maxNumber])      // vertex 개수가 v개일 때, 최대 path 개수는 v(v-1)이므로 maxNumber^2의 크기로 할당.
{
}

WtGraph::~WtGraph()
{
    delete[] vertexList;    // 할당 해제.
    delete[] adjMatrix;
    delete[] pathMatrix;
}

//--------------------------------------------------------------------

int WtGraph::getIndex(char* v)  // char 배열 형태를 입력받아 그러한 label을 가진 vertex의 index를 검색.
{
    string vertexstr, str = v;

    for (int i = 0; i < size; i++) 
    {
        vertexstr = vertexList[i].label;
        if (vertexstr == str)       //존재한다면, 그 index 반환
            return i;
    }

    return -1;      //존재하지 않는다면, -1 반환.
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
    if (isFull() == true)       // 가득 찼을 때 예외처리
        cout << ">> Graph is Full <<" << endl;
    else
    {
        string str1, str2;
        str2 = newVertex.label;

        for (int i = 0; i < size; i++)  // vertex가 이미 존재하면, Update (정점만, 연결되는 edge들은 그대로).
        {
            str1 = vertexList[i].label;

            if (str1 == str2)
            {
                vertexList[i] = newVertex;
                return;                 // update 했다면 size를 늘리지 않고, insertVertex 종료.
            }
        }

        vertexList[size] = newVertex;   // 새로운 vertex면, array에 넣고 나서 size를 +1

        for (int i = 0; i < size; i++)          // 존재하고 있던 vertex들과 새로 들어온 vertex 사이의 간선의 가중치를 infiniteEdgeWt로 초기화해줌.
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

    if (index1 == -1 || index2 == -1)       // 없는 vertex가 입력되거나, weight가 양수로 입력되지 않으면 그대로 insertEdge 종료.
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

    // Edge가 이미 존재하더라도, setEdge를 통해 weight가 update 됨.
    // 자기 자신으로 돌아오는 Edge도 설정 가능.
    setEdge(index1, index2, wt);
    setEdge(index2, index1, wt);
}

//--------------------------------------------------------------------

bool WtGraph::retrieveVertex(char* v, Vertex& vData)
{
    int index;

    index = getIndex(v);        // vertexList에서 입력된 문자가 label인 vertex 검색

    if (index == -1)            // 못 찾으면 false 반환
        return false;
    else                        // 찾으면 true
        return true;
   
}

bool WtGraph::getEdgeWeight(char* v1, char* v2, int& wt)
{
    int index1, index2;
    string vertexstr, v1str = v1, v2str = v2;

    index1 = getIndex(v1);      // insertEdge에서와 같이 vertexList에서 v1, v2에 해당하는 label을 가진 vertex 검색.
    index2 = getIndex(v2);

    if (index1 == -1 || index2 == -1)       // 없는 vertex가 입력되면 그대로 getEdgeWeight 종료.
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
    for (int i = removeindex; i < size - 1; i++)      // 지울 vertex부터 vertex를 앞으로 한 칸씩 당김
    {
        vertexList[i] = vertexList[i + 1];
    }

    for (int i = 0; i < size; i++)      // adjMatrix에서 지울 [열]부터 한 줄 앞으로 당김
    {
        for (int j = removeindex; j < size; j++)
        {
            setEdge(i, j, getEdge(i, j + 1));
        }
        setEdge(i, size, infiniteEdgeWt);
    }
    for (int i = 0; i < size; i++)      // adjMatrix에서 지울 [행]부터 한 줄 앞으로 당김
    {
        for (int j = removeindex; j < size; j++)
        {
            setEdge(j, i, getEdge(j + 1, i));
        }
        setEdge(size, i, infiniteEdgeWt);
    }

    size--;     // 마지막으로 size를 -1
}

void WtGraph::removeEdge(char* v1, char* v2)       // v1, v2사이 edge만 지워줌
{
    int index1 = getIndex(v1);
    int index2 = getIndex(v2);

    setEdge(index1, index2, infiniteEdgeWt);
    setEdge(index2, index1, infiniteEdgeWt);
}

//--------------------------------------------------------------------

void WtGraph::clear()
{
    for (int i = 0; i < maxSize * maxSize; i++)     // 두 matrix 모두 infinite로 삭제.
    {
        adjMatrix[i] = infiniteEdgeWt;
        pathMatrix[i] = infiniteEdgeWt;
    }

    size = 0;   // size도 0으로 줄임.
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
     for (int i = 0; i < maxSize * maxSize; i++)    // edge로 직행하는 path는 모두 pathMatrix에 미리 넣어 놓고
     {
         pathMatrix[i] = adjMatrix[i];
     }
     for (int i = 0; i < maxSize; i++)
     {
         setPath(i, i, infiniteEdgeWt);
     }

     // j->k의 path를 계산해서 넣어 줄 것. (j->m->k)
     for (int m = 0; m < size; m++)
     {
         for (int j = 0; j < size; j++)
         {
             for (int k = 0; k < size; k++)
             {
                 if (j == k || j == m || k == m)         // 이 경우는 edge로 직행하는 path이거나, 자기 자신으로 돌아오는 경우이기 때문에 이미 pathMatrix에 넣었으므로, 제외.
                 { }
                 else if ( getPath(j, m) != infiniteEdgeWt && getPath(m, k) != infiniteEdgeWt )     // j->m, m->k인 path가 존재한다면, j->k인 path를 추가하게 됨
                 {
                     if (getPath(j, k) > getPath(j, m) + getPath(m, k))     // 이 때, j->m->k가 j->k보다 weight가 적다면 j->m->k의 weight를 j->k path의 weight로
                         setPath(j, k, getPath(j, m) + getPath(m, k));
                     // j->k < j->m->k 라면, j->k의 edge의 weight를 path의 weight로 하는 것이 맞으나, 이미 위에서 그 값을 넣었기 때문에 바꿀 필요 없음.
                 }
             }
         }
     }
 }