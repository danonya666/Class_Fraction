#include <iostream>
#include <fstream>
using namespace std;


class Fraction
{
private:
    int numerator_;
    int denomenator_;

public:
    Fraction(int numerator_, int denomenator_):
        numerator_(numerator_),
        denomenator_(denomenator_)
        {
            if (!denomenator_)
                throw "Error";
        }

    Fraction():
        numerator_(numerator_),
        denomenator_(denomenator_)
    {
        numerator_ = 0;
        denomenator_ = 1;
    }
    int numerator()
    {
        return this->numerator_;
    }

    int denomenator()
    {
        return this->denomenator_;
    }

    double Value() const
    {
        double value = (float)this->numerator() / (float)this->denomenator();
        return value;
    }

    Fraction(Fraction &other)
    {
        if (other.denomenator() == 0)
            throw "Error";
        if (this->Value() != other.Value())
            {
                this->numerator_ = other.numerator();
                this->denomenator_ = other.denomenator();
            }
    }

    void simplify()
    {
        for(int i = 1; i <= max(this->denomenator(), this->numerator()); i++)
        {
            if(this->denomenator() % i == 0 && this->numerator() % i == 0)
            {
                this->denomenator_ /= i;
                this->numerator_ /= i;
            }
        }
    }

    int const SCM(Fraction f1) //NOK
    {
        int large = (f1.denomenator() > this->denomenator())? f1.denomenator(): this->denomenator();
        for(int i = large; ; i++)
        {
            if (i % f1.denomenator() == 0 && i % this->denomenator() == 0)
                return i;
        }
    }


    Fraction operator + (Fraction& other)
    {
        Fraction result;
        int scm = this->SCM(other);
        result.denomenator_ = scm;
        int difference1 = scm / this->denomenator();
        int difference2 = scm / other.denomenator();

        result.numerator_ = difference1 * this->numerator() + difference2 * other.numerator();
        return result;
    }

    Fraction operator - (Fraction& other)
    {
        Fraction result;
        int scm = this->SCM(other);
        result.denomenator_ = scm;
        int difference1 = scm / this->denomenator();
        int difference2 = scm / other.denomenator();

        result.numerator_ = difference1 * this->numerator() - difference2 * other.numerator();

        return result;
    }

    Fraction operator * (Fraction& other)
    {
        Fraction result;
        result.denomenator_ = this->denomenator() * other.denomenator();
        result.numerator_ = this->numerator() * other.numerator();
        result.simplify();
        return result;
    }

    Fraction operator / (Fraction &other)
    {
        Fraction result;
        result.denomenator_ = this->denomenator() * other.numerator();
        result.numerator_ = this->numerator() * other.denomenator();
        result.simplify();
        return result;
    }

    friend ostream& operator << (ostream& fout, Fraction& f1)
    {
        if (f1.denomenator() < 0)
            fout << f1.numerator() * -1 << " / " << f1.denomenator() * -1 << endl;
        else
            fout << f1.numerator() << " / " << f1.denomenator() << endl;
        return fout;
    }

};

int main()
{
    Fraction f1(10, 8), f2(100, 7), f3(5, 1);
    f3 = f1 + f2;
    f3.simplify();
    cout << f3 << f3.Value();
    return 0;
}


//2
