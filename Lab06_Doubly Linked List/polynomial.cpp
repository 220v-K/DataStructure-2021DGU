

//��� ���� �̾��� �κ�
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

//ListNode�� Constructor
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
	if (isFull() == true)    //���� á�� �� ����ó��
	{
		cout << "List is Full" << endl;
	}
	else if (isEmpty() == true)	 //������� ��
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

		newNode->degree = degree_data;
		newNode->coefficient = coefficient_data;

		head = newNode;
		cursor = newNode;
	}
	else
	{
		if (head->degree == degree_data)			//�Էµ� ������ head�� ������ ���� �� ���
		{
			head->coefficient = head->coefficient + coefficient_data;
		}
		else if (head->degree < degree_data)		//�Էµ� ������ head�� �������� ���� �� �� ������ ����
		{
			ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

			newNode->degree = degree_data;
			newNode->coefficient = coefficient_data;
			newNode->next = head;
			head->prior = newNode;
			head = newNode;
		}
		else										//�Էµ� ������ head�� �������� ���� ��
		{
			cursor = head;

			while (cursor->next != NULL)			//Ŀ���� ������ ������ ���� ���� ����.
			{										//Ŀ���� ������ ����� cursor->next == NULL�̹Ƿ� cursor->next->degree�� ���ǵ��� �ʾ� ������ ���Ƿ�, ������ ����
				if(cursor->next->degree > degree_data)		//Ŀ�� ���� ����� ������ �Էµ� �������� �۰ų� ���� �� ������
				{
					cursor = cursor->next;
				}
				else
				{
					break;
				}
			}

			if (cursor->next == NULL)		//Ŀ���� �� ������ ���ٸ�
			{
				if (cursor->degree == degree_data)				//������ ����� ������ �Էµ� ������ ���� ��
				{
					cursor->coefficient = cursor->coefficient + coefficient_data;
				}
				else											// ������ ����� ������ �Էµ� �������� Ŭ ��(�Էµ� ������ ������ ��� �������� ���� ��)
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
				if (cursor->next->degree == degree_data)		//Ŀ�� ���� ����� ������ �Էµ� ������ ������
				{
					cursor->next->coefficient = cursor->next->coefficient + coefficient_data;
				}
				else											//Ŀ�� ���� ����� ������ �Էµ� �������� ������ (��ü ��� �� �Է� ������ ���� ������ ���� ��尡 �������� �ʴ´ٸ�)
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
	if (isFull() == true)    //���� á�� �� ����ó��
	{
		cout << "List is Full" << endl;
	}
	else if (isEmpty() == true)		//��� �ִ� ����Ʈ�� ���� ���� ������ �ϸ� ���� ��ȣ�� �������� �߰��Ѵ�.
	{
		ListNode<DT>* newNode = new ListNode<DT>(0, 0, NULL, NULL);

		newNode->degree = degree_data;
		newNode->coefficient = coefficient_data;

		head = newNode;
		cursor = newNode;
	}
	else
	{
		if (head->degree == degree_data)			//�Էµ� ������ head�� ������ ���� �� ���(����)
		{
			head->coefficient = head->coefficient - coefficient_data;
		}
		else if (head->degree < degree_data)		//�Էµ� ������ head�� �������� ���� �� �� ������ ����
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

			while (cursor->next != NULL)			//Ŀ���� ������ ������ ���� ���� ����.
			{										//Ŀ���� ������ ����� cursor->next == NULL�̹Ƿ� cursor->next->degree�� ���ǵ��� �ʾ� ������ ���Ƿ�, ������ ����
				if (cursor->next->degree > degree_data)		//Ŀ�� ���� ����� ������ �Էµ� �������� �۰ų� ���� �� ������
				{
					cursor = cursor->next;
				}
				else
				{
					break;
				}
			}

			if (cursor->next == NULL)		//Ŀ���� �� ������ ���ٸ�
			{
				if (cursor->degree == degree_data)				//������ ����� ������ �Էµ� ������ ���� ��
				{
					cursor->coefficient = cursor->coefficient - coefficient_data;
				}
				else											// ������ ����� ������ �Էµ� �������� Ŭ ��(�Էµ� ������ ������ ��� �������� ���� ��)
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
				if (cursor->next->degree == degree_data)		//Ŀ�� ���� ����� ������ �Էµ� ������ ������
				{
					cursor->next->coefficient = cursor->next->coefficient - coefficient_data;
				}
				else											//Ŀ�� ���� ����� ������ �Էµ� �������� ������ (��ü ��� �� �Է� ������ ���� ������ ���� ��尡 �������� �ʴ´ٸ�)
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

	while (tempPtr != NULL)		//head���� �Ҵ� ����
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
			if (showPtr->coefficient >= 0)		//����� ��� or 0�� ��
			{
				if (showPtr->coefficient == 0)	//����� 0�̶��
				{
					showPtr = showPtr->next;
					continue;
				}

				if (showPtr->coefficient != 0 && isthis_firstdisplay == true)		//����� 0�� �� ���� / ó�� ��� �� �� + �ȳ���
				{
					if (showPtr->degree == 0)		//���� 0 (�����)
					{
						cout << showPtr->coefficient;
					}
					else if (showPtr->coefficient == 1)		//��� 1
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
				else if (showPtr->coefficient != 0)		//���� ����
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
			else								//����� ������ ��
			{

				if (showPtr->coefficient != 0 && isthis_firstdisplay == true)		//����� 0�� �� ���� / ó�� ��� �� �� " " �ȳ���
				{
					if (showPtr->degree == 0)		//���� 0 (�����)
					{
						cout << showPtr->coefficient;
					}
					else if (showPtr->coefficient == -1)	//��� -1
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
					if (showPtr->degree == 0)		//���� 0 (�����)
					{
						cout << " " << showPtr->coefficient;
					}
					else if (showPtr->coefficient == -1)	//��� -1
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
/*  Main �Լ� */
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
				cout << "Insert : " << coefficient << "x^" << degree << " : ��� �ִ� ����Ʈ�̹Ƿ� ���� �� ��ȣ ����" << endl;
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

