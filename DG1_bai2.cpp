/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

class PHANSO {
private:
    int tu, mau;

public:

    void nhap() {
        cout << "Tu so: ";
        cin >> tu;

        do {
            cout << "Mau so: ";
            cin >> mau;
        } while (mau == 0);
    }

    void xuat() {
        cout << tu << "/" << mau;
    }

    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    void rutGon() {
        int g = gcd(abs(tu), abs(mau));
        tu /= g;
        mau /= g;
    }

    PHANSO cong(PHANSO p) {
        PHANSO kq;
        kq.tu = tu * p.mau + p.tu * mau;
        kq.mau = mau * p.mau;
        return kq;
    }

    PHANSO tru(PHANSO p) {
        PHANSO kq;
        kq.tu = tu * p.mau - p.tu * mau;
        kq.mau = mau * p.mau;
        return kq;
    }

    PHANSO nhan(PHANSO p) {
        PHANSO kq;
        kq.tu = tu * p.tu;
        kq.mau = mau * p.mau;
        return kq;
    }

    PHANSO chia(PHANSO p) {
        PHANSO kq;
        kq.tu = tu * p.mau;
        kq.mau = mau * p.tu;
        return kq;
    }

    bool bangNhau(PHANSO p) {
        return tu * p.mau == p.tu * mau;
    }

    void tang1() {
        tu += mau;
        rutGon();
    }

    void giam1() {
        tu -= mau;
        rutGon();
    }

};

int main() {

    PHANSO ps1, ps2, kq;

    cout << "Nhap phan so thu nhat:\n";
    ps1.nhap();
    cout << "Phan so thu nhat: ";
    ps1.xuat();

    cout << "\n\nNhap phan so thu hai:\n";
    ps2.nhap();
    cout << "Phan so thu hai: ";
    ps2.xuat();

    cout << "\n\nCong 2 phan so:\n";
    cout << endl;
    ps1.xuat();
    cout << " + ";
    ps2.xuat();
    cout << " = ";

    kq = ps1.cong(ps2);
    kq.xuat();

    cout << "\nKet qua sau khi rut gon: ";
    kq.rutGon();
    kq.xuat();

    cout << "\n\nTru 2 phan so:\n";
    ps1.xuat();
    cout << " - ";
    ps2.xuat();
    cout << " = ";

    kq = ps1.tru(ps2);
    kq.xuat();

    cout << "\nKet qua sau khi rut gon: ";
    kq.rutGon();
    kq.xuat();

    cout << "\n\nNhan 2 phan so:\n";
    ps1.xuat();
    cout << " * ";
    ps2.xuat();
    cout << " = ";

    kq = ps1.nhan(ps2);
    kq.xuat();

    cout << "\nKet qua sau khi rut gon: ";
    kq.rutGon();
    kq.xuat();

    cout << "\n\nChia 2 phan so:\n";
    ps1.xuat();
    cout << " / ";
    ps2.xuat();
    cout << " = ";

    kq = ps1.chia(ps2);
    kq.xuat();

    cout << "\nKet qua sau khi rut gon: ";
    kq.rutGon();
    kq.xuat();

    cout << "\n\n";

    if (ps1.bangNhau(ps2))
        cout << "Hai phan so bang nhau\n";
    else
        cout << "Hai phan so khong bang nhau\n";

    ps1.tang1();
    cout << "\nPhan so 1 sau khi tang 1: ";
    ps1.xuat();

    ps2.giam1();
    cout << "\nPhan so 2 sau khi giam 1: ";
    ps2.xuat();

    cout << endl;

    return 0;
}