#include <iostream>
using namespace std;

class Array
{
public:
    Array(const Array& ary) { // 복사 생성자
        size_ = ary.size_;

        if (size_ > 0)
        {
            ary_ = new int[size_];
            for (int i = 0; i < size_; i++)
                ary_[i] = ary.ary_[i];
        }
        else
        {
            ary_ = NULL;
        }
    }
    Array& operator=(const Array& ary)
    {
        size_ = ary.size_;

        if (size_ > 0)
        {
            ary_ = new int[size_];
            for (int i = 0; i < size_; i++)
                ary_[i] = ary.ary_[i];
        }
        else
        {
            ary_ = NULL;
        }

        return (*this);
    }
    Array(int count = 0)
    {
        size_ = count;
        ary_ = NULL;

        if (size_ > 0)
        {
            ary_ = new int[size_];
            for (int i = 0; i < size_; i++)
                ary_[i] = 0;
        }
    }

    ~Array()
    {
        if (ary_ != NULL)
            delete[] ary_;
    }

    Array& Add(int value)
    {
        if (size_ == 0)
        {
            ary_ = new int[1];
            ary_[size_] = value;
            size_++;
        }
        else                // 원소의 개수가 1개 이상이라면
        {
            int* temp = new int[size_];
            for (int i = 0; i < size_; i++)
                temp[i] = ary_[i];

            delete[] ary_;
            size_++;
            ary_ = new int[size_];
            for (int i = 0; i < size_ - 1; i++)
                ary_[i] = temp[i];
            ary_[size_ - 1] = value;

            delete[] temp;
        }

        return (*this);
    }

    void Print() // 미사용
    {
        cout << "{ ";
        for (int i = 0; i < size_; i++)
            cout << ary_[i] << " ";
        cout << "}";
    }

    Array operator++() // ++ 전위 증가 연산자 오버로딩
    {
        for (int i = 0; i < size_; i++)
            ary_[i]++;

        return (*this);
    }

    friend Array operator+(const Array& ary1, const Array& ary2);
    friend ostream& operator<<(ostream& out, const Array& ary);

private:
    int size_;
    int* ary_;
};

Array operator+(const Array& ary1, const Array& ary2) // + 연산자 오버로딩
{
    Array result;

    for (int i = 0; i < ary1.size_; i++)
        result.Add(ary1.ary_[i]);

    for (int i = 0; i < ary2.size_; i++)
    {
        result.Add(ary2.ary_[i]);
    }

    return result;
}

ostream& operator<<(ostream& out, const Array& ary) // << 연산자 오버로딩
{
    out << "( ";
    for (int i = 0; i < ary.size_; i++)
        out << ary.ary_[i] << " ";

    out << ")";

    return out;
}

int main()
{
    Array ary1(3);
    ary1.Add(1).Add(2).Add(3);
    Array ary2;
    ary2.Add(100).Add(200).Add(300);

    ++ary1;                              // ++ 전위 증가 연산자
    Array ary3 = ary1;                  // 복사 생성자
    Array ary4 = ary1 + ary2;           // + 연산자, 복사 생성자
    Array ary5;
    ary5 = ary1;                                 // 대입 연산자 (추가)

    cout << ary1 << endl;               // << 출력 연산자
    cout << ary2 << endl;
    cout << ary3 << endl;
    cout << ary4 << endl;
    cout << ary5 << endl;

}
