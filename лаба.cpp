#include <iostream>

using namespace std;

int iBits(int &num) {
    if (num < 0) {
        for (int i = 0; i < 32; i+=2) {
           num |= (1 << i); 
        }
    }
    else{
        for (int i = 1; i < 32; i+=2) {
            num &= ~(1 << i); 
        }  
   }
    return num;
}
void fBits(float &num) {
    unsigned int *ptr = reinterpret_cast<unsigned int*>(&num);
    unsigned int value = *ptr; 

    if (num < 0) {
        
        for (int i = 0; i < 32; i += 2) {
            value &= ~((unsigned)1 << i);
        }
    }
    else {
        
        for (int i = 1; i < 32; i += 2) {
            value |= ((unsigned)1 << i);
        }
    }
    *ptr = value;
}
void zadania(int N) {
    
    cout << "1: Вывод sizeof различных типов данных"<<endl;
    cout << "2: Вывод двоичного представления в памяти целого числа"<<endl;
    cout << "3: Вывод двоичного представления в памяти типа float"<<endl;
}
int main() {
    setlocale(0, "");
    unsigned int order = 32;
    unsigned int mask = 1 << (order - 1);
    int choice;
    int N=1;
    bool p = true;
    while (p) {
        zadania(N);
        cout << "Выберите номер задания:" << endl;
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            cout << "1. Сколько памяти отводится под различные типы данных с спецификаторами и без: " << endl;
            cout << "int:" << sizeof(int)  << endl;
            cout << "short int:" << sizeof(short int) << endl;
            cout << "long int:" << sizeof(long int)  << endl;
            cout << "float:" << sizeof(float)  << endl;
            cout << "double:" << sizeof(double)  << endl;
            cout << "long double:" << sizeof(long double)  << endl;
            cout << "char:" << sizeof(char) << endl;
            cout << "bool:" << sizeof(bool)  << endl;

            break;
        case 2:

            int n;
            cout << "2. Введите число" << endl;
            cin >> n;
            cout << "2. Двоичное представление в памяти целого числа: " << endl;
            {for (unsigned int i = 1; i <= order; i++)
            {
                putchar(n & mask ? '1' : '0');
                if (i % 8 == 0) {
                    cout << " ";
                }
                if (i % order - 1 == 0) {
                    cout << " ";
                }
                mask >>= 1;
            }
            }
            cout << endl;
            iBits(n);
            cout << "Идз: Если число отрицательное, то необходимо поменять значения четных битов на 1, если положительное, то поменять значения нечетных битов на 0." << endl;
            {int sighBit = (n < 0) ? 1 : 0;
            cout << sighBit << " ";}
            for (int i = order - 2; i >= 0; --i)
            {
                cout << ((n >> i) & 1);
                if (i == 31 || i == 24 || i == 16 || i == 8) {
                    cout << " ";
                }
            }
            cout << endl;

            break;

        case 3:
            union
            {
                int int_Float;
                float f;
            };
            order = sizeof(int) * 8;
            mask = 1 << order - 1;

            cout << "3. Введите число типа float:" << endl;
            cin >> f;
            cout << "3. Двоичное представление в памяти целого числа: " << f << endl;
            for (int i = 1; i <= order; i++)
            {
                putchar((*reinterpret_cast<unsigned int*>(&f)) & mask ? '1' : '0');
                mask >>= 1;
                if (i == 1 || i == 24 || i == 25) {
                    cout << " ";
                }
            }
            
            cout << endl;

            fBits(f);
            unsigned int* ptr = reinterpret_cast<unsigned int*>(&f);
            unsigned int value = *ptr;
            cout << "Идз: Если число отрицательное, то необходимо поменять значения четных битов на 1, если положительное, то поменять значения нечетных битов на 0." << endl;
            for (int i = order - 1; i >= 0; --i)
            {
                ((value >> i) & 1);
            }
            int* num_ptr = reinterpret_cast<int*>(&f);

            for (int i = 31; i >= 0; i--)
            {
                cout << ((*num_ptr >> i) & 1);
                if (i == 31 || i == 8 || i == 7) {
                    cout << " ";
                }
            }
            cout << endl;

            break;
        }
        system("pause");
        system("cls");
    }
}
