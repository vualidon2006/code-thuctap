#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class NHANVIEN {
protected:
    string maNV;
    string hoTen;
    string ngaySinh;

public:
    double luongCoBan; 

    void nhapThongTin() {
        cout << "Ma nhan vien: ";
        cin >> maNV;
        cin.ignore();
        cout << "Ho ten: ";
        getline(cin, hoTen);
        cout << "Ngay sinh: ";
        getline(cin, ngaySinh);
        cout << "Luong co ban: ";
        cin >> luongCoBan;
    }

    void xemThongTin() {
        cout << "Ma NV: " << maNV;
        cout << "\nHo ten: " << hoTen;
        cout << "\nNgay sinh: " << ngaySinh;
        cout << "\nLuong co ban: " << fixed << setprecision(0) << luongCoBan;
    }
};

class NVVANPHONG : public NHANVIEN {
private:
    int thangLV;
    int soNgayCong;
    double troCap;
    double luongLV;

public:
    void nhapNVVP() {
        NHANVIEN::nhapThongTin();
        cout << "Thang lam viec: ";
        cin >> thangLV;
        cout << "So ngay cong: ";
        cin >> soNgayCong;
        cout << "Tro cap: ";
        cin >> troCap;
    }

    void tinhLuongNVVP() {
        luongLV = luongCoBan + (soNgayCong * 200000) + troCap;
    }

    void xemLuongNVVP() {
        NHANVIEN::xemThongTin();
        cout << "\nThang LV: " << thangLV;
        cout << "\nLuong thang: " << fixed << setprecision(0) << luongLV << " VNĐ" << endl;
    }
};

class NVSANXUAT : public NHANVIEN {
private:
    int thangSX;
    int soSanPham;
    double donGiaSP;
    double luongSP;

public:
    void nhapNVSX() {
        NHANVIEN::nhapThongTin();
        cout << "Thang san xuat: ";
        cin >> thangSX;
        cout << "So san pham: ";
        cin >> soSanPham;
        cout << "Don gia san pham: ";
        cin >> donGiaSP;
    }

    void tinhLuongNVSX() {
        luongSP = luongCoBan + (soSanPham * donGiaSP);
    }

    void xemLuongNVSX() {
        NHANVIEN::xemThongTin();
        cout << "\nThang SX: " << thangSX;
        cout << "\nLuong san pham: " << fixed << setprecision(0) << luongSP << " VNĐ" << endl;
    }
};

int main() {
    int chon;
    NVVANPHONG nvvp;
    NVSANXUAT nvsx;

    do {
        cout << "\n--- MENU QUAN LY NHAN VIEN ---" << endl;
        cout << "(1) Nhap va tinh luong Nhan vien Van phong\n";
        cout << "(2) Nhap va tinh luong Nhan vien San xuat\n";
        cout << "(0) Ket thuc\n";
        cout << "Chon chuc nang: ";
        cin >> chon;

        switch (chon) {
        case 1:
            cout << "\n[Nhap thong tin NV Van phong]\n";
            nvvp.nhapNVVP();
            nvvp.tinhLuongNVVP();
            cout << "\n[Ket qua luong NV Van phong]\n";
            nvvp.xemLuongNVVP();
            break;
        case 2:
            cout << "\n[Nhap thong tin NV San xuat]\n";
            nvsx.nhapNVSX();
            nvsx.tinhLuongNVSX();
            cout << "\n[Ket qua luong NV San xuat]\n";
            nvsx.xemLuongNVSX();
            break;
        case 0:
            cout << "Dang thoat chuong trinh...\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }
    } while (chon != 0);

    return 0;
}