

#include <iostream>
#include "hierarchyTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the binary search tree data item class
//

class TestData
{
public:

    void setKey(string newKey)
    {
        keyField = newKey;
    }   // Set the key

    string key() const
    {
        return keyField;
    }     // Returns the key

private:

    string keyField;                // Key for the data item
};

//--------------------------------------------------------------------

void print_help()
{
    cout << endl << " <Commands> " << endl;
    cout << " [Existing member] hires [new member] " << endl;
    cout << " fire [existing member] " << endl;
    cout << " Print " << endl;
    cout << endl;
}

void main()
{
    Tree<TestData, string> testTree;    // test Tree
    TestData testData1, testData2;      // Tree�� Node�� �� Key��
    string inputStr[3];              // input

    // CEO ���
    cout << "��� �̸��� 2~20�� �̳�, ��� �ϳ��� �빮�ڿ� �ҹ��� ����, ' �� - ��� ����, ���� ��� �Ұ���." << endl;
    cout << "�Ȱ��� �̸��� �ԷµǴ� ���� ������� ����. �� ���ǵ��� ���� �̸��� �Է��ϼ���." << endl;
    cout << "CEO�� ���� ����մϴ�. CEO�� �̸��� �Է��ϼ��� : ";
    cin >> inputStr[1];
    testData1.setKey(inputStr[1]);
    testTree.CEO(testData1);

    // ��ɺ�
    print_help();

    while(1)
    {
        cout << endl << "Command: ";                  // Read command
        cin >> inputStr[0];

        if (inputStr[0] == "Print" || inputStr[0] == "print")
        {
            cout << endl;
            testTree.showStructure();
        }
        else if (inputStr[0] == "Fire" || inputStr[0] == "fire")
        {
            cin >> inputStr[1];
            testData1.setKey(inputStr[1]);
            testTree.fire(testData1);
        }
        else
        {
            cin >> inputStr[1];
            if (inputStr[1] == "Hires" || inputStr[1] == "hires")
            {
                cin >> inputStr[2];
                testData1.setKey(inputStr[0]);
                testData2.setKey(inputStr[2]);
                testTree.hire(testData1, testData2);
            }
            else
                cout << "ERROR" << endl;
        }   
    }

}
