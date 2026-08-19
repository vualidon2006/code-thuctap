/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string.h>
using namespace std;
class Nguoi
{protected:
 char *HoTen;
 int NamSinh;
public:
 Nguoi();
 Nguoi(char *ht, int ns):NamSinh(ns) {HoTen=strdup(ht);}
 ~Nguoi() {delete [ ] HoTen;}
 void An() const
   { cout<<HoTen<<" an 3 chen com \n";
   }
 virtual void Xuat() const
   { cout << "Nguoi Ho ten: " << HoTen << ", Sinh nam: " << NamSinh;
   }

 //friend ostream& operator << (ostream &os, Nguoi& p);
};
class SinhVien : public Nguoi
{protected:
 char *MaSo;
 public:
 SinhVien();
 SinhVien(char *ht, char *ms, int ns) : Nguoi(ht,ns)
 { MaSo = strdup(ms);
 }
 ~SinhVien() {delete [ ] MaSo;}
 void Xuat() const
{cout<<"Sinh vien: "<<HoTen<<", Ma so: "<<MaSo;
 
}
};
class NuSinh : public SinhVien
{protected:
 char *Tinhcach;
public:
NuSinh(char *ht, char *ms, int ns,char *tc) : SinhVien(ht,ms,ns)
{Tinhcach=strdup(tc);
    
}
void An() const
{
cout << HoTen;
cout << " ma so " << MaSo << " an 2 to pho";
}
void Xuat() const
{
cout << "Nu sinh: " << HoTen;
cout << ", Tinh cach: " << Tinhcach;
}
};
class CongNhan : public Nguoi
{protected:
  double MucLuong;
 public:
CongNhan(char *n, double ml, int ns) : Nguoi(n,ns),  MucLuong(ml){ }
void Xuat() const
{
cout << "Cong nhan: " << HoTen;
cout << ", Muc luong: " << MucLuong;
}
};
void XuatDs(int n, Nguoi *an[ ])
{ for (int i = 0; i < n; i++)
  { an[i]->Xuat();
    cout << "\n";
  }
};
const int n = 4;
int main()
{ Nguoi* a[n];
  a[0] = new SinhVien("Tran Van Hao", "20203456", 1980);
  a[1] = new NuSinh("Nguyen Thi Ha Dong", "20211234", 1981,"Diu dang");
  a[2] = new CongNhan("Nguyen Dang Thanh", 6800000, 1982);
  a[3] = new Nguoi("Phung Van Thang",1970);
  XuatDs(4,a);
  return 0;
}

