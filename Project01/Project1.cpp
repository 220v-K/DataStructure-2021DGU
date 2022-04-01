
#include <fstream>
#include <string>
#include <iostream>
#include "Project1.h"
using namespace std;

ifstream file_read;
ofstream file_write;

ListNode::ListNode()
{
	this->name = '\0';
	this->phone_number = '\0';
	this->birthday = '\0';
	this->birth_month = '\0';

	this->next = NULL;
}

List::List()
{
	this->head = NULL;
    this->cursor = NULL;
}

List::~List()       //�Ҵ� ����
{
    ListNode* tempPtr;
    cursor = head;

    while (cursor != NULL)
    {
        tempPtr = cursor;
        cursor = cursor->next;
        delete tempPtr;
    }
}

void List::read(const string& filename)
{
	file_read.open(filename);   //���� ����
    if (file_read.is_open())    //������ ������ �ʾҴٸ� ����ó��
    {
        while (file_read.eof() == false)    //���� ������ ���� �� ���� �ݺ�
        {
            if (head == NULL)       //ù ���
            {
                ListNode* newNode = new ListNode();
                getline(file_read, newNode->name);
                getline(file_read, newNode->phone_number);
                getline(file_read, newNode->birthday);
                newNode->birth_month = newNode->birthday.substr(0, 2);

                head = newNode;
                cursor = newNode;
            }
            else                    //���� ������
            {
                ListNode* newNode = new ListNode();
                getline(file_read, newNode->name);
                getline(file_read, newNode->phone_number);
                getline(file_read, newNode->birthday);
                newNode->birth_month = newNode->birthday.substr(0, 2);

                cursor->next = newNode;
                cursor = newNode;
            }
        }
    }
    else
    {
        cout << "File is not readed" << endl;
        return;
    }

        //-------������ ���Ͽ��� �о��, �Ʒ����� entry ���� / month of birthday ���. -------//

        after_update();  

	
	file_read.close();   //���� �ݱ�
}

void List::write(const string& filename)
{
    file_write.open(filename); //���� ����

    if (file_write.is_open())    //������ ������ �ʾҴٸ� ����ó��
    {
        if (isEmpty() == true)      //��Ʈ���� ���ٸ� ����ó��
        {
            cout << "Entry to write isn't exist" << endl;
        }
        else
        {
            cursor = head;
            while (cursor != NULL)
            {
                file_write << cursor->name << "\n";
                file_write << cursor->phone_number << "\n";
                file_write << cursor->birthday << "\n";

                cursor = cursor->next;
            }

            cout << "The list is written into " << filename << endl;
        }
    }
    else
    {
        cout << "File is not written" << endl;
        return;
    }

    file_write.close(); //���� �ݰ�
}

void List::after_update()   //���� ����Ʈ�� ������Ʈ �� �� ���.
{
    if (isEmpty() == true)      //���� ����Ʈ�� ����� �� ����ó�� ���ְ�
    {
        cout << "File List is Empty" << endl;
    }
    else                        //�ƴ� �� ����~
    {
        int num_of_entry = 0;

        cursor = head;
        while (cursor != NULL)
        {
            num_of_entry += 1;
            cursor = cursor->next;
        }
        cout << "Total number of entries in the list : " << num_of_entry << endl;

        //----���δ� entry ����, �����δ� ���� ���� ����

        //���� ���� ���� ���� �κ�
        int num_birthmonth[12] = { 0, };

        cursor = head;
        while (cursor != NULL)
        {
            if (cursor->birth_month == "01")
                num_birthmonth[0] += 1;
            else if (cursor->birth_month == "02")
                num_birthmonth[1] += 1;
            else if (cursor->birth_month == "03")
                num_birthmonth[2] += 1;
            else if (cursor->birth_month == "04")
                num_birthmonth[3] += 1;
            else if (cursor->birth_month == "05")
                num_birthmonth[4] += 1;
            else if (cursor->birth_month == "06")
                num_birthmonth[5] += 1;
            else if (cursor->birth_month == "07")
                num_birthmonth[6] += 1;
            else if (cursor->birth_month == "08")
                num_birthmonth[7] += 1;
            else if (cursor->birth_month == "09")
                num_birthmonth[8] += 1;
            else if (cursor->birth_month == "10")
                num_birthmonth[9] += 1;
            else if (cursor->birth_month == "11")
                num_birthmonth[10] += 1;
            else if (cursor->birth_month == "12")
                num_birthmonth[11] += 1;
            else
                cout << "Error : birthday of Entry is improper" << endl;

            cursor = cursor->next;
        }

        //��� �κ�
        cout << "Number of birthdays in" << endl;

        if (num_birthmonth[0] != 0)
            cout << "       " << "January: " << num_birthmonth[0] << endl;
        if (num_birthmonth[1] != 0)
            cout << "       " << "February: " << num_birthmonth[1] << endl;
        if (num_birthmonth[2] != 0)
            cout << "       " << "March: " << num_birthmonth[2] << endl;
        if (num_birthmonth[3] != 0)
            cout << "       " << "April: " << num_birthmonth[3] << endl;
        if (num_birthmonth[4] != 0)
            cout << "       " << "May: " << num_birthmonth[4] << endl;
        if (num_birthmonth[5] != 0)
            cout << "       " << "June: " << num_birthmonth[5] << endl;
        if (num_birthmonth[6] != 0)
            cout << "       " << "July: " << num_birthmonth[6] << endl;
        if (num_birthmonth[7] != 0)
            cout << "       " << "August: " << num_birthmonth[7] << endl;
        if (num_birthmonth[8] != 0)
            cout << "       " << "September: " << num_birthmonth[8] << endl;
        if (num_birthmonth[9] != 0)
            cout << "       " << "October: " << num_birthmonth[9] << endl;
        if (num_birthmonth[10] != 0)
            cout << "       " << "November: " << num_birthmonth[10] << endl;
        if (num_birthmonth[11] != 0)
            cout << "       " << "December: " << num_birthmonth[11] << endl;
    }
}

void List::select_month()
{
    if (isEmpty() == true)
    {
        cout << "File List is Empty" << endl;
    }
    else
    {
        string selected_month, month_num;
        int i = 0, num_selected_birthmonth = 0;

        cout << "Enter the selected month (ù ���ڴ� �빮�ڷ� �Է��� �ּ���) : ";
        cin.ignore(INT_MAX, '\n');   //�Է� ���� �ʱ�ȭ
        getline(cin, selected_month);

        if (selected_month == "January")
            month_num = "01";
        else if (selected_month == "February")
            month_num = "02";
        else if (selected_month == "March")
            month_num = "03";
        else if (selected_month == "April")
            month_num = "04";
        else if (selected_month == "May")
            month_num = "05";
        else if (selected_month == "June")
            month_num = "06";
        else if (selected_month == "July")
            month_num = "07";
        else if (selected_month == "August")
            month_num = "08";
        else if (selected_month == "September")
            month_num = "09";
        else if (selected_month == "October")
            month_num = "10";
        else if (selected_month == "November")
            month_num = "11";
        else if (selected_month == "December")
            month_num = "12";
        else                                        //�߸� ������ �Լ� �����Ŵ.
        {
            cout << "Invalid name of month" << endl;
            return;
        }
           

        //�� ���� ������ ����� ��� ��� ����
        cursor = head;
        while (cursor != NULL)
        {
            if (month_num == cursor->birth_month)
                num_selected_birthmonth += 1;

            cursor = cursor->next;
        }

        cout << "Total number of birthdays in " << selected_month << " : " << num_selected_birthmonth << endl;

        //�� ���� ������ ����� ���� ��� ����
        cursor = head;
        while (cursor != NULL)
        {
            if (month_num == cursor->birth_month)
                cout << cursor->name << endl << cursor->phone_number << endl << cursor->birthday << endl << endl;

            cursor = cursor->next;
        }

    }
}

void List::insert()
{
    if (isFull() == true)
    {
        cout << "Entry List is Full" << endl;
    }
    else
    {
        //���� �Է� ����
        string new_name, new_phonenumber, new_birthday;
        cout << "Add an entry:" << endl;
        cout << "Name: "; 
        cin.ignore(INT_MAX, '\n');   //�Է� ���� �ʱ�ȭ
        getline(cin, new_name);
        cout << "Phone: ";
        getline(cin, new_phonenumber);
        cout << "Birthday: ";
        getline(cin, new_birthday);

        //entry ��� ����
        ListNode* newNode = new ListNode();
        newNode->name = new_name;
        newNode->phone_number = new_phonenumber;
        newNode->birthday = new_birthday;
        newNode->birth_month = newNode->birthday.substr(0, 2);

        //entry ��带 ���� List�� ����
        if (isEmpty() == true)      //�Էµ� entry ��尡 ù entry�� ��
        {
            head = newNode;
            cursor = newNode;
        }
        else                        //�ƴ� ��
        {
            cursor = head;
            while (cursor->next != NULL)    //Ŀ���� �� ������ ����
                cursor = cursor->next;

            cursor->next = newNode;
        }

        after_update();
    }
}

void List::remove()
{
    if (isEmpty() == true)
    {
        cout << "Entry List is Empty" << endl;
    }
    else
    {
        //���� ����� �̸� �Է�
        string removed_name;
        cout << "Remove an entry:" << endl;
        cout << "Name: ";
        cin.ignore(INT_MAX, '\n');   //�Է� ���� �ʱ�ȭ
        getline(cin, removed_name);

        cursor = head;
        if (head->next == NULL)     //��尡 1���� ���� cursor->next�� ���� �Ұ�
        {
            if (cursor->name != removed_name)
            {
                cout << "The name doesn't exist" << endl;
                return;
            }

            //��� �����
            delete head;
            head = NULL;
            cursor = NULL;
        }
        else if (head->name == removed_name)    //head�� ���� ����� ��(��尡 1�� X)
        {
            head = head->next;
            delete cursor;
            cursor = head;
        }
        else       
        {
            while (cursor->next->name != removed_name)    //Ŀ���� �̸��� �ִ� ����� �� ����
            {
                cursor = cursor->next;
                if (cursor->next == NULL)                 //�� �̸��� ����, ����Ʈ ������ ���ٸ� ����ó��~
                {
                    cout << "The name doesn't exist" << endl;
                    return;
                }
            }

            //��� �����
            ListNode* tempPtr;
            tempPtr = cursor->next;
            cursor->next = cursor->next->next;    //�߰� ��带 ����ϱ�.. ���־���
            delete tempPtr;
        }  

        after_update();
    }
}

bool List::isFull()     //���� ó���� ���. Full = true / not Full = false
{
    ListNode* testNode = new ListNode();

    if (testNode == NULL)       //���� ��带 ������ ���� �������� ������ Full.
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool List::isEmpty()       //���� ó���� ���. Empty = true / not Empty = false
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

void List::showStructure()  //�׽�Ʈ�� ��� (ä�� ���� X)
{
    cursor = head;

    while (cursor != NULL)
    {
        cout << cursor->name << "    " << cursor->phone_number << "    " << cursor->birthday << endl;
        cursor = cursor->next;
    }
    cin.ignore(INT_MAX, '\n');
}



//main-------------------------------------------------------------
void print_help()
{
    cout << endl << "Commands:" << endl;
    cout << "   R   : read from a file" << endl;
    cout << "   +   : add a new entry" << endl;
    cout << "   -   : remove an entry" << endl;
    cout << "   W   : write to a file" << endl;
    cout << "   M   : select a month" << endl;
    cout << "   Q   : Quit the test program" << endl << endl;

}

void main()
{
    List testList;
    string filename;
    char cmd;              // Input command

    do
    {
        print_help();
        cin >> cmd;

            switch (cmd)
            {
            case 'R': case 'r':
                cout << "Enter the name of the file (.txt ���Ϸ� �Է��� �ּ���) : ";
                cin.ignore(INT_MAX, '\n');    //�Է� ���� �ʱ�ȭ
                getline(cin, filename);
                testList.read(filename);
                break;

            case '+':                                  // insert
                testList.insert();
                break;

            case '-':                                  // remove
                testList.remove();
                break;

            case 'W': case 'w':                              // getCursor
                cout << "Enter the name of the file (.txt ���Ϸ� �Է��� �ּ���) : ";
                cin.ignore(INT_MAX, '\n');    //�Է� ���� �ʱ�ȭ
                getline(cin, filename);
                testList.write(filename);
                break;

            case 'M': case 'm':                              // gotoBeginning
                testList.select_month();
                break;

            case 'Q': case 'q':                      // Quit test program
                break;

            case 'T': case 't':
                testList.showStructure();

            default:                               // Invalid command
                cout << "Inactive or invalid command" << endl;
            }
    } while (cmd != 'Q' && cmd != 'q');
}
