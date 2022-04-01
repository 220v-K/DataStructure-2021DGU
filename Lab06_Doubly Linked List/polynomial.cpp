

//헤더 파일 이었던 부분
//------------------------------------------------------------------

template < class DT >         // Forward declaration of the List class
class List;

template < class DT >
class ListNode                // Facilitator class for the List class
{
private:

	// Constructor
	ListNode(const DT& degree_data, const DT& coefficient_data,
		ListNode* priorPtr, ListNode* nextPtr);

	// Data members
	DT degree, coefficient;        // List data item
	ListNode* prior,    // Pointer to the previous data item
		* next;     // Pointer to the next data item

	friend class List<DT>;
};

//--------------------------------------------------------------------

template < class DT >
class List
{
public:

	// Constructor
	List(int ignored = 0);

	// Destructor
	~List();

	// List manipulation operations
	void insert(const DT& degree_data, const DT& coefficient_data);    // Insert after cursor
	void remove(const DT& degree_data, const DT& coefficient_data);                           // Remove data item
	void replace(const DT& newDataItem);   // Replace data item
	void clear();                           // Clear list

	// List status operations
	bool isEmpty() const;                   // List is empty
	bool isFull() const;                    // List is full

	// List iteration operations
	void gotoBeginning();                    // Go to beginning
	void gotoEnd();                          // Go to end
	bool gotoNext();                        // Go to next data item
	bool gotoPrior();                       // Go to prior data item
	DT getCursor() const;                    // Return data item

	// Output the list structure -- used in testing/debugging
	void showStructure() const;

private:

	// Data members
	ListNode<DT>* head,     // Pointer to the beginning of the list
		* cursor;   // Cursor pointer
};

//--------------------------------------------------------------------------------------

//polynomial.cpp
//--------------------------------------------------------------------------------------
#include <iostream>

using namespace std;

//ListNode의 Constructor
template < class DT >
ListNode<DT>::ListNode(const DT& degree_data, const DT& coefficient_data,
	ListNode* priorPtr, ListNode* nextPtr)
{
	this->degree = degree_data;
	this->coefficient = coefficient_data;
	this->next = priorPtr;
	this->prior = nextPtr;
}

// Constructor
template < class DT >
List<DT>::List(int ignored)
{
	head = NULL;
	cursor = NULL;
}

// Destructor	
template < class DT >
List<DT>::~List()
{
	clear();
	delete head;
	delete cursor;
}


//------------ List manipulation operations ------------------


template < class DT >
void List<DT>::insert(const DT& degree_data, const DT& coefficient_data)
{
	if (isFull() == true)    //가득 찼을 때 예외처리
	{
		cout << "List is Full" << endl;
	}
	else if (isEmpty() == true)	 //비어있을 때
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

		newNode->degree = degree_data;
		newNode->coefficient = coefficient_data;

		head = newNode;
		cursor = newNode;
	}
	else
	{
		if (head->degree == degree_data)			//입력된 차수가 head의 차수와 같을 때 흡수
		{
			head->coefficient = head->coefficient + coefficient_data;
		}
		else if (head->degree < degree_data)		//입력된 차수가 head의 차수보다 높을 때 맨 앞으로 삽입
		{
			ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

			newNode->degree = degree_data;
			newNode->coefficient = coefficient_data;
			newNode->next = head;
			head->prior = newNode;
			head = newNode;
		}
		else										//입력된 차수가 head의 차수보다 작을 때
		{
			cursor = head;

			while (cursor->next != NULL)			//커서가 마지막 노드까지 갔을 때는 정지.
			{										//커서가 마지막 노드라면 cursor->next == NULL이므로 cursor->next->degree가 정의되지 않아 오류가 나므로, 앞으로 빼줌
				if(cursor->next->degree > degree_data)		//커서 다음 노드의 차수가 입력된 차수보다 작거나 같게 될 때까지
				{
					cursor = cursor->next;
				}
				else
				{
					break;
				}
			}

			if (cursor->next == NULL)		//커서가 맨 끝까지 갔다면
			{
				if (cursor->degree == degree_data)				//마지막 노드의 차수와 입력된 차수가 같을 때
				{
					cursor->coefficient = cursor->coefficient + coefficient_data;
				}
				else											// 마지막 노드의 차수가 입력된 차수보다 클 때(입력된 차수가 마지막 노드 차수보다 작을 때)
				{
					ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

					newNode->degree = degree_data;
					newNode->coefficient = coefficient_data;
					newNode->prior = cursor;
					cursor->next = newNode;
				}
			}
			else
			{
				if (cursor->next->degree == degree_data)		//커서 다음 노드의 차수가 입력된 차수와 같으면
				{
					cursor->next->coefficient = cursor->next->coefficient + coefficient_data;
				}
				else											//커서 다음 노드의 차수가 입력된 차수보다 작으면 (전체 노드 중 입력 차수와 같은 차수를 가진 노드가 존재하지 않는다면)
				{
					ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

					newNode->degree = degree_data;
					newNode->coefficient = coefficient_data;

					newNode->next = cursor->next;
					newNode->prior = cursor;
					cursor->next->prior = newNode;
					cursor->next = newNode;
				}
			}

		}


	}

}


template < class DT >
void List<DT>::remove(const DT& degree_data, const DT& coefficient_data)
{
	if (isFull() == true)    //가득 찼을 때 예외처리
	{
		cout << "List is Full" << endl;
	}
	else if (isEmpty() == true)		//비어 있는 리스트에 항을 빼는 연산을 하면 항의 부호를 반전시켜 추가한다.
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

		newNode->degree = degree_data;
		newNode->coefficient = coefficient_data;

		head = newNode;
		cursor = newNode;
	}
	else
	{
		if (head->degree == degree_data)			//입력된 차수가 head의 차수와 같을 때 흡수(빼줌)
		{
			head->coefficient = head->coefficient - coefficient_data;
		}
		else if (head->degree < degree_data)		//입력된 차수가 head의 차수보다 높을 때 맨 앞으로 삽입
		{
			ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

			newNode->degree = degree_data;
			newNode->coefficient = coefficient_data * (-1);
			newNode->next = head;
			head->prior = newNode;
			head = newNode;
		}
		else
		{
			cursor = head;

			while (cursor->next != NULL)			//커서가 마지막 노드까지 갔을 때는 정지.
			{										//커서가 마지막 노드라면 cursor->next == NULL이므로 cursor->next->degree가 정의되지 않아 오류가 나므로, 앞으로 빼줌
				if (cursor->next->degree > degree_data)		//커서 다음 노드의 차수가 입력된 차수보다 작거나 같게 될 때까지
				{
					cursor = cursor->next;
				}
				else
				{
					break;
				}
			}

			if (cursor->next == NULL)		//커서가 맨 끝까지 갔다면
			{
				if (cursor->degree == degree_data)				//마지막 노드의 차수와 입력된 차수가 같을 때
				{
					cursor->coefficient = cursor->coefficient - coefficient_data;
				}
				else											// 마지막 노드의 차수가 입력된 차수보다 클 때(입력된 차수가 마지막 노드 차수보다 작을 때)
				{
					ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

					newNode->degree = degree_data;
					newNode->coefficient = coefficient_data * (-1);
					newNode->prior = cursor;
					cursor->next = newNode;
				}
			}
			else
			{
				if (cursor->next->degree == degree_data)		//커서 다음 노드의 차수가 입력된 차수와 같으면
				{
					cursor->next->coefficient = cursor->next->coefficient - coefficient_data;
				}
				else											//커서 다음 노드의 차수가 입력된 차수보다 작으면 (전체 노드 중 입력 차수와 같은 차수를 가진 노드가 존재하지 않는다면)
				{
					ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

					newNode->degree = degree_data;
					newNode->coefficient = coefficient_data * (-1);

					newNode->next = cursor->next;
					newNode->prior = cursor;
					cursor->next->prior = newNode;
					cursor->next = newNode;
				}
			}

		}
	}





}

// Clear list
template < class DT >
void List<DT>::clear()
{
	ListNode<DT>* tempPtr = head;

	while (tempPtr != NULL)		//head부터 할당 해제
	{
		head = head->next;
		delete tempPtr;
		tempPtr = head;
	}

	head = NULL;
	cursor = NULL;
}


//------------ List status operations ------------------

// List is empty
template < class DT >
bool List<DT>::isEmpty() const
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// List is full
template < class DT >
bool List<DT>::isFull() const
{
	ListNode<DT>* testNode = new ListNode<DT>(0, 0, NULL, NULL);

	if (testNode == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//-----------------------------------------------------------

template < class DT >
void List<DT>::showStructure() const
{
	bool isthis_firstdisplay = true;

	if (isEmpty() == true)
	{
		cout << "Empty List" << endl;
	}
	else
	{
		ListNode<DT>* showPtr = head;

		while (showPtr != NULL)
		{
			if (showPtr->coefficient >= 0)		//계수가 양수 or 0일 때
			{
				if (showPtr->coefficient == 0)	//계수가 0이라면
				{
					showPtr = showPtr->next;
					continue;
				}

				if (showPtr->coefficient != 0 && isthis_firstdisplay == true)		//계수가 0인 항 제외 / 처음 출력 할 때 + 안넣음
				{
					if (showPtr->degree == 0)		//차수 0 (상수항)
					{
						cout << showPtr->coefficient;
					}
					else if (showPtr->coefficient == 1)		//계수 1
					{
						cout << "x^" << showPtr->degree;
					}
					else
					{
						cout << showPtr->coefficient << "x^" << showPtr->degree;
					}

					isthis_firstdisplay = false;
					showPtr = showPtr->next;
				}
				else if (showPtr->coefficient != 0)		//위와 동일
				{
					if (showPtr->degree == 0)		
					{
						cout << " +" << showPtr->coefficient;
					}
					else if (showPtr->coefficient == 1)
					{
						cout << " +" << "x^" << showPtr->degree;
					}
					else
					{
						cout << " +" << showPtr->coefficient << "x^" << showPtr->degree;
					}

					showPtr = showPtr->next;
				}
			}
			else								//계수가 음수일 때
			{

				if (showPtr->coefficient != 0 && isthis_firstdisplay == true)		//계수가 0인 항 제외 / 처음 출력 할 때 " " 안넣음
				{
					if (showPtr->degree == 0)		//차수 0 (상수항)
					{
						cout << showPtr->coefficient;
					}
					else if (showPtr->coefficient == -1)	//계수 -1
					{
						cout << " -" << "x^" << showPtr->degree;
					}
					else
					{
						cout << showPtr->coefficient << "x^" << showPtr->degree;
					}

					isthis_firstdisplay = false;
					showPtr = showPtr->next;
				}
				else if (showPtr->coefficient != 0)
				{
					if (showPtr->degree == 0)		//차수 0 (상수항)
					{
						cout << " " << showPtr->coefficient;
					}
					else if (showPtr->coefficient == -1)	//계수 -1
					{
						cout << " -" << "x^" << showPtr->degree;
					}
					else
					{
						cout << " " << showPtr->coefficient << "x^" << showPtr->degree;
					}

					showPtr = showPtr->next;
				}
			}
			
		}
	}
	cout << endl;
}


////////////////////////////////////////////////////////////////////////////////////

//
//
// 
/*  Main 함수 */
// 
// 
// 


void main()
{
	List<int> testList;   // Test list
	int degree=0, coefficient=0; 	 // List data element
	char cmd;					 // Input command

	do
	{
		testList.showStructure();                     // Output list

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		if (cmd == '+' || cmd == '-')
			cin >> degree >> coefficient;

		switch (cmd)
		{
		case '+':									  // insert
			cout << "Insert : " << coefficient << "x^" << degree << endl;

			testList.insert(degree, coefficient);
			break;

		case '-':                                  // remove
			if (testList.isEmpty() == true)
			{
				cout << "Insert : " << coefficient << "x^" << degree << " : 비어 있는 리스트이므로 뺐을 때 부호 반전" << endl;
			}
			else
			{
				cout << "Insert : -" << coefficient << "x^" << degree << endl;
			}
			testList.remove(degree, coefficient);
			break;

		case 'C': case 'c':                       // clear
			cout << "Clear the list" << endl;
			testList.clear();
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while (cmd != 'Q' && cmd != 'q');
}

