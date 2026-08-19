/*=============================================================
 *  BÀI TOÁN TÍNH LƯƠNG – LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG (C++)
 *  Áp dụng đa hình (Polymorphism) đúng chuẩn
 *  via Template Method Pattern
 *
 *  Cây kế thừa:
 *       NhanVien  (abstract)
 *       ├── NVVanPhong
 *       ├── NVSanXuat
 *       └── NVQuanLy
 *=============================================================*/
#include <iostream>
#include <vector>
#include <string>
#include <memory>       // unique_ptr
#include <algorithm>    // transform
#include <iomanip>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  LỚP CƠ SỞ TRỪU TƯỢNG: NhanVien
//
//  Áp dụng Template Method Pattern:
//    nhapThongTin()  &  xemThongTin()  là "sealed" ở base →
//    chúng gọi các hook thuần ảo mà lớp con BẮT BUỘC override.
//  → Đảm bảo đa hình hoàn toàn; lớp con KHÔNG được gọi tường
//    minh NhanVien::xxx() nữa.
// ─────────────────────────────────────────────────────────────
class NhanVien {
protected:
    string hoTen;
    string ngaySinh;
    double luongCoBan;

    // ── Đọc phần chung (chỉ dùng nội bộ) ────────────────────
    void nhapThongTinChung() {
        cout << "  Ho ten      : "; cin.ignore(); getline(cin, hoTen);
        cout << "  Ngay sinh   : "; getline(cin, ngaySinh);
        cout << "  Luong co ban: "; cin >> luongCoBan;
    }

    // ── In phần chung (chỉ dùng nội bộ) ─────────────────────
    void xemThongTinChung() const {
        cout << left
             << setw(22) << "  Ho ten"       << ": " << hoTen    << "\n"
             << setw(22) << "  Ngay sinh"    << ": " << ngaySinh << "\n"
             << setw(22) << "  Luong co ban" << ": "
             << fixed << setprecision(0) << luongCoBan << " VND\n";
    }

    // ── Hook thuần ảo – lớp con BẮT BUỘC cài đặt ────────────
    virtual string    tieuDe()             const = 0; // tên loại NV
    virtual void      nhapThongTinRieng()        = 0; // nhập thuộc tính riêng
    virtual void      xemThongTinRieng()   const = 0; // in thuộc tính riêng

public:
    // public để CongTy tính tổng lương qua con trỏ base
    virtual double    tinhLuong()          const = 0; // công thức lương – ĐA HÌNH
    NhanVien() : luongCoBan(0) {}
    virtual ~NhanVien() {}

    string getHoTen() const { return hoTen; }

    // ══ Template Methods – LỚP CON KHÔNG ĐƯỢC OVERRIDE ══════
    //   Kiểm soát toàn bộ luồng; gọi hook ảo → đa hình hoạt động
    // ─────────────────────────────────────────────────────────
    void nhapThongTin() {                   // << SEALED (non-virtual)
        cout << "\n--- Nhap thong tin " << tieuDe() << " ---\n";
        nhapThongTinChung();                // phần chung
        nhapThongTinRieng();               // hook → lớp con tự xử lý
    }

    void xemThongTin() const {             // << SEALED (non-virtual)
        cout << "\n======= " << tieuDe() << " =======\n";
        xemThongTinChung();                // phần chung
        xemThongTinRieng();               // hook → lớp con tự xử lý
        cout << left << setw(22) << "  => Luong thuc linh" << ": "
             << fixed << setprecision(0) << tinhLuong() << " VND\n"; // hook
    }

    // Tìm kiếm không phân biệt hoa/thường
    bool timKiem(const string& ten) const {
        string a = hoTen, b = ten;
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        transform(b.begin(), b.end(), b.begin(), ::tolower);
        return a.find(b) != string::npos;
    }
};


// ─────────────────────────────────────────────────────────────
//  LỚP CON: NVVanPhong
//  Lương = LCB + SoNgayLV * 500.000 + TroCap
// ─────────────────────────────────────────────────────────────
class NVVanPhong : public NhanVien {
private:
    int    soNgayLamViec;
    double troCap;

protected:
    string tieuDe() const override { return "NHAN VIEN VAN PHONG"; }

    void nhapThongTinRieng() override {
        cout << "  So ngay lam viec: "; cin >> soNgayLamViec;
        cout << "  Tro cap          : "; cin >> troCap;
    }

    void xemThongTinRieng() const override {
        cout << left
             << setw(22) << "  So ngay lam viec" << ": " << soNgayLamViec << "\n"
             << setw(22) << "  Tro cap"           << ": "
             << fixed << setprecision(0) << troCap << " VND\n";
    }

    double tinhLuong() const override {
        return luongCoBan + soNgayLamViec * 500000.0 + troCap;
    }

public:
    NVVanPhong() : soNgayLamViec(0), troCap(0) {}
};


// ─────────────────────────────────────────────────────────────
//  LỚP CON: NVSanXuat
//  Lương = LCB + SoSanPham * 10.000
// ─────────────────────────────────────────────────────────────
class NVSanXuat : public NhanVien {
private:
    int soSanPham;

protected:
    string tieuDe() const override { return "NHAN VIEN SAN XUAT"; }

    void nhapThongTinRieng() override {
        cout << "  So san pham: "; cin >> soSanPham;
    }

    void xemThongTinRieng() const override {
        cout << left
             << setw(22) << "  So san pham" << ": " << soSanPham << "\n";
    }

    double tinhLuong() const override {
        return luongCoBan + soSanPham * 10000.0;
    }

public:
    NVSanXuat() : soSanPham(0) {}
};


// ─────────────────────────────────────────────────────────────
//  LỚP CON: NVQuanLy
//  Lương = LCB * HeSoChuVu + Thuong
// ─────────────────────────────────────────────────────────────
class NVQuanLy : public NhanVien {
private:
    double heSoChuVu;
    double thuong;

protected:
    string tieuDe() const override { return "NHAN VIEN QUAN LY"; }

    void nhapThongTinRieng() override {
        cout << "  He so chuc vu: "; cin >> heSoChuVu;
        cout << "  Thuong        : "; cin >> thuong;
    }

    void xemThongTinRieng() const override {
        cout << left
             << setw(22) << "  He so chuc vu" << ": " << heSoChuVu << "\n"
             << setw(22) << "  Thuong"         << ": "
             << fixed << setprecision(0) << thuong << " VND\n";
    }

    double tinhLuong() const override {
        return luongCoBan * heSoChuVu + thuong;
    }

public:
    NVQuanLy() : heSoChuVu(1.0), thuong(0) {}
};


// ─────────────────────────────────────────────────────────────
//  LỚP QUẢN LÝ: CongTy
//  Dùng vector<unique_ptr<NhanVien>> – đa hình qua con trỏ base
// ─────────────────────────────────────────────────────────────
class CongTy {
private:
    vector<unique_ptr<NhanVien>> danhSach;

public:
    // Tạo đối tượng đúng loại rồi gọi nhapThongTin() – đa hình
    void themNhanVien() {
        cout << "\nChon loai nhan vien:\n"
             << "  1. Nhan vien Van Phong\n"
             << "  2. Nhan vien San Xuat\n"
             << "  3. Nhan vien Quan Ly\n"
             << "Lua chon: ";
        int loai; cin >> loai;

        unique_ptr<NhanVien> nv;
        switch (loai) {
            case 1: nv = make_unique<NVVanPhong>(); break;
            case 2: nv = make_unique<NVSanXuat>();  break;
            case 3: nv = make_unique<NVQuanLy>();   break;
            default:
                cout << "Lua chon khong hop le!\n"; return;
        }

        nv->nhapThongTin();   // ← GỌI ĐA HÌNH: đúng loại NV nào thì nhập đúng form đó
        danhSach.push_back(move(nv));
        cout << "\n[OK] Da them nhan vien thanh cong!\n";
    }

    // Xem tất cả – gọi xemThongTin() qua con trỏ base → đa hình
    void xemTatCa() const {
        if (danhSach.empty()) { cout << "Danh sach trong!\n"; return; }
        for (size_t i = 0; i < danhSach.size(); i++) {
            cout << "\n[" << i + 1 << "]";
            danhSach[i]->xemThongTin(); // ← ĐA HÌNH
        }
    }

    // Tính tổng lương – gọi tinhLuong() qua con trỏ base → đa hình
    void tinhTongLuong() const {
        if (danhSach.empty()) { cout << "Danh sach trong!\n"; return; }
        double tong = 0;
        cout << "\n" << string(62, '=') << "\n";
        cout << left << setw(30) << "Ho ten"
             << setw(20) << "Loai NV"
             << "Luong (VND)\n";
        cout << string(62, '-') << "\n";
        for (const auto& nv : danhSach) {
            double l = nv->tinhLuong();         // ← ĐA HÌNH
            tong += l;
            cout << left << setw(30) << nv->getHoTen()
                 << setw(20) << ""               // tieuDe() là protected nên dùng xemThongTin() hay getHoTen()
                 << fixed << setprecision(0) << l << "\n";
        }
        cout << string(62, '-') << "\n"
             << "TONG LUONG TOAN CONG TY: "
             << fixed << setprecision(0) << tong << " VND\n"
             << string(62, '=') << "\n";
    }

    // Tìm kiếm – gọi xemThongTin() qua con trỏ base → đa hình
    void timKiemNhanVien() const {
        string ten;
        cout << "Nhap ho ten can tim: ";
        cin.ignore(); getline(cin, ten);

        bool found = false;
        for (const auto& nv : danhSach) {
            if (nv->timKiem(ten)) {
                nv->xemThongTin();   // ← ĐA HÌNH
                found = true;
            }
        }
        if (!found)
            cout << "Khong tim thay \"" << ten << "\" trong danh sach!\n";
    }
};


// ─────────────────────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────────────────────
int main() {
    CongTy ct;
    int choice;

    do {
        cout << "\n╔══════════════════════════════════╗\n"
             << "║    QUAN LY LUONG CONG TY         ║\n"
             << "╠══════════════════════════════════╣\n"
             << "║  1. Them nhan vien               ║\n"
             << "║  2. Xem tat ca nhan vien         ║\n"
             << "║  3. Tinh tong luong cong ty      ║\n"
             << "║  4. Tim kiem nhan vien            ║\n"
             << "║  0. Thoat                        ║\n"
             << "╚══════════════════════════════════╝\n"
             << "Lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1: ct.themNhanVien();    break;
            case 2: ct.xemTatCa();        break;
            case 3: ct.tinhTongLuong();   break;
            case 4: ct.timKiemNhanVien(); break;
            case 0: cout << "\nTam biet!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}
