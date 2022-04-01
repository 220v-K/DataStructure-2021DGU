

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
    TestData testData1, testData2;      // Tree의 Node로 들어갈 Key값
    string inputStr[3];              // input

    // CEO 고용
    cout << "모든 이름은 2~20자 이내, 적어도 하나의 대문자와 소문자 포함, ' 와 - 사용 가능, 공백 사용 불가능." << endl;
    cout << "똑같은 이름이 입력되는 경우는 고려하지 않음. 이 조건들을 지켜 이름을 입력하세요." << endl;
    cout << "CEO를 먼저 고용합니다. CEO의 이름을 입력하세요 : ";
    cin >> inputStr[1];
    testData1.setKey(inputStr[1]);
    testTree.CEO(testData1);

    // 명령부
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
