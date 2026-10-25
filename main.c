#include <stdio.h>
#include <string.h>

#define MAX_NV 50

// Khai báo cấu trúc NhanVien
struct NhanVien {
    int maNV;
    char hoTen[50];
    int soPhutDiMuon;
    float luongCoBan;
};

// Khai báo nguyên mẫu hàm (Function Prototypes)
int timTheoMaNV(const struct NhanVien ds[], int n, int maNV);
int themNhanVien(struct NhanVien ds[], int n);
void hienThiDanhSach(const struct NhanVien ds[], int n);
void capNhatPhutDiMuon(struct NhanVien ds[], int n);
void timKiemNhanVien(const struct NhanVien ds[], int n);
void xoaBoDem();

int main() {
    struct NhanVien ds[MAX_NV];
    int n = 0;
    int luaChon;

    do {
        printf("\n===== HE THONG QUAN LY CHAM CONG HRM =====\n");
        printf("1. Them nhan vien moi\n");
        printf("2. Hien thi danh sach va tinh luong\n");
        printf("3. Cap nhat so phut di muon\n");
        printf("4. Tim kiem nhan vien theo ma\n");
        printf("0. Thoat\n");
        printf("==========================================\n");
        printf("Nhap lua chon: ");
        
        if (scanf("%d", &luaChon) != 1) {
            printf("[LOI]: Vui long nhap vao mot so nguyen hop le!\n");
            xoaBoDem();
            continue;
        }

        switch (luaChon) {
            case 1:
                n = themNhanVien(ds, n);
                break;
            case 2:
                hienThiDanhSach(ds, n);
                break;
            case 3:
                capNhatPhutDiMuon(ds, n);
                break;
            case 4:
                timKiemNhanVien(ds, n);
                break;
            case 0:
                printf("\nThoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("\n[LOI]: Lua chon khong hop le! Vui long chon tu 0 den 4.\n");
                break;
        }
    } while (luaChon != 0);

    return 0;
}

// Xóa bộ đệm bàn phím tránh lỗi trôi lệnh khi kết hợp scanf và fgets
void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Hàm tìm nhân viên theo mã, trả về vị trí index hoặc -1 nếu không tìm thấy
int timTheoMaNV(const struct NhanVien ds[], int n, int maNV) {
    for (int i = 0; i < n; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }
    return -1;
}

// Hàm thêm nhân viên, trả về số lượng mới
int themNhanVien(struct NhanVien ds[], int n) {
    if (n >= MAX_NV) {
        printf("\n[LOI]: Danh sach nhan vien da day (Toi da %d nhan vien)!\n", MAX_NV);
        return n;
    }

    struct NhanVien nv;
    
    printf("\n--- THEM NHAN VIEN MOI ---\n");
    
    // Nhập và kiểm tra mã nhân viên không được trùng
    while (1) {
        printf("Nhap ma NV (so nguyen): ");
        if (scanf("%d", &nv.maNV) != 1) {
            printf("[LOI]: Ma NV phai la so nguyen. Nhap lai.\n");
            xoaBoDem();
            continue;
        }

        if (timTheoMaNV(ds, n, nv.maNV) != -1) {
            printf("[LOI]: Ma NV %d da ton tai trong he thong! Nhap lai.\n", nv.maNV);
            continue;
        }
        break;
    }

    xoaBoDem(); // Xóa bộ đệm trước khi dùng fgets

    // Nhập họ và tên
    printf("Nhap ho va ten: ");
    fgets(nv.hoTen, sizeof(nv.hoTen), stdin);
    nv.hoTen[strcspn(nv.hoTen, "\n")] = 0; // Xóa ký tự xuống dòng ở cuối chuỗi

    // Nhập và kiểm tra số phút đi muộn (không được âm)
    do {
        printf("Nhap so phut di muon (>= 0): ");
        if (scanf("%d", &nv.soPhutDiMuon) != 1 || nv.soPhutDiMuon < 0) {
            printf("[LOI]: So phut di muon khong hop le hoac bi am! Nhap lai.\n");
            xoaBoDem();
        } else {
            break;
        }
    } while (1);

    // Nhập và kiểm tra lương cơ bản (không được âm)
    do {
        printf("Nhap luong co ban (>= 0): ");
        if (scanf("%f", &nv.luongCoBan) != 1 || nv.luongCoBan < 0) {
            printf("[LOI]: Luong co ban khong hop le hoac bi am! Nhap lai.\n");
            xoaBoDem();
        } else {
            break;
        }
    } while (1);

    ds[n] = nv;
    printf("\n=> Them nhan vien thanh cong!\n");
    return n + 1;
}

// Hàm hiển thị danh sách nhân viên và tính lương thực nhận
void hienThiDanhSach(const struct NhanVien ds[], int n) {
    if (n == 0) {
        printf("\n[THONG BAO]: Danh sach nhan vien hien dang rong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIÊN ---\n");
    printf("%-7s | %-15s | %-11s | %-16s\n", "Ma NV", "Ho ten", "Phut muon", "Luong thuc nhan");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        float tienPhat = (ds[i].soPhutDiMuon > 15) ? 50000.0f : 0.0f;
        float luongThucNhan = ds[i].luongCoBan - tienPhat;

        printf("%-7d | %-15s | %-11d | %-16.0f\n", 
               ds[i].maNV, 
               ds[i].hoTen, 
               ds[i].soPhutDiMuon, 
               luongThucNhan);
    }
    printf("-----------------------------------------------------------\n");
}

// Hàm cập nhật số phút đi muộn
void capNhatPhutDiMuon(struct NhanVien ds[], int n) {
    if (n == 0) {
        printf("\n[THONG BAO]: Danh sach nhan vien hien dang rong!\n");
        return;
    }

    int maTimKiem;
    printf("\nNhap ma NV can cap nhat: ");
    if (scanf("%d", &maTimKiem) != 1) {
        printf("[LOI]: Ma NV khong hop le!\n");
        xoaBoDem();
        return;
    }

    int index = timTheoMaNV(ds, n, maTimKiem);
    if (index == -1) {
        printf("=> Khong tim thay nhan vien!\n");
        return;
    }

    int phutMoi;
    do {
        printf("Nhap so phut di muon moi (>= 0): ");
        if (scanf("%d", &phutMoi) != 1 || phutMoi < 0) {
            printf("[LOI]: So phut di muon khong hop le! Nhap lai.\n");
            xoaBoDem();
        } else {
            break;
        }
    } while (1);

    ds[index].soPhutDiMuon = phutMoi;
    printf("=> Cap nhat thanh cong!\n");
}

// Hàm tìm kiếm và hiển thị thông tin nhân viên theo mã
void timKiemNhanVien(const struct NhanVien ds[], int n) {
    if (n == 0) {
        printf("\n[THONG BAO]: Danh sach nhan vien hien dang rong!\n");
        return;
    }

    int maTimKiem;
    printf("\nNhap ma NV can tim: ");
    if (scanf("%d", &maTimKiem) != 1) {
        printf("[LOI]: Ma NV khong hop le!\n");
        xoaBoDem();
        return;
    }

    int index = timTheoMaNV(ds, n, maTimKiem);
    if (index == -1) {
        printf("=> Khong tim thay nhan vien co ma %d!\n", maTimKiem);
        return;
    }

    float tienPhat = (ds[index].soPhutDiMuon > 15) ? 50000.0f : 0.0f;
    float luongThucNhan = ds[index].luongCoBan - tienPhat;

    printf("\n--- THONG TIN NHAN VIEN --- \n");
    printf("Mã NV         : %d\n", ds[index].maNV);
    printf("Họ tên        : %s\n", ds[index].hoTen);
    printf("Số phút muộn  : %d\n", ds[index].soPhutDiMuon);
    printf("Lương cơ bản  : %.0f VNĐ\n", ds[index].luongCoBan);
    printf("Lương thực nhận: %.0f VNĐ\n", luongThucNhan);
}