#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
    class NhanVien {
protected:
    string hoTen;
    string ngaySinh;
    double luongCoBan;
    static NhanVien* ds[100];
    static int n;

public:
    NhanVien(string ht = "", string ns = "", double lcb = 0.0)
        : hoTen(ht), ngaySinh(ns), luongCoBan(lcb) {}

    virtual void nhapThongTin() {
        cout << "Nhap ho ten: ";
        getline(cin >> ws, hoTen);
        cout << "Nhap ngay sinh: ";
        getline(cin >> ws, ngaySinh);
        cout << "Nhap luong co ban: ";
        cin >> luongCoBan;
    }

    
    virtual double tinhTongLuong() const = 0;

    string getHoTen() const { return hoTen; }

    virtual void xemTT() const {
        cout << left
             << setw(25) << hoTen
             << setw(15) << ngaySinh
             << setw(15) << fixed << setprecision(0) << luongCoBan;
    }

    
    virtual ~NhanVien() {}

    
    static void them(NhanVien* nv) {
        if (n >= 100) { cout << "Danh sach da day!" << endl; return; }
        ds[n++] = nv;
    }

    
    static void xemThongTin() {
        if (n == 0) { cout << "Chua co nhan vien nao!" << endl; return; }
        cout << left
             << setw(25) << "Ho ten"
             << setw(15) << "Ngay sinh"
             << setw(15) << "Luong CB"
             << setw(15) << "Bo phan"
             << setw(15) << "Tong Luong" << endl;
        cout << string(85, '-') << endl;
        for (int i = 0; i < n; i++)
            ds[i]->xemTT(); 
    }

    
    static void tinhTongLuongCongTy() {
        if (n == 0) { cout << "Chua co nhan vien nao!" << endl; return; }
        double tong = 0;
        for (int i = 0; i < n; i++)
            tong += ds[i]->tinhTongLuong();  
        cout << "Tong luong cong ty: " << fixed << setprecision(0) << tong << " VND" << endl;
    }

    
    static void timKiem() {
        if (n == 0) { cout << "Chua co nhan vien nao!" << endl; return; }
        string tenTim;
        cout << "Nhap ten can tim: ";
        getline(cin >> ws, tenTim);
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (ds[i]->getHoTen().find(tenTim) != string::npos) {
                ds[i]->xemTT(); 
                found = true;
            }
        }
        if (!found)
            cout << "Khong tim thay nhan vien: " << tenTim << endl;
    }

    
    static void giaiPhong() {
        for (int i = 0; i < n; i++)
            delete ds[i];  
        n = 0;
    }
};


NhanVien* NhanVien::ds[100];
int NhanVien::n = 0;

    class NhanVienVanPhong : public NhanVien {
private:
    int    soNgayLamViec;
    double troCap;

public:
    void nhapThongTin() override {
        NhanVien::nhapThongTin();  
        cout << "Nhap so ngay lam viec: ";
        cin >> soNgayLamViec;
        cout << "Nhap tro cap: ";
        cin >> troCap;
    }

    double tinhLuong() const {
        return luongCoBan + (double)soNgayLamViec * 500000 + troCap;
    }

    double tinhTongLuong() const override { return tinhLuong(); }

    void xemTT() const override {
        NhanVien::xemTT();
        cout << setw(15) << "Van phong"
             << setw(15) << fixed << setprecision(0) << tinhTongLuong() << endl;
    }
};


    class NhanVienSanXuat : public NhanVien {
private:
    int soSanPham;

public:
    void nhapThongTin() override {
        NhanVien::nhapThongTin();
        cout << "Nhap so san pham: ";
        cin >> soSanPham;
    }

    double tinhLuong() const {
        return luongCoBan + (double)soSanPham * 10000;
    }

    double tinhTongLuong() const override { return tinhLuong(); }

    void xemTT() const override {
        NhanVien::xemTT();
        cout << setw(15) << "San xuat"
             << setw(15) << fixed << setprecision(0) << tinhTongLuong() << endl;
    }
};


    class NhanVienQuanLy : public NhanVien {
private:
    double heSoChucVu;
    double thuong;

public:
    void nhapThongTin() override {
        NhanVien::nhapThongTin();
        cout << "Nhap he so chuc vu: ";
        cin >> heSoChucVu;
        cout << "Nhap thuong: ";
        cin >> thuong;
    }

    double tinhLuong() const {
        return luongCoBan * heSoChucVu + thuong;
    }

    double tinhTongLuong() const override { return tinhLuong(); }

    void xemTT() const override {
        NhanVien::xemTT();
        cout << setw(15) << "Quan ly"
             << setw(15) << fixed << setprecision(0) << tinhTongLuong() << endl;
    }
};

int main() {
    int chon;

    do {
        cout << "\n----- QUAN LY LUONG -----\n";
        cout << "1. Nhap NV Van phong\n";
        cout << "2. Nhap NV San xuat\n";
        cout << "3. Nhap NV Quan ly\n";
        cout << "4. Xem thong tin tat ca NV\n";
        cout << "5. Tinh tong luong cong ty\n";
        cout << "6. Tim kiem theo ho ten\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        if (chon >= 1 && chon <= 3) {
            NhanVien* nv = (chon == 1) ? (NhanVien*) new NhanVienVanPhong() :
                           (chon == 2) ? (NhanVien*) new NhanVienSanXuat()  :
                                         (NhanVien*) new NhanVienQuanLy();
            nv->nhapThongTin();   
            NhanVien::them(nv);   
        }
        else if (chon == 4) NhanVien::xemThongTin();
        else if (chon == 5) NhanVien::tinhTongLuongCongTy();
        else if (chon == 6) NhanVien::timKiem();
        else if (chon != 0) cout << "Lua chon khong hop le!" << endl;

    } while (chon != 0);

    NhanVien::giaiPhong();  
    return 0;
}