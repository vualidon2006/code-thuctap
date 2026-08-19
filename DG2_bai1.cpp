#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// --- LỚP CHA: GIAO VIEN ---
class GiaoVien {
protected:
    string maGV, hoTen, ngaySinh, diaChi, trinhDo, chuyenMon;

public:
    // Phương thức ảo để lớp con có thể ghi đè (Override)
    virtual void nhapThongTin() {
        cout << "Nhap Ma GV: "; getline(cin, maGV);
        cout << "Nhap Ho ten: "; getline(cin, hoTen);
        cout << "Nhap Ngay sinh: "; getline(cin, ngaySinh);
        cout << "Nhap Dia chi: "; getline(cin, diaChi);
        cout << "Nhap Trinh do: "; getline(cin, trinhDo);
        cout << "Nhap Chuyen mon: "; getline(cin, chuyenMon);
    }

    virtual void xemThongTin() {
        cout << "\n[Ma GV: " << maGV << " | Ho ten: " << hoTen << "]" << endl;
        cout << "Trinh do: " << trinhDo << " | Chuyen mon: " << chuyenMon << endl;
    }

    // Destructor ảo để giải phóng bộ nhớ an toàn cho lớp con
    virtual ~GiaoVien() {}
};

// --- LỚP CON: GIAO VIEN CO HUU ---
class GVCoHuu : public GiaoVien {
private:
    double luongCoDinh;
    int thang;
    int soTietGiangDay;
    double donGiaGiangDay;
    int soGioNCKH;
    double donGiaNCKH;

public:
    void nhapThongTin() override {
        GiaoVien::nhapThongTin();
        cout << "Luong co dinh: "; cin >> luongCoDinh;
        cout << "Thang: "; cin >> thang;
        cout << "So tiet giang day: "; cin >> soTietGiangDay;
        cout << "Don gia giang day: "; cin >> donGiaGiangDay;
        cout << "So gio NCKH: "; cin >> soGioNCKH;
        cout << "Don gia NCKH: "; cin >> donGiaNCKH;
        cin.ignore(); // Xóa bộ nhớ đệm
    }

    double tinhLuongSanPham() {
        return (soTietGiangDay * donGiaGiangDay) + (soGioNCKH * donGiaNCKH);
    }

    double tinhLuongThang() {
        return luongCoDinh + tinhLuongSanPham();
    }

    void xemThongTin() override {
        GiaoVien::xemThongTin();
        cout << "Loai: Giao vien Co huu" << endl;
        cout << "==> Luong thang: " << fixed << setprecision(0) << tinhLuongThang() << " VND" << endl;
    }
};

// --- LỚP CON: GIAO VIEN THINH GIANG ---
class GVThinhGiang : public GiaoVien {
private:
    string hocKy;
    int namHoc;
    string tenMonGiangDay;
    int soTietMonDay;
    double donGiaMonDay;

public:
    void nhapThongTin() override {
        GiaoVien::nhapThongTin();
        cout << "Hoc ky: "; getline(cin, hocKy);
        cout << "Nam hoc: "; cin >> namHoc; cin.ignore();
        cout << "Ten mon giang day: "; getline(cin, tenMonGiangDay);
        cout << "So tiet mon day: "; cin >> soTietMonDay;
        cout << "Don gia mon day: "; cin >> donGiaMonDay;
        cin.ignore();
    }

    double tinhTienGiangDayMon() {
        return soTietMonDay * donGiaMonDay;
    }

    double tinhThueTNCN() {
        return tinhTienGiangDayMon() * 0.1; // 10%
    }

    double tinhTienThucLinh() {
        return tinhTienGiangDayMon() - tinhThueTNCN();
    }

    void xemThongTin() override {
        GiaoVien::xemThongTin();
        cout << "Loai: Giao vien Thinh giang" << endl;
        cout << "==> Tien thuc linh (sau thue 10%): " << fixed << setprecision(0) << tinhTienThucLinh() << " VND" << endl;
    }
};

// --- CHUONG TRINH CHINH ---
int main() {
    vector<GiaoVien*> dsGiaoVien;
    int luaChon;

    do {
        cout << "\n===============================";
        cout << "\n   HE THONG QUAN LY GIAO VIEN";
        cout << "\n1. Them Giao vien Co huu";
        cout << "\n2. Them Giao vien Thinh giang";
        cout << "\n3. Xem danh sach va Luong";
        cout << "\n0. Thoat";
        cout << "\nLua chon cua ban: ";
        cin >> luaChon;
        cin.ignore();

        if (luaChon == 1) {
            GiaoVien* gv = new GVCoHuu();
            gv->nhapThongTin();
            dsGiaoVien.push_back(gv);
        } 
        else if (luaChon == 2) {
            GiaoVien* gv = new GVThinhGiang();
            gv->nhapThongTin();
            dsGiaoVien.push_back(gv);
        } 
        else if (luaChon == 3) {
            cout << "\n--- DANH SACH CHI TIET ---";
            for (GiaoVien* gv : dsGiaoVien) {
                gv->xemThongTin();
                cout << "-------------------------------";
            }
        }
    } while (luaChon != 0);

    // Giai phong bo nho da cap phat dong
    for (GiaoVien* gv : dsGiaoVien) {
        delete gv;
    }
    dsGiaoVien.clear();

    cout << "\nCam on ban da su dung phan mem!\n";
    return 0;
}