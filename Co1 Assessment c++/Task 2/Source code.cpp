#include <iostream>
#include <vector>
using namespace std;
int& highestMark(int marks[], int size)
{
    int maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (marks[i] > marks[maxIndex])
        {
            maxIndex = i;
        }
    }
    return marks[maxIndex];
}
const int& getHighestMark(const int marks[], int size)
{
    int maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (marks[i] > marks[maxIndex])
        {
            maxIndex = i;
        }
    }
    return marks[maxIndex];
}
int getHighestMarkCopy(const int marks[], int size)
{
    int maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (marks[i] > marks[maxIndex])
        {
            maxIndex = i;
        }
    }
    return marks[maxIndex];
}
int& dangerousFunction()
{
    int x = 50;
    return x;  // Warning: returning reference to local variable
}
int highestMarkIndex(const int marks[], int size)
{
    int maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (marks[i] > marks[maxIndex])
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}
int* highestMarkPointer(int marks[], int size)
{
    int maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (marks[i] > marks[maxIndex])
        {
            maxIndex = i;
        }
    }
    return &marks[maxIndex];
}
int main()
{
    int marks[5] = {75, 85, 90, 80, 88};
    cout << "Original Marks: ";
    for (int i = 0; i < 5; i++)
    {
        cout << marks[i] << " ";
    }
    cout << "\n\n";
    int& highest = highestMark(marks, 5);
    cout << "Highest Mark: " << highest << endl;
    highest += 2;
    cout << "After Moderation: " << highest << endl;
    cout << "Updated Marks: ";
    for (int i = 0; i < 5; i++)
    {
        cout << marks[i] << " ";
    }
    cout << "\n\n";
    highestMark(marks, 5) = 100;
    cout << "After Direct Assignment: ";
    for (int i = 0; i < 5; i++)
    {
        cout << marks[i] << " ";
    }
    cout << "\n\n";
    cout << "Highest Mark using const reference: "
         << getHighestMark(marks, 5) << endl;
    cout << "Highest Mark using copy: "
         << getHighestMarkCopy(marks, 5) << endl;
    int index = highestMarkIndex(marks, 5);
    cout << "Highest Mark Index: " << index << endl;
    marks[index] += 2;
    cout << "After Index Modification: " << marks[index] << endl;
    int* ptr = highestMarkPointer(marks, 5);
    cout << "Highest Mark using Pointer: " << *ptr << endl;
    *ptr += 2;
    cout << "After Pointer Modification: " << *ptr << endl;
    vector<int> studentMarks = {70, 80, 90};
    int& ref = studentMarks[2];
    cout << "\nVector Highest Mark: " << ref << endl;
    studentMarks.push_back(95);
    cout << "Vector size after adding mark: "
         << studentMarks.size() << endl;
    return 0;
}
