#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

void swap(int* a, int* b);
int partition(int* arr, int low, int high);
void quickSort(int* arr, int low, int high);
void merge(int* main, int* arr1, int* arr2, int sizeArr, int sizeArr2, int sizeMain);

void writeArray(const string& filename, int*& array, int& till);


int main() {
    string filename = "C:/C++/filename.txt";

    int size = 1000 * 700;
    int* rand_arr = new int[size];
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < size; i++)
        rand_arr[i] = 10 + rand() % 89;

    writeArray(filename, rand_arr, size);

    int tempFileSize = size / 2;
    int tempFileSize2 = 0;
    int* tempArr = new int[tempFileSize];
    int* tempArr2 = nullptr;

    (size % 2 != 0) ? tempFileSize2 = size / 2 + 1 : tempFileSize2 = size / 2;
    tempArr2 = new int[tempFileSize2];

    fstream fs;
    fs.open(filename, fstream::in);

    if (fs.is_open())
    {
        int i = 0;
        while (!fs.eof())
        {
            if (i < tempFileSize)
            {
                fs >> tempArr[i];
                i++;
            }
            else
            {
                fs >> tempArr2[i - tempFileSize];
                i++;
            }
        }
        fs.close();
    }

    quickSort(tempArr, 0, tempFileSize - 1);
    quickSort(tempArr2, 0, tempFileSize2 - 1);

    string tempName01 = "C:/C++/temp01.txt";
    string tempName02 = "C:/C++/temp02.txt";

    writeArray(tempName01, tempArr, tempFileSize);
    writeArray(tempName02, tempArr2, tempFileSize2);

    merge(rand_arr, tempArr, tempArr2, tempFileSize, tempFileSize2, size);

    writeArray(filename, rand_arr, size);

    remove("C:/C++/temp01.txt");
    remove("C:/C++/temp02.txt");

    delete[] rand_arr;
    delete[] tempArr;
    delete[] tempArr2;
    return 0;
}

void writeArray(const string& filename, int*& array, int& till)
{
    fstream fs;
    fs.open(filename, fstream::out);
    if (fs.is_open())
    {
        for (int i = 0; i < till; i++)
        {
            fs << array[i] << ' ';
        }
        fs.close();
    }
}


void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int low, int high)
{
    int pivot = arr[high];    // ������� �������
    int i = (low - 1);  // ������ ����������� ��������
    for (int j = low; j <= high - 1; j++)
    {
        // ���� ������� ������� ������ ��� ����� ��������
        if (arr[j] <= pivot)
        {
            i++;    // ����������� ������ ������������ ��������
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // ������ �������� ��������

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void merge(int* main, int* arr1, int* arr2, int sizeArr, int sizeArr2, int sizeMain)
{

    int i = 0, j = 0;
    int k = 0;  // ������ ����� �����

    while (i < sizeArr && j < sizeArr2) {
        // ���������� ����������� �������� ������� �� ������� ������
        if (arr1[i] <= arr2[j]) {
            main[k] = arr1[i];
            i++;
        }
        else {
            main[k] = arr2[j];
            j++;
        }
        k++;
    }
    // ���������� ���������� �������� ����� �����
    while (i < sizeArr) {
        main[k] = arr1[i];
        i++;
        k++;
    }
    // ���������� ���������� �������� ������ �����
    while (j < sizeArr2) {
        main[k] = arr2[j];
        j++;
        k++;
    }

}